#include <stdio.h>
#include <stdlib.h>
#define ERROR 0
#define OK 1
#define Overflow 2
#define Underflow 3
#define NotPresent 4
#define Duplicate 5

typedef struct {
    int n;
    int maxLength;
    int *element;
} SeqList;

SeqList L;

int Init (SeqList *L, int mSize) {
    L->maxLength = mSize;
    L->n = 0;
    L->element = (int *)malloc(sizeof(int) * mSize);
    if (!L->element) {
        return ERROR;
    }
    return OK;
}

int Find (SeqList L , int i , int *x) {
    if (i < 0 || i > L.n - 1) {
        return ERROR;
    }
    *x = L.element[i];
    return OK;
}

int Insert(SeqList *L , int i , int x) {
    int j;
    if (i < -1 || i > L->n - 1) {
        return ERROR;
    }
    if (L->n == L->maxLength) {
        return ERROR;
    }
    for(j = L->n - 1 ; j > i ; j++) {
        L->element[j + 1] = L->element[j];
    }
    L->element[i + 1] = x;
    L->n++;
    return OK;
}

int Delete(SeqList *L , int i) {
    int j;
    if(i < 0 || i > L-> n - 1)
        return ERROR;
    if(!L->n)
        return ERROR;
    for(j = i + 1; j < L->n; j++) {
        L->element[j - 1] = L->element[j];
    }
    L->n--;
    return OK;
}

int Output(SeqList L) {
    int i;
    if (!L.n) return ERROR;
    for(i = 0; i <= L.n - 1; i++){
        printf("%d ", L.element[i]);
    }
    return OK;
}

void Destroy (SeqList *L){
    (*L).n = 0;
    (*L).maxLength = 0;
    free((*L).element);
}
int main() {
    SeqList list;
    if(Init(&list, 10000)){
        printf("初始化成功\n");
    };
    for(int i = 0; i < 9; i++) {
        Insert(&list, i-1, i);
    }
    printf("插入成功\n");
    printf("现在顺序表的元素：\n");
    Output(list);
    printf("\n");
    Delete(&list, 2);
    printf("删除第顺序表第二个元素成功\n");
    printf("现在顺序表的元素：\n");
    Output(list);
    printf("\n");
    Destroy(&list);
    printf("内存成功释放\n");
}









