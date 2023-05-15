#! https://zhuanlan.zhihu.com/p/629627297
# 如何使用WSL+VScode+Texlive+git+SSH搭建LaTeX环境

## 前言：为什么要大费周章在WSL里面使用LaTeX？
一句话，Windows下编译LaTeX太慢了，仅此而已

## 安装WSL

- 在开始菜单搜索“启用或关闭Windows功能”
- 勾选“适用于 Linux 的 Windows 子系统”
- 在Microsoft Store中搜索Ubuntu，安装Ubuntu 22.04 LTS
- 安装完成后，点击启动，等待安装完成
- 设置用户名和密码

## git&SSH

### git配置
- 输入
``` bash
vi ~/.gitconfig
```
- 在文件中黏贴以下内容（这样最快）
``` bash
[user]
        name = YOUR_NAME
        email = YOUR_EMAIL
[alias]
        co = commit
        st = status
        logl = log --graph --all --oneline
[core]
        quotepath = false
        editor = code --wait --new-window
        excludesfile = ~/.gitignore
[filter "lfs"]
        process = git-lfs filter-process
        required = true
        clean = git-lfs clean -- %f
        smudge = git-lfs smudge -- %f
[diff]
        tool = vscode-diff
[difftool]
        prompt = false
[difftool "vscode-diff"]
        cmd = code --wait --diff $LOCAL $REMOTE
[merge]
        tool = vscode-merge
[mergetool "vscode-merge"]
        cmd = code --wait $MERGED

[init]
        defaultBranch = main
[http]
        sslVerify = false
[https]
        sslVerify = false
[branch]
        autosetuprebase = always
```
- 记得修改前两行的YOUR_NAME和YOUR_EMAIL 
- 保存退出
- 输入
``` bash
vi ~/.gitignore
```
- 在文件中黏贴以下内容
``` bash
*.log
*.orig
*.exe
*.aux
*.fdb_latexmk
*.fls
*.out
*.toc
```
- 保存退出

### ssh-key配置
- 输入
``` bash
ssh-keygen -t rsa -C "YOUR_EMAIL"
```
一直回车，不用输入密码
- 在Github/GitLab上添加ssh-key

### 本人的不成熟的Git工作流
- 在Github/GitLab上创建一个仓库
- 远程仓库中只有main一个分支，用作同步
- 本地在WSL中新建一个WSL分支，在Windows下建立一个Windows分支，每次在对应的分支下工作，做完之后使用cherry-pick将提交pick到main上进行同步


## Texlive安装
这里也可以按照官网教程做，不过这个比较简单（虽然版本比较老，不过我是用不出差别）

- 更新一下
  ```bash
  sudo apt update
  ```
  不做这一步下面找不到安装包 texlive-full
- 在Ubuntu中安装Texlive
  ```bash
  sudo apt install texlive-full
  ```
- 安装完成后，输入
  ```bash
  tex --version
  ```
  查看版本，如果出现版本号，说明安装成功

## VScode配置
-  在目标文件夹下输入
    ```bash
    code .
    ```
-  打开VScode 

## 常见问题
- VSCode 使用LaTeX-workshop编译时报错，提示 
  ```bash
   Does the executable exist? $PATH: undefined
   ```

   解决方法：
   - 如果是通过官网安装的，看一下~/.bashrc里面有没有添加到PATH里面，如果没有，手动添加一下：
   - 如果确认已经在PATH中了，输入
    ```bash
    source ~/.bashrc
    ```
    如果还没好，退出重启一下就好（这里非常玄学，有时候自己就好了，有时候得重启几次）
## 附录
本人的部分配置文件(setting.json)关于LaTeX的部分：
```json
    "latex-workshop.latex.autoBuild.run": "never",
    "latex-workshop.showContextMenu": true,
    "latex-workshop.intellisense.package.enabled": true,
    "latex-workshop.message.error.show": false,
    "latex-workshop.message.warning.show": false,
    "latex-workshop.latex.tools": [
        {
            "name": "xelatex",
            "command": "xelatex",
            "args": [
                "-synctex=1",
                "-interaction=nonstopmode",
                "-file-line-error",
                "%DOC%"
            ]
        },
        {
            "name": "pdflatex",
            "command": "pdflatex",
            "args": [
                "-synctex=1",
                "-interaction=nonstopmode",
                "-file-line-error",
                "%DOCFILE%"
            ]
        },
        {
            "name": "latexmk",
            "command": "latexmk",
            "args": [
                "-synctex=1",
                "-interaction=nonstopmode",
                "-file-line-error",
                "-pdf",
                "-outdir=%OUTDIR%",
                "%DOCFILE%"
            ]
        },
        {
            "name": "biber",
            "command": "biber",
            "args": [
                "%DOCFILE%"
            ]
        },
        {
            "name": "bibtex",
            "command": "bibtex",
            "args": [
                "%DOCFILE%"
            ]
        }
    ],
    "latex-workshop.latex.recipes": [
        {
            "name": "xelatex * 2",
            "tools": [
                "xelatex",
                "xelatex"
            ]
        },
        {
            "name": "XeLaTeX",
            "tools": [
                "xelatex"
            ]
        },
        {
            "name": "PDFLaTeX",
            "tools": [
                "pdflatex"
            ]
        },
        {
            "name": "BibTeX",
            "tools": [
                "bibtex"
            ]
        },
        {
            "name": "LaTeXmk",
            "tools": [
                "latexmk"
            ]
        },
        {
            "name": "xe->bibtex->xe*2",
            "tools": [
                "xelatex",
                "bibtex",
                "xelatex",
                "xelatex"
            ]
        },
        {
            "name": "pdf->bibtex->pdf*2",
            "tools": [
                "pdflatex",
                "bibtex",
                "pdflatex",
                "pdflatex"
            ]
        },
        {
            "name": "xe->biber->xe*2",
            "tools": [
                "xelatex",
                "biber",
                "xelatex",
                "xelatex"
            ]
        },
    ],
    "latex-workshop.latex.recipe.default": "lastUsed",
    "latex-workshop.latex.clean.fileTypes": [
        "*.aux",
        "*.bbl",
        "*.blg",
        "*.idx",
        "*.ind",
        "*.lof",
        "*.lot",
        "*.out",
        "*.toc",
        "*.acn",
        "*.acr",
        "*.alg",
        "*.glg",
        "*.glo",
        "*.gls",
        "*.ist",
        "*.fls",
        "*.log",
        "*.fdb_latexmk",
    ],
    "latex-workshop.latex.autoClean.run": "onBuilt",
    "latex-workshop.view.pdf.internal.synctex.keybinding": "double-click",
    "latex-workshop.view.pdf.viewer": "tab",
    "latex.linter.enabled": false,//禁用警告
```

