/*
给定一棵二叉树，判断其是否为二叉搜索树
*/

#include "BinaryTree.h"

//层次遍历判断是否二叉树是否为二叉搜索树
template <class T>
bool isBST(BinTreeNode<T> *subTree)
{
    if (subTree == NULL) return true;
    SeqStack<BinTreeNode<T> *> s; BinTreeNode<T> *p = subTree; s.push(p); //根进栈
    T *pre = NULL;                                                      //记录前一个结点的值
    do
    {
        while (p != NULL) {s.push(p); p = p->leftChild;}
        if (!s.isEmpty()) 
        {
            s.pop(p); cout << p->data << " ";
            if (pre == NULL) pre = &(p->data);
            else if (p->data <= *pre) return false;                      //不满足中序遍历值递增的条件
            p = p->rightChild;
        }
    } while (!s.isEmpty() || p != NULL);
     return true;                  //全部结点符合要求，返回true
}

int main()
{
    BinaryTree<int> BT(-1);
    cout << "请输入前序表达式(空结点用'-1'表示)：";
    cin >> BT;        
    //是：53 17 9 -1 -1 45 23 -1 -1 -1 78 65 -1 -1 87 81 -1 -1 94 -1 -1
    //不是：53 45 23 -1 -1 9 -1 -1 78 81 -1 -1 65 94 -1 -1 -1
    cout << BT;
    BinTreeNode<int> *root = BT.getRoot(); int a = INT_MIN;
    if (isBST(root)) cout << "是二叉搜索树" << endl;
    else cout << "不是二叉搜索树" << endl;

    system("pause");
    return 0;
}