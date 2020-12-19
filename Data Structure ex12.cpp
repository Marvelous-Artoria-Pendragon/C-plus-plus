/*分别写出用邻接矩阵和邻接表做图的存储结构，并分别实施广度优先遍历和深度优先遍历。*/
/*邻接表*/
#include <iostream>
#include <string.h>
#include "Queue.h"
using namespace std;

#define DefaultSize 20
//边的定义
struct Edge
{
    int dest;                   //边的另一端
    int cost;                   //权值
    Edge *link;                 //下一条边的链指针
    Edge(Edge *l = NULL): link(l){};                                //构造函数
    Edge(int v, int weight, Edge *l = NULL)                         //给定端点、权值的构造函数
        : dest(v), cost(weight), link(l){};
    bool operator != (Edge &R) {return dest != R.dest;}             //判边不等否
};

//顶点定义
struct Vertex
{
    int v;                                  //顶点编号
    Edge *adj;                              //边
    Vertex(): v(0), adj(NULL){};            //构造函数
};

//邻接表定义(无向图)
struct AdjacencyList
{
    Vertex *NodeTable;                      //顶点表
    int numVertices;                        //顶点数
    AdjacencyList(int sz = DefaultSize);    //构造函数
    ~AdjacencyList();                       //析构函数
    int getFirstNeighbor(int v);            //返回顶点v的某邻接顶点w的下一个邻接顶点
    int getNextNeighbor(int v, int w);      //返回顶点v的第一个邻接顶点
    friend istream &operator >> (istream &in, AdjacencyList &aj);       //重载输入流
};

istream &operator >> (istream &in, AdjacencyList &aj)
{
    cout << "请输入边的个数: ";
    int edge, m, n, w, i = 0; cin >> edge;
    cout << "请输入边的信息(每行输入两个顶点(0~n)以及权重，用空格分隔)：\n";
    Edge *newEdge = NULL;
    while (i < edge)
    {
        if (cin >> m >> n >> w, (m > edge || m < 0) || (n > edge || n < 0))
            {cout << "边两端有误，请重新输入！\n"; continue;}
        newEdge = new Edge(n, w, aj.NodeTable[m].adj);      //头插入法链入m->n的边
        aj.NodeTable[m].adj = newEdge;
        newEdge = new Edge(m, w, aj.NodeTable[n].adj);      //头插入法链入n->m的边
        aj.NodeTable[n].adj = newEdge;
        i++;
    } return in;
}

//构造函数
AdjacencyList::AdjacencyList(int sz)
{
    NodeTable = new Vertex[sz](); numVertices = sz;
    for (int i = 0; i < sz; i++) 
    {NodeTable[i].v = i; NodeTable[i].adj = NULL;}          //初始化
}

//析构函数
AdjacencyList::~AdjacencyList()
{
    Edge *p = NULL;
    for (int i = 0; i < numVertices; i++) 
    {
        p = NodeTable[i].adj;
        while (p != NULL)
        {NodeTable[i].adj = p->link; delete p; p = NodeTable[i].adj;}
    } delete[] NodeTable;
}

//深搜
void dfs(AdjacencyList &aj, int v, bool *visited)
{
    cout << v << " "; visited[v] = true;                            //访问
    Edge *p = aj.NodeTable[v].adj;
    while (p != NULL)
    {
        if (!visited[p->dest]) dfs(aj, p->dest, visited);
        p = p->link;
    }
}

//广搜
void bfs(AdjacencyList &aj, int v)
{
    bool *visited = new bool [aj.numVertices];                          //标记是否进队过
    memset(visited, 0, sizeof(bool) * aj.numVertices);                  //初始化全为假
    LinkedQueue<Vertex> Q;
    Edge *p = NULL; Vertex temp = aj.NodeTable[v];
    Q.EnQueue(temp); visited[v] = true;                                 //标记已进队
    while (!Q.isEmpty())
    {
        Q.DeQueue(temp);                                                //退队
        cout << temp.v << " "; p = temp.adj;                            //访问
        while (p != NULL)                                               //遍历该顶点所有的邻接顶点
        {
            if (!visited[p->dest]) Q.EnQueue(aj.NodeTable[p->dest]);    //不为空且未进队
            visited[p->dest] = true; p = p->link;
        }
    } delete[] visited;
}

int main()
{
    cout << "请输入顶点数："; 
    int n, v; cin >> n;
    AdjacencyList aj(n); cin >> aj;
    bool *visited = new bool [n];                   //标记是否访问过
    memset(visited, 0, sizeof(bool) * n);           //初始化全为假
    cout << "请输入开始遍历的顶点:"; cin >> v;
    dfs(aj, v, visited);                            //从顶点v开始深搜
    cout << endl;
    bfs(aj, v);                                     //从顶点v开始广搜
    delete[] visited;
    system("pause");
    return 0;
}
/*
6
5
1 2 3
1 5 4
3 5 5
4 5 4
3 0 6
*/
