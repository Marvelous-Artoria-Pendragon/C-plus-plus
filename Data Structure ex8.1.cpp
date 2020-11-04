/*一棵具有 n 个结点的完全二叉树存放在二叉树的顺序存储结构中，试编写非递归算法对该树进行中序遍历*/
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
        if (i < t);                                 //最后一层结点无子女结点
        {
            arr[i].leftChild = 2 * i + 1;
            arr[i].rightChild = 2 * i + 2;
        }
    }
    return arr;
}
*/

/*
//对二叉树的顺序存储结构，使用非递归方式实现中序遍历
template <class T>
void preOrder(LinearBinTreeNode<T> *arr, void (*visit)(LinearBinTreeNode<T> &))
{
    SeqStack<int> s; int p = 0;                              //p为遍历指针，从根结点序号开始
    do
    {
        while (p > -1)                                       //指针未进入到最左下的结点，不空
        {
            s.push(p);                                       //该子树沿途结点进栈
            p = arr[p].leftChild;                            //遍历指针进到到左子女结点
        }
        if (!s.isEmpty())
        {
            s.pop(p); visit(arr[p]);                         //退出一个结点，访问根结点
            p = arr[p].rightChild;                           //进入右子女结点
        }
    } while (!s.isEmpty());
}
*/
template <class T>
void display(LinearBinTreeNode<T> &current) {cout << current.data << " ";}

int main()
{
    cout << "请输入结点个数：";
    int n; cin >> n;    //ABCDEFGHIJ
    LinearBinTreeNode<char> *arr = createCompleteLinearBinaryTree<char>(n);
    preOrder<char>(arr, display<char>);
    delete[] arr;
    system("pause");
    return 0;
}