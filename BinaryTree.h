/*二叉链表树*/
#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <iostream>
#include "Stack.h"
#include "Queue.h"
using namespace std;

template <class T>
struct BinTreeNode
{
    T data;                 //数据域
    BinTreeNode<T> *leftChild, *rightChild;          //左子女，右子女链域
    BinTreeNode(): leftChild(NULL), rightChild(NULL){};
    BinTreeNode(T x, BinTreeNode<T> *l = NULL, BinTreeNode<T> *r = NULL)
        : data(x), leftChild(l), rightChild(r){};
};

template <class T>
class BinaryTree
{
    public:
        BinaryTree(): root(NULL){};                                                             //构造函数
        BinaryTree(T value): RefValue(value), root(NULL){};                                     //设定停止输入标志的构造函数
        BinaryTree(BinaryTree<T> &s);                                                           //拷贝构造函数
        ~BinaryTree() {destroy(root);}                                                          //析构函数
        bool isEmpty() {return (root == NULL ? true : false);}                                  //判断二叉树空否
        BinTreeNode<T> *Parent(BinTreeNode<T> *current)                                         //返回父节点
            {return (root == NULL || root == current) ? NULL : Parent(root, current);}
        BinTreeNode<T> *LeftChild(BinTreeNode<T> *current)                                      //返回左子女
            {return (current != NULL) ? current->leftChild : NULL;}
        BinTreeNode<T> *RightChild(BinTreeNode<T> *current)                                     //返回右子女
            {return (current != NULL) ? current->rigthChild : NULL;}
        int Height(){return Height(root);}                                                      //返回树高度
        int Size() {return Size(root);}                                                         //返回结点数
        BinTreeNode<T> *getRoot() const{return root;}                                           //返回根结点
        void preOrder(void (*visit)(BinTreeNode<T> *current)) {preOrder(root, visit);}          //前序遍历
        void inOrder(void (*visit)(BinTreeNode<T> *current)) {inOrder(root, visit);}            //中序遍历
        void postOrder(void (*visit)(BinTreeNode<T> *current)) {postOrder(root, visit);}        //后序遍历
        void leverOrder(void (*visit)(BinTreeNode<T> *current));                                //层次遍历
        int Insert(const T &item);                                                              //插入新元素
        BinTreeNode<T> *Find(T &item) const;                                                    //搜索
    protected:
        BinTreeNode<T> *root;                                                                   //二叉树的根指针
        T RefValue;                                                                             //数据输入停止的标志
        void CreateBinTree(istream &in, BinTreeNode<T> *&subTree);                              //前序遍历递归建树
        void CreateBinTreeByList(istream &in, BinTreeNode<T> *&subTree);                        //根据输入广义表建树
        bool Insert(BinTreeNode<T> *&subTree, const T &x);                                      //插入
        void destroy(BinTreeNode<T> *&subTree);                                                 //删除
        bool Find(BinTreeNode<T> *subTree, const T &x) const;                                   //查找
        BinTreeNode<T> *Copy(BinTreeNode<T> *orignode);                                         //复制
        int Height(BinTreeNode<T> *subTree) const;                                              //返回数的高度
        int Size(BinTreeNode<T> *subTree) const;                                                //返回结点数
        BinTreeNode<T> *Parent(BinTreeNode<T> *subTree, BinTreeNode<T> *current);               //返回父节点
        //BinTreeNode<T> *Find(BinTreeNode<T> *subTree, const T &x) const;                       //搜寻x
        void Traverse(BinTreeNode<T> *subTree, ostream &out);                                   //前序遍历输出
        void preOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *current));         //前序遍历
        void inOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *current));          //中序遍历
        void postOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *current));        //中序遍历
        friend istream &operator >> (istream &in, BinaryTree<T> &Tree);                         //重载输入流
        friend ostream &operator << (ostream &out, BinaryTree<T> &Tree);                        //重载输出流

};

//私有函数：若指针subTree不为空，则删除根为subTree的子树
template <class T>
void BinaryTree<T>::destroy(BinTreeNode<T> *&subTree)
{
    if (subTree != NULL)
    {
        destroy(current->leftChild);                                //递归删除subTree的左子树
        destroy(current->rightChild);                               //递归删除subTree的右子树
        delete subtTree;                                            //递归删除subTree
    }
}

//私有函数：从结点subTree开始，搜索结点current的父结点。若找到，则返回父结点地址，否则返回NULL
template <class T>
BinTreeNode<T> *BinaryTree<T>::Parent(BinTreeNode<T> *subTree, BinTreeNode<T> *current)
{
    if (subTree == NULL) return NULL;
    if (subTree->leftChild == current || subTree->rightChild == current)
        return subTree;    //找到，返回父结点subTree
    BinTreeNode<T> *p;
    if (p = Parent((subTree->leftChild, current)) != NULL) return p;        //递归在左子树中搜索
    else return Parent((subTree-rightChild, current));                      //递归在右子树中搜索
}

