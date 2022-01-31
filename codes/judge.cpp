//
// Created by Carre on 19/3/2020.
//
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
#include <vector>

using namespace std;

//#include <spoj.h>

FILE *spoj_p_in, *spoj_p_out, *spoj_t_out;
#define PIN "testcases/med1.in"
#define POUT "testcases/med1.out"
#define TOUT "testcases/user.out"
//
#define SCORE "score.txt"

void spoj_init(){
    spoj_p_in=fopen(PIN, "r");
    spoj_p_out=fopen(POUT, "r");
    spoj_t_out=fopen(TOUT, "r");
}

 #define spoj_assert assert

int main() {
    spoj_init();
    int t;
    fscanf(spoj_p_in, "%d", &t);
    while (t--) {
        int usrvalue,expectedvalue;
        spoj_assert(fscanf(spoj_t_out, "%d", &usrvalue)==1);
        fscanf(spoj_p_out, "%d", &expectedvalue);
        spoj_assert(usrvalue==expectedvalue);

        int H,W,N;
        fscanf(spoj_p_in, "%d %d %d", &H, &W, &N);


        vector<int> p_t(N);
        {// read user p_t values
            for (int i = 0; i < N; ++i) {
                int tmp;
                spoj_assert(fscanf(spoj_t_out, "%d", &tmp) == 1);
                spoj_assert(tmp == 1 || tmp == -1);
                p_t[i] = tmp;
            }
        }
        vector<vector<int> > G(H+2,vector<int> (W+2,0));
        vector<vector<int> > p(N,vector<int> (3));
        {// testcase input
            for (int i = 1; i <= H; ++i) {
                for (int j = 1; j <= W; ++j) {
                    int tmp;
                    fscanf(spoj_p_in, "%d", &tmp);
                    G[i][j] = tmp;
                }
            }

            for (int i = 0; i < N; ++i) {
                int y,x,v;
                fscanf(spoj_p_in, "%d %d %d", &y,&x,&v);
                p[i][0]=y; p[i][1]=x;p[i][2]=v;
            }
        }

        {// check maxvalue from user's p_t values
            int val=0;
            for(int i=0;i<N;++i){
                val += p[i][2]*p_t[i]*G[p[i][0]][p[i][1]];
            }
            for(int i=0;i<N;++i){
                for(int j=i+1;j<N;++j){
                    if (abs(p[i][0]-p[j][0]) + abs(p[i][1]-p[j][1]) == 1){
                        val += p[i][2]*p_t[i] * p[j][2]*p_t[j];
                    }
                }
            }
            spoj_assert(val==usrvalue);
        }
    }
}
