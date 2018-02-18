#include<stdio.h>
#include <sys/timeb.h>
#include<time.h>
#include<algorithm>
#include<iostream>
using namespace std;
const int MaxSize = 100000;
int original[MaxSize];//记录原始数据
struct timeb t1, t2; //计算程序运行时间
typedef struct entry {
    int key;
    int data;
} Entry;
typedef struct list {
    int n;
    Entry D[MaxSize + 20];
} List;
List list;

void random1() { //产生n个随机数
    srand((unsigned)time(NULL));//初始化随机数种子
    for(int i = 0; i < MaxSize; i++) {
        int k = rand();
        original[i] = k;
    }
}

void initial(List *list) {
    for(int i = 0; i < MaxSize; i++) {
        list->D[i].key = original[i];
    }
}

int FindMin(List list, int startIndex) {
    int i, minIndex = startIndex;
    for(i = startIndex + 1; i < list.n; i++) {
        if(list.D[i].key < list.D[minIndex].key) {
            minIndex = i;
        }
    }
    return minIndex;
}

void swap(Entry *D, int i, int j) {
    if(i == j) return;
    Entry temp = *(D + i);
    *(D + i) = *(D + j);
    *(D + j) = temp;
}

void SelectSort(List *list) {
    int minIndex, startIndex = 0;
    initial(list);
    ftime(&t1);
    while(startIndex < list->n - 1) {
        minIndex = FindMin(*list, startIndex);
        swap(list->D, startIndex, minIndex);
        startIndex++;
    }
    ftime(&t2);
    printf("SelectSort:");
    cout<<(t2.time-t1.time)*1000+(t2.millitm-t1.millitm)<<"ms"<<endl;
}

void InsertSort(List *list) {
    int i, j;
    initial(list);
    ftime(&t1);
    for(i = 1; i < list->n; i++) {
        Entry insertItem = list->D[i];
        for(j = i - 1; j >= 0; j--) {
            if(insertItem.key < list->D[j].key) {
                list->D[j + 1] = list->D[j];
            } else break;
        }
        list->D[j + 1] = insertItem;
    }
    ftime(&t2);
    printf("InsertSort:");
    cout<<(t2.time-t1.time)*1000+(t2.millitm-t1.millitm)<<"ms"<<endl;
}

void BubbleSort(List *list) {
    int i, j;
    initial(list);
    ftime(&t1);
    bool isSwap = false;
    for(i = list->n - 1; i > 0; i--) {
        for(j = 0; j < i; j++) {
            if(list->D[j].key > list->D[j + 1].key) {
                swap(list->D, j, j + 1);
                isSwap = true;
            }
        }
        if(!isSwap) break;
    }
    ftime(&t2);
    printf("BubbleSort:");
    cout<<(t2.time-t1.time)*1000+(t2.millitm-t1.millitm)<<"ms"<<endl;
}

int Partition(List *list, int low, int high) {
    int i = low;
    int j = high + 1;
    Entry pivot = list->D[low];
    do {
        do {
            i++;
        } while (list->D[i].key < pivot.key);
        do {
            j--;
        } while (list->D[j].key > pivot.key);
        if(i < j) {
            swap(list->D, i, j);
        }
    } while(i < j);
    swap(list->D, low, j);
    return j;
}

void QuickSort(List *list, int low, int high) {
    int k;
    if(low < high) {
        k = Partition(list, low, high);
        QuickSort(list, low, k - 1);
        QuickSort(list, k + 1, high);
    }
}

void QuickSort(List *list) {
    initial(list);
    ftime(&t1);
    QuickSort(list, 0, list->n - 1);
    ftime(&t2);
    printf("QuickSort:");
    cout<<(t2.time-t1.time)*1000+(t2.millitm-t1.millitm)<<"ms"<<endl;
}

void MergeArray(List *list, int first, int mid, int last) { //合并两个序列
    int i = first, j = mid + 1;
    int m = mid, n = last;
    int temp[MaxSize], k = 0;
    while(i <= m && j <= n) {
        if(list->D[i].key < list->D[j].key)
            temp[k++] = list->D[i++].key;
        else
            temp[k++] = list->D[j++].key;
    }
    while(i <= m)
        temp[k++] = list->D[i++].key;
    while(j <= n)
        temp[k++] = list->D[j++].key;
    for(i = 0; i < k; i++)
        list->D[first + i].key = temp[i];
}

void MergeSort(List *list, int first, int last) {
    int mid;
    if(first < last) {
        mid = (first + last) / 2;
        MergeSort(list, first, mid);
        MergeSort(list, mid + 1, last);
        MergeArray(list, first, mid, last);
    }
}

void mergesort(List *list) { //归并排序1
        initial(list);
    ftime(&t1);
    MergeSort(list, 0, list->n - 1);
    ftime(&t2);
    printf("MergeSort:");
    cout<<(t2.time-t1.time)*1000+(t2.millitm-t1.millitm)<<"ms"<<endl;
}

void AdjustHeap(List *list,int s,int m)//调整堆
{
    int j,temp=list->D[s].key;
    for(j=2*s;j<=m;j*=2)
    {
        if(j<m&&list->D[j].key<list->D[j+1].key)
            j++;
        if(temp>=list->D[j].key)
            break;
        list->D[s].key=list->D[j].key;
        s=j;
    }
    list->D[s].key=temp;
}

void HeapSort(List *list)//堆排序
{
    int i;
    initial(list);
    ftime(&t1);
    for(i=MaxSize/2-1;i>=0;i--)//建立堆
        AdjustHeap(list,i,MaxSize);
    for(i=MaxSize-1;i>0;i--)
    {
        swap(list->D,0,i);//交换堆顶和栈底元素
        AdjustHeap(list,0,i-1);//重新调整堆顶节点成为大顶堆
    }
    ftime(&t2);
    printf("HeapSort:");
    cout<<(t2.time-t1.time)*1000+(t2.millitm-t1.millitm)<<"ms"<<endl;
}

int main() {
    random1();
    list.n = MaxSize;
    printf("MaxSize = %d\n",MaxSize);
    QuickSort(&list);
    mergesort(&list);
    HeapSort(&list);
    SelectSort(&list);
    InsertSort(&list);
    BubbleSort(&list);
    return 0;
}