/*һ�þ��� n ��������ȫ����������ڶ�������˳��洢�ṹ�У��Ա�д�ǵݹ��㷨�Ը��������������*/
#include "BinaryTree.h"
#include <math.h>
/*
template <class T>
LinearBinTreeNode<T> * createCompleteLinearBinaryTree(int n)
{

    LinearBinTreeNode<T> *arr = new LinearBinTreeNode[n];
    int parent = -1, t = pow(2, n - 1);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i].data;
        arr[i].parent = (i - 1) / 2;
        if (i < t);                                 //���һ��������Ů���
        {
            arr[i].leftChild = 2 * i + 1;
            arr[i].rightChild = 2 * i + 2;
        }
    }
    return arr;
}
*/

/*
//�Զ�������˳��洢�ṹ��ʹ�÷ǵݹ鷽ʽʵ���������
template <class T>
void preOrder(LinearBinTreeNode<T> *arr, void (*visit)(LinearBinTreeNode<T> &))
{
    SeqStack<int> s; int p = 0;                              //pΪ����ָ�룬�Ӹ������ſ�ʼ
    do
    {
        while (p > -1)                                       //ָ��δ���뵽�����µĽ�㣬����
        {
            s.push(p);                                       //��������;����ջ
            p = arr[p].leftChild;                            //����ָ�����������Ů���
        }
        if (!s.isEmpty())
        {
            s.pop(p); visit(arr[p]);                         //�˳�һ����㣬���ʸ����
            p = arr[p].rightChild;                           //��������Ů���
        }
    } while (!s.isEmpty());
}
*/
template <class T>
void display(LinearBinTreeNode<T> &current) {cout << current.data << " ";}

int main()
{
    cout << "�������������";
    int n; cin >> n;    //ABCDEFGHIJ
    LinearBinTreeNode<char> *arr = createCompleteLinearBinaryTree<char>(n);
    preOrder<char>(arr, display<char>);
    delete[] arr;
    system("pause");
    return 0;
}