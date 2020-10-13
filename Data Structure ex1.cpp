//�����Ա�洢������A[0..arrsize-1]��ǰelenum�������أ��ҵ�������
//�Ա�дһ���㷨����x���뵽���Ա���ʵ�λ���ϣ��Ա������Ա�������ԣ����ҷ����㷨��ʱ�临�Ӷ�

#include <iostream>
using namespace std;

template <class T>
class LinearList
{
    
    public:
        int maxSize, length;
        T *arr = new T[maxSize];

        LinearList(int ms = 10): maxSize(ms), length(0) {};
        ~LinearList() {delete[] arr;}
        
        bool insert(int index, T x);
        template<class Y>
        friend ostream &operator << (ostream &os, LinearList<Y> &a);
};

template <class T>
bool LinearList<T>::insert(int index, T x)
{
    if (index < 0 || length - 1 >= maxSize || index > length) return false;    //�������Ϸ�������������
    for(int i = length - 1; i > index; i--)        //�Բ���Ԫ�غ������Ԫ��������һλ
        arr[i + 1] = arr[i];
    arr[index] = x;
    length++;           //Ԫ�ظ���+1
    return true;
}

template <class Y>
ostream &operator << (ostream &os, LinearList<Y> &a)
{
    for (int i = 0; i < a.length; i++)
        os << a.arr[i] << " ";
    os << endl;
    return os;
}

int main()
{
    LinearList<int> l(10);
    int x; int index;
    for (int i; i < 7; i++)            //��ʼ������
        l.insert(i, i * 10);
    cout << l << endl;
    cout << "��ֱ������������֣���һ��Ϊ����λ�ã��ڶ���ΪԪ��ֵ:" << endl;
    
    cin >> index >> x;
    if (!l.insert(index - 1, x)) cout << "����ʧ�ܣ�" << endl;
    cout << "\n" << l;
    system("pause");
    return 0;
}

