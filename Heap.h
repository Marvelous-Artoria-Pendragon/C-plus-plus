#ifndef HEAP_H
#define HEAP_H
#include <iostream>
using namespace std;
//��С��
template <class E>
class MinHeap
{
    public:
        MinHeap(int sz = 50);                                              //���캯���������ն�
        MinHeap(E arr[], int n);                                                    //���캯����ͨ��һ�����齨��
        ~MinHeap() {delete[] heap;}                                                 //��������
        bool insert(const E &x);                                                    //��x���뵽��С��
        bool removeMin(E &x);                                                       //ɾ���Ѷ��ϵ���СԪ��
        bool isEmpty() const                                                        //�ж϶��Ƿ�Ϊ��
            {return currentSize == 0 ? true : false;}
        bool isFull() const                                                         //�ж϶��Ƿ�Ϊ��
            {return currentSize == maxHeapSize ? true : false;}
        void mmakeEmpty() {currentSize = 0;}                                        //�ÿն�
    private:
        E *heap;                                                                    //�����С����Ԫ�ص�����
        int currentSize;                                                            //��С���е�ǰԪ�صĸ���
        int maxHeapSize;                                                            //��С���������Ԫ�ظ���
        void siftDown(int start, int m);                                            //��start��m�»���������С��
        void siftUp(int start);                                                     //��start��0�ϻ���������С��
};

//���캯��
template<class E>
MinHeap<E>::MinHeap(int sz)
{
    maxHeapSize = sz;
    heap = new E[maxHeapSize]; if (heap == NULL) {cerr << "�Ѵ洢�������" << endl; exit(1);} 
    currentSize = 0;         //������ǰ��С
}

//���캯��:ͨ��һ�����齨��
template <class E>
MinHeap<E>::MinHeap(E arr[], int n)
{
    maxHeapSize = n;
    heap = new E[maxHeapSize]; if (heap == NULL) {cerr << "�Ѵ洢�������" << endl; exit(1);}
    for (int i = 0; i < n; i++) heap[i] = arr[i];
    currentSize = n;                                                                //���ƶ����飬������ǰ��С
    int currentPos = (currentSize - 2) / 2;                                         //Ѱ���������Ϊֵ������֧���
    while (currentPos >= 0)                                                         //�Ե������������γɶ�
    {
        siftDown(currentPos, currentSize - 1);                                      //�ֲ����������»�����
        currentPos--;                                                               //����ǰ��һ����֧���
    }
}

//˽�к�������start��mΪֹ���������ϱȽϣ������Ů��ֵС�ڸ��ڵ��ֵ��
//��ؼ���С���ϸ����������²�Ƚϣ�������һ�����Ͼֲ���������С��
template <class E>
void MinHeap<E>::siftDown(int start, int m)
{
    int current = start, min = 2 * current + 1;                                     //currentΪ��ǰ��㣬minΪcurrent����С����Ů
    E temp = heap[current];
    while (min <= m)                                                                //����Ƿ����λ��
    {
        if (min < m && heap[min] > heap[min + 1]) min++;                            //��minָ������Ů�е�С��
        if (temp <= heap[min]) break;                                               //С�򲻵���
        else {heap[current] = heap[min]; current = min; min = 2 * min + 1;}         //����С�����ƣ�current��min����
    } heap[current] = temp;                                                         //�ط�temp���ݴ��Ԫ��
}

//˽�к�������start��mΪֹ���������ϱȽϣ������Ů��ֵС�ڸ��ڵ��ֵ
//���໥�������������������µ���Ϊ��С�ѡ�
template <class E>
void MinHeap<E>::siftUp(int start)
{
    int current = start, parent = (current - 1) / 2; E temp = heap[current];       
    while (current > 0)                                                                         //�ظ����·������ֱ���
    {
        if (heap[parent] <= temp) break;                                                        //�����ֵС��������
        else {heap[current] = heap[parent]; current = parent; parent = (parent - 1) / 2;}       //�����ֵ�󣬵���
    } heap[current] = temp;                                                                     //�ط�temp���ݴ��Ԫ��
}

//������������x���뵽��С��
template <class E>
bool MinHeap<E>::insert(const E &x)
{
    if (currentSize == maxHeapSize) {cerr << "Heap Full" << endl; return false;}                //����
    heap[currentSize] = x;                                                                      //����
    siftUp(currentSize);                                                                        //���ϵ���
    currentSize++; return true;                                                                 //�Ѽ���+1
}

//����������ɾ���Ѷ��ϵ���СԪ��
template <class E>
bool MinHeap<E>::removeMin(E &x)
{
    if (!currentSize) return false;                                                             //�ѿգ�����false
    x = heap[0]; heap[0] = heap[currentSize - 1];                                               //���Ԫ����������
    currentSize--; siftDown(0, currentSize - 1); return true;                                   //�������µ���Ϊ��
}
#endif  //HEAP_H