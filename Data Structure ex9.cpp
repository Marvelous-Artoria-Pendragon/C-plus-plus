/*
已知一棵完全二叉树存放于一个一维数组T[n]中，T[n]中存放的是各结点的值。
试设计一个算法，从T[0]开始顺序读出各结点的值，建立该二叉树的二叉链表表示
*/

#include "CompleteBinaryTree.h"

//item为完全二叉树的顺序存储结构，subTree为建树根结点，n为新建结点数
template <class T>
void CreateBinTree(T *item, BinTreeNode<T> *&subTree, int n)
{
    LinkedQueue<BinTreeNode<T> *> Q;                                        //设置结点数
    subTree = new BinTreeNode<T>(item[0]); if (subTree == NULL) {cerr << "存储分配错误！" << endl; exit(1);}    //新建根结点
    BinTreeNode<T> *temp = subTree, *newNode = NULL; int cnt = 1;           //对新建结点计数
    Q.EnQueue(temp);                                                        //根结点先进队
    while (cnt < n)
    {
        if (++cnt & 1) Q.DeQueue(temp);                                     //新建右子女才退队
        else Q.getFront(temp);
        newNode = new BinTreeNode<T>(item[cnt - 1]); if (newNode == NULL) {cerr << "存储分配错误！" << endl; exit(1);}
        Q.EnQueue(newNode);                            //左/右子女进队
        temp->child[cnt & 1] = newNode;                                     //新结点入树
    }
}

//删除
template <class T>
void destroy(BinTreeNode<T> *&subTree)
{
    if (subTree != NULL)
    {
        destroy(subTree->child[0]);                                //递归删除subTree的左子树
        destroy(subTree->child[1]);                                //递归删除subTree的右子树
        delete subTree;                                            //递归删除subTree
    }
}

//递归前序遍历输出
template <class T>
void preOrder(BinTreeNode<T> *subTree)
{
    if (subTree != NULL)
    {
        cout << subTree->data << " ";
        preOrder(subTree->child[0]);
        preOrder(subTree->child[1]);
    }
}

int main()
{
    cout << "请输入n："; int n = 0; cin >> n;
    int *T = new int[n];
    cout << "请分别输入各个值：\n";
    for (int i = 0; i < n; i++) cin >> T[i];
    BinTreeNode<int> *root = NULL;
    CreateBinTree(T, root, n);          //建树
    preOrder(root);                     //输出
    destroy(root);                      //析构
    system("pause");
    return 0;
}