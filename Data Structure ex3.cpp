//��֪������L�еĽ���ǰ�ֵ�����������еģ��Ա�дһ�㷨��ֵΪX��Ԫ�ز�������L�У�ʹ��L��Ȼ����

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
        LinkedList(){first = new LinkNode<int>;}        //�����ձ�ͷ
        bool Insert(int i, T &x);
        LinkNode<T> *Locate(int i);
        void output();
};

//���ҵ�i�����
template <class T>
LinkNode<T> *LinkedList<T>::Locate(int i)
{
    if (i < 0) return NULL;
    LinkNode<T> *current = first; int k = 0;
    while (current != NULL && k < i)
        {current = current->link; k++;}
    return current;
}

//iΪ�����λ�ã�xΪ����
template <class T>
bool LinkedList<T>::Insert(int i, T &x)
{
    LinkNode<T> *current = Locate(i);
    if (current == NULL) return false;
    LinkNode<T> *newNode = new LinkNode<T>(x);
    if (newNode == NULL) {cerr << "�洢�������" << endl; exit(1);}
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
        l.Insert(i, i);     //��ʼ������
    l.output();

    //�����
    int index, item;
    cout << "��ǰ˳���" << endl;
    l.output();
    cout << "��ֱ���������λ�ú���ֵ: ";
    cin >> index >> item;
    l.Insert(index - 1, item);
    
    cout << "��ǰ˳���" << endl;
    l.output();
    system("pause");
    return 0;
}