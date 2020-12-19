/*�ֱ�д�����ڽӾ�����ڽӱ���ͼ�Ĵ洢�ṹ�����ֱ�ʵʩ������ȱ�����������ȱ�����*/
/*�ڽӾ���*/

#include <iostream>
#include <string.h>
#include "Queue.h"

using namespace std;

struct AdjacencyMatrix
{
    int **Edge;
    int size;                               //��ĸ���
    AdjacencyMatrix(int n);                 //���캯��
    ~AdjacencyMatrix();                     //��������
    int getNextNeighbor(int v, int w);      //���ض���v��ĳ�ڽӶ���w����һ���ڽӶ���
    int getFirstNeighbor(int v);            //���ض���v�ĵ�һ���ڽӶ���
    friend istream &operator >> (istream &in, AdjacencyMatrix &am);
};

AdjacencyMatrix::AdjacencyMatrix(int n)
{
    size = n; Edge = new int *[size];
    for (int i = 0; i < size; i++)          //�����ڽӾ���
    {
        Edge[i] = new int [size];
        memset(Edge[i], 0, sizeof(int) * size);
    }
}

AdjacencyMatrix::~AdjacencyMatrix()
{
    for (int i = 0; i < size; i ++) delete[] Edge[i];  //��������
    delete Edge;
}

istream &operator >> (istream &in, AdjacencyMatrix &am)
{
    int edge, m, n, i = 0;  
    cout << "������ߵĸ�����"; cin >> edge;
    cout << "������ߵ���Ϣ(ÿ��������������(0~n)���ÿո�ָ�)��\n";
    while (i < edge) 
    {
        if (cin >> m >> n, (m > am.size || m < 0) || (n > am.size || n < 0))  //���㲻����
            {cout << "�����˵���������������!\n"; continue;}
        am.Edge[m][n] = am.Edge[n][m] = 1; i++;                               //����Գ�����
    } 
    for (int i = 0; i < am.size; i++)
    {
        for (int j = 0; j < am.size; j++)
            cout << am.Edge[i][j] << " ";
        cout << endl;
    } return in;
}

//���ض���v�ĵ�һ���ڽӶ����λ��
int AdjacencyMatrix::getFirstNeighbor(int v)
{
    if (v != -1)
        for (int col = 0; col < size; col++)
            if (Edge[v][col]) return col;
    return -1;
}


//�ҳ�����v��ĳ�ڽӶ����w����һ���ڽӶ���
int AdjacencyMatrix::getNextNeighbor(int v, int w)
{
    if (v != -1 && w != -1)
    {
        for (int col = w + 1; col < size; col++)
            if (Edge[v][col]) return col;           //�ҵ����ظõ�
    } return -1;                                    //�Ҳ���������-1
}

//����
void dfs(AdjacencyMatrix &am, int v, bool visited[])
{
    cout << v << " ";                                      //���ʶ���v
    visited[v] = true;                                     //�����ʺ�ı��
    int w = am.getFirstNeighbor(v);                        //�ҳ�����v�ĵ�һ���ڽӶ���
    while (w != -1)                                        //�ڽӶ���w����
    {
        if (!visited[w]) dfs(am, w, visited);              //wδ���ʹ����ݹ����w
        w = am.getNextNeighbor(v, w);                      //ȡv����w�������һ���ڽӶ���
    }
}

//����
void bfs(AdjacencyMatrix &am, int v)
{
    int loc = 0, w = 0;
    bool *visited = new bool [am.size];                   //����Ƿ���ʹ�
    memset(visited, 0, sizeof(bool) * am.size);           //��ʼ��ȫΪ��
    cout << v << " ";                                     //���ʶ���v
    visited[v] = true;
    LinkedQueue<int> Q; Q.EnQueue(v);
    while (!Q.isEmpty())
    {
        Q.DeQueue(loc);
        w = am.getFirstNeighbor(loc);                      //ȡ����v�ĵ�һ���ڽӶ���
        while (w != -1)
        {
            if (!visited[w])                               //�ö���δ���ʹ�
            {
                cout << w << " "; visited[w] = true;       //���������ѽ���
                Q.EnQueue(w);
            } w = am.getNextNeighbor(loc, w);              //Ѱ����һ���ڽӶ���
        }
    } delete[] visited;
}

int main()
{
    int n; cout << "�����붥������"; cin >> n;
    AdjacencyMatrix am(n); cin >> am;
    bool *visited = new bool [n];                   //����Ƿ���ʹ�
    memset(visited, 0, sizeof(bool) * n);           //��ʼ��ȫΪ��
    cout << "�����뿪ʼ�����Ķ��㣺"; int v; cin >> v;
    dfs(am, v, visited);                            //�Ӷ���v��ʼ����
    cout << endl;
    bfs(am, v);                                     //�Ӷ���v��ʼ����
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