/*
1.��дһ����������ʽ�ṹ�洢�Ķ�����������Ҷ�ӽ������������ӳɵ�������㷨��
*/

#include <iostream>
#include "BinaryTree.h"
using namespace std;

int main()
{
    BinaryTree<char> BT('.');
    cout << "������ǰ����ʽ(�ս����'.'��ʾ)��";
    cin >> BT;  //ABC..DE.G..F...
    cout << "����ǰ����ʽΪ��" << endl << BT;
    BinTreeNode<char> *root = BT.getRoot();
    LinkNode<char> *l = new LinkNode<char>;             //�����׵�ַ(����ͷ)
    LinkNode<char> *current = l;      //���ڱ�������
    BT.leafLinkedList(root, current);
    current = l;
    while (current != NULL)
    {
        cout << current->data << " ";
        current = current->link;
    }

    LinkNode<char> *del;
    while (l != NULL)
    {
        del = l;
        l = l->link;
        delete del;
    }
    system("pause");
    return 0;
}