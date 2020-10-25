/*
1.用递归方法实现单链表的逆置。
*/

#include <iostream>
using namespace std;

template<class T>
struct LinkNode
{
    T data;                         //数据域
    LinkNode<T> *link;              //链指针域
    LinkNode(LinkNode<T> *ptr = NULL) {link = ptr;}     //初始化指针的构造函数
    LinkNode(const T &item, LinkNode<T> *ptr = NULL)    //初始化数据域和指针的构造函数
    {data = item; link = ptr;}
};

//带表头结点的非循环单链表
template <class T>
class LinearList
{
    public:
        LinearList<T>();                                                 //构造函数
        ~LinearList<T>();                                                //析构函数
        LinearList<T>(LinearList<T> &);                                  //拷贝构造函数
        LinkNode<T> *getHead() {return first;}                           //返回头结点
        template <class Y>
        friend ostream &operator << (ostream &, LinearList<Y> &);        //重载输出流函数
        void reverse(LinkNode<T> *current, LinkNode<T> *last = NULL);    //将链表元素逆转
    protected:
        LinkNode<T> *first;                                              //头指针
};

//构造函数，初始化5个结点
template <class T>
LinearList<T>::LinearList()
{
    int i = 0;
    LinkNode<T> *current = first = new LinkNode<T>(0);                   //创建表头结点
    if (first == NULL) {cerr << "存储分配错误！" << endl; exit(1);}
    while (i++ < 5)                                                      //初始化5个结点
    {
        LinkNode<T> *newNode = new LinkNode<T>(i);
        if (newNode == NULL) {cerr << "存储分配错误！" << endl; exit(1);}
        current->link = newNode;
        current = current->link;
    }
}

//拷贝构造函数
template <class T>
LinearList<T>::LinearList(LinearList<T> &L)
{
    LinkNode<T> *srcptr = L.getHead()->link, *destptr = first = new LinkNode<T>(0);
    if (first == NULL) {cerr << "存储分配错误！" << endl; exit(1);}
    while (srcptr != NULL)
    {
        destptr->link = new LinkNode<T>(srcptr->data);
        destptr = destptr->link;
        srcptr = srcptr->link;
    }
}

//析构函数
template <class T>
LinearList<T>::~LinearList()
{
    LinkNode<T> *del;
    while (first != NULL)
    {
        del = first;
        first = first->link;
        delete del;
    }
}

//重载输出流
template <class T>
ostream &operator << (ostream &output, LinearList<T> &c)
{
    LinkNode<T> *temp = c.getHead()->link;                  //跳过表头结点
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->link;
    }
    cout << endl;
    return output;
}

//链表逆置递归函数
template <class T>
void LinearList<T>::reverse(LinkNode<T> *current, LinkNode<T> *last)
{
    if (current->link == NULL)
    {current->link = last; first->link = current; return;}                    //当前结点的下一个结点为空，返回当前结点地址
    reverse(current->link, current);                                          //逆置当前结点和下一个结点
    current->link = last;                                                     //当前结点指向上一个结点
}


int main()
{
    LinearList<int> l1;
    cout << l1;
    l1.reverse(l1.getHead()->link);
    cout << l1;
    LinearList<int> l2 = l1;            //拷贝
    cout << l2;
    system("pause");
    return 0;
}