/*
设二叉树采用二叉链表表示，指针root指向根结点，试编写一个在二叉树中查找值为x的结点，并打印该结点所有祖先结点的算法。
在此算法中，假设值为x的结点不多于一个
*/
#include "BinaryTree.h"
int main()
{
    BinaryTree<char> BT('.');
    /*
    cout << "请输入前序表达式(空结点用'.'表示)：";
    cin >> BT;  //ABC..DE.G..F...
    cout << "树的前序表达式为：" << endl << BT;
    SeqStack<BinTreeNode<char> * > s;                               //用于存储所有祖先结点
    BinTreeNode<char> *root = BT.getRoot();
    BT.findAncestors(root, 'E', s);
    cout << "该结点的所有祖先结点的值为：" << endl;
    while (!s.isEmpty())            //循环输出储存的结点的值
    {
        BinTreeNode<char> *temp = NULL;
        s.pop(temp);
        cout << temp->data << " ";
    }
    */
    /*
    BT.CreateBinTreeByList(cin);        //A(B(C,D(E(G),F)))
    BinTreeNode<char> *root = BT.getRoot();
    BT.PringBinTreeByList(root);
    */
    system("pause");
    return 0;
}