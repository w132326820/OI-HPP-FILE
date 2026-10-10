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
    dysegment_balance<int,int>t;t.init(1,ss);
    for(int i=1;i<=1;i++){
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