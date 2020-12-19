#ifndef MINSPANTREE_H
#define MINSPANTREE_H

#include "Graph.h"
#include "UFSet.h"
#include "Heap.h"
#include <iostream>
using namespace std;
const int maxValue = 10000;                //�����в�����ܳ��ֵĴ���

//��С�������߽��
template <class T, class K>
struct MSTEdgeNode
{
    int tail, head; K key;                      //������λ�ü����ϵ�Ȩֵ
    MSTEdgeNode(): tail(-1), head(-1), key(0){}     //���캯��
    //�����ж����㷨
    bool operator <= (MSTEdgeNode<T, K> &R) {return key <= R.key;}
    bool operator > (MSTEdgeNode<T, K> &R) {return key > R.key;}
};

//��С������
template <class T, class K>
class MinSpanTree
{
    protected:
        MSTEdgeNode<T, K> *edgeValue;                                   //��ֵ�����ʾ��
        int maxSize, currentSize;                                       //��������Ԫ�ظ����͵�ǰ����
    public:
        MinSpanTree(int sz = 10 - 1): maxSize(sz), currentSize(0)       //���캯��
            {edgeValue = new MSTEdgeNode<T, K>[sz]();}
        ~MinSpanTree() {delete[] edgeValue;}                            //��������
        bool insert(const MSTEdgeNode<T, K> &item);                     //����
        template <class M, class N>
        friend ostream &operator << (ostream &out, MinSpanTree<M, N> &MST);
};

//�������
template <class T, class K>
ostream &operator << (ostream &out, MinSpanTree<T, K> &M)
{
    for (int i = 0; i < M.currentSize; i++)
        cout << M.edgeValue[i].tail << "->" << M.edgeValue[i].head << endl;
    return out;
}

//��item������С������
template <class T, class K>
bool MinSpanTree<T, K>::insert(const MSTEdgeNode<T, K> &item)
{
    if (currentSize == maxSize) return false;           //����������
    edgeValue[currentSize++] = item; return true;
}

//Kruskal������С���㷨
template <class T, class E>
void Kruskal(Graphlnk<T, E> &G, MinSpanTree<T, E> &MST)
{
    MSTEdgeNode<T, E> ed; E cost;
    int u, v, count,                                                //�߽�㸨����Ԫ
    vertices = G.Vertices(),                                          //������
    edges = G.Edges();                                                //����
    MinHeap<MSTEdgeNode<T, E>> H(2 * edges);                          //��С�ѣ��ܼ���ô����ΪE
    UFSet F(vertices);                                              //���鼯
    bool *Vmst = new bool[vertices];
    for (u = 0; u < vertices; u++)
    {
        for (v = u + 1; v < vertices; v++)
        {
            if (cost = G.getWeight(u, v), !Vmst[v] && cost != 0 )
            {
                ed.tail = u; ed.head = v;                           //�����
                ed.key = cost; H.insert(ed);
            }
        }
        Vmst[u] = true;                                             //����ͼ���ȥ��
    }

    count = 1;                                                      //��С�����������������
    while (count < vertices)                                        //����ִ�У�ȡn-1����
    {
        H.removeMin(ed);                                            //����С�����˳�������СȨֵ�ı�ed
        u = F.find(ed.tail); v = F.find(ed.head);                   //ȡ���������ڼ��ϵĸ�u��v
        if (u != v)                                                 //����ͬһ���ϣ�˵������ͨ
        {
            F.Union(u, v);                                          //�ϲ�����ͨ����
            MST.insert(ed); count++;                                //�ñߴ�����С������
        }
    }
    delete[] Vmst;
}

//Prim������С���㷨
template <class T, class E>
void Prim(Graphlnk<T, E> &G, const T start, MinSpanTree<T, E> &MST)
{
    MSTEdgeNode<T, E> ed; E cost;
    int v, count,                                                   //�߽�㸨����Ԫ
    u = G.getVertexPos(start),                                      //����ʼ����ı��
    vertices = G.Vertices(),                                          //������
    edges = G.Edges();                                                //����
    MinHeap<MSTEdgeNode<T, E>> H(edges);                            //��С�ѣ� �ؼ�������ΪE
    bool *Vmst = new bool[vertices];                                //��С���������㼯��
    memset(Vmst, 0, sizeof(bool) * vertices);
    Vmst[u] = true;                                                 //u����������
    count = 1;
    do
    {
        v = G.getFirstNeighbor(u);
        while (v != -1)                                             //��u�������ڽӶ�������
        {
            if (!Vmst[v])                                           //��v������������(u, v)�����
            {
                ed.tail = u; ed.head = v;
                ed.key = G.getWeight(u, v);                             //tail�����ڣ�head��������
                H.insert(ed);
            }
            v = G.getNextNeighbor(u, v);                            //�Ҷ���u����һ���ڽӶ���v
        }
        while (!H.isEmpty() && count < vertices)
        {
            H.removeMin(ed);                                        //�Ӷ����˳�������СȨֵ�ı�ed
            if (!Vmst[ed.head])
            {
                MST.insert(ed);                                     //δ���ʹ���������С������
                u = ed.head; Vmst[u] = true;                        //u������С���������㼯��
                count++; break;
            }
        }
    } while (count < vertices);                                            //ѡȡn-1����
    delete[] Vmst;
}
#endif  //MINSPANTREE_H