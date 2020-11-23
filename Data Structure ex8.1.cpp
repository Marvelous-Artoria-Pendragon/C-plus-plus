/*һ�þ��� n ��������ȫ����������ڶ�������˳��洢�ṹ�У��Ա�д�ǵݹ��㷨�Ը��������������*/
#include "BinaryTree.h"
/*
//����һ�þ���n��������ȫ��������˳�򴢴�ṹ�����ش����������
template <class T>
T *createCompleteLinearBinaryTree(int n)
{
    T *arr = new T[n];
    cout << "��ֱ�����ÿ���������ݣ�";
    for (int i = 0; i < n; i++) cin >> arr[i];
    return arr;
}


//�Ծ���n��������ȫ��������˳��洢�ṹ��ʹ�÷ǵݹ鷽ʽʵ���������
//arrΪ��������sizeΪ�����С��visitΪ���ʺ���
template <class T>
void inOrder(T *arr, int size, void (*visit)(T &data))
{
    SeqStack<int> s; int p = 0;                                //pΪ����ָ�룬�Ӹ������ſ�ʼ
    do
    {
        while (p < size)                                       //ָ��δ���뵽�����µĽ�㣬����
        {
            s.push(p);                                         //��������;����ջ
            p = 2 * p + 1;                                     //����ָ�����������Ů���
        }
        if (!s.isEmpty())
        {
            s.pop(p); visit(arr[p]);                           //�˳�һ����㣬���ʸ����
            p = 2 * p + 2;                                     //��������Ů���
        }
    } while (p < size || !s.isEmpty());                        //p > -1����ȥ������ʾ���н��δ����
}
*/
template <class T>
void display(T &data) {cout << data << " ";}

int main()
{
    cout << "�������������";
    int n; cin >> n;    //ABCDEFGHIJ
    char *arr = createCompleteLinearBinaryTree<char>(n);
    inOrder<char>(arr, n, display<char>);
    delete[] arr;
    system("pause");
    return 0;
}