//私有函数：搜索并输出根为subTree的二叉树
template <class T>
void BinaryTree<T>::Traverse(BinTreeNode<T> *subTree, ostream &out)
{
    if (subTree != NULL)
    {
        out << subTree->data << " ";                //输出subTree的值
        Traverse(subTree->leftChild, out);          //递归搜索并输出subTree的左子树
        Traverse(subTree->rightChild, out);          //递归搜索并输出subTree的右子树
    }
}

//重载操作：输入并建立一棵二叉树Tree,in为输入流对象
template <class T>
istream &operator >> (istream &in, BinaryTree<T> &Tree)
{CreateBinTree(in, Tree.root); return in;}

//重载操作：输出一棵二叉树Tree，out是输出流对象
template <class T>
ostream &operator << (ostream &out, BinaryTree<T> &Tree)
{
    out << "二叉树的前序遍历\n";
    Tree.Traverse(Tree.root, out);              //从根开始输出
    out << endl; return out;
}

//私有函数：以前序遍历递归方式建立二叉树
template <class T>
void BinaryTree<T>::CreateBinTree(istream &in, BinTreeNode<T> *&subTree)
{
    T value; in >> value;
    if (value != RefValue)
    {
        subTree = new BinTreeNode<T>(value);              //建立根结点
        if (subTree == NULL) {cerr << "存储分配错误！" << endl; exit(1);}
        CreateBinTree(in, subTree->leftChild);            //递归建立左子树
        CreateBinTree(in, subTree->rightChild);           //递归建立右子树
    }
    else subTree = NULL;                                  //封闭指向空子树的指针
}

//输入广义表表示建立二叉树
template <class T>
void BinaryTree<T>::CreateBinTreeByList(istream &in, BinTreeNode<T> *&subTree)
{
    Stack<BinTreeNode<T> * > s;
    subTree = NULL;
    BinTreeNode<T> *p, *t; int k;           //k为处理左、右子树标记
    T ch; in >> ch;                      //从in顺序读入一个字符
    while (ch != RefValue)
    {
        switch (ch)
        {
            case '(': s.Push(p); k = 1; break;          //进入子树
            case ')': s.Pop(t); break;                  //退出子树
            case ',': k = 2; break;
        default: p = new BinTreeNode(ch);
            if (p == NULL) {cerr << "存储分配错误！" << endl; exit(1);}
            if (subTree == NULL) subTree = p;
            else if (k == 1) {s.getTop(t); t->leftChild = p;}               //链入*t的左子女
            else {s.getTop(t); t->rightChild = p;}               //链入*t的右子女
        }
        in >> ch;
    }
}

//私有函数：这个函数返回一个指针，它给出一个以orignode为根的二叉树的副本
template <class T>
BinTreeNode<T> *BinaryTree<T>::Copy(BinTreeNode<T> *orignode)
{
    if (orignode == NULL) return NULL;                          //根为空，返回空指针
    BinTreeNode<T> *temp = new BinTreeNode<T>;                  //创建空结点
    if (temp == NULL) {cerr << "存储分配错误！" << endl; exit(1);}
    temp->data = orignode->data;                                //传送数据
    temp->leftChild = Copy(orignode->leftChild);                //复制左子女
    temp->rightChild = Copy(orignode->rightChild);              //复制右子女
    return temp;
}

//判断两棵二叉树相等
template <class T>
int operator == (const BinaryTree<T> &s, const BinaryTree<T> &t)
{return (equal(s.root, t.root)) ? true : false;}

//如果a和b的子树不等同，则函数返回false，否则返回true
template <class T>
bool equal(BinTreeNode<T> *a, BinTreeNode<T> *b)
{
    if (a == NULL && b == NULL) return true;                    //两者都为空
    if (a !+ NULL && b != NULL && a->data == b->data            //两者跟结点数据相等
        && equal(a->leftChild, b->leftChild)                    //且左子树相同
        && equal(a->rightChild, b->rightChild))                 //且右子树相同
    return true;
    else return false;
}

//递归前序遍历
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

//递归中序遍历
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

//递归后序遍历
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
    if (subTree != NULL)                                //树为空结束递归
    {
        cout << subTree->data;                          //输出根结点的值
        if (subTree->leftChild != NULL || subTree->rightChild != NULL)
        {
            cout << '(';                                //输出左括号
            PringBinTreeByList(subTree->leftChild);     //递归输出左子树
            cout << ',';
            if (subTree->rightChild != NULL)            //右子树不为空
            PringBinTreeByList(subTree->rightChild);    //递归输出右子树
            cout << ')';                                //输出右括号
        }
    }
}

//利用队列实现层次序遍历
template <class T>
void BinaryTree<T>::leverOrder(void (*visit)(BinTreeNode<T> *current))
{
    Queue<BinTreeNode<T> * > Q;
    BinTreeNode<T> *current = root;
    Q.EnQueue(current);
    while (!Q.isEmpty())                                //队列不为空
    {
        Q.DeQueue(current); visit(current);             //退出一个结点，访问
        if (current->leftChild != NULL) Q.EnQueue(current->leftChild);        //左子女进队
        if (current->rightChild != NULL) Q.EnQueue(current->rightChild);      //右子女进队
    }
}

#endif //BINARYTREE_H