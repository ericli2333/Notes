#! https://zhuanlan.zhihu.com/p/610756971
# kmp算法

## 前言

kmp算法和最原始的暴力算法最大的区别就是kmp可以不回退指向目标串的指针，通过构建一个next数组，使得每一次匹配失败的时候直接快进在模式串中的指针

kmp算法构建的思想是在每一次匹配失败的时候其实前面的j个字符是确定的，所以我们可以跳过重复的匹配过程

## 复杂度分析

由于在目标串中指针永远不回退，只需要遍历一遍整个目标串，在这个过程从的时间复杂度是$O(n)$，加上预处理next数组的时间$O(m)$，总的时间复杂度为$O(m + n)$

## 算法实现

### 求解next数组部分

#### 代码

```c++
vector<int> buildNext(const string &src) {
    int n = (int) src.length();
    vector<int> next(n, 0);
    cout << endl;
    for (int i = 1; i < n; i++) {
        int j = next[i - 1];
        while (j > 0 && src[i] != src[j]) j = next[j - 1];
        if (src[i] == src[j]) j++;
        next[i] = j;
    }
    return next;
}
```

#### 算法思路

next数组的含义是在第j位上dst串中前缀与后缀匹配的最大数，比如$abcab$中最大匹配的前缀与后缀是$ab$，那么在这个位置上next的值就是2

我们想要求出整个next数组，最简单的方法就是暴力枚举，不过这样时间复杂度是$O(n^{2})$的，可以进行优化

优化的思路就是，我们考虑从$\mathrm{next}[i - 1]$，到$\mathrm{next}[i]$,的一个dp过程，首先$\mathrm{next}[i]$最多只会比$\mathrm{next}[i - 1]$大1，如果在第$i$位上$src[i] == src[j]$，那么$\mathrm{next}[i] = \mathrm{next}[i - 1] + 1$，否则就考虑怎么回退$j$，我们注意到，在这种前后缀匹配的过程中，前后的字符串是一样的，即对于序列ababcdababa，在倒数第二个b的位置上，next的值是4，而最后一位由于是a，不可以匹配上，我们就考虑吧j回退到b的上一个字母a对应的next的位置，即3，这是由于即使最后一个b后面接a匹配不上，短一点的字符串也可能匹配上，对应语句

```c++
while (j > 0 && src[i] != src[j]) j = next[j - 1];
```

详情参见视频

[KMP算法之求next数组代码讲解_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV16X4y137qw/?spm_id_from=333.337.search-card.all.click&vd_source=05a77c081c8cd02275a91188c3c96c26)

建议直接空降14分16秒，秒懂

### kmp匹配部分

```c++
int kmpCompare(const string &dst, const string &target) {
    vector<int> next = buildNext(target);
    int cnt = 0;
    int j = 0;
    for (auto i: dst) {
        if (j == target.length() - 1) {
            cnt++;
            j = 0;
        }
        if (i == target[j]) {
            j++;
            continue;
        }
        j = next[j];
    }
    return cnt;
}
```

这里就直接利用next数组，跳转就可以了