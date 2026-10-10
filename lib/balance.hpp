#include <vector>
namespace WAOI_lib{
    template<class T> class fenwick_balance{
        std::vector<T>c;
        int n,lg;      
        T summer=0;  
        void add(int x,T y){
            summer+=y;
            for(int i=x;i<=n;i+=(i&-i))
                c[i]+=y;
        }
        T query(int x){
            T cnt=0;
            for(int i=x;i>=1;i-=(i&-i))
                cnt+=c[i];
            return cnt;
        }
    public:
        void init(int nn){
            n=nn;
            summer=0;
            c.resize(n+1);
            for(int i=1;i<=n;i++)
                c[i]=0;
            lg=0;int tn=1;
            while(tn<n)tn<<=1,lg++;
        }
        void insert(int x,T y=(T)(1)){add(x,y);}
        void remove(int x,T y=(T)(1)){add(x,-y);}
        T rnk(int x){return x==0?0:query(x);}
        T kth(T k){
            int x=0;T sum=0;
            for(int i=lg;~i;i--){
                T y=x+(1<<i);
                if(y<n&&sum+c[y]<k){
                    x=y;
                    sum+=c[y];
                }
            }
            return x+1;
        }
        T get_pre(int x){return rnk(x-1)==0?0:kth(rnk(x-1));}
        T get_nxt(int x){return rnk(x)==summer?n+1:kth(rnk(x)+1);}
    };
    template<class T,class T2> class segment_balance{
        std::vector<T>num;
        T2 L,R;
        void build(int p,T2 l,T2 r){
            num[p]=0;
            if(l==r)return ;
            T2 mid=(l+r)>>1;
            build(p<<1,l,mid);
            build(p<<1|1,mid+1,r);
        }
        void inserts(int p,T2 l,T2 r,T2 x,T y){
            if(l==r){
                num[p]+=y;
                return ;
            }
            T2 mid=(l+r)>>1;
            if(mid>=x)inserts(p<<1,l,mid,x,y);
            else inserts(p<<1|1,mid+1,r,x,y);
            num[p]=num[p<<1]+num[p<<1|1];
        }
        T query(int p,T2 l,T2 r,T2 ql,T2 qr){
            if(ql<=l&&r<=qr)return num[p];
            T2 mid=(l+r)>>1;
            if(mid>=ql&&mid<qr)
                return query(p<<1,l,mid,ql,qr)+query(p<<1|1,mid+1,r,ql,qr);
            if(mid>=ql)
                return query(p<<1,l,mid,ql,qr);
            return query(p<<1|1,mid+1,r,ql,qr);
        }
        T2 kthr(int p,T2 l,T2 r,T x){
            if(l==r)return l;
            T2 mid=(l+r)>>1;
            T k=num[p<<1];
            if(k>=x)return kthr(p<<1,l,mid,x);
            return kthr(p<<1|1,mid+1,r,x-k);
        }
    public:
        void init(T2 ll,T2 rr){
            L=ll,R=rr;
            num.resize(1+(R-L+1)<<2);
            build(1,L,R);
        }
        void insert(T2 x,T y=(T)(1)){inserts(1,L,R,x,y);}
        void remove(T2 x,T y=(T)(1)){inserts(1,L,R,x,-y);}
        T rnk(T2 x){return x<L?0:query(1,L,R,L,x);}
        T2 kth(T x){return kthr(1,L,R,x);}
        T get_pre(T2 x){return rnk(x-1)==0?L-1:kth(rnk(x-1));}
        T get_nxt(T2 x){return rnk(x)==num[1]?R+1:kth(rnk(x)+1);}
    };
    template<class T,class T2> class dysegment_balance{
        std::vector<T>num;
        std::vector<int>ls,rs;
        int tot,rt;
        T2 L,R;
        void inserts(int &p,T2 l,T2 r,T2 x,T y){
            if(l==r){
                num[p]+=y;
                return ;
            }
            T2 mid=(l+r)>>1;
            if(mid>=x)inserts(ls[p],l,mid,x,y);
            else inserts(rs[p],mid+1,r,x,y);
            num[p]=num[ls[p]]+num[rs[p]];
        }
        T query(int p,T2 l,T2 r,T2 ql,T2 qr){
            if(!p)return 0;
            if(ql<=l&&r<=qr)return num[p];
            T2 mid=(l+r)>>1;
            if(mid>=ql&&mid<qr)
                return query(ls[p],l,mid,ql,qr)+query(rs[p],mid+1,r,ql,qr);
            if(mid>=ql)
                return query(ls[p],l,mid,ql,qr);
            return query(rs[p],mid+1,r,ql,qr);
        }
        T2 kthr(int p,T2 l,T2 r,T x){
            if(l==r)return l;
            T2 mid=(l+r)>>1;
            T k=num[ls[p]];
            if(k>=x)return kthr(ls[p],l,mid,x);
            return kthr(rs[p],mid+1,r,x-k);
        }
    public:
        void init(T2 ll,T2 rr){
            L=ll,R=rr;
            tot=0;rt=0;
            num.clear(),ls.clear(),rs.clear();
            num.push_back(0);
            ls.push_back(0);
            rs.push_back(0);
        }
        void insert(T2 x,T y=(T)(1)){inserts(rt,L,R,x,y);}
        void remove(T2 x,T y=(T)(1)){inserts(rt,L,R,x,-y);}
        T rnk(T2 x){return x<L?0:query(rt,L,R,L,x);}
        T2 kth(T x){return kthr(rt,L,R,x);}
        T get_pre(T2 x){return rnk(x-1)==0?L-1:kth(rnk(x-1));}
        T get_nxt(T2 x){return rnk(x)==num[rt]?R+1:kth(rnk(x)+1);}
    }; 
}