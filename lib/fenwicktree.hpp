#include <vector>
namespace WAOI_lib{
    template<class T> class fenwick{
        std::vector<T>c;
        int n;
    public:
        void init(int nn){
            n=nn;
            c.resize(n);
            for(int i=0;i<n;i++)
                c[i]=0;
        }
        void add(int x,T y){
            for(int i=x+1;i<=n;i+=(i&-i))
                c[i-1]+=y;
        }
        T pre_query(int x){
            T cnt=0;
            for(int i=x+1;i>=1;i-=(i&-i))
                cnt+=c[i-1];
            return cnt;
        }
        T query(int l,int r){
            return pre_query(r)-(l?pre_query(l-1):0);
        }
    };
    template<class T> class fenwick_interval{
        WAOI_lib::fenwick<T>c,C;
        int n;
    public:
        void init(int nn){
            n=nn;
            c.init(n);
            C.init(n);
        }
        void add(int l,int r,T x){
            c.add(l,x),C.add(l,(T)(l)*x);
            if(r+1<n)c.add(r+1,-x),C.add(r+1,-(T)(r+1)*x);
        }
        T query(int l,int r){
            return (T)(r+1)*c.pre_query(r)-(l?(T)(l)*c.pre_query(l-1):0)
                -C.query(l,r);
        }
    };
}