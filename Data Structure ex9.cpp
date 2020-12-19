/*
��֪һ����ȫ�����������һ��һά����T[n]�У�T[n]�д�ŵ��Ǹ�����ֵ��
�����һ���㷨����T[0]��ʼ˳�����������ֵ�������ö������Ķ��������ʾ
*/

#include "CompleteBinaryTree.h"

//itemΪ��ȫ��������˳��洢�ṹ��subTreeΪ��������㣬nΪ�½������
template <class T>
void CreateBinTree(T *item, BinTreeNode<T> *&subTree, int n)
{
    LinkedQueue<BinTreeNode<T> *> Q;                                        //���ý����
    subTree = new BinTreeNode<T>(item[0]); if (subTree == NULL) {cerr << "�洢�������" << endl; exit(1);}    //�½������
    BinTreeNode<T> *temp = subTree, *newNode = NULL; int cnt = 1;           //���½�������
    Q.EnQueue(temp);                                                        //������Ƚ���
    while (cnt < n)
    {
        if (++cnt & 1) Q.DeQueue(temp);                                     //�½�����Ů���˶�
        else Q.getFront(temp);
        newNode = new BinTreeNode<T>(item[cnt - 1]); if (newNode == NULL) {cerr << "�洢�������" << endl; exit(1);}
        Q.EnQueue(newNode);                            //��/����Ů����
        temp->child[cnt & 1] = newNode;                                     //�½������
    }
}

//ɾ��
template <class T>
void destroy(BinTreeNode<T> *&subTree)
{
    if (subTree != NULL)
    {
        destroy(subTree->child[0]);                                //�ݹ�ɾ��subTree��������
        destroy(subTree->child[1]);                                //�ݹ�ɾ��subTree��������
        delete subTree;                                            //�ݹ�ɾ��subTree
    }
}

//�ݹ�ǰ��������
template <class T>
void preOrder(BinTreeNode<T> *subTree)
{
    if (subTree != NULL)
    {
        cout << subTree->data << " ";
        preOrder(subTree->child[0]);
        preOrder(subTree->child[1]);
    }
}

int main()
{
    cout << "������n��"; int n = 0; cin >> n;
    int *T = new int[n];
    cout << "��ֱ��������ֵ��\n";
    for (int i = 0; i < n; i++) cin >> T[i];
    BinTreeNode<int> *root = NULL;
    CreateBinTree(T, root, n);          //����
    preOrder(root);                     //���
    destroy(root);                      //����
    system("pause");
    return 0;
}