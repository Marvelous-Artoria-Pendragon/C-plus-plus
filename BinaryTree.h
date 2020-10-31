/*����������*/
#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <iostream>
#include "Stack.h"
#include "Queue.h"
using namespace std;

template <class T>
struct BinTreeNode
{
    T data;                 //������
    BinTreeNode<T> *leftChild, *rightChild;          //����Ů������Ů����
    BinTreeNode(): leftChild(NULL), rightChild(NULL){};
    BinTreeNode(T x, BinTreeNode<T> *l = NULL, BinTreeNode<T> *r = NULL)
        : data(x), leftChild(l), rightChild(r){};
};

template <class T>
class BinaryTree
{
    public:
        BinaryTree(): root(NULL){};                                                             //���캯��
        BinaryTree(T value): RefValue(value), root(NULL){};                                     //�趨ֹͣ�����־�Ĺ��캯��
        BinaryTree(BinaryTree<T> &s);                                                           //�������캯��
        ~BinaryTree() {destroy(root);}                                                          //��������
        bool isEmpty() {return (root == NULL ? true : false);}                                  //�ж϶������շ�
        BinTreeNode<T> *Parent(BinTreeNode<T> *current)                                         //���ظ��ڵ�
            {return (root == NULL || root == current) ? NULL : Parent(root, current);}
        BinTreeNode<T> *LeftChild(BinTreeNode<T> *current)                                      //��������Ů
            {return (current != NULL) ? current->leftChild : NULL;}
        BinTreeNode<T> *RightChild(BinTreeNode<T> *current)                                     //��������Ů
            {return (current != NULL) ? current->rigthChild : NULL;}
        int Height(){return Height(root);}                                                      //�������߶�
        int Size() {return Size(root);}                                                         //���ؽ����
        BinTreeNode<T> *getRoot() const{return root;}                                           //���ظ����
        void preOrder(void (*visit)(BinTreeNode<T> *current)) {preOrder(root, visit);}          //ǰ�����
        void inOrder(void (*visit)(BinTreeNode<T> *current)) {inOrder(root, visit);}            //�������
        void postOrder(void (*visit)(BinTreeNode<T> *current)) {postOrder(root, visit);}        //�������
        void leverOrder(void (*visit)(BinTreeNode<T> *current));                                //��α���
        int Insert(const T &item);                                                              //������Ԫ��
        BinTreeNode<T> *Find(T &item) const;                                                    //����
    protected:
        BinTreeNode<T> *root;                                                                   //�������ĸ�ָ��
        T RefValue;                                                                             //��������ֹͣ�ı�־
        void CreateBinTree(istream &in, BinTreeNode<T> *&subTree);                              //ǰ������ݹ齨��
        void CreateBinTreeByList(istream &in, BinTreeNode<T> *&subTree);                        //��������������
        bool Insert(BinTreeNode<T> *&subTree, const T &x);                                      //����
        void destroy(BinTreeNode<T> *&subTree);                                                 //ɾ��
        bool Find(BinTreeNode<T> *subTree, const T &x) const;                                   //����
        BinTreeNode<T> *Copy(BinTreeNode<T> *orignode);                                         //����
        int Height(BinTreeNode<T> *subTree) const;                                              //�������ĸ߶�
        int Size(BinTreeNode<T> *subTree) const;                                                //���ؽ����
        BinTreeNode<T> *Parent(BinTreeNode<T> *subTree, BinTreeNode<T> *current);               //���ظ��ڵ�
        //BinTreeNode<T> *Find(BinTreeNode<T> *subTree, const T &x) const;                       //��Ѱx
        void Traverse(BinTreeNode<T> *subTree, ostream &out);                                   //ǰ��������
        void preOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *current));         //ǰ�����
        void inOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *current));          //�������
        void postOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *current));        //�������
        friend istream &operator >> (istream &in, BinaryTree<T> &Tree);                         //����������
        friend ostream &operator << (ostream &out, BinaryTree<T> &Tree);                        //���������

};

//˽�к�������ָ��subTree��Ϊ�գ���ɾ����ΪsubTree������
template <class T>
void BinaryTree<T>::destroy(BinTreeNode<T> *&subTree)
{
    if (subTree != NULL)
    {
        destroy(current->leftChild);                                //�ݹ�ɾ��subTree��������
        destroy(current->rightChild);                               //�ݹ�ɾ��subTree��������
        delete subtTree;                                            //�ݹ�ɾ��subTree
    }
}

//˽�к������ӽ��subTree��ʼ���������current�ĸ���㡣���ҵ����򷵻ظ�����ַ�����򷵻�NULL
template <class T>
BinTreeNode<T> *BinaryTree<T>::Parent(BinTreeNode<T> *subTree, BinTreeNode<T> *current)
{
    if (subTree == NULL) return NULL;
    if (subTree->leftChild == current || subTree->rightChild == current)
        return subTree;    //�ҵ������ظ����subTree
    BinTreeNode<T> *p;
    if (p = Parent((subTree->leftChild, current)) != NULL) return p;        //�ݹ���������������
    else return Parent((subTree-rightChild, current));                      //�ݹ���������������
}

//˽�к����������������ΪsubTree�Ķ�����
template <class T>
void BinaryTree<T>::Traverse(BinTreeNode<T> *subTree, ostream &out)
{
    if (subTree != NULL)
    {
        out << subTree->data << " ";                //���subTree��ֵ
        Traverse(subTree->leftChild, out);          //�ݹ����������subTree��������
        Traverse(subTree->rightChild, out);          //�ݹ����������subTree��������
    }
}

