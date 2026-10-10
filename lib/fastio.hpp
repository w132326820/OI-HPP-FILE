#include <cstdio>
namespace WAOI_lib_unlockedio{
    char buf[1<<20],*p1,*p2;
    char getchar(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++;}
    template<class T> void read(T &x){
        x=0;char c=getchar();
        T f=1;
        while(c<48||c>57){
            if(c=='-')f=-1;
            c=getchar();
        }
        while(c>=48&&c<=57){
            x=x*10+(c&15);
            c=getchar();
        }
        x*=f;
    }
    template<class T,class ...Args> void read(T &x,Args &...args){
        read(x),read(args...);
    }
}
namespace WAOI_lib{
    template<class T> void read(T &x){
        x=0;char c=getchar();
        T f=1;
        while(c<48||c>57){
            if(c=='-')f=-1;
            c=getchar();
        }
        while(c>=48&&c<=57){
            x=x*10+(c&15);
            c=getchar();
        }
        x*=f;
    }
    template<class T> void write(T x){
        if(x<0){putchar('-');write(-x);return ;}
        if(x/10)write(x/10);
        putchar(x%10+48);
    }
    template<class T,class ...Args> void read(T &x,Args &...args){
        read(x),read(args...);
    }
}