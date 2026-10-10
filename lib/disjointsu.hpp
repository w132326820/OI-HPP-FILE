#include <vector>
#include <utility>
namespace WAOI_lib{
    class dsu{
        std::vector<int>f,sz;
    public:
        void init(int n){
            f.resize(n),sz.resize(n);
            for(int i=0;i<n;i++)f[i]=i,sz[i]=1;
        }
        void clear(){f.clear();sz.clear();}
        int getf(int x){return f[x]==x?x:f[x]=getf(f[x]);}
        void add(int x,int y){
            x=getf(x),y=getf(y);
            if(x!=y){
                if(sz[x]<sz[y])std::swap(x,y);
                f[y]=x,sz[x]+=sz[y];
            }
        }
        bool in(int x,int y){return getf(x)==getf(y);}
        int size(int x){return sz[getf(x)];}
    };
}