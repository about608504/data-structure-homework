#include<stdio.h>
#include<stdlib.h>
#define MaxVexNum 100

int visited[100];        //访问变量
int vis[100];
typedef struct node {   //邻接表结点
    int NO;            //邻接点字母对应序号
    char adjvex;
    double wdata; //权值
    struct node *next;
} ArcNode;
typedef struct vnode {   //顶点表结点
    char vertex;
    ArcNode *firstArc;  //邻接表头指针
} VexNode;
typedef struct {
    VexNode adjlist[MaxVexNum];   //邻接表
    int n, e; //顶点数和边数
} ALGraph;

ALGraph *CreateALGraph() {  //创建邻接表
    int i, j, k;
    double m;
    ArcNode *p, *q;
    ALGraph *G;
    G = (ALGraph *)malloc(sizeof(ALGraph));
    FILE *fp;
    fp = fopen("/Users/bcy/ALGraph.txt", "r"); //打开文件
    if(fp == NULL) {
        printf("Can't open the file!\n");
        exit(1);
    }
    fscanf(fp, "%d", &G->n);
    fscanf(fp, "%d", &G->e);
    char ccc = fgetc(fp);
    ccc = fgetc(fp);
    for(i = 1; i <= G->n; i++) {    //顶点信息
        G->adjlist[i].vertex = fgetc(fp);
        G->adjlist[i].firstArc = NULL;
        visited[i] = i;
    }
    for(k = 1; k <= G->e; k++) {   //边信息
        p = (ArcNode *)malloc(sizeof(ArcNode));
        q = (ArcNode *)malloc(sizeof(ArcNode));
        fscanf(fp, "%d %d %lf", &i, &j, &m);
        p->NO = j;
        p->adjvex = G->adjlist[j].vertex;
        p->wdata = m;
        p->next = G->adjlist[i].firstArc;
        G->adjlist[i].firstArc = p;
        q->NO = i;
        q->adjvex = G->adjlist[i].vertex;
        q->wdata = m;
        q->next = G->adjlist[j].firstArc;
        G->adjlist[j].firstArc = q;
    }
    fclose(fp);
    return G;
}
bool haveEdge(ALGraph *G, int u, int v) {
    ArcNode *s;
    int i = 1;
    s = G->adjlist[u].firstArc;
    while(s) {
        if(s->NO == v) {
            return true;
        }
        s = s->next;
    }
    //printf("%d,%d\n",s->NO,s->next->NO);
    return false;
}
void dfs(ALGraph *G, int v) {
    printf("%d\n", v);
    vis[v] = 1;
    for(int i = 1; i < 100; i++) {
        if((haveEdge(G, v, i)) && (vis[i] == 0)) {
            dfs(G, i);
        }
    }
}
void bfs(ALGraph *G, int v) {
    int head = 0;
    int tail = 1;
    int queue[100];
    for(int i = 1; i < 100; i++) {
        vis[i] = 0;
        queue[i] = 0;
    }
    queue[tail] = v;
    vis[v] = 1;
    while(head < tail) {
        head++;
        printf("%d\n", queue[head]);
        for(int i = 1; i < 100; i++) {
            if((haveEdge(G, queue[head], i)) && (vis[i] == 0)) {
                tail++;
                queue[tail] = i;
                vis[i] = 1;
            }
        }
    }
}
void Tree(ALGraph *G) {         //prim算法
    int i, j, k;
    double w[100];       //权值
    int a[100];
    double min, sum = 0;
    ArcNode *s;
    s = (ArcNode *)malloc(sizeof(ArcNode));
    visited[1] = 0;       //从顶点A开始
    s = G->adjlist[1].firstArc;
    for(i = 1; i <= G->n; i++) {
        w[i] = 100;
        a[i] = 1;
    }
    while(s != NULL) {
        w[s->NO] = s->wdata;
        s = s->next;
    }
    for(i = 1; i < G->n; i++) {
        min = 100;
        for(j = 1; j <= G->n; j++) {
            if(visited[j] > 0 && w[j] < min) { //找最小权值
                min = w[j];
                k = j;
            }
        }
        sum = sum + min;
        visited[k] = 0;        //将k号顶点并入到顶点集合中
        s = G->adjlist[k].firstArc;
        while(s != NULL) {
            if(visited[s->NO] > 0 && s->wdata < w[s->NO]) { //找最小权值
                w[s->NO] = s->wdata;
                a[s->NO] = k;
            }
            s = s->next;
        }
    }
    for(i = 2; i <= G->n; i++) { //输出最小生成树
        printf("(%c,%c) %.2lf\n", G->adjlist[i].vertex, G->adjlist[a[i]].vertex, w[i]);
    }
    printf("min:%.2lf\n", sum);
}

int main() {
    int i, j;
    ALGraph *G;
    ArcNode *p;
    for(int i = 1; i < 100; i++) {
        vis[i] = 0;
    }
    p = (ArcNode *)malloc(sizeof(ArcNode));
    G = CreateALGraph();
    printf("最小生成树：\n");
    Tree(G);
    printf("dfs:\n");
    dfs(G, 1);
    printf("bfs:\n");
    bfs(G, 1);

}
