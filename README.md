# WAOI 模板库

## 前言

编译选项：

`-std=c++17`

### 注意事项

- 有关区间的数据结构（例如线段树，ST 表，树状数组等）实现的时候使用的是**闭区间**而非左闭右开。
- 若无特殊说明，所有涉及到节点编号的模板（例如并查集，后缀数组等），均从 $0$ 开始标号。
- 若无特殊说明，所有涉及模板均在命名空间 `WAOI_lib` 中。

### 重要更新

- Upd on $2026.10.6$：开始写模板库。

## 第一部分 基础模板

### 快速 IO（Fast IO）

**【功能介绍】**

`[namespace] WAIO_lib`：

- `void read(T &x)`：从标准输入读取一个类型为 `T` 的有符号整数；
- `void read(T &x,Args &...args)`：从标准输入读多个类型为 `T` 的有符号整数；
- `void write(T x)`：向标准输出写入一个类型为 `T` 的有符号整数。

`[namespace] WAIO_lib_unlockedio`：

- `char getchar()`：基于 `fread` 并维护一个内部缓冲区的读入函数，用于从标准输入读取一个字符；
- `void read(T &x)` 和 `void read(T &x,Args &...args)`：基于上面 `getchar` 的读入函数功能同上。

**【示例代码】**

[【模板】快速读入](https://www.luogu.com.cn/record/301415444)。

::::success[Code]

```cpp
#include <bits/stdc++.h>
#include "waoi.hpp"
using namespace std;
using namespace WAOI_lib;
int main(){
    int n;read(n);
    int sum=0;
    for(int i=1,x;i<=n;i++)read(x),sum+=x;
    write(sum);
    return 0;
}
```

::::

[【模板】快速读入](https://www.luogu.com.cn/record/301418756)。

::::success[Code]

```cpp
#include <bits/stdc++.h>
#include "waoi.hpp"
using namespace std;
using namespace WAOI_lib_unlockedio;
int main(){
    int n;read(n);
    int sum=0;
    for(int i=1,x;i<=n;i++)read(x),sum+=x;
    WAOI_lib::write(sum);
    return 0;
}
```

::::

### 并查集（Disjoint Set Union）

**【功能介绍】**

- `dsu d`：创建一个并查集 $d$。占用空间为两个 `vector<int>`；
- `void d.init(int n)`：将并查集大小初始化为 $n$。时间复杂度 $\mathcal{O}(n)$；
- `void d.clear()`：将并查集清空。时间复杂度 $\mathcal{O}(n)$；**注意，这个函数并非必须调用，多次初始化时只用调用 `init` 函数**；
- `int d.getf(int x)`：返回 $x$ 所在连通块的根，时间复杂度均摊 $\mathcal{O}(\alpha(n))$，最坏 $\mathcal{O}(\log n)$；
- `void d.add(int x,int y)`：将 $x$ 和 $y$ 连通，时间复杂度同 `getf`；
- `bool d.in(int x,int y)`：判断 $x$ 和 $y$ 是否连通，若连通则返回 `1`；时间复杂度同 `getf`；
- `int d.size(int x)`：返回 $x$ 所在连通块的大小，时间复杂度同 `getf`。

**【示例代码】**

[【模板】并查集](https://www.luogu.com.cn/record/301423589)。

::::success[Code]

```cpp
#include <bits/stdc++.h>
#include "waoi.hpp"
using namespace std;
using namespace WAOI_lib;
int main(){
    int n,m;
    cin>>n>>m;
    dsu f;
    f.init(n);
    while(m--){
        int opt,x,y;
        cin>>opt>>x>>y;x--;y--;
        if(opt==1)f.add(x,y);
        else cout<<(f.in(x,y)?"Y\n":"N\n");
    }
    return 0;
}
```

::::

### ST 表（Sparse Table）

**【功能介绍】**

- `s_table<T,op>s`：创建一个 ST 表 $s$，占用空间为 $\mathcal{O}(\log n)$ 个 `vector<T>`；其中 `T` 为类型，`op` 为一个**满足幂等性**的你要维护的操作，例如 $\gcd,\min,\max$ 等（满足幂等性：$op(x,x)=x$）；
- `void s.init(vector<T>a)`：为 ST 表初始化为 $a$，时间复杂度 $\mathcal{O}(n\log nK)$，其中 $K$ 为一次 $\operatorname{op}$ 的复杂度；
- `T s.qeury(int l,int r)`：查询 $\operatorname{op}_{i=l}^r a_i$，时间复杂度 $\mathcal{O}(K)$；
- `int s.qlg(int x)`：查询 $\lfloor\log x\rfloor$（特别的，`s.qlg(0)=0`），需满足 $0\le x\le n$。

**【示例代码】**

[【模板】ST 表 & RMQ 问题](https://www.luogu.com.cn/record/301437307)。

::::success[Code]

```cpp
#include <bits/stdc++.h>
#include "waoi.hpp"
using namespace std;
using namespace WAOI_lib;
int n,m;
int maxs(int a,int b){return a>b?a:b;}
vector<int>a;
s_table<int,maxs>A;
int main(){
    read(n,m);
    a.resize(n);
    for(int i=0;i<n;i++)read(a[i]);
    A.init(a);
    while(m--){
        int l,r;
        read(l,r);
        write(A.query(l-1,r-1));putchar('\n');
    }
    return 0;
}
```

::::

### 树状数组（Fenwick Tree）

**【功能介绍】**

- `fenwick<T>t`：创建一个树状数组，占用空间一个 `std::vector<int>`；
- `void t.init(int n)`：将树状数组初始化为大小 $n$，时间复杂度 $\mathcal{O}(n)$；
- `void t.add(int x,T y)`：将对于位置 $x$ 执行单点 $y$，时间复杂度 $\mathcal{O}(\log n)$；
- `T pre_query(int x)`：查询 $0\sim x$ 的前缀和，复杂度同上；
- `T query(int l,int r)`：查询区间 $[l,r]$ 的和，复杂度同上。

可以支持区间加的树状数组：

- `fenwick_interval<T>t`：创建一个树状数组，占用空间两个 `std::vector<int>`；
- `void t.init(int n)`：将树状数组初始化为大小 $n$，时间复杂度 $\mathcal{O}(n)$；
- `void t.add(int l,int r,T x)`：将对于位置 $[l,r]$ 执行区间加 $x$，时间复杂度 $\mathcal{O}(\log n)$；
- `T query(int l,int r)`：查询区间 $[l,r]$ 的和，复杂度同上。

**【示例代码】**

[【模板】树状数组 1](https://www.luogu.com.cn/record/301531490)。

::::success[Code]

```cpp
#include <bits/stdc++.h>
#include "waoi.hpp"
using namespace std;
using namespace WAOI_lib;
int n,m;
int main(){
    cin>>n>>m;
    fenwick<int>t;t.init(n);
    for(int i=0,x;i<n;i++)cin>>x,t.add(i,x);
    while(m--){
        int opt,l,r;
        cin>>opt>>l>>r;
        if(opt==1)t.add(l-1,r);
        else cout<<t.query(l-1,r-1)<<"\n";
    }
    return 0;
}
```

::::

[【模板】线段树 1](https://www.luogu.com.cn/record/301533144)。

::::success[Code]

```cpp
#include <bits/stdc++.h>
#include "waoi.hpp"
using namespace std;
using namespace WAOI_lib;
#define int long long
int n,m;
signed main(){
    cin>>n>>m;
    fenwick_interval<int>t;t.init(n);
    for(int i=0,x;i<n;i++)cin>>x,t.add(i,i,x);
    while(m--){
        int opt,x,y,z;
        cin>>opt>>x>>y;
        if(opt==1)cin>>z,t.add(x-1,y-1,z);
        else cout<<t.query(x-1,y-1)<<"\n";
    }
    return 0;
}
```

::::

### 普通平衡树（Common Balance Tree）

**【功能介绍】**

基于树状数组的伪平衡树：

- `fenwick_balance<T>t`：创建一个可以支持平衡树基本操作的树状数组，占用空间一个 `vector<T>`，其中 `T` 为存储 `rnk` 操作结果的类型；特别的，**下标从 $1$ 开始；**
- `void t.init(int n)`：将树状数组的大小初始化为 $n$，时间复杂度 $\mathcal{O}(n)$；
- `void t.insert(int x,T y)`：加入 $y$ 个元素 $x$，时间复杂度同树状数组；特别的，参数 $y$ 可以不填，默认为 $1$；
- `void t.remove(int x,T y)`：移除 $y$ 个元素 $x$，其余同上；**特别的，如果 $y$ 比当前实际的剩余 $x$ 个数大，不保证此操作及以后操作后，该类型的行为；**
- `T t.rnk(int x)`：返回 $\le x$ 的元素个数；
- `int t.kth(T x)`：返回第 $x$ 小的元素；
- `int t.get_pre(int x)` 和 `int t.get_nxt(int x)`：返回 $x$ 的前驱后继，前驱不存在则返回 $0$，后继不存在则返回 $n+1$。

基于线段树的伪平衡树：

- `segment_balance<T,T2>t`：创建一个可以支持平衡树基本操作的线段树，占用空间一个 `vector<T>`（注意四倍空间），其中 `T` 为存储 `rnk` 操作结果的类型，`T2` 为你要维护的数字的类型；
- `void t.init(T2 ll,T2 rr)`：将线段树的下标范围初始化为 $[ll,rr]$，时间复杂度 $\mathcal{O}(rr-ll)$；
- `void t.insert(T2 x,T y)`：加入 $y$ 个元素 $x$，时间复杂度同树状数组；特别的，参数 $y$ 可以不填，默认为 $1$；
- `void t.remove(T2 x,T y)`：移除 $y$ 个元素 $x$，其余同上；**特别的，如果 $y$ 比当前实际的剩余 $x$ 个数大，不保证此操作及以后操作后，该类型的行为；**
- `T t.rnk(T2 x)`：返回 $\le x$ 的元素个数；
- `T2 t.kth(T x)`：返回第 $x$ 小的元素；
- `T2 t.get_pre(T2 x)` 和 `T2 t.get_nxt(T2 x)`：返回 $x$ 的前驱后继，前驱不存在则返回 $ll-1$，后继不存在则返回 $rr+1$。

动态开点线段树（**注意，由于 `std::vector` 自身实现的一些问题，致使作者无法确认此模板正确性，请谨慎使用**）。

- `dysegment_balance<T,T2>`：定义一个此类，空间三个 `std::vector<T>`；
- 其余线段树模板。

无旋 Treap：

- `treap<T>t`：定义一个存储类型为 `T` 的平衡树，占用空间 $5$ 个 `std::vector`；
- `void t.clear()`：清空 $t$，复杂度 $\mathcal{O}(n)$；
- 其余操作同线段树，不过注意当 `get_pre` 和 `get_nxt` 函数的参数为最小或最大值时，**不保证该函数行为**。

**【示例代码】**

[【模板】普通平衡树](https://www.luogu.com.cn/record/301767462)。

::::success[Code]

```cpp
#include <bits/stdc++.h>
#include "waoi.hpp"
using namespace std;
using namespace WAOI_lib;
const int N=500050;
int n,opt[N],xm[N],x[N],ss;
int get(int x){
    return lower_bound(xm+1,xm+1+ss,x)-xm;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>opt[i]>>x[i];
        xm[i]=x[i];
    }
    sort(xm+1,xm+1+n);
    ss=unique(xm+1,xm+1+n)-xm-1;
    fenwick_balance<int>t;t.init(ss);
    for(int i=1;i<=n;i++){
        int k=get(x[i]);
        if(opt[i]==1)t.insert(k,1);
        if(opt[i]==2)t.insert(k,-1);
        if(opt[i]==3)cout<<t.rnk(k-1)+1<<"\n";
        if(opt[i]==4)cout<<xm[t.kth(x[i])]<<"\n";
        if(opt[i]==5){
            cout<<xm[t.get_pre(k)]<<"\n";
        }
        if(opt[i]==6){
            cout<<xm[t.get_nxt(k)]<<"\n";
        }
    }
    return 0;
}
```

::::

[【模板】普通平衡树](https://www.luogu.com.cn/record/301776709)。

::::success[Code]

```cpp
#include <bits/stdc++.h>
#include "waoi.hpp"
using namespace std;
using namespace WAOI_lib;
const int N=500050;
int n,opt[N],xm[N],x[N],ss;
int get(int x){
    return lower_bound(xm+1,xm+1+ss,x)-xm;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>opt[i]>>x[i];
        xm[i]=x[i];
    }
    sort(xm+1,xm+1+n);
    ss=unique(xm+1,xm+1+n)-xm-1;
    segment_balance<int,int>t;t.init(1,ss);
    for(int i=1;i<=n;i++){
        int k=get(x[i]);
        if(opt[i]==1)t.insert(k,1);
        if(opt[i]==2)t.insert(k,-1);
        if(opt[i]==3)cout<<t.rnk(k-1)+1<<"\n";
        if(opt[i]==4)cout<<xm[t.kth(x[i])]<<"\n";
        if(opt[i]==5){
            cout<<xm[t.get_pre(k)]<<"\n";
        }
        if(opt[i]==6){
            cout<<xm[t.get_nxt(k)]<<"\n";
        }
    }
    return 0;
}
```

::::

[【模板】普通平衡树](https://www.luogu.com.cn/record/302434691)。

::::success[Code]

```cpp
#include <bits/stdc++.h>
#include "waoi.hpp"
using namespace std;
using namespace WAOI_lib;
const int N=500050;
int n,opt[N],xm[N],x[N],ss;
int get(int x){
    return lower_bound(xm+1,xm+1+ss,x)-xm;
}
int main(){
    cin>>n;
    treap<int>t;
    while(n--){
        int opt,x;
        cin>>opt>>x;
        if(opt==1)t.insert(x);
        if(opt==2)t.remove(x);
        if(opt==3)cout<<t.rnk(x-1)+1<<"\n";
        if(opt==4)cout<<t.kth(x)<<"\n";
        if(opt==5)cout<<t.get_pre(x)<<"\n";
        if(opt==6)cout<<t.get_nxt(x)<<"\n";
    }
    return 0;
}
```

::::