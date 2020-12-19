#ifndef HEAP_H
#define HEAP_H
#include <iostream>
using namespace std;
//最小堆
template <class E>
class MinHeap
{
    public:
        MinHeap(int sz = 50);                                              //构造函数：建立空堆
        MinHeap(E arr[], int n);                                                    //构造函数：通过一个数组建堆
        ~MinHeap() {delete[] heap;}                                                 //析构函数
        bool insert(const E &x);                                                    //将x插入到最小堆
        bool removeMin(E &x);                                                       //删除堆顶上的最小元素
        bool isEmpty() const                                                        //判断堆是否为空
            {return currentSize == 0 ? true : false;}
        bool isFull() const                                                         //判断堆是否为满
            {return currentSize == maxHeapSize ? true : false;}
        void mmakeEmpty() {currentSize = 0;}                                        //置空堆
    private:
        E *heap;                                                                    //存放最小堆中元素的数组
        int currentSize;                                                            //最小堆中当前元素的个数
        int maxHeapSize;                                                            //最小堆最多允许元素个数
        void siftDown(int start, int m);                                            //从start到m下滑调整成最小堆
        void siftUp(int start);                                                     //从start到0上滑调整成最小堆
};

//构造函数
template<class E>
MinHeap<E>::MinHeap(int sz)
{
    maxHeapSize = sz;
    heap = new E[maxHeapSize]; if (heap == NULL) {cerr << "堆存储分配错误！" << endl; exit(1);} 
    currentSize = 0;         //建立当前大小
}

//构造函数:通过一个数组建堆
template <class E>
MinHeap<E>::MinHeap(E arr[], int n)
{
    maxHeapSize = n;
    heap = new E[maxHeapSize]; if (heap == NULL) {cerr << "堆存储分配错误！" << endl; exit(1);}
    for (int i = 0; i < n; i++) heap[i] = arr[i];
    currentSize = n;                                                                //复制堆数组，建立当前大小
    int currentPos = (currentSize - 2) / 2;                                         //寻找最初调整为值：最后分支结点
    while (currentPos >= 0)                                                         //自底向上逐步扩大形成堆
    {
        siftDown(currentPos, currentSize - 1);                                      //局部自伤向下下滑调整
        currentPos--;                                                               //再向前换一个分支结点
    }
}

//私有函数：从start到m为止，自上向上比较，如果子女的值小于父节点的值，
//则关键码小的上浮，继续向下层比较，这样将一个集合局部调整成最小堆
template <class E>
void MinHeap<E>::siftDown(int start, int m)
{
    int current = start, min = 2 * current + 1;                                     //current为当前结点，min为current结点较小的子女
    E temp = heap[current];
    while (min <= m)                                                                //检查是否到最后位置
    {
        if (min < m && heap[min] > heap[min + 1]) min++;                            //让min指向两子女中的小者
        if (temp <= heap[min]) break;                                               //小则不调整
        else {heap[current] = heap[min]; current = min; min = 2 * min + 1;}         //否则小者上移，current，min下移
    } heap[current] = temp;                                                         //回放temp中暂存的元素
}

//私有函数：从start到m为止，自下向上比较，如果子女的值小于父节点的值
//则相互交换，这样将集合重新调整为最小堆。
template <class E>
void MinHeap<E>::siftUp(int start)
{
    int current = start, parent = (current - 1) / 2; E temp = heap[current];       
    while (current > 0)                                                                         //沿父结点路径向上直达跟
    {
        if (heap[parent] <= temp) break;                                                        //父结点值小，不调整
        else {heap[current] = heap[parent]; current = parent; parent = (parent - 1) / 2;}       //父结点值大，调整
    } heap[current] = temp;                                                                     //回放temp中暂存的元素
}

//公共函数：将x插入到最小堆
template <class E>
bool MinHeap<E>::insert(const E &x)
{
    if (currentSize == maxHeapSize) {cerr << "Heap Full" << endl; return false;}                //堆满
    heap[currentSize] = x;                                                                      //插入
    siftUp(currentSize);                                                                        //向上调整
    currentSize++; return true;                                                                 //堆计数+1
}

//公共函数：删除堆顶上的最小元素
template <class E>
bool MinHeap<E>::removeMin(E &x)
{
    if (!currentSize) return false;                                                             //堆空，返回false
    x = heap[0]; heap[0] = heap[currentSize - 1];                                               //最后元素填补到根结点
    currentSize--; siftDown(0, currentSize - 1); return true;                                   //自上向下调整为堆
}
#endif  //HEAP_H