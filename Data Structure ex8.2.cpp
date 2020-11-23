/*设具有 n 个结点的二叉树采用二叉链式存储结构，试写出一个算法将该二叉链式存储结构转换为顺序存储结构。*/

#include "BinaryTree.h"

/*
//将二叉链式结构转换成顺序存储结构
//arr为引用返回数组，n为引用返回数组大小
template <class T>
void BinaryTree<T>::toLinearBinaryTree(BinTreeNode<T> *subTree, T *&arr, int &n) const
{
    LinkedQueue<BinTreeNode<T> * > Q;
    LinkedQueue<int> index;                             //存放结点在数组中表示的序号
    BinTreeNode<T> *current = subTree;
    int h = Height(), count = 0;                        //h为树的高度，count为当前处理的结点的标号
    n = pow(2, h) - 1; arr = new T[n];                  //n为数组大小
    for (int i = 0; i < n; i++) arr[i] = 0;
    Q.EnQueue(current); index.EnQueue(count);
    while (!Q.isEmpty())                                //队列不为空
    {
        Q.DeQueue(current); index.DeQueue(count); arr[count] = current->data;
        if (current->leftChild != NULL)                         //左子女进队
        {Q.EnQueue(current->leftChild); index.EnQueue(2 * count + 1);}
        if (current->rightChild != NULL)                        //右子女进队
        {Q.EnQueue(current->rightChild); index.EnQueue(2 * count + 2);}
    }
}
*/

int main()
{
    BinaryTree<char> BT('.');
    cout << "请输入前序表达式(空结点用'.'表示)：";
    cin >> BT;        //ABD..E.GH..I..C.F..
    cout << BT;
    BinTreeNode<char> *root = BT.getRoot();
    char *L; int n;
    BT.toLinearBinaryTree(root, L, n);
    cout << "\tdata " << endl;
    for (int i = 0; i < n; i++)
        cout << i << ": " << L[i] << endl;
    system("pause");
    return 0;
}