//���ز��������벢����һ�ö�����Tree,inΪ����������
template <class T>
istream &operator >> (istream &in, BinaryTree<T> &Tree)
{CreateBinTree(in, Tree.root); return in;}

//���ز��������һ�ö�����Tree��out�����������
template <class T>
ostream &operator << (ostream &out, BinaryTree<T> &Tree)
{
    out << "��������ǰ�����\n";
    Tree.Traverse(Tree.root, out);              //�Ӹ���ʼ���
    out << endl; return out;
}

//˽�к�������ǰ������ݹ鷽ʽ����������
template <class T>
void BinaryTree<T>::CreateBinTree(istream &in, BinTreeNode<T> *&subTree)
{
    T value; in >> value;
    if (value != RefValue)
    {
        subTree = new BinTreeNode<T>(value);              //���������
        if (subTree == NULL) {cerr << "�洢�������" << endl; exit(1);}
        CreateBinTree(in, subTree->leftChild);            //�ݹ齨��������
        CreateBinTree(in, subTree->rightChild);           //�ݹ齨��������
    }
    else subTree = NULL;                                  //���ָ���������ָ��
}

//���������ʾ����������
template <class T>
void BinaryTree<T>::CreateBinTreeByList(istream &in, BinTreeNode<T> *&subTree)
{
    Stack<BinTreeNode<T> * > s;
    subTree = NULL;
    BinTreeNode<T> *p, *t; int k;           //kΪ���������������
    T ch; in >> ch;                      //��in˳�����һ���ַ�
    while (ch != RefValue)
    {
        switch (ch)
        {
            case '(': s.Push(p); k = 1; break;          //��������
            case ')': s.Pop(t); break;                  //�˳�����
            case ',': k = 2; break;
        default: p = new BinTreeNode(ch);
            if (p == NULL) {cerr << "�洢�������" << endl; exit(1);}
            if (subTree == NULL) subTree = p;
            else if (k == 1) {s.getTop(t); t->leftChild = p;}               //����*t������Ů
            else {s.getTop(t); t->rightChild = p;}               //����*t������Ů
        }
        in >> ch;
    }
}

//˽�к����������������һ��ָ�룬������һ����orignodeΪ���Ķ������ĸ���
template <class T>
BinTreeNode<T> *BinaryTree<T>::Copy(BinTreeNode<T> *orignode)
{
    if (orignode == NULL) return NULL;                          //��Ϊ�գ����ؿ�ָ��
    BinTreeNode<T> *temp = new BinTreeNode<T>;                  //�����ս��
    if (temp == NULL) {cerr << "�洢�������" << endl; exit(1);}
    temp->data = orignode->data;                                //��������
    temp->leftChild = Copy(orignode->leftChild);                //��������Ů
    temp->rightChild = Copy(orignode->rightChild);              //��������Ů
    return temp;
}

//�ж����ö��������
template <class T>
int operator == (const BinaryTree<T> &s, const BinaryTree<T> &t)
{return (equal(s.root, t.root)) ? true : false;}

//���a��b����������ͬ����������false�����򷵻�true
template <class T>
bool equal(BinTreeNode<T> *a, BinTreeNode<T> *b)
{
    if (a == NULL && b == NULL) return true;                    //���߶�Ϊ��
    if (a !+ NULL && b != NULL && a->data == b->data            //���߸�����������
        && equal(a->leftChild, b->leftChild)                    //����������ͬ
        && equal(a->rightChild, b->rightChild))                 //����������ͬ
    return true;
    else return false;
}

//�ݹ�ǰ�����
template <class T>
void BinaryTree<T>::preOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *current))
{
    if (subTree != NULL)
    {
        visit(subTree);
        preOrder(subtTree->leftChild, visit);
        preOrder(subtTree->rightChild, visit);
    }
}

//�ݹ��������
template <class T>
void BinaryTree<T>::inOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *current))
{
    if (subTree != NULL)
    {
        preOrder(subtTree->leftChild, visit);
        visit(subTree);
        preOrder(subtTree->rightChild, visit);
    }
}

//�ݹ�������
template <class T>
void BinaryTree<T>::postOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *current))
{
    if (subTree != NULL)
    {
        preOrder(subtTree->leftChild, visit);
        preOrder(subtTree->rightChild, visit);
        visit(subTree);
    }
}

template <class T>
void PringBinTreeByList(BinTreeNode<T> *subTree)
{
    if (subTree != NULL)                                //��Ϊ�ս����ݹ�
    {
        cout << subTree->data;                          //���������ֵ
        if (subTree->leftChild != NULL || subTree->rightChild != NULL)
        {
            cout << '(';                                //���������
            PringBinTreeByList(subTree->leftChild);     //�ݹ����������
            cout << ',';
            if (subTree->rightChild != NULL)            //��������Ϊ��
            PringBinTreeByList(subTree->rightChild);    //�ݹ����������
            cout << ')';                                //���������
        }
    }
}

//���ö���ʵ�ֲ�������
template <class T>
void BinaryTree<T>::leverOrder(void (*visit)(BinTreeNode<T> *current))
{
    Queue<BinTreeNode<T> * > Q;
    BinTreeNode<T> *current = root;
    Q.EnQueue(current);
    while (!Q.isEmpty())                                //���в�Ϊ��
    {
        Q.DeQueue(current); visit(current);             //�˳�һ����㣬����
        if (current->leftChild != NULL) Q.EnQueue(current->leftChild);        //����Ů����
        if (current->rightChild != NULL) Q.EnQueue(current->rightChild);      //����Ů����
    }
}

#endif //BINARYTREE_H