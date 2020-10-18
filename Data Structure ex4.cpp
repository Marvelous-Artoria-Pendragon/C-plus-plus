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
        CircList<T>(CircList<T> &);                   //拷贝构造函数
        void reverse();                                     //将链表元素逆转
        LinkNode<T> *getRear() {return rear;}               //返回尾指针
        template <class Y>
        friend ostream &operator << (ostream &, const CircList<Y> &);        //重载输出流函数

    protected:
        LinkNode<T> *rear;      //尾指针
};

template <class T>
CircList<T>::CircList()
{
    int i = 0;
    rear = new LinkNode<T>(i);                                              //初始化一个表头结点
    if (rear == NULL) {cerr << "存储分配错误！" << endl; exit(1);}           //动态分配失败
    rear->link = rear;                                                      //表头结点指向自己
    while (i++ < 4)                                                           //创建7个结点
    {
        LinkNode<T> *p = new LinkNode<T>(i);
        if (p == NULL) {cerr << "存储分配错误！" << endl; exit(1);}          //动态分配失败
        p->link = rear->link;                                               //尾插入
        rear->link = p;
        rear = p;
    }
}

template <class T>
CircList<T>::~CircList()
{
    LinkNode<T> *del;
    while (rear->link != rear)
    {
        del = rear->link;
        rear->link = del->link;
        delete del;
    }
    delete rear;
}

template <class T>
CircList<T>::CircList(CircList<T> &L)
{
    LinkNode<T> *srcptr = L.getRear()->link;
    rear = new LinkNode<T>(0);
    if (rear == NULL) {cerr << "存储分配错误！" << endl; exit(1);}          //动态分配失败
    rear->link = rear;          //头尾链接

    while (srcptr->link != L.getRear()->link)
    {
        LinkNode<T> *newNode = new LinkNode<T>(srcptr->link->data);
        newNode->link = rear->link;
        rear->link = newNode;
        srcptr = srcptr->link;          //复制的下一个结点
        rear = newNode;
    }
}

//将单链表中元素逆置
template <class T>
void CircList<T>::reverse()
{
    LinkNode<T> *next, *current, *last, *ret;       //ret记录逆转后的链表的最后一个结点， next指向下一个结点
                                                    //current指向当前结点，last指向上一个结点
    last = rear; current = last->link; ret = next = current->link;
    do
    {
        current->link = last;
        last = current;
        current = next;
        next = next->link;
    } while (last != rear);
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
    while(temp->link != c.rear->link)
    {
        cout << temp->link->data << ' ';
        temp = temp->link;
    }
    return output;
}

int main()
{
    CircList<int> c1;
    cout << c1 << endl;
    c1.reverse();
    cout << c1 << endl;
    CircList<int> c2 = c1;
    cout << c2 << endl;
    system("pause");
    return 0;
}