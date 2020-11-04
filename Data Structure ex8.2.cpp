/*设具有 n 个结点的二叉树采用二叉链式存储结构，试写出一个算法将该二叉链式存储结构转换为顺序存储结构。*/

#include "BinaryTree.h"

/*
//将二叉链式结构转换成顺序存储结构，函数返回数组首地址;
//index标记当前数组第几个元素
template <class T>
LinearBinTreeNode<T> *BinaryTree<T>::toLinearBinaryTree(BinTreeNode<T> *current) const
{
    if (current == NULL) return NULL;                                               //根结点为空，返回空
    LinkedQueue<BinTreeNode<T> *> traverse;                                         //层次遍历每个结点队列
    LinkedQueue<int> parent;                                                        //存放父结点的队列
    int count = 0, currentindex = 0, temp = 0, size = Size();                       //count统计结点数，currentindex为当前处理的结点
    LinearBinTreeNode<T> *arr = new LinearBinTreeNode<T>[size]();
    traverse.EnQueue(current);                                                      //从根结点开始队列处理
    parent.EnQueue(-1);                                                             //根结点无父节点，-1进队
    while (!traverse.isEmpty())                                                     //队列不为空
    {
        traverse.DeQueue(current); parent.DeQueue(temp);                            //退出一个结点，
        arr[currentindex].data = current->data; arr[currentindex].parent = temp;
        if (current->leftChild != NULL) 
        {
            traverse.EnQueue(current->leftChild);                                   //左子女进队
            arr[currentindex].leftChild = ++count;                                  //父节点的左子女索引
            parent.EnQueue(currentindex);                                           //该结点成为其子女的父节点
        }
        if (current->rightChild != NULL)
        {
            traverse.EnQueue(current->rightChild);                                  //右子女进队
            arr[currentindex].rightChild = ++count;                                 //父节点的右子女索引
            parent.EnQueue(currentindex);                                           //该结点成为其子女的父节点
        }
        currentindex++;
    }
    return arr;
}
*/

int main()
{
    BinaryTree<char> BT('.');
    cout << "请输入前序表达式(空结点用'.'表示)：";
    cin >> BT;        //ABD..E.GH..I..C.F..
    cout << BT;
    BinTreeNode<char> *root = BT.getRoot();
    LinearBinTreeNode<char> *L = BT.toLinearBinaryTree(root);
    int n = 9;
    cout << "data " << "parent " << "leftChild " << "rightChild " << endl;
    for (int i = 0; i < n; i++)
        cout << L[i].data << "\t" << L[i].parent << "\t" << L[i].leftChild << "\t" << L[i].rightChild << endl;
    system("pause");
    return 0;
}