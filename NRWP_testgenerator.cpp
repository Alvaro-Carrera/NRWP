// not_a_real world_problem

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned int ui;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
#define FOR(i,n) for (int i=0;i<(n);++i)
#define MP make_pair
#define dbg(x) cerr << #x"= " << x << endl
const int INF=1E9;

const int Seed=837639273;
std::mt19937_64  generator(Seed);

const int MAXGRD=1000;
const int MAXFIELD=1000;
const int MAXmomentum=100;
const int MAXparticles=300;
uniform_int_distribution<int> distr_h(-MAXFIELD, MAXFIELD);
uniform_int_distribution<int> distr_p(0, MAXmomentum);
vii vecinos={{-1,0},{0,1},{1,0},{0,-1}};


struct input{
    int H,W,N;
    vvi h, p;
    input(int _H,int _W,int _N){
        resize(_H,_W,_N);
    }
    void resize(int _H,int _W,int _N){
        H=_H, W=_W,N=_N;
        assert(H>0 && H<=MAXGRD);
        assert(W>0 && W<=MAXGRD);
        assert(N>0 && N<=MAXparticles && N<=H*W);
        h.assign(H,vi(W,1));
        p.assign(N,vi(3));
    }
    void print(ofstream &file){
        file << H << " " << W << " " << N << '\n';
        for(int i=0;i<H;++i){
            file << h[i][0];
            for(int j=1;j<W;++j)
                 file << " " << h[i][j];
            file << '\n';
        }
        shuffle(p.begin(),p.end(),generator);
        for(auto &v:p){
            file << v[0] << " " << v[1] << " " << v[2] << '\n';
        }
    }
};

void oneline(int W,int N,ofstream &file,int norm_field=1){
    assert(W>=1 && W<=MAXGRD);
    assert(N<=W);
    input test(1,W,N);
    for(int i=0;i<W;++i) test.h[0][i] = distr_h(generator)/norm_field;
    vi p(W);
    iota(p.begin(),p.end(),1);
    shuffle(p.begin(),p.end(),generator);
    for(int i=0;i<N;++i) {
        test.p[i][0]=1;
        test.p[i][1]=p[i];
        test.p[i][2]=distr_p(generator);
    }
    test.print(file);
}

void twolines(int W,int N,ofstream &file,int norm_field=1){
    int H=2;
    assert(W>=1 && W<=MAXGRD);
    assert(N<=W*H);
    input test(H,W,N);
    for(int i=0;i<H;++i) {
        for (int j = 0; j < W; ++j) test.h[i][j] = distr_h(generator)/norm_field;
    }
    vii p(W*H);
    int idx=0;
    for(int i=1;i<=H;++i){
        for(int j=1;j<=W;++j){
            p[idx++] = MP(i,j);
        }
    }
    shuffle(p.begin(),p.end(),generator);
    for(int i=0;i<N;++i) {
        test.p[i][0]=p[i].first;
        test.p[i][1]=p[i].second;
        test.p[i][2]=distr_p(generator);
    }
    test.print(file);
}

void twolines_interrupted(int W,int N,ofstream &file,int norm_field=1){
    int H=2;
    assert(W>=1 && W<=MAXGRD);
    assert(N<=W*H);
    input test(H,W,N);
    for(int i=0;i<H;++i) {
        for (int j = 0; j < W; ++j) test.h[i][j] = distr_h(generator)/norm_field;
    }
    vii p(N);
    int cut = N/2;
    if (cut%2!=0) ++cut;
    for(int idx=0,i=0,j=0;idx<N;++idx){
        if (idx==cut) ++j;
        p[idx].first=i+1;
        p[idx].second=j+1;
        if (i) {i=0;++j;}
        else {++i;}
    }

    shuffle(p.begin(),p.end(),generator);
    for(int i=0;i<N;++i) {
        test.p[i][0]=p[i].first;
        test.p[i][1]=p[i].second;
        test.p[i][2]=distr_p(generator);
    }
    test.print(file);
}

