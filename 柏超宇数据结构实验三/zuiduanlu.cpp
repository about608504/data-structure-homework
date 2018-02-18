#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
#define Max 0xfffffff
#define N 1005
int p[N][N], mark[N], f[N];
int t, n;
void Dijkstra() {
    int i, j, k, min;
    memset(mark, 0, sizeof(mark));
    for(i = 1; i <= n; i++)
        f[i] = p[1][i];
    f[1] = 0;
    for(i = 1; i <= n; i++) {
        min = Max;
        for(j = 1; j <= n; j++) {
            if(!mark[j] && f[j] < min) {
                min = f[j];
                k = j;
            }
        }
        if(min == Max) break;
        mark[k] = 1;
        for(j = 1; j <= n; j++) {
            if(!mark[j] && f[j] > f[k] + p[k][j])
                f[j] = f[k] + p[k][j];
        }
    }
    printf("ans:\n");
    for(i = 1;i <=n; i++){
        printf("%d ", f[i]);
    }
}
int main() {
    int i, j;
    while(scanf("%d%d", &t, &n) != EOF) {
        for(i = 1; i <= n; i++)
            for(j = 1; j <= n; j++)
                p[i][j] = Max;
        for(j = 0; j < t; j++) {
            int a, b, len;
            scanf("%d%d%d", &a, &b, &len);
            if(p[a][b] > len)
                p[a][b] = p[b][a] = len;
        }
        Dijkstra();
    }
    
    return 0;
}