//设线性表存储在数组A[0..arrsize-1]的前elenum个分量重，且递增有序。
//试编写一个算法：将x插入到线性表的适当位置上，以保持线性表的有序性，并且分析算法的时间复杂度

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
    if (index < 0 || length - 1 >= maxSize || index > length) return false;    //索引不合法，或数组已满
    for(int i = length - 1; i > index; i--)        //对插入元素后的所有元素往后移一位
        arr[i + 1] = arr[i];
    arr[index] = x;
    length++;           //元素个数+1
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
    for (int i; i < 7; i++)            //初始化数组
        l.insert(i, i * 10);
    cout << l << endl;
    cout << "请分别输入两个数字，第一个为插入位置，第二个为元素值:" << endl;
    
    cin >> index >> x;
    if (!l.insert(index - 1, x)) cout << "插入失败！" << endl;
    cout << "\n" << l;
    system("pause");
    return 0;
}