void square_small(ofstream &file,int norm_field=1){
    int H=100,W=100,N=15;
    input test(H,W,N);
    for(int i=0;i<H;++i) {
        for (int j = 0; j < W; ++j) test.h[i][j] = distr_h(generator)/norm_field;
    }
    int istart = rand()%80 + 1;
    int jstart = rand()%80 + 1;

    int idx=0;
    FOR(i,4){
        FOR(j,4){
            if (idx==N) break;
            test.p[idx][0]=i+istart;
            test.p[idx][1]=j+jstart;
            test.p[idx++][2]=distr_p(generator);
        }
    }
    test.print(file);
}
void square(ofstream &file,int norm_field=1){
    int H=100,W=100,N=100;
    input test(H,W,N);
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) test.h[i][j] = distr_h(generator) / norm_field;
    }
    int istart = rand()%80 + 1;
    int jstart = rand()%80 + 1;

    int idx=0;
    FOR(i,10){
        FOR(j,10){
            test.p[idx][0]=i+istart;
            test.p[idx][1]=j+jstart;
            test.p[idx++][2]=distr_p(generator);
        }
    }
    test.print(file);
}

void square_huge(ofstream &file,int norm_field=1){
    int H=100,W=110,N=200;
    input test(H,W,N);
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) test.h[i][j] = distr_h(generator) / norm_field;
    }
    int istart = 40 + rand()%10;
    int jstart = 40 + rand()%10;

    int idx=0;
    FOR(i,14){
        FOR(j,14){
            test.p[idx][0]=i+istart;
            test.p[idx][1]=j+jstart;
            test.p[idx++][2]=distr_p(generator);
        }
    }
    test.p[idx][0]=istart-1;
    test.p[idx][1]=jstart+7;
    test.p[idx++][2]=distr_p(generator);
    test.p[idx][0]=istart-1;
    test.p[idx][1]=jstart+8;
    test.p[idx++][2]=distr_p(generator);
    test.p[idx][0]=7;
    test.p[idx][1]=jstart+14;
    test.p[idx++][2]=distr_p(generator);
    test.p[idx][0]=8;
    test.p[idx][1]=jstart+14;
    test.p[idx++][2]=distr_p(generator);

    test.print(file);
}

void square_huge2(ofstream &file,int norm_field=1){
    int H=200,W=210,N=289;
    input test(H,W,N);
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) test.h[i][j] = distr_h(generator) / norm_field;
    }
    int istart = 40 + rand()%10;
    int jstart = 40 + rand()%10;

    int idx=0;
    FOR(i,17){
        FOR(j,17){
            test.p[idx][0]=i+istart;
            test.p[idx][1]=j+jstart;
            test.p[idx++][2]=distr_p(generator);
        }
    }

    test.print(file);
}
void _random(int H,int W,int N,ofstream &file,int norm_field=1){
    input test(H,W,N);
    for(int i=0;i<H;++i) {
        for (int j = 0; j < W; ++j) test.h[i][j] = distr_h(generator)/norm_field;
    }
    uniform_int_distribution<int> distr_row(1,H);
    uniform_int_distribution<int> distr_col(1,W);
    vector<vector<bool>> used(H+1,vector<bool> (W+1,false));
    FOR(i,N){
        int y=0,x;
        while(y==0 || used[y][x]) {
            y = distr_row(generator);
            x = distr_col(generator);
        }
        used[y][x]=1;
        test.p[i][0]=y;
        test.p[i][1]=x;
        test.p[i][2] = distr_p(generator);
    }
    test.print(file);
}


void zerofield(ofstream &file){
    int H=10,W=10,N=100;
    input test(H,W,N);
    for(int i=0;i<H;++i) {
        test.h[i][0] = -MAXFIELD;
        test.h[i][W-1] = MAXFIELD;
        for(int j=1;j<W-1;++j) test.h[i][j]=0;
    }
    int idx=0;
    for(int i=1;i<=H;++i){
        for(int j=1;j<=W;++j) {
            test.p[idx][0] = i;
            test.p[idx][1] = j;
            test.p[idx++][2] = distr_p(generator);
        }
    }
    test.print(file);
}

void periodic(ofstream &file){
    int H=35,W=3,N=100;
    input test(H,W,N);
    vi per(5);
    per[0]=-MAXFIELD;
    for(int i=1;i<5;++i) per[i] = -MAXFIELD + i*MAXFIELD/2;
    for(int i=0;i<H;++i) {
        for(int j=0;j<W;++j) test.h[i][j]=per[i%5];
    }
    int idx=0;
    for(int i=1;i<=H;++i){
        if (i==3) continue;
        if (i==31){
            test.p[idx][0]=i;test.p[idx][1]=2;test.p[idx++][2]=distr_p(generator);
            continue;
        }
        for(int j=1;j<=W;++j) {
            test.p[idx][0] = i;
            test.p[idx][1] = j;
            test.p[idx++][2] = distr_p(generator);
        }
    }
    test.print(file);
}

