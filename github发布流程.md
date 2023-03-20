#! https://zhuanlan.zhihu.com/p/606857354
# github发布流程

## 0.解决上不去或者访问慢

查找github.com的ip

在C:\Windows\System32\Drivers\etc的路径下修改hosts文件

```
# GitHub Start
52.74.223.119     github.com
52.74.223.119   gist.github.com
54.169.195.247   api.github.com
185.199.111.153   assets-cdn.github.com
185.199.108.133    raw.githubusercontent.com
185.199.108.133    gist.githubusercontent.com
199.232.96.133    cloud.githubusercontent.com
199.232.96.133   camo.githubusercontent.com
199.232.96.133   avatars0.githubusercontent.com
199.232.96.133    avatars1.githubusercontent.com
199.232.96.133   avatars2.githubusercontent.com
199.232.96.133    avatars3.githubusercontent.com
199.232.96.133    avatars4.githubusercontent.com
199.232.96.133    avatars5.githubusercontent.com
199.232.96.133    avatars6.githubusercontent.com
199.232.96.133    avatars7.githubusercontent.com
199.232.96.133    avatars8.githubusercontent.com
199.232.96.133  user-images.githubusercontent.com
185.199.109.154   github.githubassets.com
# GitHub End
```

使用终端刷新DNS

```bash
ipconfig /flushdns
```

### 如何解决中文文件名乱码

```bash
git config --global core.quotepath false
```



## 1.在github上创建仓库

## 2.添加远程ssh/HTTPS

```bash
git remote add github ***
```

这里github的名字可以随便改，默认是origin

如果没写后面可以使用

```bash
git rename A B
```

修改名字

## 3.git pull

```bash
git pull github master --allow-unrelated-histories
```

这里的github和上面的名字是一样的

## 4.git push

```bash
git push github master
```

发布本地master分支

## 5.删除远程分支

```bash
git push origin ——delete 分支名
```

## 6.分支重命名

在开发中，我们可能会涉及到对某个分支进行重命命的操作，需要用到的命令有：

### 1、本地分支重命名

本地分支是指：你当前这个分支还没有推送到远程的情况，这种情况修改分支名称就要方便很多

```bash
git branch -m 原始名称 新名称

//例如 修改 test 为 newTest
git branch -m test  newTest
```

### 2、远程分支重命名

远程分支是指：假设你当前已经将该分支推送到远程了，这种情况修改起来要稍微多几步

#### 1.先重命名本地分支

```bash
git branch -m 旧分支名称  新分支名称
```

#### 2.删除远程分支

```bash
git push --delete origin 旧分支名称
```

#### 3.上传新修改名称的本地分支

```bash
git push origin 新分支名称
```

#### 4.修改后的本地分支关联远程分支

```bash
git branch --set-upstream-to origin/新分支名称
```

## 7.如何在发布的时候忽略掉某些不宜发布的文件

1. 在bash中输入

   ```bash
   git config merge.ours.driver true  
   ```

2. 创建**.gitattributes**然后文件中写入需要忽略的文件名 + merge=ours

   如果是文件夹就是文件夹名/** merge=ours

   e.x.

   ```
   folder1/** merge=ours
   ```

3. 在这个分支提交一次

4. 切换回要merge的分支

   
