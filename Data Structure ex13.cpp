/*1.д���õݹ鷽��ʵ���Ե��������洢�ṹ��ֱ�Ӳ����������*/
/*д���õݹ鷽��ʵ���Ե��������洢�ṹ��ֱ�Ӳ����������*/
#include <iostream>
#include "LinkedList.h"
using namespace std;

//ֱ�Ӳ���(��С����)�ݹ��㷨
//headΪ�����׵�ַ��currentΪ��ǰ����Ľ�㣬preΪcurrent��ǰһ�����
template <class T>
void insertSort(LinkNode<T> *head, LinkNode<T> *current, LinkNode<T> *pre)
{
    if (current == NULL) return;                            //�ս��ֱ�ӷ���
    insertSort(head, current->link, current);               //��ʣ�µ�n-1���������������
    LinkNode<T> *temp = head;                               //����ǰn��������õĽ���ָ��
    while (temp != current)
    {
        if (current->data < temp->link->data)
        {
            pre->link = current->link;                      //��current�����뵽temp->link�Ľ��ǰ��
            current->link = temp->link;
            temp->link = current; return;
        } temp = temp->link;
    } 
}


int main()
{
    //5 3 1 6 7 2
    cout << "������������";
    int n; cin >> n;
    LinkNode<int> *first = new LinkNode<int>,              //��ͷ���ĵ�����
    *newNode = NULL, *pre = first, *del = NULL;            //�½����ָ�롢��һ�����ָ�롢ɾ�����ָ��
    cout << "��ֱ�����ÿ���������ݣ�";
    for (int i = 0; i < n; i++)                            //��ʼ������
    {
        newNode = new LinkNode<int>; cin >> newNode->data;  //�½���㲢��������
        pre->link = newNode; pre = pre->link;               //������
    }
    insertSort(first, first->link, first);
    cout << "�����Ľ����\n";
    del = first; first = del->link; 
    while (del = first, del != NULL)                        //���������
        {first = del->link; cout << del->data << " "; delete del;}
    cout << endl;
    system("pause");
    return 0;
}