/*
1.��дһ����������ʽ�ṹ�洢�Ķ�����������Ҷ�ӽ������������ӳɵ�������㷨��
*/

#include "BinaryTree.h"
int main()
{
    BinaryTree<char> BT('.');
    cout << "������ǰ����ʽ(�ս����'.'��ʾ)��";
    cin >> BT;  //ABC..DE.G..F...
    cout << "����ǰ����ʽΪ��" << endl << BT;
    BinTreeNode<char> *root = BT.getRoot();
    LinkNode<char> *l = new LinkNode<char>, *current = l;             //�����׵�ַ(����ͷ)
    BT.leafLinkedList(root, current);
    current = l;
    while (current != NULL)                     //ѭ�����Ҷ������
    {
        cout << current->data << " ";
        current = current->link;
    }
    LinkNode<char> *del;
    while (l != NULL)                           //ѭ��ɾ��Ҷ������
    {
        del = l;
        l = l->link;
        delete del;
    }
    system("pause");
    return 0;
}