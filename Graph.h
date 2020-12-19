#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
using namespace std;

//�ߵĶ���
template <class T, class E>
struct Edge
{
    int dest;                                            //�ߵ���һ��
    E cost;                                              //Ȩֵ
    Edge<T, E> *link;                                    //��һ���ߵ���ָ��
    Edge(Edge<T, E> *l = NULL): link(l){};               //���캯��
    Edge(int v, E weight, Edge *l = NULL)                //�����˵㡢Ȩֵ�Ĺ��캯��
        : dest(v), cost(weight), link(l){};
    bool operator != (Edge &R) {return dest != R.dest;}  //�б߲��ȷ�
};

//���㶨��
template <class T, class E>
struct Vertex
{
    T data;                                                                 //��������
    Edge<T, E> *adj;                                                        //��
    Vertex(): adj(NULL){};                                                  //���캯��
    Vertex(const T &item, Edge<T, E> *l = NULL): data(item), adj(l) {};     //���캯��

};

//�ڽӱ��ͼ�Ķ���
template <class T, class E>
class Graphlnk
{
    public:
        Graphlnk(int sz = 20);                                              //���캯��
        ~Graphlnk();                                                        //��������
        T getValue(int i)                                                   //ȡλ��Ϊi�Ķ����е�ֵ
            {return (i >= 0 && i < numVertices) ? NodeTable[i].data : 0;}
        E getWeight(int v1, int v2);                                        //���ر�(v1, v2)�ϵ�Ȩֵ
        // bool insertVertex(const T &vertex);                                 //��ͼ�в���һ������vertex
        // bool removeVertex(int v);                                           //��ͼ��ɾ��һ������v
        // bool insertEdge(int v1, int v2, E cost);                            //��ͼ�в���һ����(v1, v2)
        // bool removeEdge(int v1, int v2);                                    //��ͼ��ɾ��һ����
        int getVertexPos(const T& vertex);                                   //��������vertex��ͼ�е�λ��
        int getFirstNeighbor(int v);                                        //ȡ����v�ĵ�һ���ڽӶ���
        int getNextNeighbor(int v, int w);                                  //ȡv���ڽӶ���w����һ�ڽӶ���
        int Vertices(){return numVertices;}                                 //���ض�����
        int Edges(){return numEdges;}                                       //���ر���
        template <class M, class N>
        friend istream &operator >> (istream &in, Graphlnk<M, N> &G);       //����
    private:
        Vertex<T, E> *NodeTable;                                            //�����
        int numVertices;                                                    //��ǰ������
        int numEdges;                                                       //��ǰ����
        int maxVertices;                                                    //��󶥵���
};

//���캯��������һ���յ��ڽӱ�
template <class T, class E>
Graphlnk<T, E>::Graphlnk(int sz)
{
    maxVertices = sz; numVertices = 0; numEdges = 0;
    NodeTable = new Vertex<T, E>[maxVertices]();                              //�������������
    if (NodeTable == NULL) {cerr << "�����洢�������" << endl; exit(1);}
}

//����������ɾ��һ���ڽӱ�
template <class T, class E>
Graphlnk<T, E>::~Graphlnk()
{
    for (int i = 0; i < numVertices; i++)                                   //ɾ�����������еĽ��
    {
        Edge<T, E> *p = NodeTable[i].adj;                                   //�ҵ����Ӧ��������׽ڵ�
        while (p != NULL)
        {NodeTable[i].adj = p->link; delete p; p = NodeTable[i].adj;}
    } delete[] NodeTable;
}

//��������
template <class T, class E>
istream &operator >> (istream &in, Graphlnk<T, E> &G)
{
    cout << "�����붥������" << endl; cin >> G.numVertices;
    cout << "��ֱ�������������Ϣ��" << endl;
    for (int i = 0; i < G.numVertices; i++)
        cin >> G.NodeTable[i].data;
    
    cout << "������ߵĸ���: ";
    int edge, m, n, w, i = 0; cin >> edge; G.numEdges = edge;
    cout << "������ߵ���Ϣ(ÿ��������������(0~n)�Լ�Ȩ�أ��ÿո�ָ�)��\n";
    Edge<T, E> *newEdge = NULL;
    while (i < edge)
    {
        if (cin >> m >> n >> w, (m > edge || m < 0) || (n > edge || n < 0))
            {cout << "�������������������룡\n"; continue;}
        newEdge = new Edge<T, E>(n, w, G.NodeTable[m].adj);      //ͷ���뷨����m->n�ı�
        G.NodeTable[m].adj = newEdge;
        newEdge = new Edge<T, E>(m, w, G.NodeTable[n].adj);      //ͷ���뷨����n->m�ı�
        G.NodeTable[n].adj = newEdge;
        i++;
    } return in;
}

//��������vertex��ͼ�е�λ��
template <class T, class E>
int Graphlnk<T, E>::getVertexPos(const T& vertex)
{
    for (int i = 0; i < numVertices; i++)                           //####ʹ�ù�ϣ���Ч��
        if (NodeTable[i].data == vertex) return i;
    return -1;
}
//��������λ��Ϊv�ĵ�һ���ڽӶ����λ�ã�����Ҳ�������������-1
template <class T, class E>
int Graphlnk<T, E>::getFirstNeighbor(int v)
{
    if (v != -1)                                                            //����v����
    {
        Edge<T, E> *p = NodeTable[v].adj;                                   //��Ӧ������ĵ�һ���߽��
        if (p != NULL) return p->dest;                                      //���ڣ����ص�һ���ڽӶ���
    } return -1;                                                            //��һ���ڽӶ��㲻����
}

//��������v���ڽӶ���w����һ���ڽӶ����λ�ã���û����һ���ڽӶ��㣬��������-1
template <class T, class E>
int Graphlnk<T, E>::getNextNeighbor(int v, int w)
{
    if (v != -1)                                                            //����v����
    {
        Edge<T, E> *p = NodeTable[v].adj;                                   //��Ӧ������ĵ�һ���߽��
        while (p != NULL && p->dest != w) p = p->link;                      //Ѱ���ڽӶ���w
        if (p != NULL && p->link != NULL)                                   //���ڣ����ص�һ���ڽӶ���
            return p->link->dest;
    } return -1;                                                            //��һ���ڽӶ��㲻����
}

//�������ر�(v1, v2)�ϵ�Ȩֵ�����ñ߲���ͼ�У���������Ȩֵ0
template <class T, class E>
E Graphlnk<T, E>::getWeight(int v1, int v2)
{
    if (v1 != -1 && v2 != -1)
    {
        Edge<T, E> *p = NodeTable[v1].adj;                                  //v1�ĵ�һ�������ı�
        while (p != NULL && p->dest != v2) p = p->link;                     //Ѱ���ڽӶ���v2
        if (p != NULL) return p->cost;                                      //�ҵ������ߣ�����Ȩֵ
    } return 0;                                                             //��(v1, v2)������
}

/*
//��ͼ�Ķ�����в���һ���¶���vertex
template <class T, class E>
bool Graphlnk<T, E>::insertVertex(const T &vertex)
{
    if (numVertices == maxVertices) return false;                           //������������ܲ���
    NodeTable[numVertices].data = vertex;                                   //�����ڱ�����
    numVertices++; return true;
}
*/

#endif  //GRAPH_H