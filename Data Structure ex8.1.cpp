/*一棵具有 n 个结点的完全二叉树存放在二叉树的顺序存储结构中，试编写非递归算法对该树进行中序遍历*/
#include "BinaryTree.h"
using namespace std;

template <class T>
class LinearBinaryTree
{
    private:
        LinearBinTreeNode<T> *root;                                             //根节点
    public:
        LinearBinaryTree(): root(NULL){}                                        //构造函数，根节点为空
        LinearBinaryTree(LinearBinaryTree<T> x[]);                              //使用已有二叉树数组构造
        ~LinearBinaryTree() {delete[] root;}                                    //析构函数
        void preOrder(int subTree);                                             //非递归算法对subTree为根的树进行中序遍历
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
