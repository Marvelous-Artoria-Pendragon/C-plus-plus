/*写出求一顶点到其余各个顶点的最短路径的程序*/
#include <iostream>
#include "Graph.h"
#include <string.h>
using namespace std;

const int maxValue = 0xffff;                                //题目中不会出现的最大值

//Dijkstra算法求最短路径
//Graph是一个带权有向图。
//v为路径开始的顶点
//dist[j], 0<=j<n, 是当前求到的从顶点v到顶点j的最短路径长度，同时用数组path[j], 0<=j<n, 存放求到的最短路径
template <class T, class E>
void ShortestPath(Graphlnk<T, E> &G, T v, E *dist, int *path)
{
    int vertices = G.Vertices();                                //顶点数
    bool *Vmst = new bool[vertices];                            //最短路径顶点集
    memset(Vmst, 0, sizeof(bool) * vertices);
    int i, j, k; E w, min, temp;                                //遍历变量i,j,k, w为权值，min记录当前最小的权值
    for (i = 0; i < vertices; i++)
    {
        temp = G.getWeight(v, i);
        dist[i] = temp == 0 ? maxValue : temp;                  //数组权值初始化,无法直接到达的权值设置为无穷大
        if (i != v && dist[i] != 0) path[i] = v;                //可以直接到达，前一个顶点设为v
        else path[i] = -1;                                      //无法直接到达的前一个顶点先设为-1
    }

    Vmst[v] = true; dist[v] = 0;                                //顶点v加入顶点集合
    for (i = 0; i < vertices - 1; i++)
    {
        min = maxValue; int u = v;                              //选不在Vmst中具有最短路径的顶点u
        for (j = 0; j < vertices; j++)                          //找出该点最小的一条边
            if (Vmst[j] == false && dist[j] < min) {u = j; min = dist[j];}
        Vmst[u] = true;                                         //将顶点u加入集合Vmst
        for (k = 0; k < vertices; k++)                          //修改
        {
            w = G.getWeight(u, k);
            if (!Vmst[k] && w != 0 && dist[u] + w < dist[k])    //顶点k为加入Vmst，且绕过u可以缩短路径
                {dist[k] = dist[u] + w; path[k] = u;}           //修改到k的最短路径
        }
    } delete[] Vmst;
}

//从path数组读取最短路径的算法
template <class T, class E>
void printShortestPath(Graphlnk<T, E> &G, int v, E *dist, int *path)
{
    cout << "从顶点" << G.getValue(v) << "到其他各顶点的最短路径为：" << endl;
    int i, j, k, vertices = G.Vertices();                                       //遍历变量、顶点数
    int *d = new int [vertices];                                                //记录寻找某顶点最短路径的栈
    for (i = 0; i < vertices; i++)
    {
        if (i != v)
        {
            j = i, k = 0;                                                       //j指示i最短路径的前一个顶点，k指示栈当前位置
            while (j != v) {d[k++] = j; j = path[j];}
            cout << "顶点" << G.getValue(i) << "的最短路径为:" << G.getValue(v) << " ";
            while (k > 0) cout << G.getValue(d[--k]) << " "; 
            cout << "最短路径长度为：" << dist[i] << endl;
        }
    } delete[] d;
}

int main()
{
    Graphlnk<int, int> G(20, true); cin >> G;
    int dist[7], path[7];
    ShortestPath(G, 0, dist, path);             //求顶点0到其它各顶点的最短路径
    printShortestPath(G, 0, dist, path);        //打印最短路径及长度
    system("pause");
    return 0;
}

/*
5
0 1 2 3 4
7
0 1 10
0 3 30
0 4 100
1 2 50
2 4 10
3 2 20
3 4 60

*/