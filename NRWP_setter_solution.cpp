//
// Created by Carre on 19/3/2020.
//  Not a Real World Problem
////////////////////////

#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
#define dbg(x) cerr << #x"= " << x << endl

const int INF=1E9;
const int GRDSZ=1002; // maximum grid size + 2
const int PARTICLES=200; // maximum particles number + 1
int h[GRDSZ][GRDSZ];  // stores the value's of the cells
int x[PARTICLES]; // stores the columns of the particles
int y[PARTICLES]; // stores the row of the particles
int p[PARTICLES]; // stores the absolute value of the particles
int up[PARTICLES];   // stores the sign given to each particle's value
int H;  // height of the grid
int W; // width of the grid
int N; // number of particles

namespace dinic { // dinic's algorithm to find max flow of a network
    struct edge {int to, rev, f, cap;};

    struct graph {
        int NN,src,dest;
        vi dist, q, work;
        vector<vector<edge> > g;

        graph(int n):NN(n){dist.resize(n);q.resize(n);work.resize(n);g.resize(n);}

        void add_edge(int s, int t, int cap) {
            edge a{t, (int)g[t].size(), 0, cap};
            edge b{s, (int)g[s].size(), 0, cap};
            g[s].emplace_back(a);
            g[t].emplace_back(b);
        }

        bool bfs() {
            dist.assign(NN,-1);
            dist[src] = 0;
            int qsz = 0;
            q[qsz++] = src;
            for (int iq = 0; iq < qsz; ++iq) {
                int u = q[iq];
                for (auto &e : g[u]) {
                    int v = e.to;
                    if (dist[v] < 0 && e.f < e.cap) {
                        dist[v] = dist[u] + 1;
                        q[qsz++] = v;
                    }
                }
            }
            return dist[dest] >= 0;
        }

        int dfs(int u, int f) {
            if (u == dest) return f;
            for (int &i = work[u]; i < (int)g[u].size(); ++i) {
                edge &e = g[u][i];
                if (e.cap <= e.f) continue;
                int v = e.to;
                if (dist[v] == dist[u] + 1) {
                    int df = dfs(v, min(f, e.cap - e.f));
                    if (df > 0) {
                        e.f += df;
                        g[v][e.rev].f -= df;
                        return df;
                    }
                }
            }
            return 0;
        }

        int mf(int s, int t) {
            src = s; dest = t;
            int ret = 0;
            while (bfs()) {
                work.assign(NN,0);
                while (int delta = dfs(s, INF))
                    ret += delta;
            }
            return ret;
        }
    };
};

void dfs_up(int node, const dinic::graph &G){
    up[node]=1;
    for(const auto &e : G.g[node]){
        if (e.cap > e.f && up[e.to]==-1)
            dfs_up(e.to,G);
    }
}

void solve_case(){
    dinic::graph G(N+2); // network flow graph (source=0; dest = N+1)

    int V=0; // stores de value of the V functions as defined in statement
    // we will first sum the contributions of abs(h_i * p_i) and abs(p_i * p_j) and then substract the negative ones

    for(int i=1;i<=N;++i){
        V += abs(h[y[i]][x[i]])*p[i];    // interaction between particle and cell
        if (h[y[i]][x[i]] >= 0) // if the cell has non-negative h, connect particle to source
            G.add_edge(0,i,h[y[i]][x[i]]*p[i]);
        if (h[y[i]][x[i]] <= 0) // if the cell has non-positve h, connect particle to dest
            G.add_edge(i,N+1,-h[y[i]][x[i]]*p[i]);
        for(int j=i+1;j<=N;++j){ // we scan all other particles to find adjacent (N <= 100, so we can doit in N*N time)
            if (abs(y[i]-y[j]) + abs(x[i]-x[j])==1) { // if particles are adjacent, add an edge between them
                G.add_edge(i,j,p[i]*p[j]);
                V += p[i]*p[j]; // interaction between particles
            }
        }
    }
    // find max flow (min cut)
    int mincut = G.mf(0,N+1);

    V -= 2*mincut;  // we remove (twice) the nagative contributions (see editorial)

    // let's  find the sign of each particle
    fill(up,up + N + 1,-1); // initially set all of them to -1 (T component, see editorial);
    dfs_up(0,G); // we do dfs starting from source to find all nodes that belongs to the S component and assign them sign +1;

    // output the results
    cout << V << '\n';
    for(int i=1;i<=N;++i)
        cout << up[i] << " \n"[i==N];
}

void read_case(){
    cin >> H >> W >> N;
    vector<vector<bool>> used(H+1,vector<bool> (W+1,false));
    for (int i = 1; i <= H; ++i) {
        for (int j = 1; j <= W; ++j)
            cin >> h[i][j];
    }
    for (int i = 1; i <= N; ++i) {
        cin >> y[i] >> x[i] >> p[i];
        assert(used[y[i]][x[i]] == false);
        used[y[i]][x[i]] = 1;
    }
}
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);
    freopen("testcases/small1.in","r",stdin);
  //  freopen("testcases/setter.out","w",stdout);
    int t;cin >> t;
    while (t--) {
        read_case();
        solve_case();
    }
}