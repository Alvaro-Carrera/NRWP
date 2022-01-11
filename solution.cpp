#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
int arr[1001][1001];
int p[1001][1001];
vector<int> v[300],w[300],v2[300];
vector <int*> w2[300];
int level[300];
map <pair<int,int>,int> mp;
map <int,int> mp2;
int depth;
bool visited[300];
void bfs(int x,int t){
    bool flag[v[x].size()];
    memset(flag,false,sizeof(flag));
    for(int i=0;i<v[x].size();i++){
        int node=v[x][i];
        if(level[node]==0&&w[x][i]>0){
            v2[x].push_back(node);
            w2[x].push_back(&w[x][i]);
            level[node]=depth+1;
            flag[i]=true;
        }
    }
    for(int i=0;i<v[x].size();i++){
        int node=v[x][i];
        if(flag[i]){
            depth++;
            bfs(node,t);
            depth--;
        }
    }
}
int dfs(int x,int p,int t,int mn){
    if(x==t)return mn;
    for(int i=0;i<v2[x].size();i++){
        int node=v2[x][i];
        if(mp2[node]||(*w2[x][i])==0||node==p)continue;
        int val=dfs(node,x,t,min(mn,*w2[x][i]));
        if(val==0)mp2[node]=1;
        else {
            *w2[x][i]-=val;
            return val;
        }
    }
    return 0;
}
ll dinic(int s,int t){
    ll total=0;
    for(int i=s;i<=t;i++){
        v2[i].clear();
        w2[i].clear();
    }
    memset(level,0,sizeof(level));
    depth=0;
    bfs(s,t);
    while(level[t]){
        mp2.clear();
        while(int flow=dfs(s,0,t,1e9))total+=flow;
        for(int i=s;i<=t;i++){
            v2[i].clear();
            w2[i].clear();
        }
        memset(level,0,sizeof(level));
        bfs(s,t);
    }
    return total;
}
void dfs2(int x){
    visited[x]=true;
    for(int i=0;i<v[x].size();i++){
        int node=v[x][i];
        if(!visited[node]&&w[x][i])dfs2(node);
    }
}
int main()
{
    freopen("testcases/med1.in","r",stdin);
    freopen("testcases/user.out","w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--){
        int H,W,N;
        cin>>H>>W>>N;
        mp.clear();
        for(int i=1;i<=H;i++){
            for(int j=1;j<=W;j++){
                cin>>arr[i][j];
                p[i][j]=0;
            }
        }
        for(int i=0;i<=N+1;i++){
            v[i].clear();
            w[i].clear();
        }
        for(int i=1;i<=N;i++){
            int a,b,x;
            cin>>a>>b>>x;
            mp[{a,b}]=i;
            p[a][b]=x;
        }
        ll ans=0;
        for(int i=1;i<=H;i++){
            for(int j=1;j<=W;j++){
                if(p[i][j]){
                    if(arr[i][j]>0){
                        v[0].push_back(mp[{i,j}]);
                        v[mp[{i,j}]].push_back(0);
                        w[0].push_back(arr[i][j]*p[i][j]);
                        w[mp[{i,j}]].push_back(arr[i][j]*p[i][j]);
                        ans+=(arr[i][j]*p[i][j]);
                    }
                    else if(arr[i][j]<0){
                        v[N+1].push_back(mp[{i,j}]);
                        v[mp[{i,j}]].push_back(N+1);
                        w[N+1].push_back(abs(arr[i][j]*p[i][j]));
                        w[mp[{i,j}]].push_back(abs(arr[i][j]*p[i][j]));
                        ans+=abs(arr[i][j]*p[i][j]);
                    }
                    if(i-1>0&&p[i-1][j]){
                        v[mp[{i,j}]].push_back(mp[{i-1,j}]);
                        v[mp[{i-1,j}]].push_back(mp[{i,j}]);
                        w[mp[{i,j}]].push_back(p[i][j]*p[i-1][j]);
                        w[mp[{i-1,j}]].push_back(p[i][j]*p[i-1][j]);
                        ans+=(p[i][j]*p[i-1][j]);
                    }
                    if(j-1>0&&p[i][j-1]){
                        v[mp[{i,j}]].push_back(mp[{i,j-1}]);
                        v[mp[{i,j-1}]].push_back(mp[{i,j}]);
                        w[mp[{i,j}]].push_back(p[i][j]*p[i][j-1]);
                        w[mp[{i,j-1}]].push_back(p[i][j]*p[i][j-1]);
                        ans+=(p[i][j]*p[i][j-1]);
                    }
                }
            }
        }
        ans-=(2*dinic(0,N+1));
        cout<<ans<<endl;
        memset(visited,false,sizeof(visited));
        dfs2(0);
        for(int i=1;i<=N;i++){
            if(visited[i])cout<<1<<" ";
            else cout<<-1<<" ";
        }
        cout<<endl;
    }
    return 0;
}