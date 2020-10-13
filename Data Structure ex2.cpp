#include <iostream>
using namespace std;

//������Josephus���� ******
int solve(int n, int s, int m)
{
    int *arr = new int[n];
    for(int i = 0; i < n - 1; i++)      //��ʼ������
        arr[i] = i + 1;
    arr[n - 1] = 0;

    int current = s - 2, //��ǰָ���ͬѧ
    next = s - 1;        //��ǰͬѧ����һ��ͬѧ
    while (current != next)
    {
        //ÿm-1���ˣ���һ���˳���
        for(int i = 0; i < m - 1; i++)
        {
            current = next;
            next = arr[current];
        }
        cout << "��" << next + 1 << "��ͬѧ" << "����" << endl;
        arr[current] = arr[next];
        current = next;
        next = arr[current];
    }
    //delete arr;
    return current;
}

int main()
{
    int n, s, m, result;
    cout << "��ֱ�����n, s, m:" << endl;
    cin >> n >> s >> m;
    //�ж�n,s,m�Ƿ��ڷ�Χ��
    if (n < 1) {cout << "n��������1��" << endl; exit(1);}
    if (s < 1 | s > n) {cout << "s����������Χ�ڣ�" << endl; exit(1);}
    if (m < 1) {cout << "m��������1��" << endl; exit(1);}
    result = solve(n, s, m);
    cout << "�������µ���" << "��" << result + 1 << "��ͬѧ" << endl;
    system("pause");
    return 0;
}