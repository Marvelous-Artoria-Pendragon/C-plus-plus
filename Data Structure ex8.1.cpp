/*一棵具有 n 个结点的完全二叉树存放在二叉树的顺序存储结构中，试编写非递归算法对该树进行中序遍历*/
#include "BinaryTree.h"
/*
//创建一棵具有n个结点的完全二叉树的顺序储存结构，返回创建后的数组
template <class T>
T *createCompleteLinearBinaryTree(int n)
{
    T *arr = new T[n];
    cout << "请分别输入每个结点的数据：";
    for (int i = 0; i < n; i++) cin >> arr[i];
    return arr;
}


//对具有n个结点的完全二叉树的顺序存储结构，使用非递归方式实现中序遍历
//arr为数组名，size为数组大小，visit为访问函数
template <class T>
void inOrder(T *arr, int size, void (*visit)(T &data))
{
    SeqStack<int> s; int p = 0;                                //p为遍历指针，从根结点序号开始
    do
    {
        while (p < size)                                       //指针未进入到最左下的结点，不空
        {
            s.push(p);                                         //该子树沿途结点进栈
            p = 2 * p + 1;                                     //遍历指针进到到左子女结点
        }
        if (!s.isEmpty())
        {
            s.pop(p); visit(arr[p]);                           //退出一个结点，访问根结点
            p = 2 * p + 2;                                     //进入右子女结点
        }
    } while (p < size || !s.isEmpty());                        //p > -1不能去掉，表示仍有结点未访问
}
*/
template <class T>
void display(T &data) {cout << data << " ";}

int main()
{
    cout << "请输入结点个数：";
    int n; cin >> n;    //ABCDEFGHIJ
    char *arr = createCompleteLinearBinaryTree<char>(n);
    inOrder<char>(arr, n, display<char>);
    delete[] arr;
    system("pause");
    return 0;
}