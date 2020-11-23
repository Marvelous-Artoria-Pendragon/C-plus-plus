/*
1.编写一个将二叉链式结构存储的二叉树的所有叶子结点从左向右链接成单链表的算法。
*/

#include "BinaryTree.h"
/*
//对一棵树的所有叶子结点，从左往右连接成一条单链表
//current为树的根结点，last为链表表头首地址
template <class T>
void BinaryTree<T>::leafLinkedList(BinTreeNode<T> *current, LinkNode<T> *&last)
{
    if (current == NULL) return;
    if (current->leftChild == NULL && current->rightChild == NULL)                  //均无左右子女为叶子结点
    {
        LinkNode<T> *newNode = new LinkNode<T>(current->data);
        if (newNode == NULL) {cerr << "存储分配错误！" << endl; exit(1);}
        last->link = newNode;
        last = last->link;
    }
    else
    {
        leafLinkedList(current->leftChild, last);                              //递归对左子树叶子结点建链
        leafLinkedList(current->rightChild, last);                             //递归对右子树叶子结点建链
    }
}
*/

int main()
{
    BinaryTree<char> BT('.');
    cout << "请输入前序表达式(空结点用'.'表示)：";
    cin >> BT;  //ABC..DE.G..F...
    cout << BT;
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