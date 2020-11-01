/*
1.编写一个将二叉链式结构存储的二叉树的所有叶子结点从左向右链接成单链表的算法。
*/

#include "BinaryTree.h"
int main()
{
    BinaryTree<char> BT('.');
    cout << "请输入前序表达式(空结点用'.'表示)：";
    cin >> BT;  //ABC..DE.G..F...
    cout << "树的前序表达式为：" << endl << BT;
    BinTreeNode<char> *root = BT.getRoot();
    LinkNode<char> *l = new LinkNode<char>, *current = l;             //链表首地址(带表头)
    BT.leafLinkedList(root, current);
    current = l;
    while (current != NULL)                     //循环输出叶子链表
    {
        cout << current->data << " ";
        current = current->link;
    }
    LinkNode<char> *del;
    while (l != NULL)                           //循环删除叶子链表
    {
        del = l;
        l = l->link;
        delete del;
    }
    system("pause");
    return 0;
}