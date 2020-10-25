/*
设有编号为1,2,3....n的列车，顺序开入栈式结构的展台，则可能出栈序列有多少种？
*/

#include <iostream>
#include <stack>
using namespace std;

int cnt = 0;                                      //统计有多少种出栈序列

//n为需要进栈的火车数，i为从第几号车开始进栈
void dispatch(int n, int i, stack<int> rail, string ss)
{
    rail.push(i);
    while (!rail.empty())                           //栈内还有火车
    {
        if (i + 1 <= n)
        dispatch(n, i + 1, rail, ss);               //火车进栈后留下
        
        ss += to_string(rail.top());
        rail.pop();                                 //火车进栈后离开
    }
    if (i + 1 <= n)                                 //栈内无火车，但还有火车要进栈
        dispatch(n, i + 1, rail, ss);
    else 
    {cout << ss << endl; cnt++;}
}

int main()
{
    int n; cin >> n;                            //进栈火车数
    stack<int> rail;                            //栈式结构
    string ss = "";                             //输出序列字符串
    dispatch(n, 1, rail, ss);
    cout << "一共有" << cnt << "种" << endl;
    system("pause");
    return 0;
}