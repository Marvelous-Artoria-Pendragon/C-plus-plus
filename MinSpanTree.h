#ifndef MINSPANTREE_H
#define MINSPANTREE_H

#include "Graph.h"
#include "UFSet.h"
#include "Heap.h"
#include <iostream>
using namespace std;
const int maxValue = 10000;                //问题中不大可能出现的大数

//最小生成树边结点
template <class T, class K>
struct MSTEdgeNode
{
    int tail, head; K key;                      //两定点位置及边上的权值
    MSTEdgeNode(): tail(-1), head(-1), key(0){}     //构造函数
    //重载判断运算法
    bool operator <= (MSTEdgeNode<T, K> &R) {return key <= R.key;}
    bool operator > (MSTEdgeNode<T, K> &R) {return key > R.key;}
};

//最小生成树
template <class T, class K>
class MinSpanTree
{
    protected:
        MSTEdgeNode<T, K> *edgeValue;                                   //边值数组表示树
        int maxSize, currentSize;                                       //数组的最大元素个数和当前个数
    public:
        MinSpanTree(int sz = 10 - 1): maxSize(sz), currentSize(0)       //构造函数
            {edgeValue = new MSTEdgeNode<T, K>[sz]();}
        ~MinSpanTree() {delete[] edgeValue;}                            //析构函数
        bool insert(const MSTEdgeNode<T, K> &item);                     //插入
        template <class M, class N>
        friend ostream &operator << (ostream &out, MinSpanTree<M, N> &MST);
};

//重载输出
template <class T, class K>
ostream &operator << (ostream &out, MinSpanTree<T, K> &M)
{
    for (int i = 0; i < M.currentSize; i++)
        cout << M.edgeValue[i].tail << "->" << M.edgeValue[i].head << endl;
    return out;
}

//将item加入最小生成树
template <class T, class K>
bool MinSpanTree<T, K>::insert(const MSTEdgeNode<T, K> &item)
{
    if (currentSize == maxSize) return false;           //生成树已满
    edgeValue[currentSize++] = item; return true;
}

//Kruskal生成最小树算法
template <class T, class E>
void Kruskal(Graphlnk<T, E> &G, MinSpanTree<T, E> &MST)
{
    MSTEdgeNode<T, E> ed; E cost;
    int u, v, count,                                                //边结点辅助单元
    vertices = G.Vertices(),                                          //顶点数
    edges = G.Edges();                                                //边数
    MinHeap<MSTEdgeNode<T, E>> H(2 * edges);                          //最小堆，管家那么类型为E
    UFSet F(vertices);                                              //并查集
    bool *Vmst = new bool[vertices];
    for (u = 0; u < vertices; u++)
    {
        for (v = u + 1; v < vertices; v++)
        {
            if (cost = G.getWeight(u, v), !Vmst[v] && cost != 0 )
            {
                ed.tail = u; ed.head = v;                           //插入堆
                ed.key = cost; H.insert(ed);
            }
        }
        Vmst[u] = true;                                             //无向图标记去重
    }

    count = 1;                                                      //最小生成树加入边数计数
    while (count < vertices)                                        //反复执行，取n-1条边
    {
        H.removeMin(ed);                                            //从最小堆中退出具有最小权值的边ed
        u = F.find(ed.tail); v = F.find(ed.head);                   //取两顶点所在集合的根u与v
        if (u != v)                                                 //不是同一集合，说明不连通
        {
            F.Union(u, v);                                          //合并，连通它们
            MST.insert(ed); count++;                                //该边存入最小生成树
        }
    }
    delete[] Vmst;
}

//Prim生成最小树算法
template <class T, class E>
void Prim(Graphlnk<T, E> &G, const T start, MinSpanTree<T, E> &MST)
{
    MSTEdgeNode<T, E> ed; E cost;
    int v, count,                                                   //边结点辅助单元
    u = G.getVertexPos(start),                                      //求起始顶点的编号
    vertices = G.Vertices(),                                          //顶点数
    edges = G.Edges();                                                //边数
    MinHeap<MSTEdgeNode<T, E>> H(edges);                            //最小堆， 关键码类型为E
    bool *Vmst = new bool[vertices];                                //最小生成树顶点集合
    memset(Vmst, 0, sizeof(bool) * vertices);
    Vmst[u] = true;                                                 //u加入生成树
    count = 1;
    do
    {
        v = G.getFirstNeighbor(u);
        while (v != -1)                                             //将u的所有邻接顶点加入堆
        {
            if (!Vmst[v])                                           //若v不在生成树，(u, v)加入堆
            {
                ed.tail = u; ed.head = v;
                ed.key = G.getWeight(u, v);                             //tail在树内，head不在树内
                H.insert(ed);
            }
            v = G.getNextNeighbor(u, v);                            //找顶点u的下一个邻接顶点v
        }
        while (!H.isEmpty() && count < vertices)
        {
            H.removeMin(ed);                                        //从堆中退出具有最小权值的边ed
            if (!Vmst[ed.head])
            {
                MST.insert(ed);                                     //未访问过，加入最小生成树
                u = ed.head; Vmst[u] = true;                        //u加入最小生成树顶点集合
                count++; break;
            }
        }
    } while (count < vertices);                                            //选取n-1条边
    delete[] Vmst;
}
#endif  //MINSPANTREE_H