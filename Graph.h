#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
using namespace std;

//边的定义
template <class T, class E>
struct Edge
{
    int dest;                                            //边的另一端
    E cost;                                              //权值
    Edge<T, E> *link;                                    //下一条边的链指针
    Edge(Edge<T, E> *l = NULL): link(l){};               //构造函数
    Edge(int v, E weight, Edge *l = NULL)                //给定端点、权值的构造函数
        : dest(v), cost(weight), link(l){};
    bool operator != (Edge &R) {return dest != R.dest;}  //判边不等否
};

//顶点定义
template <class T, class E>
struct Vertex
{
    T data;                                                                 //顶点名字
    Edge<T, E> *adj;                                                        //边
    Vertex(): adj(NULL){};                                                  //构造函数
    Vertex(const T &item, Edge<T, E> *l = NULL): data(item), adj(l) {};     //构造函数

};

//邻接表的图的定义
template <class T, class E>
class Graphlnk
{
    public:
        Graphlnk(int sz = 20);                                              //构造函数
        ~Graphlnk();                                                        //析构函数
        T getValue(int i)                                                   //取位置为i的顶点中的值
            {return (i >= 0 && i < numVertices) ? NodeTable[i].data : 0;}
        E getWeight(int v1, int v2);                                        //返回边(v1, v2)上的权值
        // bool insertVertex(const T &vertex);                                 //在图中插入一个顶点vertex
        // bool removeVertex(int v);                                           //在图中删除一个顶点v
        // bool insertEdge(int v1, int v2, E cost);                            //在图中插入一条边(v1, v2)
        // bool removeEdge(int v1, int v2);                                    //在图中删除一条边
        int getVertexPos(const T& vertex);                                   //给出顶点vertex在图中的位置
        int getFirstNeighbor(int v);                                        //取顶点v的第一个邻接顶点
        int getNextNeighbor(int v, int w);                                  //取v的邻接顶点w的下一邻接顶点
        int Vertices(){return numVertices;}                                 //返回顶点数
        int Edges(){return numEdges;}                                       //返回边数
        template <class M, class N>
        friend istream &operator >> (istream &in, Graphlnk<M, N> &G);       //输入
    private:
        Vertex<T, E> *NodeTable;                                            //顶点表
        int numVertices;                                                    //当前顶点数
        int numEdges;                                                       //当前边数
        int maxVertices;                                                    //最大顶点数
};

//构造函数：建立一个空的邻接表
template <class T, class E>
Graphlnk<T, E>::Graphlnk(int sz)
{
    maxVertices = sz; numVertices = 0; numEdges = 0;
    NodeTable = new Vertex<T, E>[maxVertices]();                              //创建顶点表数组
    if (NodeTable == NULL) {cerr << "顶点表存储分配错误！" << endl; exit(1);}
}

//析构函数：删除一个邻接表
template <class T, class E>
Graphlnk<T, E>::~Graphlnk()
{
    for (int i = 0; i < numVertices; i++)                                   //删除各边链表中的结点
    {
        Edge<T, E> *p = NodeTable[i].adj;                                   //找到其对应边链表的首节点
        while (p != NULL)
        {NodeTable[i].adj = p->link; delete p; p = NodeTable[i].adj;}
    } delete[] NodeTable;
}

//重载输入
template <class T, class E>
istream &operator >> (istream &in, Graphlnk<T, E> &G)
{
    cout << "请输入顶点数：" << endl; cin >> G.numVertices;
    cout << "请分别输入各顶点的信息：" << endl;
    for (int i = 0; i < G.numVertices; i++)
        cin >> G.NodeTable[i].data;
    
    cout << "请输入边的个数: ";
    int edge, m, n, w, i = 0; cin >> edge; G.numEdges = edge;
    cout << "请输入边的信息(每行输入两个顶点(0~n)以及权重，用空格分隔)：\n";
    Edge<T, E> *newEdge = NULL;
    while (i < edge)
    {
        if (cin >> m >> n >> w, (m > edge || m < 0) || (n > edge || n < 0))
            {cout << "边两端有误，请重新输入！\n"; continue;}
        newEdge = new Edge<T, E>(n, w, G.NodeTable[m].adj);      //头插入法链入m->n的边
        G.NodeTable[m].adj = newEdge;
        newEdge = new Edge<T, E>(m, w, G.NodeTable[n].adj);      //头插入法链入n->m的边
        G.NodeTable[n].adj = newEdge;
        i++;
    } return in;
}

//给出顶点vertex在图中的位置
template <class T, class E>
int Graphlnk<T, E>::getVertexPos(const T& vertex)
{
    for (int i = 0; i < numVertices; i++)                           //####使用哈希提高效率
        if (NodeTable[i].data == vertex) return i;
    return -1;
}
//给出顶点位置为v的第一个邻接顶点的位置，如果找不到，则函数返回-1
template <class T, class E>
int Graphlnk<T, E>::getFirstNeighbor(int v)
{
    if (v != -1)                                                            //顶点v存在
    {
        Edge<T, E> *p = NodeTable[v].adj;                                   //对应边链表的第一个边结点
        if (p != NULL) return p->dest;                                      //存在，返回第一个邻接顶点
    } return -1;                                                            //第一个邻接顶点不存在
}

//给出顶点v的邻接顶点w的下一个邻接顶点的位置，若没有下一个邻接顶点，则函数返回-1
template <class T, class E>
int Graphlnk<T, E>::getNextNeighbor(int v, int w)
{
    if (v != -1)                                                            //顶点v存在
    {
        Edge<T, E> *p = NodeTable[v].adj;                                   //对应边链表的第一个边结点
        while (p != NULL && p->dest != w) p = p->link;                      //寻找邻接顶点w
        if (p != NULL && p->link != NULL)                                   //存在，返回第一个邻接顶点
            return p->link->dest;
    } return -1;                                                            //第一个邻接顶点不存在
}

//函数返回边(v1, v2)上的权值，若该边不再图中，则函数返回权值0
template <class T, class E>
E Graphlnk<T, E>::getWeight(int v1, int v2)
{
    if (v1 != -1 && v2 != -1)
    {
        Edge<T, E> *p = NodeTable[v1].adj;                                  //v1的第一条关联的边
        while (p != NULL && p->dest != v2) p = p->link;                     //寻找邻接顶点v2
        if (p != NULL) return p->cost;                                      //找到这条边，返回权值
    } return 0;                                                             //边(v1, v2)不存在
}

/*
//在图的顶点表中插入一个新顶点vertex
template <class T, class E>
bool Graphlnk<T, E>::insertVertex(const T &vertex)
{
    if (numVertices == maxVertices) return false;                           //顶点表满，不能插入
    NodeTable[numVertices].data = vertex;                                   //插入在表的最后
    numVertices++; return true;
}
*/

#endif  //GRAPH_H