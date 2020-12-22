/*分别写出用邻接矩阵和邻接表做图的存储结构，并分别实施广度优先遍历和深度优先遍历。*/
/*邻接矩阵*/

#include <iostream>
#include <string.h>
#include "Queue.h"

using namespace std;

struct AdjacencyMatrix
{
    int **Edge;
    int size;                               //点的个数
    AdjacencyMatrix(int n);                 //构造函数
    ~AdjacencyMatrix();                     //析构函数
    int getNextNeighbor(int v, int w);      //返回顶点v的某邻接顶点w的下一个邻接顶点
    int getFirstNeighbor(int v);            //返回顶点v的第一个邻接顶点
    friend istream &operator >> (istream &in, AdjacencyMatrix &am);
};

AdjacencyMatrix::AdjacencyMatrix(int n)
{
    size = n; Edge = new int *[size];
    for (int i = 0; i < size; i++)          //创建邻接矩阵
    {
        Edge[i] = new int [size];
        memset(Edge[i], 0, sizeof(int) * size);
    }
}

AdjacencyMatrix::~AdjacencyMatrix()
{
    for (int i = 0; i < size; i ++) delete[] Edge[i];  //遍历析构
    delete Edge;
}

istream &operator >> (istream &in, AdjacencyMatrix &am)
{
    int edge, m, n, i = 0;  
    cout << "请输入边的个数："; cin >> edge;
    cout << "请输入边的信息(每行输入两个顶点(0~n)，用空格分隔)：\n";
    while (i < edge) 
    {
        if (cin >> m >> n, (m > am.size || m < 0) || (n > am.size || n < 0))  //顶点不存在
            {cout << "边两端点有误，请重新输入!\n"; continue;}
        am.Edge[m][n] = am.Edge[n][m] = 1; i++;                               //矩阵对称输入
    } 
    for (int i = 0; i < am.size; i++)
    {
        for (int j = 0; j < am.size; j++)
            cout << am.Edge[i][j] << " ";
        cout << endl;
    } return in;
}

//返回顶点v的第一个邻接顶点的位置
int AdjacencyMatrix::getFirstNeighbor(int v)
{
    if (v != -1)
        for (int col = 0; col < size; col++)
            if (Edge[v][col]) return col;
    return -1;
}


//找出顶点v的某邻接顶点的w的下一个邻接顶点
int AdjacencyMatrix::getNextNeighbor(int v, int w)
{
    if (v != -1 && w != -1)
    {
        for (int col = w + 1; col < size; col++)
            if (Edge[v][col]) return col;           //找到返回该点
    } return -1;                                    //找不到，返回-1
}

//深搜
void dfs(AdjacencyMatrix &am, int v, bool visited[])
{
    cout << v << " ";                                      //访问顶点v
    visited[v] = true;                                     //做访问后的标记
    int w = am.getFirstNeighbor(v);                        //找出顶点v的第一个邻接顶点
    while (w != -1)                                        //邻接顶点w存在
    {
        if (!visited[w]) dfs(am, w, visited);              //w未访问过，递归访问w
        w = am.getNextNeighbor(v, w);                      //取v排在w后面的下一个邻接顶点
    }
}

//广搜
void bfs(AdjacencyMatrix &am, int v)
{
    int loc = 0, w = 0;
    bool *visited = new bool [am.size];                   //标记是否访问过
    memset(visited, 0, sizeof(bool) * am.size);           //初始化全为假
    cout << v << " ";                                     //访问顶点v
    visited[v] = true;
    LinkedQueue<int> Q; Q.EnQueue(v);
    while (!Q.isEmpty())
    {
        Q.DeQueue(loc);
        w = am.getFirstNeighbor(loc);                      //取顶点v的第一个邻接顶点
        while (w != -1)
        {
            if (!visited[w])                               //该顶点未访问过
            {
                cout << w << " "; visited[w] = true;       //输出并标记已进队
                Q.EnQueue(w);
            } w = am.getNextNeighbor(loc, w);              //寻找下一个邻接顶点
        }
    } delete[] visited;
}

int main()
{
    int n; cout << "请输入顶点数："; cin >> n;
    AdjacencyMatrix am(n); cin >> am;
    bool *visited = new bool [n];                   //标记是否访问过
    memset(visited, 0, sizeof(bool) * n);           //初始化全为假
    cout << "请输入开始遍历的顶点："; int v; cin >> v;
    dfs(am, v, visited);                            //从顶点v开始深搜
    cout << endl;
    bfs(am, v);                                     //从顶点v开始广搜
    delete[] visited;
    
    system("pause");
    return 0;
}

/*
6
5
1 2
1 5
3 5
4 5
3 0
*/