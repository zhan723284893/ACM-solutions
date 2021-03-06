#include<bits/stdc++.h>
using namespace std;

const int N=(2e5)+50005;
const int C=26;

struct Node{
    int fa, go[C], mx, l;
    bool ok;
};

struct SAM{

    Node no[N<<1];
    int tol, t[N<<1], d[N], len;
    char ans[N];

    int newNode(int mx=-1, int fa=-1, int *go=NULL){
        no[tol].mx=mx;
        no[tol].fa=fa;
        no[tol].l=-1;
        no[tol].ok=true;
        if(go) memcpy(no[tol].go, go, sizeof(int) * C);
        else memset(no[tol].go, -1, sizeof(int) * C);
        return tol++;
    }

    void init(){
        tol=len=0;
        newNode(0);
    }

    int split(int x,int len){
        int y=newNode(len, no[x].fa, no[x].go);
        no[x].fa=y;
        return y;
    }

    int add(int u, char ch){
        int c=ch-'a';
        int z=newNode(no[u].mx+1);
        int v=u;
        while(v!=-1&&no[v].go[c]==-1){
            no[v].go[c]=z;
            v=no[v].fa;
        }
        if(v==-1){
            no[z].fa=0;
            return z;
        }

        int x=no[v].go[c];
        if(no[x].mx==no[v].mx+1){
            no[z].fa=x;
            return z;
        }

        int y=split(x, no[v].mx+1);
        while(v!=-1&&no[v].go[c]==x){
            no[v].go[c]=y;
            v=no[v].fa;
        }
        no[z].fa=y;
        return z;
    }

    void topo(){
        int n=0;
        for(int i = 0; i < tol; i++) n=max(n, no[i].mx);
        for(int i = 0; i <= n; i++) d[i]=0;

        for(int i = 0; i < tol; i++) d[no[i].mx]++;
        for(int i = 1; i <= n; i++) d[i]+=d[i-1];
        for(int i = 0; i < tol; i++) t[--d[no[i].mx]]=i;

    }


    void build(char *s){
        init();
        int cur=0;
        for(int i = 0; s[i]; i++) cur=add(cur, s[i]);
        topo();
    }

    void search(char *s){
        int u, l;
        u=l=0;
        for(int i = 0; s[i]; i++){
            int c=s[i]-'a';
            while(u&&no[u].go[c]==-1){
                u=no[u].fa;
                l=no[u].mx;
            }
            if(no[u].go[c]!=-1){
                u=no[u].go[c];
                l++;
            }else u=l=0;

            no[u].l=max(no[u].l, l);
        }
    }

    void dfs(int u){
        if(no[u].l<no[u].mx) break;
        for(int i = 0; i < C; i++){
            int v=no[u].go[i];
            if(no[v].ok){
                ans[len++]=i+'a';
                dfs(v);
                break;
            }
        }
    }

    void solve(){
        //mark
        for(int i = tol-1; i >= 0; i--){
            int u=t[i];
            if(!u) continue;
            if(no[u].l==-1) continue;
            else no[no[u].fa].l=no[no[u].fa].mx;
            if(no[u].l==no[u].mx) no[u].ok=false;
        }
        for(int i = tol-1; i >= 0; i--){
            int u=t[i];
            for(int j = 0; j < C; j++){
                int v=no[u].go[j];
                if(no[v].ok) no[u].ok=true;
            }
        }
    }


};

int main(){

    return 0;
}
