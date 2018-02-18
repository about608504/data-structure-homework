#include<stdio.h>
#include<stdlib.h>
double a[105][105];
int vis[105];
int head = 0;
int tail = 1;
int queue[100];
double cost[100][100];
int Insert(int u, int v, double w) {
    a[u][v] = w;
    a[v][u] = w;
    return 0;
}
void dfs(int v) {
    printf("%d\n", v);
    vis[v] = 1;
    for(int i = 1; i < 100 ; i++) {
        if((a[v][i] != 0) && (vis[i] == 0)) {
            dfs(i);
        }
    }
}
void bfs(int v) {
    head = 0;
    tail = 1;
    for(int i = 1 ; i < 100 ; i++) {
        vis[i] = 0;
    }
    for (int i = 0; i < 100; i++) {
        queue[i] = 0;
    }
    queue[tail] = v;
    vis[v] = 1;
    while(head < tail) {
        head++;
        printf("%d\n", queue[head]);
        for (int i = 1; i < 100; i++) {
            if((a[queue[head]][i]) && (vis[i] == 0)) {
                tail++;
                queue[tail] = i;
                vis[i] = 1;
            }
        }
    }
}
void  floyd(){
    for(int i = 1;i<=20;i++){
        for(int j = 1;j<= 20; j++){
            if(a[i][j] == 0){
                cost[i][j] = 9999;
            }else{
                cost[i][j] = a[i][j];
            }
            if(i == j){
                cost[i][j] = 0;
            }
        }
    }
    for(int k = 1;k<=9; k++){
        for(int i = 1; i<=9; i++){
            for(int j = 1; j<=9; j++){
                if(cost[i][j] > cost[i][k]+cost[k][j]){
                    cost[i][j] = cost[i][k]+cost[k][j];
                }
            }
        }
    }
    for(int i = 1; i < 10 ;i++){
        for(int j = 1; j< 10; j++){
            printf("%lf\t", cost[i][j]);
        }
        printf("\n");
    }
}

int main() {
    for(int i = 1; i < 100; i++) {
        for (int j = 1; j < 100; j++) {
            a[i][j] = 0;
        }
    }
    for(int i = 1; i < 100; i++) {
        vis[i] = 0;
    }
    Insert(1, 2, 32.8);
    Insert(1, 3, 44.6);
    Insert(1, 8, 12.1);
    Insert(1, 9, 18.2);
    Insert(2, 3, 5.9);
    Insert(3, 4, 21.3);
    Insert(3, 5, 41.1);
    Insert(3, 7, 56.4);
    Insert(4, 5, 67.3);
    Insert(4, 6, 98.7);
    Insert(5, 6, 85.6);
    Insert(5, 7, 10.5);
    Insert(6, 9, 79.2);
    Insert(7, 8, 52.5);
    Insert(8, 9, 8.7);
    printf("DFS:\n");
    dfs(1);
    printf("BFS:\n");
    bfs(1);
    printf("floyd\n");
    floyd();
}