/*����� n �����Ķ��������ö�����ʽ�洢�ṹ����д��һ���㷨���ö�����ʽ�洢�ṹת��Ϊ˳��洢�ṹ��*/

#include "BinaryTree.h"

/*
//��������ʽ�ṹת����˳��洢�ṹ���������������׵�ַ;
//index��ǵ�ǰ����ڼ���Ԫ��
template <class T>
LinearBinTreeNode<T> *BinaryTree<T>::toLinearBinaryTree(BinTreeNode<T> *current) const
{
    if (current == NULL) return NULL;                                               //�����Ϊ�գ����ؿ�
    LinkedQueue<BinTreeNode<T> *> traverse;                                         //��α���ÿ��������
    LinkedQueue<int> parent;                                                        //��Ÿ����Ķ���
    int count = 0, currentindex = 0, temp = 0, size = Size();                       //countͳ�ƽ������currentindexΪ��ǰ����Ľ��
    LinearBinTreeNode<T> *arr = new LinearBinTreeNode<T>[size]();
    traverse.EnQueue(current);                                                      //�Ӹ���㿪ʼ���д���
    parent.EnQueue(-1);                                                             //������޸��ڵ㣬-1����
    while (!traverse.isEmpty())                                                     //���в�Ϊ��
    {
        traverse.DeQueue(current); parent.DeQueue(temp);                            //�˳�һ����㣬
        arr[currentindex].data = current->data; arr[currentindex].parent = temp;
        if (current->leftChild != NULL) 
        {
            traverse.EnQueue(current->leftChild);                                   //����Ů����
            arr[currentindex].leftChild = ++count;                                  //���ڵ������Ů����
            parent.EnQueue(currentindex);                                           //�ý���Ϊ����Ů�ĸ��ڵ�
        }
        if (current->rightChild != NULL)
        {
            traverse.EnQueue(current->rightChild);                                  //����Ů����
            arr[currentindex].rightChild = ++count;                                 //���ڵ������Ů����
            parent.EnQueue(currentindex);                                           //�ý���Ϊ����Ů�ĸ��ڵ�
        }
        currentindex++;
    }
    return arr;
}
*/

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
        cout << L[i].data << "\t" << L[i].parent << "\t" << L[i].leftChild << "\t" << L[i].rightChild << endl;
    system("pause");
    return 0;
}