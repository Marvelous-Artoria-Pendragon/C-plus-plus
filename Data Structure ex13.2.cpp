/*д����һ���㵽���������������·���ĳ���*/
#include <iostream>
#include "Graph.h"
#include <string.h>
using namespace std;

const int maxValue = 0xffff;                                //��Ŀ�в�����ֵ����ֵ

//Dijkstra�㷨�����·��
//Graph��һ����Ȩ����ͼ��
//vΪ·����ʼ�Ķ���
//dist[j], 0<=j<n, �ǵ�ǰ�󵽵ĴӶ���v������j�����·�����ȣ�ͬʱ������path[j], 0<=j<n, ����󵽵����·��
template <class T, class E>
void ShortestPath(Graphlnk<T, E> &G, T v, E *dist, int *path)
{
    int vertices = G.Vertices();                                //������
    bool *Vmst = new bool[vertices];                            //���·�����㼯
    memset(Vmst, 0, sizeof(bool) * vertices);
    int i, j, k; E w, min, temp;                                //��������i,j,k, wΪȨֵ��min��¼��ǰ��С��Ȩֵ
    for (i = 0; i < vertices; i++)
    {
        temp = G.getWeight(v, i);
        dist[i] = temp == 0 ? maxValue : temp;                  //����Ȩֵ��ʼ��,�޷�ֱ�ӵ����Ȩֵ����Ϊ�����
        if (i != v && dist[i] != 0) path[i] = v;                //����ֱ�ӵ��ǰһ��������Ϊv
        else path[i] = -1;                                      //�޷�ֱ�ӵ����ǰһ����������Ϊ-1
    }

    Vmst[v] = true; dist[v] = 0;                                //����v���붥�㼯��
    for (i = 0; i < vertices - 1; i++)
    {
        min = maxValue; int u = v;                              //ѡ����Vmst�о������·���Ķ���u
        for (j = 0; j < vertices; j++)                          //�ҳ��õ���С��һ����
            if (Vmst[j] == false && dist[j] < min) {u = j; min = dist[j];}
        Vmst[u] = true;                                         //������u���뼯��Vmst
        for (k = 0; k < vertices; k++)                          //�޸�
        {
            w = G.getWeight(u, k);
            if (!Vmst[k] && w != 0 && dist[u] + w < dist[k])    //����kΪ����Vmst�����ƹ�u��������·��
                {dist[k] = dist[u] + w; path[k] = u;}           //�޸ĵ�k�����·��
        }
    } delete[] Vmst;
}

//��path�����ȡ���·�����㷨
template <class T, class E>
void printShortestPath(Graphlnk<T, E> &G, int v, E *dist, int *path)
{
    cout << "�Ӷ���" << G.getValue(v) << "����������������·��Ϊ��" << endl;
    int i, j, k, vertices = G.Vertices();                                       //����������������
    int *d = new int [vertices];                                                //��¼Ѱ��ĳ�������·����ջ
    for (i = 0; i < vertices; i++)
    {
        if (i != v)
        {
            j = i, k = 0;                                                       //jָʾi���·����ǰһ�����㣬kָʾջ��ǰλ��
            while (j != v) {d[k++] = j; j = path[j];}
            cout << "����" << G.getValue(i) << "�����·��Ϊ:" << G.getValue(v) << " ";
            while (k > 0) cout << G.getValue(d[--k]) << " "; 
            cout << "���·������Ϊ��" << dist[i] << endl;
        }
    } delete[] d;
}

int main()
{
    Graphlnk<int, int> G(20, true); cin >> G;
    int dist[7], path[7];
    ShortestPath(G, 0, dist, path);             //�󶥵�0����������������·��
    printShortestPath(G, 0, dist, path);        //��ӡ���·��������
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