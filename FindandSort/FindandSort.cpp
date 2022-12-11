// FindandSort.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
using namespace std;
#include <iostream>
#include<math.h>

//将int重命名为Elemtype
typedef int Elemtype;

//顺序表结构体
typedef struct SqList
{
    Elemtype* a; //定义的一个int型指针（用来初始化时开辟数组空间）
    int length;  //顺序表长度
}SqList;

//辅助函数：顺序表初始化
void InitSqList(SqList& L);
void InitSqList2(SqList& L);
void PrintList(SqList& L);

//折半查找
int BinarySearch(SqList& L, Elemtype key);
int BinarySearch_Rec(SqList& L, Elemtype key,int low ,int high);

//快速排序
int Partition(SqList& L, int low, int high);
void QSort(SqList& L, int low, int high);
void QuickSort(SqList& L);
int main()
{
    SqList L1;
    InitSqList(L1);

    printf("[折半查找][非递归] 所查元素所在下标为%d\n", BinarySearch(L1, 7));
    printf("[折半查找][ 递归 ] 所查元素所在下标为%d\n", BinarySearch_Rec(L1, 7, 0, L1.length-1));

    //快速排序 （不对L.a[0]的元素进行排序 从a[1]开始）
    SqList L2;
    InitSqList2(L2);
    PrintList(L2);
    QuickSort(L2);
    PrintList(L2);
    
    
    
    std::cout << "Hello World!\n";
}

void InitSqList(SqList& L)
{
    int i;
    L.a = new Elemtype[10];
    L.length = 10;
    for (i = 0; i < L.length; i++)
    {
        L.a[i] = i;
    }
}
void InitSqList2(SqList& L)
{
    int b[10] = {8,2,3,6,5,4,9,1,7,10 };
    int i;
    L.a = new Elemtype[11];
    L.length = 10;
    L.a[0] = -1;
    for (i = 1; i < L.length+1; i++)
    {
        L.a[i] = b[i-1];
    }
}
void PrintList(SqList& L)
{
    int i;
    for ( i = 0; i < L.length+1; i++)
    {
        cout << L.a[i] << endl;
    }
    cout<<"\n";
}

int BinarySearch(SqList& L, Elemtype key)
{
    int low=0, high=L.length-1, mid;
    while (low<=high)
    {
        mid = (low + high) / 2;
        if (L.a[mid] < key)
        {
            low = mid + 1;
        }
        else if (L.a[mid] > key)
        {
            high = mid - 1;
        }
        else
        {
            return mid;
        }
    }
    return -1;
}
int BinarySearch_Rec(SqList& L, Elemtype key, int low, int high)
{
    int mid;
    mid = (low + high) / 2;
    //递归出口1 ：查找失败
    if (low > high)
    {
        return -1;
    }
    //递归出口2 ：查找成功
    else if (L.a[mid] == key)
    {
        return mid;
    }
    //递归体1
    else if (L.a[mid] < key)
        return BinarySearch_Rec(L, key, mid + 1, high);
    //递归体2
    else
        return BinarySearch_Rec(L, key, low, mid-1);

   
}

//快速排序
int Partition(SqList& L, int low, int high)
{
    int pivotkey;
    L.a[0] = L.a[low]; //选取第一个记录a[1]为枢轴记录 并存放在a[0]中
    pivotkey = L.a[low]; //pivotkey用来保存枢轴记录
    while (low < high) //从表的两端交替向中间扫描
    {
        while (low < high && L.a[high] >= pivotkey)
        {
            high--;
        }
        L.a[low] = L.a[high];//比枢轴小的移动到左端
        while (low < high && L.a[low] <= pivotkey)
        {
            low++;
        }
        L.a[high] = L.a[low]; //比枢轴大的移动到右端
    }
    L.a[low] = L.a[0];//枢轴移动到该趟排序所应该在的最终位置
    return low;//返回枢轴在该趟排序的最终位置
}
void QSort(SqList& L, int low, int high)
{
    int pivotloc;
    if (low < high)//长度大于一
    {
        pivotloc = Partition(L, low, high); //将L.a[]一分为二
        QSort(L, low, pivotloc - 1);//左子表递归排序
        QSort(L, pivotloc+1, high);//右子表递归排序
    }
}
void QuickSort(SqList& L)
{
    QSort(L, 1, L.length);
}