void crux(ofstream &file,int norm_field=1){
    int H=200,W=200,N=100;
    input test(H,W,N);
    for(int i=0;i<H;++i) {
        for (int j = 0; j < W; ++j) test.h[i][j] = distr_h(generator) / norm_field;
    }
    int idx=0;
    for(int i=40;i<=41;++i){
        for(int j=50;j<=76;++j){
            test.p[idx][0]=i;
            test.p[idx][1] = j;
            test.p[idx++][2]=distr_p(generator);
        }
    }
    for(int i = 42;i<=52;++i){
        for(int j=53;j<=54;++j){
            test.p[idx][0]=i;
            test.p[idx][1]=j;
            test.p[idx++][2]=distr_p(generator);
        }
    }
    for(int i = 39;idx<N;--i){
        for(int j=70;j<=71;++j){
            test.p[idx][0]=i;
            test.p[idx][1]=j;
            test.p[idx][2]=distr_p(generator);
            if (++idx==N) break;
        }
    }
    test.print(file);
}

void crux_huge(ofstream &file,int norm_field=1){
    int H=150,W=140,N=200;
    input test(H,W,N);
    for(int i=0;i<H;++i) {
        for (int j = 0; j < W; ++j) test.h[i][j] = distr_h(generator)/ norm_field;
    }
    int idx=0;
    for(int i=5;i<20;++i){
        for(int j=5;j<8;++j){
            test.p[idx][0]=i;
            test.p[idx][1]=j;
            test.p[idx++][2]=distr_p(generator);
        }
    }
    for(int i=20;i<23;++i){
        for(int j=4;j<30;++j){
            test.p[idx][0]=i;
            test.p[idx][1]=j;
            test.p[idx++][2]=distr_p(generator);
        }
    }
    for(int i=23;i<100;++i){
        if (idx==N) break;
        for(int j=26;j<29;++j){
            test.p[idx][0]=i;
            test.p[idx][1]=j;
            test.p[idx++][2]=distr_p(generator);
            if (idx==N) break;
        }
    }
    assert(idx==N);
    test.print(file);
}


void stairs(ofstream &file,int norm_field=1){
    int H=500,W=500,N=100;
    input test(H,W,N);
    for(int i=0;i<H;++i) {
        for (int j = 0; j < W; ++j) test.h[i][j] = distr_h(generator)/norm_field;
    }
    int idx=0;
    test.p[idx][0]=1;
    test.p[idx][1] = 1;
    test.p[idx++][2]=distr_p(generator);
    test.p[idx][0]=1;
    test.p[idx][1] = 2;
    test.p[idx++][2]=distr_p(generator);
    test.p[idx][0]=1;
    test.p[idx][1] = W;
    test.p[idx++][2]=distr_p(generator);
    test.p[idx][0]=2;
    test.p[idx][1] = W;
    test.p[idx++][2]=distr_p(generator);
    test.p[idx][0]=H;
    test.p[idx][1] = 1;
    test.p[idx++][2]=distr_p(generator);
    test.p[idx][0]=H;
    test.p[idx][1] = 2;
    test.p[idx++][2]=distr_p(generator);
    test.p[idx][0]=H;
    test.p[idx][1] = W;
    test.p[idx++][2]=distr_p(generator);
    test.p[idx][0]=H-1;
    test.p[idx][1] = W;
    test.p[idx++][2]=distr_p(generator);
    
    int i=200,di=1;
    for(int j=200;idx<N;++j){
        for(int dd=0;dd<di;++dd){
            test.p[idx][0]=i+dd;
            test.p[idx][1] = j;
            test.p[idx][2]=distr_p(generator);
            if (++idx==N) break;
            if (dd==0) continue;
            test.p[idx][0]=i-dd;
            test.p[idx][1] = j;
            test.p[idx][2]=distr_p(generator);
            if (++idx==N) break;
        }
        ++di;
    }
    test.print(file);
};


