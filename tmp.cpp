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