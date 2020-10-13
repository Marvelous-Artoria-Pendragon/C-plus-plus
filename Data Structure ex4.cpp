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

template <class T>
class CircList
{
    public:
        CircList<T>();                                      //构造函数
        ~CircList<T>();                                     //析构函数
        CircList<T>(const CircList<T> &);                   //拷贝构造函数
        void reverse();                     //将链表元素逆转
        template <class Y>
        friend ostream &operator << (ostream &, const CircList<Y> &);        //重载输出流函数

    protected:
        LinkNode<T> *rear;      //尾指针
        int length;
};

template <class T>
CircList<T>::CircList()
{
    int i = 0;
    rear = new LinkNode<T>(i);         //初始化一个表头结点
    if (rear == NULL) {cerr << "存储分配错误！" << endl; exit(1);}          //动态分配失败
    rear->link = rear;              //表头结点指向自己
    while (i < 8)                 //创建7个结点
    {
        i++;
        LinkNode<T> *p = new LinkNode<T>(i);
        if (p == NULL) {cerr << "存储分配错误！" << endl; exit(1);}          //动态分配失败
        p->link = rear->link;
        rear->link = p;
        rear = p;
    }
}

template <class T>
CircList<T>::~CircList()
{
    LinkNode<T> *del, *current = rear;
    do
    {
        del = current;
        current = current->link;
        delete del;
    } while (current != rear);
}

template <class T>
CircList<T>::CircList(const CircList<T> &L)
{
    LinkNode<T> *current = L->rear;
    rear = new LinkNode<T>(current->data);
    if (rear == NULL) {cerr << "存储分配错误！" << endl; exit(1);}          //动态分配失败
    rear->link = rear;          //头尾链接

    while (current->link != L->rear)
    {
        LinkNode<T> *p = new LinkNode<T>(current->data);
        p->link = rear->link;
        rear = p;
        current = current->link;
    }
}

//将单链表中元素逆置
template <class T>
void CircList<T>::reverse()
{
    LinkNode<T> *next, *current, *last, *ret;       //ret记录逆转后的链表的最后一个结点， next指向下一个结点
                                            //current指向当前结点，last指向上一个结点
    last = current = rear, ret = next = current->link;
    do
    {
        current = next;             //移动到下一个结点
        next = current->link;       //将下一个结点指向当前结点
        current->link = last;       //将当前结点指向上一个结点
        last = current;             //当前结点成为下一次修改过程的上一个结点
    } while (current != rear);
    rear = ret;
}

/*
//单向非循环链表逆转链表
template <class T>
LinkNode<T> *CircList<T>::reverse()
{
    LinkNode<T> *last = NULL, *current, *next;
    while (current != NULL)
    {
        next = current->link;
        current->link = last;
        last = current;
        current = next;
    }
    return last;
}
*/

template <class T>
ostream &operator << (ostream &output, const CircList<T> &c)
{
    LinkNode<T> *temp = c.rear->link;
    do
    {
        cout << temp->data << ' ';
        temp = temp->link;
    } while (temp != c.rear->link);
    return output;
}

int main()
{
    CircList<int> cl;
    cout << cl << endl;
    cl.reverse();
    cout << cl << endl;
    system("pause");
    return 0;
}