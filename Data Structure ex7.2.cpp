/*
����������ö��������ʾ��ָ��rootָ�����㣬�Ա�дһ���ڶ������в���ֵΪx�Ľ�㣬����ӡ�ý���������Ƚ����㷨��
�ڴ��㷨�У�����ֵΪx�Ľ�㲻����һ��
*/
#include "BinaryTree.h"
int main()
{
    BinaryTree<char> BT('.');
    /*
    cout << "������ǰ����ʽ(�ս����'.'��ʾ)��";
    cin >> BT;  //ABC..DE.G..F...
    cout << "����ǰ����ʽΪ��" << endl << BT;
    SeqStack<BinTreeNode<char> * > s;                               //���ڴ洢�������Ƚ��
    BinTreeNode<char> *root = BT.getRoot();
    BT.findAncestors(root, 'E', s);
    cout << "�ý����������Ƚ���ֵΪ��" << endl;
    while (!s.isEmpty())            //ѭ���������Ľ���ֵ
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