/*����� n �����Ķ��������ö�����ʽ�洢�ṹ����д��һ���㷨���ö�����ʽ�洢�ṹת��Ϊ˳��洢�ṹ��*/

#include "BinaryTree.h"

int main()
{
    BinaryTree<char> BT('.');
    cout << "������ǰ����ʽ(�ս����'.'��ʾ)��";
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