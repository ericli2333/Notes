# 如何在华为matepad11上安装termux+Debian+code-server 并运行机器学习Python程序

## 在华为matepad11上安装termux
先到[termux app github网页](https://github.com/termux/termux-app)下载对应的app，在右边有个release，进去找到对应自己设备的cpu的安装包下载，然后点击安装就可以了，后面问你权限的时候点击是

## 在termux里面安装Debian Linux

### 更新源

进入termux, 照例先更新一下，执行
```bash
pkg update
```
出现对应的可升级的包之后输入
```bash
pkg upgrade XXX
```
升级对应的包（注意这里是pkg，虽然用apt也可以，但是版本有细微区别）

### 访问外部储存

输入
```bash
termux-setup-storage 
```
输入这一行命令以后可以访问外部储存

### 安装Linux发行版

下载 `proot` 和 `proot-distro`
```bash
pkg install proot proot-distro
```
就可以安装对应的程序了

安装结束后，输入
```bash
proot-distro list
```
可以查看所有proot可以安装的Linux发行版列表

选择一个你喜欢的安装（这里选择Debian）

输入
```bash
proot-distro install debian
```
就可以安装了，如果因为网络原因安装慢、安装失败，建议自己学习魔法

### 进入Debian系统

输入
```bash
proot-distro login debian
```
可以进入系统，以后每一次登陆都是这个命令，建议写一个`login.sh`以后每次 `sh login.sh` 就可以进来了

## Debian 系统配置

进入Debian系统之后，照例还是要更新一波

```bash
apt update
apt upgrade 
```

### 安装 neofetch

输入
```bash
apt install neofetch
```

### 安装sudo

输入
```bash
apt install sudo
```
一路回车安装`sudo` 就可以了
接下来创建新用户
```bash
adduser USERNAME
```
用户名自己取，替换掉`USERNAME`，接下来输入两次密码一路回车到底

将新用户添加到sudoers组里面
```bash
nano /etc/sudoers
```
加入 'USERNAME=(ALL:ALL) ALL'即可

**注意，这里建议使用nano，虽然我也一直用的vim，但是这个文件用vim没有权限保存，sudo也没用**

然后输入 `exit` 退出系统

下次再使用你的用户登陆，就在termux里面输入
```bash
proot-distro login debian --user USERNAME
```

## 在 Debian中安装 code-server
使用脚本一键安装
```bash
curl -fsSL https://code-server.dev/install.sh | sh
```
等一小会儿就好啦

然后输入
```bash
code-server
```
就可以**启动了

