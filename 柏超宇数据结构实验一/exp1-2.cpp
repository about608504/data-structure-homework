#include <stdio.h>
#include <stdlib.h>
#define ERROR 0
#define OK 1
#define Overflow 2
#define Underflow 3
#define NotPresent 4
#define Duplicate 5

typedef struct Node {
    int element;
    struct Node *link;
} Node;

typedef struct {
    struct Node *first;
    int n;
} SingleList;


int Init(SingleList *L) {
    L->first = (Node *)malloc(sizeof(Node));
    if(!L->first) return ERROR;
    L->first->link = NULL;
    L->n = 0;
    L->first->element = 99;
    return OK;
}

int Insert(SingleList *L, int i, int x) {
    Node *p, *q;
    int j;
    if(i < -1 || i > L->n - 1) return ERROR;
    p = L->first->link;
    for (j = 0; j < i ; j++) p = p->link;
    q = (Node *)malloc(sizeof(Node));
    q->element = x;
    if(i > -1) {
        q->link = p->link;
        p->link = q;
    } else {
        q->link = L->first->link;
        L->first->link = q;
    }
    L->n++;
    return OK;
}

int Output(SingleList L) {
    Node *p;
    if(!L.n) return ERROR;
    p = L.first->link;
    while(p) {
        printf("%d ", p->element);
        p = p->link;
    }
    printf("\n");
    return OK;

}

int Delete(SingleList *L, int i) {
    int j;
    Node *p, *q;
    if(!L->n) {
        return ERROR;
    }
    if(i < 0 || i > L->n - 1) return ERROR;
    q = L->first;
    for(j = 0; j < i; j++) {
        q = q->link;
    }
    p = q->link;
    q->link = p->link;
    free(p);
    L->n--;
    return OK;
}

int ReverseList(SingleList *L) {
    if(L->first == NULL || L->first->link == NULL) return OK;
    Node *p;
    Node *q;
    Node *r;
    p = L->first->link;
    q = L->first->link->link;
    L->first->link->link = NULL;
    while(q) {
        r = q->link;
        q->link = p;
        p = q;
        q = r;
    }
    L->first->link = p;
    return OK;
}

int Swap(SingleList *L, int x, int y) {
    Node *p, *q, *perp, *perq, *sp, *sq;
    p = L->first->link;
    perp = L->first;
    q = L->first->link;
    perq = L->first;
    if(x < -1 || x > L->n - 1) return ERROR;
    if(y < -1 || y > L->n - 1) return ERROR;
    for(int i = 0; i < x; i++) {
        perp = perp->link;
        p = p->link;
    }
    for(int i = 0; i < y; i++) {
        perq = perq->link;
        q = q->link;
    }
    sp = p->link;
    sq = q->link;
    if(abs(x - y) > 1) {
        perp->link = q;
        q->link = sp;
        perq->link = p;
        p->link = sq;
    }
    if(y - x == 1) {
        perp->link = q;
        q->link = p;
        p->link = sq;
    }
    if(y - x == -1) {
        perq->link = p;
        p->link = q;
        q->link = sp;
    }
    return OK;
}

int SortList(SingleList *L) {
    int i, j, min, index;
    Node *p, *q;
    for(i = 0; i < L->n - 1; i++) {
        min = 999;
        for(j = i; j < L->n; j++) {
            p = L->first->link;
            for(int k = 0; k < j; k++) {
                p = p->link;
            }
            if (p->element < min) {
                index = j;
                min = p->element;
            }
        }
        Swap(L, i, index);
    }
    return OK;
}

int main() {
    SingleList list;
    Init(&list);
    printf("单链表初始化完毕\n");
    for (int i = 0; i < 10; ++i) {
        Insert(&list, i - 1, i);
    }
    printf("单链表中插入0~9:\n");
    Output(list);
    ReverseList(&list);
    printf("将单链表进行反转:\n");
    Output(list);
    Swap(&list, 6, 7);
    Swap(&list, 3, 9);
    Swap(&list, 1, 4);
    printf("进行一系列交换让单链表乱序:\n");
    Output(list);
    SortList(&list);
    printf("将单链表排序:\n");
    Output(list);
    Delete(&list, 9);
    printf("删除最后一个元素:\n");
    Output(list);
}