void stairs_huge(ofstream &file,int norm_field=1){
    int H=140,W=140,N=200;
    input test(H,W,N);
    for(int i=0;i<H;++i) {
        for (int j = 0; j < W; ++j) test.h[i][j] = distr_h(generator)/norm_field;
    }
    int idx=0;
    int i=20,di=1;
    for(int j=20;idx<N;++j){
        for(int dd=0;dd<di;++dd){
            test.p[idx][0]=i+dd;
            test.p[idx][1] = j;
            test.p[idx][2]=distr_p(generator);
            if (++idx==N) break;
            if (dd==0) continue;
            test.p[idx][0]=i-dd;
            test.p[idx][1] = j;
            test.p[idx][2]=distr_p(generator);
            if (++idx==N) break;
        }
        ++di;
    }
    assert(idx==N);
    test.print(file);
};

void by_dfs(int H,int W,int N,int groups,ofstream &file,int norm_field){
    assert(H>0 && H<=MAXGRD);
    assert(W>0 && W<=MAXGRD);
    assert(N>0 && N<=MAXparticles);
    assert(N<=2*H*W);
    assert(groups>0 && groups<N);
    assert(N%groups==0);
    input test(H,W,N);
    for(int i=0;i<H;++i) {
        for (int j = 0; j < W; ++j) test.h[i][j] = distr_h(generator)/norm_field;
    }
    uniform_int_distribution<int> distr_row(1,H);
    uniform_int_distribution<int> distr_col(1,W);
    vvi used(H+1,vi (W+1,0));

    function<bool(int,int,int)> dfs = [&](int r,int c,int faltan){
        used[r][c]=-1;
        if (--faltan==0){
            used[r][c]=1;
            return true;
        }
        auto vec=vecinos;
        shuffle(vec.begin(),vec.end(),generator);
        for(int i=0;i<4;++i){
            int rr=r+vec[i].first;
            int cc=c+vec[i].second;
            if (rr>0 && rr<=H && cc>0 && cc<=W && used[rr][cc]==0){
                if (dfs(rr,cc,faltan)){
                    used[r][c]=1;
                    return true;
                }
            }
        }
        used[r][c]=0;
        return false;
    };
    int ppg=N/groups;
    while(groups--){
        while(1) {
            int r = distr_row(generator);
            int c = distr_col(generator);
            while (used[r][c] != 0) {
                r = distr_row(generator);
                c = distr_col(generator);
            }
            if (dfs(r,c,ppg)) break;
        }
    }
    int idx=0;
    for(int i=1;i<=H;++i){
        for(int j=1;j<=W;++j){
            if (used[i][j]==1) {
                test.p[idx][0] = i;
                test.p[idx][1] = j;
                test.p[idx++][2] = distr_p(generator);
            }
        }
    }
    assert(idx==N);
    test.print(file);
}


void limits(int H,int W,int N,ofstream &file) {
    assert(H > 0 && H <= MAXGRD);
    assert(W > 0 && W <= MAXGRD);
    assert(N > 0 && N <= MAXparticles);
    assert(N <= H * W);
    input test(H, W, N);
    for(int i=0;i<H;++i) {
        for (int j = 0; j < W; ++j) test.h[i][j] = 1;
    }
    int idx=0;
    for(int j=1;j<5;++j){
        test.h[0][j-1] = MAXFIELD;
        test.p[idx][0]=1;
        test.p[idx][1]=j;
        test.p[idx++][2]=MAXmomentum;
    }
    for(int i=2;i<5;++i){
        test.h[i-1][0] = -MAXFIELD;
        test.p[idx][0]=i;
        test.p[idx][1]=1;
        test.p[idx++][2]=MAXmomentum;
    }
    for(int j=1;j<=4;++j){
        test.h[H-1][W-j] = MAXFIELD;
        test.p[idx][0]=H;
        test.p[idx][1]=W-j+1;
        test.p[idx++][2]=MAXmomentum;
    }
    for(int i=1;i<5;++i){
        test.h[H-i-1][W-1] = -MAXFIELD;
        test.p[idx][0]=H-i;
        test.p[idx][1]=W;
        test.p[idx++][2]=MAXmomentum;
    }
    assert(idx==N);
    test.print(file);
}

