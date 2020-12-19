/*�ֱ�д�����ڽӾ�����ڽӱ���ͼ�Ĵ洢�ṹ�����ֱ�ʵʩ������ȱ�����������ȱ�����*/
/*�ڽӱ�*/
#include <iostream>
#include <string.h>
#include "Queue.h"
using namespace std;

#define DefaultSize 20
//�ߵĶ���
struct Edge
{
    int dest;                   //�ߵ���һ��
    int cost;                   //Ȩֵ
    Edge *link;                 //��һ���ߵ���ָ��
    Edge(Edge *l = NULL): link(l){};                                //���캯��
    Edge(int v, int weight, Edge *l = NULL)                         //�����˵㡢Ȩֵ�Ĺ��캯��
        : dest(v), cost(weight), link(l){};
    bool operator != (Edge &R) {return dest != R.dest;}             //�б߲��ȷ�
};

//���㶨��
struct Vertex
{
    int v;                                  //������
    Edge *adj;                              //��
    Vertex(): v(0), adj(NULL){};            //���캯��
};

//�ڽӱ���(����ͼ)
struct AdjacencyList
{
    Vertex *NodeTable;                      //�����
    int numVertices;                        //������
    AdjacencyList(int sz = DefaultSize);    //���캯��
    ~AdjacencyList();                       //��������
    int getFirstNeighbor(int v);            //���ض���v��ĳ�ڽӶ���w����һ���ڽӶ���
    int getNextNeighbor(int v, int w);      //���ض���v�ĵ�һ���ڽӶ���
    friend istream &operator >> (istream &in, AdjacencyList &aj);       //����������
};

istream &operator >> (istream &in, AdjacencyList &aj)
{
    cout << "������ߵĸ���: ";
    int edge, m, n, w, i = 0; cin >> edge;
    cout << "������ߵ���Ϣ(ÿ��������������(0~n)�Լ�Ȩ�أ��ÿո�ָ�)��\n";
    Edge *newEdge = NULL;
    while (i < edge)
    {
        if (cin >> m >> n >> w, (m > edge || m < 0) || (n > edge || n < 0))
            {cout << "�������������������룡\n"; continue;}
        newEdge = new Edge(n, w, aj.NodeTable[m].adj);      //ͷ���뷨����m->n�ı�
        aj.NodeTable[m].adj = newEdge;
        newEdge = new Edge(m, w, aj.NodeTable[n].adj);      //ͷ���뷨����n->m�ı�
        aj.NodeTable[n].adj = newEdge;
        i++;
    } return in;
}

//���캯��
AdjacencyList::AdjacencyList(int sz)
{
    NodeTable = new Vertex[sz](); numVertices = sz;
    for (int i = 0; i < sz; i++) 
    {NodeTable[i].v = i; NodeTable[i].adj = NULL;}          //��ʼ��
}

//��������
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

//����
void dfs(AdjacencyList &aj, int v, bool *visited)
{
    cout << v << " "; visited[v] = true;                            //����
    Edge *p = aj.NodeTable[v].adj;
    while (p != NULL)
    {
        if (!visited[p->dest]) dfs(aj, p->dest, visited);
        p = p->link;
    }
}

//����
void bfs(AdjacencyList &aj, int v)
{
    bool *visited = new bool [aj.numVertices];                          //����Ƿ���ӹ�
    memset(visited, 0, sizeof(bool) * aj.numVertices);                  //��ʼ��ȫΪ��
    LinkedQueue<Vertex> Q;
    Edge *p = NULL; Vertex temp = aj.NodeTable[v];
    Q.EnQueue(temp); visited[v] = true;                                 //����ѽ���
    while (!Q.isEmpty())
    {
        Q.DeQueue(temp);                                                //�˶�
        cout << temp.v << " "; p = temp.adj;                            //����
        while (p != NULL)                                               //�����ö������е��ڽӶ���
        {
            if (!visited[p->dest]) Q.EnQueue(aj.NodeTable[p->dest]);    //��Ϊ����δ����
            visited[p->dest] = true; p = p->link;
        }
    } delete[] visited;
}

int main()
{
    cout << "�����붥������"; 
    int n, v; cin >> n;
    AdjacencyList aj(n); cin >> aj;
    bool *visited = new bool [n];                   //����Ƿ���ʹ�
    memset(visited, 0, sizeof(bool) * n);           //��ʼ��ȫΪ��
    cout << "�����뿪ʼ�����Ķ���:"; cin >> v;
    dfs(aj, v, visited);                            //�Ӷ���v��ʼ����
    cout << endl;
    bfs(aj, v);                                     //�Ӷ���v��ʼ����
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
