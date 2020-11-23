/*
1.��дһ����������ʽ�ṹ�洢�Ķ�����������Ҷ�ӽ������������ӳɵ�������㷨��
*/

#include "BinaryTree.h"
/*
//��һ����������Ҷ�ӽ�㣬�����������ӳ�һ��������
//currentΪ���ĸ���㣬lastΪ�����ͷ�׵�ַ
template <class T>
void BinaryTree<T>::leafLinkedList(BinTreeNode<T> *current, LinkNode<T> *&last)
{
    if (current == NULL) return;
    if (current->leftChild == NULL && current->rightChild == NULL)                  //����������ŮΪҶ�ӽ��
    {
        LinkNode<T> *newNode = new LinkNode<T>(current->data);
        if (newNode == NULL) {cerr << "�洢�������" << endl; exit(1);}
        last->link = newNode;
        last = last->link;
    }
    else
    {
        leafLinkedList(current->leftChild, last);                              //�ݹ��������Ҷ�ӽ�㽨��
        leafLinkedList(current->rightChild, last);                             //�ݹ��������Ҷ�ӽ�㽨��
    }
}
*/

int main()
{
    BinaryTree<char> BT('.');
    cout << "������ǰ����ʽ(�ս����'.'��ʾ)��";
    cin >> BT;  //ABC..DE.G..F...
    cout << BT;
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