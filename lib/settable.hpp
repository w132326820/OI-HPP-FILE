#include <vector>
namespace WAOI_lib{
    template<class T,auto op> class s_table{
        std::vector<int>lg;
        std::vector<std::vector<T>>st;
        int n;
    public:
        void init(std::vector<T>A){
            n=A.size();
            lg.resize(n+1);
            lg[0]=lg[1]=0;
            for(int i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
            st.resize(lg[n]+1,std::vector<T>(n,0));
            for(int i=0;i<n;i++)st[0][i]=A[i];
            for(int i=1;i<=lg[n];i++)
                for(int j=0;j+(1<<i)-1<n;j++)
                    st[i][j]=op(st[i-1][j],st[i-1][j+(1<<i-1)]);
        }
        T query(int l,int r){
            int k=lg[r-l+1];
            return op(st[k][l],st[k][r-(1<<k)+1]);
        }
        int qlg(int x){return lg[x];}
    };
}