int main(){
    srand(Seed);
    ios_base::sync_with_stdio(false); cin.tie(0);
    {
        for(int i=5;i<=5;++i) {
            string filename = "testcases/large" + to_string(i) + ".in";
            ofstream file;
            file.open(filename,ios::binary);
            int T = 10;
            file << T << '\n';
            square_huge2(file,100);
            square_huge2(file,4);
            square_huge2(file,10);
            square_huge2(file,2);
            square_huge2(file,50);
            square_huge2(file,3);
            square_huge2(file,60);
            square_huge2(file,500);
            square_huge2(file,20);
            square_huge2(file,90);
            file.flush();
            file.close();
        }
    }
    {
        string filename = "testcases/small1.in";
        ofstream file;
        file.open(filename,ios::binary);
        int T = 3;
        file << T << '\n';
        file << "2 2 3\n1 4\n-1 -2\n1 1 3\n1 2 1\n2 2 2\n"; // example
        file << "2 1 2" << '\n';
        file << "1000\n1000\n1 1 0\n2 1 0\n";
        file << "1 3 2" << '\n';
        file << "0 1000 0\n1 1 10\n1 3 11\n";
        file.flush();
        file.close();
    }
    for(int i=2;i<=2;++i) {
        string filename = "testcases/small" + to_string(i) + ".in";
        ofstream file;
        file.open(filename,ios::binary);
        int T = 10;
        file << T << '\n';
        square_small(file);
        square_small(file,10);
        square_small(file,100);
        oneline(2, 1, file,100);
        oneline(15, 15, file);
        oneline(18, 15, file,10);
        twolines_interrupted(10, 14, file,10);
        twolines_interrupted(12, 13, file,100);
        _random(25, 24, 15, file,10);
        _random(400, 1000, 15, file);
        file.flush();
        file.close();
    }
    {
        string filename = "testcases/small3.in";
        ofstream file;
        file.open(filename,ios::binary);
        int T = 1;
        file << T << '\n';
        limits(1000,1000,15,file);
        file.flush();
        file.close();
    }

    for(int i=1;i<=2;++i) {
        string filename = "testcases/med" + to_string(i) + ".in";
        ofstream file;
        file.open(filename,ios::binary);
        int T = 10;
        file << T << '\n';
        oneline(i*100,i*100,file,10);
        oneline(i*100,i*100-3,file,10);
        oneline(1000,i*93,file);
        twolines(i,2,file,10);
        twolines(1000,i*100,file);
        twolines(i*100,i*100,file,10);
        twolines(i*50,i*100,file,100);
        twolines(i*100,i*100-1,file);
        twolines_interrupted(1000,i*100,file,10);
        twolines_interrupted(i*50+10,i*100-3,file,100);
        file.flush();
        file.close();
    }
    {
        string filename = "testcases/med3.in";
        ofstream file;
        file.open(filename,ios::binary);
        int T = 5;
        file << T << '\n';
        input test(2, 1000, 200);

        // 1
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 1000; ++j) test.h[i][j] = -distr_p(generator)/5-1;
        }
        test.h[0][952] = MAXFIELD;
        test.h[1][951] = MAXFIELD;
        int idx=0;
        for(int j=901;j<=1000;++j) {
            for(int i=1;i<=2;++i){
                test.p[idx][0] = i;
                test.p[idx][1] = j;
                test.p[idx++][2] = (MAXmomentum-i+1)/ (j%3 + 1);
            }
        }
        test.print(file);

        /// 2
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 1000; ++j) test.h[i][j] = (MAXFIELD/5) * ((i+j)%2==0 ? 1:-1);
        }
        idx=0;
        for(int i=1;i<=2;++i){
            for(int j=1;j<=100;++j) {
                test.p[idx][0] = i;
                test.p[idx][1] = j;
                test.p[idx++][2] = MAXmomentum - rand() % 3;
            }
        }
        test.print(file);

        /// 3
        for (int j = 0; j < 1000; ++j) test.h[0][j] = -MAXmomentum/2;
        for (int j = 0; j < 1000; ++j) test.h[1][j] = MAXmomentum/2;
        idx=0;
        for(int g=0,j=1;g<10;++g){
            for(int gg=0;gg<20;++gg){
                test.p[idx][0] = g%2 + 1;
                test.p[idx][1] = j++;
                test.p[idx++][2] = MAXmomentum - rand() % 3;
            }
            --j;
        }
        test.print(file);

        // 4
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 1000; ++j) test.h[i][j] = MAXmomentum/2 * ((i+j)%2==0 ? 1:-1);
        }
        idx=0;
        for(int g=0,j=1;g<10;++g){
            for(int gg=0;gg<20;++gg){
                test.p[idx][0] = g%2+1;
                test.p[idx][1] = j++;
                test.p[idx++][2] = MAXmomentum - rand() % 3;
            }
            --j;
        }
        test.print(file);

        // 5
        for(int j=500;j<600;++j) test.h[1][j]=-2;
        for(int j=600;j<705;++j) test.h[1][j]=2;
        idx=0;
        for(int j=500;idx<200;++idx, ++j) {
            test.p[idx][0] = 2;
            test.p[idx][1] = j;
            test.p[idx][2] = MAXmomentum - rand() % 3;
        }
        test.print(file);
        file.flush();
        file.close();
    }


    for(int i=1;i<=1;++i) {
        string filename = "testcases/large" + to_string(i) + ".in";
        ofstream file;
        file.open(filename,ios::binary);
        int T = 10;
        file << T << '\n';
        square(file);
        square(file,5);
        square(file,10);
        periodic(file);
        zerofield(file);
        crux(file,10);
        _random(100,100,100,file);
        _random(50,40,100,file,50);
        crux(file,10);
        stairs(file,2);
        file.flush();
        file.close();
    }

    for(int i=2;i<=2;++i) {
        string filename = "testcases/large" + to_string(i) + ".in";
        ofstream file;
        file.open(filename,ios::binary);
        int T = 10;
        file << T << '\n';
        square_huge(file,100);
        square_huge(file,4);
        crux_huge(file,4);
        _random(50,10,199,file);
        stairs_huge(file,4);
        by_dfs(200,200,200,1,file,5);
        by_dfs(250,250,200,2,file,5);
        by_dfs(300,300,200,5,file,5);
        by_dfs(300,300,200,10,file,5);
        by_dfs(320,320,200,20,file,5);
        file.flush();
        file.close();
    }

    {
        string filename = "testcases/large3.in";
        ofstream file;
        file.open(filename,ios::binary);
        int T = 7;
        file << T << '\n';
        int H=100,W=100,N=176;
        input test(H,W,N);

        // 1
        for (int i = 5; i+5 < H; ++i) {
            for (int j = 5; j+5 < W; ++j) test.h[i][j] = rand()%3 * (rand()?1:-1);
        }
        for(int i=0;i<5;++i){
            for(int j=0;j<5;++j) {
                test.h[i][j] = rand() % 10 + 95;
                test.h[i+20][j+20] = rand() % 3;
                test.h[i][20+j] = -495 + rand()%10;
                test.h[20+i][j] = -495 + rand()%10;
            }
        }
        int idx=0;
        for(int i=1;i<=5;++i){
            for(int j=1;j<=5;++j) {
                test.p[idx][0]=i;
                test.p[idx][1]=j;
                test.p[idx++][2]=MAXmomentum - rand()%10;
                test.p[idx][0]=i;
                test.p[idx][1]=j+20;
                test.p[idx++][2]=MAXmomentum - rand()%10;
                test.p[idx][0]=i+20;
                test.p[idx][1]=j;
                test.p[idx++][2]=MAXmomentum - rand()%10;
                test.p[idx][0]=i+20;
                test.p[idx][1]=j+20;
                test.p[idx++][2]=MAXmomentum - rand()%10;
            }
        }
        for(int j=6;j<=11;++j){
            test.p[idx][0]=1;
            test.p[idx][1]=j;
            test.p[idx++][2]=MAXmomentum - rand()%10;
            test.p[idx][0]=22;
            test.p[idx][1]=j;
            test.p[idx++][2]=MAXmomentum - rand()%10;
        }
        for(int j=10;j<=15;++j){
            test.p[idx][0]=2;
            test.p[idx][1]=j;
            test.p[idx++][2]=MAXmomentum - rand()%10;
            test.p[idx][0]=23;
            test.p[idx][1]=j;
            test.p[idx++][2]=MAXmomentum - rand()%10;
        }
        for(int j=14;j<=20;++j){
            test.p[idx][0]=1;
            test.p[idx][1]=j;
            test.p[idx++][2]=MAXmomentum - rand()%10;
            test.p[idx][0]=24;
            test.p[idx][1]=j;
            test.p[idx++][2]=MAXmomentum - rand()%10;
        }
        for(int i=6;i<=11;++i){
            test.p[idx][0]=i;
            test.p[idx][1]=5;
            test.p[idx++][2]=MAXmomentum - rand()%10;
            test.p[idx][0]=i;
            test.p[idx][1]=23;
            test.p[idx++][2]=MAXmomentum - rand()%10;
        }
        for(int i=10;i<=15;++i){
            test.p[idx][0]=i;
            test.p[idx][1]=6;
            test.p[idx++][2]=MAXmomentum - rand()%10;
            test.p[idx][0]=i;
            test.p[idx][1]=22;
            test.p[idx++][2]=MAXmomentum - rand()%10;
        }
        for(int i=14;i<=20;++i){
            test.p[idx][0]=i;
            test.p[idx][1]=5;
            test.p[idx++][2]=MAXmomentum - rand()%10;
            test.p[idx][0]=i;
            test.p[idx][1]=21;
            test.p[idx++][2]=MAXmomentum - rand()%10;
        }

        assert(idx==N);
        test.print(file);

        // 2
        N=200;
        test.resize(H,W,N);
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) test.h[i][j] = -MAXFIELD;
        }
        idx=0;
        for(int i=53;i<53+14;++i){
            for(int j=5;j<5+14;++j){
                test.p[idx][0]=i;
                test.p[idx][1]=j;
                test.p[idx++][2] = MAXmomentum;
            }
        }
        for(int j=6;j<10;++j) {
            test.p[idx][0]=53+14;
            test.p[idx][1]=j;
            test.p[idx++][2]=MAXmomentum;
        }
        assert(idx==N);
        test.print(file);


        // 3: connected groups
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) test.h[i][j] = distr_p(generator) * ((i/5 + j/5)%2==0? 1 : -1);
        }
        idx=0;
        vvi nodes = {{49,49},{49,50},{50,49},{50,50}};
        test.p[idx][0]=49;
        test.p[idx][1]=49;
        test.p[idx++][2]=MAXmomentum - rand()%10;
        test.p[idx][0]=49;
        test.p[idx][1]=50;
        test.p[idx++][2]=MAXmomentum - rand()%10;
        test.p[idx][0]=50;
        test.p[idx][1]=49;
        test.p[idx++][2]=MAXmomentum - rand()%10;
        test.p[idx][0]=50;
        test.p[idx][1]=50;
        test.p[idx++][2]=MAXmomentum - rand()%10;
        int inode=0;
        int acum=0;
        while(idx<N) {
            if (++acum < 6 || rand() % 2) {
                if (inode == 0) nodes[0][rand() % 2]--;
                else if (inode == 1) {
                    if (rand() % 2)nodes[1][0]--;
                    else nodes[1][1]++;
                } else if (inode == 2) {
                    if (rand() % 2)nodes[2][0]++;
                    else nodes[2][1]--;
                } else nodes[3][rand() % 2]++;
                test.p[idx][0]=nodes[inode][0];
                test.p[idx][1]=nodes[inode][1];
                test.p[idx++][2]=distr_p(generator);
            }else{
                acum=0;
                if (inode == 0){
                    test.p[idx][0]=nodes[inode][0]-1;
                    test.p[idx][1]=nodes[inode][1];
                    test.p[idx][2]=distr_p(generator);
                    if (++idx==N) break;
                    test.p[idx][0]=nodes[inode][0];
                    test.p[idx][1]=--nodes[inode][1];
                    test.p[idx][2]=distr_p(generator);
                    if (++idx==N) break;
                    test.p[idx][0]=--nodes[inode][0];
                    test.p[idx][1]=nodes[inode][1];
                    test.p[idx][2]=distr_p(generator);
                    if (++idx==N) break;
                }
                else if (inode == 1) {
                    test.p[idx][0]=nodes[inode][0]-1;
                    test.p[idx][1]=nodes[inode][1];
                    test.p[idx][2]=distr_p(generator);
                    if (++idx==N) break;
                    test.p[idx][0]=nodes[inode][0];
                    test.p[idx][1]=++nodes[inode][1];
                    test.p[idx][2]=distr_p(generator);
                    if (++idx==N) break;
                    test.p[idx][0]=--nodes[inode][0];
                    test.p[idx][1]=nodes[inode][1];
                    test.p[idx][2]=distr_p(generator);
                    if (++idx==N) break;
                } else if (inode == 2) {
                    test.p[idx][0]=nodes[inode][0]+1;
                    test.p[idx][1]=nodes[inode][1];
                    test.p[idx][2]=distr_p(generator);
                    if (++idx==N) break;
                    test.p[idx][0]=nodes[inode][0];
                    test.p[idx][1]=--nodes[inode][1];
                    test.p[idx][2]=distr_p(generator);
                    if (++idx==N) break;
                    test.p[idx][0]=++nodes[inode][0];
                    test.p[idx][1]=nodes[inode][1];
                    test.p[idx][2]=distr_p(generator);
                    if (++idx==N) break;
                } else{
                    test.p[idx][0]=nodes[inode][0]+1;
                    test.p[idx][1]=nodes[inode][1];
                    test.p[idx][2]=distr_p(generator);
                    if (++idx==N) break;
                    test.p[idx][0]=nodes[inode][0];
                    test.p[idx][1]=++nodes[inode][1];
                    test.p[idx][2]=distr_p(generator);
                    if (++idx==N) break;
                    test.p[idx][0]=++nodes[inode][0];
                    test.p[idx][1]=nodes[inode][1];
                    test.p[idx][2]=distr_p(generator);
                    if (++idx==N) break;
                }
            }
            if (++inode==4) inode=0;
        }
        assert(idx==N);
        test.print(file);

        // 4
        N=197;
        H=W=200;
        test.resize(H,W,N);
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) test.h[i][j] = distr_p(generator);
        }
        int istart=7,jstart=18;
        idx=0;
        for(int i=0;i<14;++i){
            for(int j=0;j<14;++j){
                test.h[i+istart][j+jstart] = rand()%10+1;
                test.h[i+istart+15][j+jstart] = rand()%10+1;
                test.p[idx][0] = i+istart+1;
                test.p[idx][1] = j+jstart+1;
                if (j==7 && (i==13 || i==15)){
                    test.p[idx++][2] = MAXmomentum;
                }else
                    test.p[idx++][2] = distr_p(generator)/4 + 1;
            }
        }
        test.h[istart+14][jstart+7] = -500;
        test.p[idx][0] = istart+15;
        test.p[idx][1] = jstart+8;
        test.p[idx++][2] = MAXmomentum;
        assert(idx==N);
        test.print(file);

        // 5
        N=189;
        test.resize(H,W,N);
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) test.h[i][j] = distr_p(generator);
        }
        istart=31;
        jstart=52;
        idx=0;
        for(int i=0;i<17;i+=2){
            for(int j=0;j<14;++j) {
                test.p[idx][0] = i + istart;
                test.p[idx][1] = j + jstart;
                test.p[idx++][2] = distr_p(generator);
                test.h[istart + i-1][jstart + j-1] = (j%2==0? abs(distr_h(generator))/5 + 1: 0);
            }
        }
        for(int j=jstart+1;j<jstart+14;j+=2){
            for(int i=istart-1;i<=istart+15;i+=2){
                test.p[idx][0] = i;
                test.p[idx][1] = j;
                test.p[idx++][2] = distr_p(generator);
                test.h[i-1][j-1] = -abs(distr_h(generator))/5 - 1;
            }
        }

        assert(idx==N);
        test.print(file);


        // 6

        {
            N = 200;
            test.resize(H, W, N);
            for (int i = 0; i < H; ++i) {
                for (int j = 0; j < W; ++j) test.h[i][j] = 0;
            }
            vector<vector<bool>> visited(H,vector<bool> (W,false));
            idx=0;
            function<void(int,int)> dfs = [&](int i,int j){
                visited[i][j]=1;
                test.p[idx][0]=i;
                test.p[idx][1]=j;
                test.p[idx][2]=rand()%MAXmomentum+1;
                if (++idx==N) return;
                if (idx==23) test.h[i-1][j-1] = MAXmomentum;
                else if (idx==145) test.h[i-1][j-1] = -MAXmomentum;
                vi s = {0,1,2,3};
                shuffle(s.begin(),s.end(),generator);
                for(int c=0;c<4;++c){
                    int i2=i + vecinos[c].first;
                    int j2=j+vecinos[c].second;
                    if (i2>0 && i2<=H && j2>0 && j2<=W && !visited[i2][j2]) {
                        dfs(i2, j2);
                        if (idx==N) return;
                    }
                }
            };

            dfs(13,94);
            assert(idx==N);
            test.print(file);

        }

        // 7
        {
            N = 200;
            test.resize(H, W, N);
            for (int i = 0; i < H; ++i) {
                for (int j = 0; j < W; ++j) test.h[i][j] = 1;
            }
            idx=0;
            for(int i=0;idx<N;i+=2){
                for(int j=(i%2)+1;j<30;j+=2){
                    test.p[idx][0]=i+1;
                    test.p[idx][1]=j+1;
                    test.p[idx][2] = 1;
                    test.h[i][j]=0;
                    if (++idx==N) break;
                }
            }
            assert(idx==N);
            test.print(file);
        }

        file.flush();
        file.close();
    }


}