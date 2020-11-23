/*
����һ�ö��������ж����Ƿ�Ϊ����������
*/

#include "BinaryTree.h"

//��α����ж��Ƿ�������Ƿ�Ϊ����������
template <class T>
bool isBST(BinTreeNode<T> *subTree)
{
    if (subTree == NULL) return false;                                      //��Ϊ��
    LinkedQueue<BinTreeNode<T> *> Q; BinTreeNode<T> *current = subTree;
    Q.EnQueue(current);
    while (!Q.isEmpty())                                //���в�Ϊ��
    {
        Q.DeQueue(current); 
        if (current->leftChild != NULL) 
        {
            if (current->leftChild->data >= current->data) return false;      //����Ů��ֵ���ڵ��ڸ����
            else Q.EnQueue(current->leftChild);      //����Ů����
        }
        
        if (current->rightChild != NULL)
        {
            if (current->rightChild->data <= current->data) return false;     //����Ů��ֵС�ڵ��ڸ����
            else Q.EnQueue(current->leftChild);      //����Ů����
        }
    } return true;                  //ȫ��������Ҫ�󣬷���true
}

int main()
{
    BinaryTree<int> BT(-1);
    cout << "������ǰ����ʽ(�ս����'-1'��ʾ)��";
    cin >> BT;        
    //�ǣ�53 17 9 -1 -1 45 23 -1 -1 -1 78 65 -1 -1 87 81 -1 -1 94 -1 -1
    //���ǣ�53 45 23 -1 -1 9 -1 -1 78 81 -1 -1 65 94 -1 -1 -1
    cout << BT;
    BinTreeNode<int> *root = BT.getRoot();
    if (isBST(root)) cout << "�Ƕ���������" << endl;
    else cout << "���Ƕ���������" << endl;

    system("pause");
    return 0;
}