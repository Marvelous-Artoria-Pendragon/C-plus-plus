/*
1.�õݹ鷽��ʵ�ֵ���������á�
*/

#include <iostream>
using namespace std;

template<class T>
struct LinkNode
{
    T data;                         //������
    LinkNode<T> *link;              //��ָ����
    LinkNode(LinkNode<T> *ptr = NULL) {link = ptr;}     //��ʼ��ָ��Ĺ��캯��
    LinkNode(const T &item, LinkNode<T> *ptr = NULL)    //��ʼ���������ָ��Ĺ��캯��
    {data = item; link = ptr;}
};

//����ͷ���ķ�ѭ��������
template <class T>
class LinearList
{
    public:
        LinearList<T>();                                                 //���캯��
        ~LinearList<T>();                                                //��������
        LinearList<T>(LinearList<T> &);                                  //�������캯��
        LinkNode<T> *getHead() {return first;}                           //����ͷ���
        template <class Y>
        friend ostream &operator << (ostream &, LinearList<Y> &);        //�������������
        void reverse(LinkNode<T> *current, LinkNode<T> *last = NULL);    //������Ԫ����ת
    protected:
        LinkNode<T> *first;                                              //ͷָ��
};

//���캯������ʼ��5�����
template <class T>
LinearList<T>::LinearList()
{
    int i = 0;
    LinkNode<T> *current = first = new LinkNode<T>(0);                   //������ͷ���
    if (first == NULL) {cerr << "�洢�������" << endl; exit(1);}
    while (i++ < 5)                                                      //��ʼ��5�����
    {
        LinkNode<T> *newNode = new LinkNode<T>(i);
        if (newNode == NULL) {cerr << "�洢�������" << endl; exit(1);}
        current->link = newNode;
        current = current->link;
    }
}

//�������캯��
template <class T>
LinearList<T>::LinearList(LinearList<T> &L)
{
    LinkNode<T> *srcptr = L.getHead()->link, *destptr = first = new LinkNode<T>(0);
    if (first == NULL) {cerr << "�洢�������" << endl; exit(1);}
    while (srcptr != NULL)
    {
        destptr->link = new LinkNode<T>(srcptr->data);
        destptr = destptr->link;
        srcptr = srcptr->link;
    }
}

//��������
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

//���������
template <class T>
ostream &operator << (ostream &output, LinearList<T> &c)
{
    LinkNode<T> *temp = c.getHead()->link;                  //������ͷ���
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->link;
    }
    cout << endl;
    return output;
}

//�������õݹ麯��
template <class T>
void LinearList<T>::reverse(LinkNode<T> *current, LinkNode<T> *last)
{
    if (current->link == NULL)
    {current->link = last; first->link = current; return;}                    //��ǰ������һ�����Ϊ�գ����ص�ǰ����ַ
    reverse(current->link, current);                                          //���õ�ǰ������һ�����
    current->link = last;                                                     //��ǰ���ָ����һ�����
}


int main()
{
    LinearList<int> l1;
    cout << l1;
    l1.reverse(l1.getHead()->link);
    cout << l1;
    LinearList<int> l2 = l1;            //����
    cout << l2;
    system("pause");
    return 0;
}