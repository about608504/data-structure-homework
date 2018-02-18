#include <stdio.h>
#include <stdlib.h>
typedef struct BinaryTreeNode {
    char data;
    struct BinaryTreeNode *LChild, *RChild;
} BinaryTreeNode, *BinTree;

BinaryTreeNode *PreCreateBt(BinaryTreeNode *t) {
    char ch;
    ch = getchar();
    if (ch == '#')
        t = NULL;
    else {
        t = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
        t->data = ch;
        t->LChild = PreCreateBt(t->LChild);
        t->RChild = PreCreateBt(t->RChild);
    }
    return t;
}
void PreOrderTransverse(BinTree t) {
    if (t == NULL) return;
    printf("%c", t->data);
    PreOrderTransverse(t->LChild);
    PreOrderTransverse(t->RChild);
}

void InOrderTransverse(BinTree t) {
    if (t == NULL) return;
    InOrderTransverse(t->LChild);
    printf("%c", t->data);
    InOrderTransverse(t->RChild);
}
void PostOrderTransverse(BinTree t) {
    if (t == NULL) return;
    PostOrderTransverse(t->LChild);
    PostOrderTransverse(t->RChild);
    printf("%c", t->data);
}
int SSize(BinTree t) {
    int nodes = 0;
    if(t == NULL) return 0;
    nodes = SSize(t->LChild) + SSize(t->RChild) + 1;
    return nodes;
}
int numberOfLeafs(BinTree t) {
    if(t == NULL) {
        return 0;
    } else if((t->LChild == NULL) && (t->RChild == NULL)) {
        return 1;
    } else {
        return numberOfLeafs(t->LChild) + numberOfLeafs(t->RChild);
    }
}
int HeightOfLeafs(BinTree t) {
    if (t == NULL) {
        return 0;
    } else if((t->LChild == NULL) && (t->RChild == NULL)) {
        return 1;
    } else {
        return (HeightOfLeafs(t->LChild) > HeightOfLeafs(t->RChild) ?
                HeightOfLeafs(t->LChild) : HeightOfLeafs(t->RChild)) + 1;
    }
}
int exchange(BinTree t) {
    BinaryTreeNode *temp ;
    if(t == NULL) {
        return 0;
    }
    if((t->LChild == NULL) && (t->RChild == NULL)) {
        return 0;
    }
    temp = t->LChild;
    t->LChild = t->RChild;
    t->RChild = temp;
    if(t->RChild) exchange(t->RChild);
    if(t->LChild) exchange(t->LChild);
    return 0;

}
int main() {
    BinaryTreeNode *tree;
    tree = PreCreateBt(tree);
    printf("先序输出：\n");
    PreOrderTransverse(tree);
    printf("\n");
    printf("中序输出\n");
    InOrderTransverse(tree);
    printf("\n");
    printf("后序输出\n");
    PostOrderTransverse(tree);
    printf("\n");
    exchange(tree);
    printf("交换后先序输出\n");
    InOrderTransverse(tree);
    printf("\n");
    printf("树的节点个数:%d\n", SSize(tree));
    printf("树的叶子节点个数:%d\n",numberOfLeafs(tree));
    printf("树的高度:%d\n", HeightOfLeafs(tree));
}