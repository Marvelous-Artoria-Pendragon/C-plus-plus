/*
���б��Ϊ1,2,3....n���г���˳����ջʽ�ṹ��չ̨������ܳ�ջ�����ж����֣�
*/

#include <iostream>
#include <stack>
using namespace std;

int cnt = 0;                                      //ͳ���ж����ֳ�ջ����

//nΪ��Ҫ��ջ�Ļ�����iΪ�ӵڼ��ų���ʼ��ջ
void dispatch(int n, int i, stack<int> rail, string ss)
{
    rail.push(i);
    while (!rail.empty())                           //ջ�ڻ��л�
    {
        if (i + 1 <= n)
        dispatch(n, i + 1, rail, ss);               //�𳵽�ջ������
        
        ss += to_string(rail.top());
        rail.pop();                                 //�𳵽�ջ���뿪
    }
    if (i + 1 <= n)                                 //ջ���޻𳵣������л�Ҫ��ջ
        dispatch(n, i + 1, rail, ss);
    else 
    {cout << ss << endl; cnt++;}
}

int main()
{
    int n; cin >> n;                            //��ջ����
    stack<int> rail;                            //ջʽ�ṹ
    string ss = "";                             //��������ַ���
    dispatch(n, 1, rail, ss);
    cout << "һ����" << cnt << "��" << endl;
    system("pause");
    return 0;
}