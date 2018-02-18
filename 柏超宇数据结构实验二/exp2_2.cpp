#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 10000

typedef struct {
    int weight;
    int parent, lchild, rchild;
} hafuman;

typedef struct {
    char data[N]; //数据
    char copy[N][10 * N]; //编码
} bianma;

void display();
int input(int w[], bianma *bm);
void creat_hafuman(hafuman ht[], int w[], int n);
void select(hafuman ht[], int m, int *s1,  int *s2);
void encoding(hafuman ht[], bianma *bm, int n);
void coding(bianma *bm, int n);
void codingcoding(hafuman ht[], bianma *bm, int n);//译码
void output(bianma *bm, int n);
int i, j, k;

void display() {
    printf("\n\n\n");
    printf("1.输出编码\n");
    printf("2.译码\n");
    printf("3.exit\n");
    printf("请选择(1~~3):  ");
}


int input(int w[], bianma *bm) {
    int n = 0;

    printf("\n请输入句子或文章(以#结束)\n");

    while(1) {
        bm->data[n] = getchar();

        if(bm->data[n] == '#')
            break;
        n++;
    }

    for(i = 0; i < n; i++) {
        w[i] = 1;

        for(j = i + 1; j < n; ) {
            if( bm->data[i] == bm->data[j] ) {
                w[i]++;

                for(k = j; k < n; k++) {
                    bm->data[k] = bm->data[k + 1];
                }
                n--; 
            } else
                j++;
        }
    }
    return n;
}


void creat_hafuman(hafuman ht[], int w[], int n) {
    int s1, s2;
    int t;

    for(t = 1; t <= n; t++) {
        ht[t].weight = w[t - 1];
        ht[t].parent = 0;
        ht[t].lchild = 0;
        ht[t].rchild = 0;
    }

    for(t = n + 1; t <= 2 * n - 1; t++) {
        ht[t].weight = 0;
        ht[t].parent = 0;
        ht[t].lchild = 0;
        ht[t].rchild = 0;
    }


    for(t = n + 1; t <= 2 * n - 1; t++) {
        select(ht, t - 1, &s1, &s2); 

        ht[t].weight = ht[s1].weight + ht[s2].weight;

        ht[t].lchild = s1, ht[t].rchild = s2;

        ht[s1].parent = t, ht[s2].parent = t;

    }
}

void select(hafuman ht[], int m, int *s1,  int *s2) {
    int min1, min2, a, b;
    i = 1;
    while( ht[i].parent != 0) {
        i++;
    }
    min1 = ht[i].weight;
    a = i;

    for(j = i + 1; j <= m; j++) {
        if(min1 > ht[j].weight && ht[j].parent == 0) {
            min1 = ht[j].weight;
            a = j;
        }
    }

    i = 1;
    while( ht[i].parent != 0 || a == i ) {
        i++;
    }

    min2 = ht[i].weight;
    b = i;

    for(j = i + 1; j <= m; j++) {
        if(j == a)
            continue;

        if(min2 > ht[j].weight && ht[j].parent == 0) {
            min2 = ht[j].weight;
            b = j;
        }
    }
    *s1 = a;
    *s2 = b;

}

void encoding(hafuman ht[], bianma *bm, int n) { 
    int start, c, p;
    char *ch;
    ch = (char *)malloc( n * sizeof(char) );
    ch[n - 1] = '\0';

    for(i = 1; i <= n; i++) { 
        start = n - 1;
        c = i, p = ht[i].parent; 

        while(p != 0) {
            start--;
            if(ht[p].lchild == c)
                ch[start] = '0';
            else
                ch[start] = '1';

            c = p;
            p = ht[p].parent;  
        }

        strcpy( bm->copy[i - 1], &ch[start] );
      
    }
    free(ch);

}

void codingcoding(hafuman ht[], bianma *bm, int n) { 
    char s[10 * N];
    int p;
    printf("\n请输入密码\n");
    fflush(stdin);
    scanf("%s", s);
    printf("\n译码\n");
    p = 2 * n - 1;
    for(i = 0; s[i] != '\0'; i++) {
        if(s[i] == '0')
            p = ht[p].lchild;
        else if(s[i] == '1')
            p = ht[p].rchild;
        if(ht[p].lchild == 0 && ht[p].rchild == 0) {
            printf("%c", bm->data[p - 1]); 
            p = 2 * n - 1;
            continue;
        }

    }
    puts("\n");
}

void output(bianma *bm, int n) {
    printf("\n");
    for(i = 0; i < n; i++) {
        printf("%c\t", bm->data[i] );

        printf("%s\n", bm->copy[i]);
    }
}

int main() {
    hafuman ht[N];
    bianma *bm;
    int w[N];
    int n, m;
    bm = (bianma *)malloc( sizeof(bianma) );
    n = input(w, bm);
    printf("\n不同字符总数: %d\n", n);
    creat_hafuman(ht, w, n);
    encoding(ht, bm, n);
    getchar();
    while(1) {
        display();
        scanf("%d",  &m);
        switch(m) {
        case 1:
            output(bm, n);
            printf("\n请按任意键继续");
            getchar();
            break;
        case 2:
            codingcoding(ht, bm, n);
            printf("\n请按任意键继续");
            getchar();
            break;
        case 3:
            return 0;
        default:
            printf("ERROR\n");
        }
    }
}