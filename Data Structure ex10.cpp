/*
给定一棵二叉树，判断其是否为二叉搜索树
*/

#include "BinaryTree.h"

//层次遍历判断是否二叉树是否为二叉搜索树
template <class T>
bool isBST(BinTreeNode<T> *subTree)
{
    if (subTree == NULL) return false;                                      //树为空
    LinkedQueue<BinTreeNode<T> *> Q; BinTreeNode<T> *current = subTree;
    Q.EnQueue(current);
    while (!Q.isEmpty())                                //队列不为空
    {
        Q.DeQueue(current); 
        if (current->leftChild != NULL) 
        {
            if (current->leftChild->data >= current->data) return false;      //左子女的值大于等于父结点
            else Q.EnQueue(current->leftChild);      //左子女进队
        }
        
        if (current->rightChild != NULL)
        {
            if (current->rightChild->data <= current->data) return false;     //右子女的值小于等于父结点
            else Q.EnQueue(current->leftChild);      //左子女进队
        }
    } return true;                  //全部结点符合要求，返回true
}

int main()
{
    BinaryTree<int> BT(-1);
    cout << "请输入前序表达式(空结点用'-1'表示)：";
    cin >> BT;        
    //是：53 17 9 -1 -1 45 23 -1 -1 -1 78 65 -1 -1 87 81 -1 -1 94 -1 -1
    //不是：53 45 23 -1 -1 9 -1 -1 78 81 -1 -1 65 94 -1 -1 -1
    cout << BT;
    BinTreeNode<int> *root = BT.getRoot();
    if (isBST(root)) cout << "是二叉搜索树" << endl;
    else cout << "不是二叉搜索树" << endl;

    system("pause");
    return 0;
}