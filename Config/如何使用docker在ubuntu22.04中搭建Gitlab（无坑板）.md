# 如何使用docker在ubuntu22.04中搭建Gitlab（无坑版）
## 安装docker
这里推荐使用官方教程[docker官方安装教程](https://docs.docker.com/engine/install/ubuntu/#set-up-the-repository)安装
- 更新源
```bash
sudo apt-get update
sudo apt-get install ca-certificates curl gnupg
``` 
- 添加**GPG**key
```bash
sudo install -m 0755 -d /etc/apt/keyrings
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg
sudo chmod a+r /etc/apt/keyrings/docker.gpg
```
- 建立仓库
```bash
echo \
  "deb [arch="$(dpkg --print-architecture)" signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu \
  "$(. /etc/os-release && echo "$VERSION_CODENAME")" stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
```

- 更新一下源
```bash
sudo apt-get update
```

- 安装docker
```bash
sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
```

- 测试一下
```bash
sudo docker run hello-world
```

### tips
每次使用docker命令的时候都要求sudo权限，为了避免麻烦，可以在~目录下建立 .bash_aliases 在里面输入
```bash
alias docker='sudo docker'
```
然后输入
```bash
source ~/.bashrc
```

## 使用docker安装Gitlab

### 建立环境变量
为了使镜像与配置分离，首先建立如下的环境变量