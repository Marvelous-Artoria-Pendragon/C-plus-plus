/*设具有 n 个结点的二叉树采用二叉链式存储结构，试写出一个算法将该二叉链式存储结构转换为顺序存储结构。*/

#include "BinaryTree.h"

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
    {
        cout << L[i].data << "\t" << L[i].parent << "\t" << L[i].leftChild << "\t" << L[i].rightChild << endl;
    }
    system("pause");
    return 0;
}