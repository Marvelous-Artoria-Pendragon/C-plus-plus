/*һ�þ��� n ��������ȫ����������ڶ�������˳��洢�ṹ�У��Ա�д�ǵݹ��㷨�Ը��������������*/
#include "BinaryTree.h"
using namespace std;

template <class T>
class LinearBinaryTree
{
    private:
        LinearBinTreeNode<T> *root;                                             //���ڵ�
    public:
        LinearBinaryTree(): root(NULL){}                                        //���캯�������ڵ�Ϊ��
        LinearBinaryTree(LinearBinaryTree<T> x[]);                              //ʹ�����ж��������鹹��
        ~LinearBinaryTree() {delete[] root;}                                    //��������
        void preOrder(int subTree);                                             //�ǵݹ��㷨��subTreeΪ�����������������
};

template <class T>
void LinearBinaryTree<T>::preOrder(int subTree)
{
    SeqStack<int> s;
    s.push(subTree);
    while (!s.isEmpty())
    {

    }
}
