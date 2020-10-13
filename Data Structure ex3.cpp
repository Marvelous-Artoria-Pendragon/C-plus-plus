//已知单链表L中的结点是按值递增有序排列的，试编写一算法将值为X的元素插入链表L中，使得L仍然有序。

#include <iostream>
using namespace std;

template <class T>
struct LinkNode
{
    T data;
    LinkNode *link;
    LinkNode(LinkNode<T> *ptr = NULL) {link = ptr;}
    LinkNode(const T &item, LinkNode<T> *ptr = NULL) {link = ptr; data = item;}
};


template <class T>
class LinkedList
{
    protected:
        LinkNode<T> *first;
    
    public:
        LinkedList(){first = new LinkNode<int>;}        //创建空表头
        bool Insert(int i, T &x);
        LinkNode<T> *Locate(int i);
        void output();
};

//查找第i个结点
template <class T>
LinkNode<T> *LinkedList<T>::Locate(int i)
{
    if (i < 0) return NULL;
    LinkNode<T> *current = first; int k = 0;
    while (current != NULL && k < i)
        {current = current->link; k++;}
    return current;
}

//i为插入的位置，x为数据
template <class T>
bool LinkedList<T>::Insert(int i, T &x)
{
    LinkNode<T> *current = Locate(i);
    if (current == NULL) return false;
    LinkNode<T> *newNode = new LinkNode<T>(x);
    if (newNode == NULL) {cerr << "存储分配错误！" << endl; exit(1);}
    newNode->link = current->link;
    current->link = newNode;
    return true;
}

template <class T>
void LinkedList<T>::output()
{
    LinkNode<T> *current = first->link;
    while (current != NULL)
    {
        cout << current->data << " ";
        current = current->link;
    }
    cout << endl;
}

int main()
{
    LinkedList<int> l;
    
    for (int i = 0; i < 5; i++)
        l.Insert(i, i);     //初始化链表
    l.output();

    //插入后
    int index, item;
    cout << "当前顺序表：" << endl;
    l.output();
    cout << "请分别输入插入的位置和数值: ";
    cin >> index >> item;
    l.Insert(index - 1, item);
    
    cout << "当前顺序表：" << endl;
    l.output();
    system("pause");
    return 0;
}