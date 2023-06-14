#! https://zhuanlan.zhihu.com/p/636983434
# 如何使用docker在ubuntu22.04中搭建Gitlab（无坑版）
[TOC]
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
```bash
echo 'export GITLAB_HOME=/srv/gitlab' >> ~/.bash_profile
```
然后输入
```bash
source ~/.bash_profile
```
这里的 /srv 可以自己选择

### 下载gitlab镜像
```bash
docker pull gitlab/gitlab-ce:latest
```
这个有两个G，要等一会儿。
这里的ce是稳定版，你也可以下载ee或其他版本

### 安装Gitlab
```bash
sudo docker run --detach \
  --hostname gitlab.example.com \
  --publish 443:443 --publish 80:80 --publish 22:22 \
  --name gitlab \
  --restart always \
  --volume $GITLAB_HOME/config:/etc/gitlab \
  --volume $GITLAB_HOME/logs:/var/log/gitlab \
  --volume $GITLAB_HOME/data:/var/opt/gitlab \
  gitlab/gitlab-ce:latest
```
注意事项：
- --hostname gitlab.example.com 这里的gitlab.example.com是你的域名，如果没有域名，可以使用ip地址，而且一旦生效之后不好修改，如果后续要修改比较麻烦。如果你要发布到公网上，建议这里填写预留的域名
- --publish 443:443 --publish 80:80 --publish 22:22 这里的端口号可以自己选择，但是443和80是必须的，443是https的端口，80是http的端口，22是ssh的端口，如果你要发布到公网上，建议这里填写预留的端口号。同样，这个一旦生效之后不好修改，建议先考虑好再填写例如：'--publish 443:443 --publish 8080:80 --publish 2222:22'
- --name gitlab 这里的gitlab是你的容器名，可以自己选择

### 配置Gitlab
等到gitlab启动之后，输入
```bash
sudo docker exec -it gitlab /bin/bash
```
进入对应的bash（如果前面自定义了容器名称记得修改gitlab为你自己定义的名字）
然后输入
```bash
vi /etc/gitlab/gitlab.rb
```
去修改配置文件

#### 修改http相关配置
```bash
# 配置http协议所使用的访问地址,不加端口号默认为80,有自己的域名在这里修改
external_url 'http://127.0.0.1'
#配置时区
gitlab_rails['time_zone'] = 'Asia/Shanghai'  
# 配置ssh协议所使用的访问地址和端口
gitlab_rails['gitlab_ssh_host'] = 'YOUR_SSH_SERVER_ADDRESS'
gitlab_rails['gitlab_shell_ssh_port'] = 22 # 此端口是run时22端口映射的222端口
```

#### 配置邮箱服务
这里给出一份QQ邮箱的配置，网上其他教程在这里都有坑，最多的是把 'smtp_tls' 服务和 'smtp_auto_starttls' 服务同时设置为 'true'，这样会导致服务启动失败
```bash
# 开始邮箱服务
gitlab_rails['smtp_enable'] = true
# 设置邮箱smtp 服务, 根据自己/公司使用的邮箱协议自由设置即可
gitlab_rails['smtp_address'] = "smtp.qq.com"
# 设置邮箱smtp 服务端口
gitlab_rails['smtp_port'] = 465
# 设置发件人, 建设单独申请邮箱
gitlab_rails['smtp_user_name'] = "YOUR_QQ_EMAIL"
# 设置登录邮箱密码
gitlab_rails['smtp_password'] = "YOUR_QQ_EMAIL_PASSWORD" #注意这里是授权码
gitlab_rails['smtp_domain'] = "smtp.qq.com"

gitlab_rails['smtp_authentication'] = "login"
gitlab_rails['smtp_tls'] = true

# gitlab发送人, 可以根据自己的需求自己定义
gitlab_rails['gitlab_email_from'] = 'YOUR_QQ_EMAIL'
gitlab_rails['gitlab_email_display_name'] = 'gitlab admin'    # 显示的发件人
gitlab_rails['gitlab_email_reply_to'] = 'YOUR_QQ_EMAIL'      # 回复的邮箱
```

#### 更新配置
```bash
gitlab-ctl reconfigure
```
然后等一下就好了

#### 验证邮箱配置是否成功
```bash
gitlab-rails console -e production
```
等他启动之后输入
```bash
Notify.test_email('YOUR_QQ_EMAIL', 'Message Subject', 'Message Body').deliver_now
```
如果他显示成功发送了邮件，那么就成功了
如果没有成功，并且显示sh: 1: /usr/sbin/sendmail: not found
可以考虑在bash中输入
```bash
apt-get update
apt-get install sendmail
```
安装对应服务

#### 配置root账户
启动服务之后不要quit退出，在console里面输入
```bash
user = User.where(id: 1).first
user.password = 'new_password'
user.save!
```
new_password是你的密码，然后就可以quit退出了

### 去验证一下你的gitlab
在浏览器输入你的域名或者ip地址，如果你的配置正确，那么就会出现gitlab的登录界面，输入root账户和密码就可以登录了

### 配置cpolar做内网穿透
看官方教程[cpolar官网教程](https://zhuanlan.zhihu.com/p/617352879)，这里就不多说了