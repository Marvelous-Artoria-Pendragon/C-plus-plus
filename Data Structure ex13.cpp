/*1.写出用递归方法实现以单链表做存储结构的直接插入排序程序。*/
/*写出用递归方法实现以单链表做存储结构的直接插入排序程序。*/
#include <iostream>
#include "LinkedList.h"
using namespace std;

//直接插入(从小到大)递归算法
//head为链表首地址，current为当前处理的结点，pre为current的前一个结点
template <class T>
void insertSort(LinkNode<T> *head, LinkNode<T> *current, LinkNode<T> *pre)
{
    if (current == NULL) return;                            //空结点直接返回
    insertSort(head, current->link, current);               //对剩下的n-1个结点作插入排序
    LinkNode<T> *temp = head;                               //遍历前n个已排序好的结点的指针
    while (temp != current)
    {
        if (current->data < temp->link->data)
        {
            pre->link = current->link;                      //将current结点插入到temp->link的结点前面
            current->link = temp->link;
            temp->link = current; return;
        } temp = temp->link;
    } 
}


int main()
{
    //5 3 1 6 7 2
    cout << "请输入结点数：";
    int n; cin >> n;
    LinkNode<int> *first = new LinkNode<int>,              //带头结点的单链表
    *newNode = NULL, *pre = first, *del = NULL;            //新建结点指针、上一个结点指针、删除结点指针
    cout << "请分别输入每个结点的数据：";
    for (int i = 0; i < n; i++)                            //初始化链表
    {
        newNode = new LinkNode<int>; cin >> newNode->data;  //新建结点并输入数据
        pre->link = newNode; pre = pre->link;               //链入结点
    }
    insertSort(first, first->link, first);
    cout << "排序后的结果：\n";
    del = first; first = del->link; 
    while (del = first, del != NULL)                        //输出并析构
        {first = del->link; cout << del->data << " "; delete del;}
    cout << endl;
    system("pause");
    return 0;
}