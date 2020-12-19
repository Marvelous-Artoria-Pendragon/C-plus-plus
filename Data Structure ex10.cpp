/*
����һ�ö��������ж����Ƿ�Ϊ����������
*/

#include "BinaryTree.h"

//��α����ж��Ƿ�������Ƿ�Ϊ����������
template <class T>
bool isBST(BinTreeNode<T> *subTree)
{
    if (subTree == NULL) return true;
    SeqStack<BinTreeNode<T> *> s; BinTreeNode<T> *p = subTree; s.push(p); //����ջ
    T *pre = NULL;                                                      //��¼ǰһ������ֵ
    do
    {
        while (p != NULL) {s.push(p); p = p->leftChild;}
        if (!s.isEmpty()) 
        {
            s.pop(p); cout << p->data << " ";
            if (pre == NULL) pre = &(p->data);
            else if (p->data <= *pre) return false;                      //�������������ֵ����������
            p = p->rightChild;
        }
    } while (!s.isEmpty() || p != NULL);
     return true;                  //ȫ��������Ҫ�󣬷���true
}

int main()
{
    BinaryTree<int> BT(-1);
    cout << "������ǰ����ʽ(�ս����'-1'��ʾ)��";
    cin >> BT;        
    //�ǣ�53 17 9 -1 -1 45 23 -1 -1 -1 78 65 -1 -1 87 81 -1 -1 94 -1 -1
    //���ǣ�53 45 23 -1 -1 9 -1 -1 78 81 -1 -1 65 94 -1 -1 -1
    cout << BT;
    BinTreeNode<int> *root = BT.getRoot(); int a = INT_MIN;
    if (isBST(root)) cout << "�Ƕ���������" << endl;
    else cout << "���Ƕ���������" << endl;

    system("pause");
    return 0;
}