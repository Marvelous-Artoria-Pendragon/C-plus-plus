/*����� n �����Ķ��������ö�����ʽ�洢�ṹ����д��һ���㷨���ö�����ʽ�洢�ṹת��Ϊ˳��洢�ṹ��*/

#include "BinaryTree.h"

/*
//��������ʽ�ṹת����˳��洢�ṹ
//arrΪ���÷������飬nΪ���÷��������С
template <class T>
void BinaryTree<T>::toLinearBinaryTree(BinTreeNode<T> *subTree, T *&arr, int &n) const
{
    LinkedQueue<BinTreeNode<T> * > Q;
    LinkedQueue<int> index;                             //��Ž���������б�ʾ�����
    BinTreeNode<T> *current = subTree;
    int h = Height(), count = 0;                        //hΪ���ĸ߶ȣ�countΪ��ǰ����Ľ��ı��
    n = pow(2, h) - 1; arr = new T[n];                  //nΪ�����С
    for (int i = 0; i < n; i++) arr[i] = 0;
    Q.EnQueue(current); index.EnQueue(count);
    while (!Q.isEmpty())                                //���в�Ϊ��
    {
        Q.DeQueue(current); index.DeQueue(count); arr[count] = current->data;
        if (current->leftChild != NULL)                         //����Ů����
        {Q.EnQueue(current->leftChild); index.EnQueue(2 * count + 1);}
        if (current->rightChild != NULL)                        //����Ů����
        {Q.EnQueue(current->rightChild); index.EnQueue(2 * count + 2);}
    }
}
*/

int main()
{
    BinaryTree<char> BT('.');
    cout << "������ǰ����ʽ(�ս����'.'��ʾ)��";
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