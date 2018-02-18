#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#define OK 1
#define ERROR 0
#define Underflow 3
#define NotPresent 4
#define Duplicate 5
typedef struct PNode {
    double coef;
    int exp;
    struct PNode *link;
} PNode, *SingleList;
typedef   SingleList   polynomial;
void PrintPoly(polynomial L) {
    polynomial p;
    int nCount = 0;
    p = L;
    while(1) {
        if((fabs(p->coef)) > 1e-6) {
            printf("%.2lf", p->coef);
            if(p->exp == 1) {
                printf("X");
            } else if(p->exp != 0) {
                printf("X^%d", p->exp);
            }
            nCount++;
        }

        if(p->link != NULL) {
            if(p->link->coef > 0) {
                printf("+");
            }
            p = p->link;
        } else {
            break;
        }
    }
    if(nCount == 0) {
        printf("0");
    }
    printf("\n");
}
polynomial SortPoly(polynomial &ha) {
    polynomial hb;
    polynomial t, r, s;
    int  exp = -256;
    int nCount = 0;

    t = ha;
    while(t != NULL) {
        if(t->exp > exp) {
            exp = t->exp;
        }
        t = t->link;
    }
    hb = (polynomial)malloc(sizeof(PNode));
    r = hb;

    while(exp >= -256) {
        t = ha;
        nCount = 0;
        while(t != NULL) {
            if(exp == t->exp) {
                nCount += t->coef;
            }
            t = t->link;
        }
        if(nCount != 0) {
            s = r;
            r ->coef = nCount;
            r ->exp = exp;
            r ->link = (polynomial)malloc(sizeof(PNode));
            r = r->link;
        }
        exp--;
    }
    s ->link = NULL;
    free(r);
    return (hb);
}
void Creat(SingleList &L) {
    polynomial r, s;
    double m;
    int n = 0;
    char c = '0', flag = 0, array[1000];
    L = (polynomial)malloc(sizeof(PNode));
    printf("coef,exp:");
    scanf("%lf,%d", &L->coef, &L->exp);
    printf("\n");
    r = L;
    while(1) {
        printf("coef,exp:");
        scanf("%lf,%d", &m, &n);
        printf("\n");
        if((fabs(m)) > 1e-6) {
            s = (polynomial)malloc(sizeof(PNode));
            s->coef = m;
            s->exp = n;
            r->link = s;
            r = r->link;
        } else {
            break;
        }
    }
    r->link = NULL;
}
polynomial Add(polynomial &ha, polynomial &hb) {
    polynomial p, q, r, hc;

    p = ha;
    q = hb;

    hc = (polynomial)malloc(sizeof(PNode));
    r = hc;

    while(p != NULL) {
        r->coef = p->coef;
        r->exp = p->exp;
        r->link = (polynomial)malloc(sizeof(PNode));
        r = r->link;
        p = p->link;
    }

    while(q != NULL) {
        r->coef = q->coef;
        r->exp = q->exp;
        r->link = (polynomial)malloc(sizeof(PNode));
        r = r->link;
        q = q->link;
    }
    r->link = NULL;
    return (SortPoly(hc));
}

polynomial Multiplied1(polynomial p1, polynomial p2) {
    polynomial hd;
    polynomial t, s, r;

    hd = (polynomial)malloc(sizeof(PNode));
    t = hd;
    while(p2 != NULL) {
        s = t;
        t->coef = p2->coef * p1->coef;
        t->exp = p2->exp + p1->exp;
        t->link = (polynomial)malloc(sizeof(PNode));
        t = t->link;
        p2 = p2->link;
    }
    s->link = NULL;
    free(t);
    return (SortPoly(hd));
}

polynomial Multiplied(polynomial &p1, polynomial &p2) {
    polynomial hd;
    polynomial t, q, s, r;
    hd = (polynomial)malloc(sizeof(PNode));
    hd->coef = 0;
    hd->exp = 0;
    hd->link = NULL;

    while(p1 != NULL) {
        t = Multiplied1(p1, p2);
        hd = Add(t, hd);
        p1 = p1->link;
    }
    return (SortPoly(hd));
}


int main() {
    polynomial ha, hb, hc, hd;
    printf("第一个多项式:\n");
    Creat(ha);
    printf("第一个多项式：");
    PrintPoly(ha);
    printf("第二个多项式:\n");
    Creat(hb);
    printf("第二个多项式：B=");
    PrintPoly(hb);
    printf("相加所得的多项式:");
    hc = Add(ha, hb);
    PrintPoly(hc);
    printf("相乘所得的多项式：");
    hd = Multiplied(ha, hb);
    PrintPoly(hd);
    return 0;
}
https://zh.wikipedia.org/wiki/%E7%BA%BF%E6%80%A7%E8%A1%A8