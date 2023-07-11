#! https://zhuanlan.zhihu.com/p/642851538
# 如何使用Gitlab CI发布软件包

## 前言
本文参考官网，给出一个在powershell下能够发布软件包的例子以及一些坑，供大家参考。

## Step 1. 安装release-cli
``` powershell
New-Item -Path 'C:\GitLab\Release-CLI\bin' -ItemType Directory
Invoke-WebRequest -Uri "https://gitlab.com/api/v4/projects/gitlab-org%2Frelease-cli/packages/generic/release-cli/latest/release-cli-windows-amd64.exe" -OutFile "C:\GitLab\Release-CLI\bin\release-cli.exe"
$env:PATH += ";C:\GitLab\Release-CLI\bin"
```
**坑点1：以上是官方的配置方法，由于某些原因，最后一步添加环境变量的方法在你重新打开一个powershell或者在gitlab-runner的环境中该环境变量不会生效，所以需要手动添加环境变量。具体方法是设置-系统-高级系统设置-环境变量-系统变量-Path-编辑-新建-输入C:\GitLab\Release-CLI\bin-确定-确定-确定。**

## .gitlab-ci.yml的配置
下面这份配置会利用cmake工具在`build_release/`目录下编译一个名为`Test.exe`的可执行文件，并将其上传到gitlab的软件包仓库中，然后创建一个名为$CI_COMMIT_TAG的release，将Test.exe作为release的附件。
``` yml
stages:
  - build
  - upload
  - release

variables:
  PACKAGE_VERSION: "$CI_COMMIT_TAG"
  PACKAGE_REGISTRY_URL: "${CI_API_V4_URL}/projects/${CI_PROJECT_ID}/packages/generic/myawesomerelease/${PACKAGE_VERSION}"

build:
  stage: build
  rules:
    - if: '$CI_COMMIT_TAG'
  script:
    - echo "Running release_build"
    - $releaseDirectory = "./build_release"
    - if (!(Test-Path -Path $releaseDirectory)) {New-Item -ItemType Directory -Path $releaseDirectory}
    - cd $releaseDirectory
    - cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Release -S .. -B .
    - ninja
    - cd ..
  artifacts:
    paths:
      - build_release/
  cache:
    paths:
      - build_release/

upload:
  stage: upload
  image: curlimages/curl:latest
  rules:
    - if: '$CI_COMMIT_TAG'
  script:
    - |
      Invoke-WebRequest -Uri "${PACKAGE_REGISTRY_URL}/Test.exe" -Headers @{ "JOB-TOKEN" = "${CI_JOB_TOKEN}" } -InFile "build_release/Test.exe" -Method PUT

release:
  stage: release
  rules:
    - if: '$CI_COMMIT_TAG'
  script:
    - $env:asset = "{`"name`":`"MyAsset`",`"url`":`"${PACKAGE_REGISTRY_URL}/Test.exe`"}"
    - $env:assetjson = $env:asset | ConvertTo-Json
    - release-cli create --name $CI_COMMIT_TAG --description "Release $CI_COMMIT_TAG" --ref $CI_COMMIT_TAG --tag-name $CI_COMMIT_TAG --assets-link=$env:assetjson
```