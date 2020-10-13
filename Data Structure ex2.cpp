#include <iostream>
using namespace std;

//数组解决Josephus问题 ******
int solve(int n, int s, int m)
{
    int *arr = new int[n];
    for(int i = 0; i < n - 1; i++)      //初始化数组
        arr[i] = i + 1;
    arr[n - 1] = 0;

    int current = s - 2, //当前指向的同学
    next = s - 1;        //当前同学的下一个同学
    while (current != next)
    {
        //每m-1个人，下一个人出局
        for(int i = 0; i < m - 1; i++)
        {
            current = next;
            next = arr[current];
        }
        cout << "第" << next + 1 << "个同学" << "出局" << endl;
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
    cout << "请分别输入n, s, m:" << endl;
    cin >> n >> s >> m;
    //判断n,s,m是否在范围内
    if (n < 1) {cout << "n不能少于1！" << endl; exit(1);}
    if (s < 1 | s > n) {cout << "s不在人数范围内！" << endl; exit(1);}
    if (m < 1) {cout << "m不能少于1！" << endl; exit(1);}
    result = solve(n, s, m);
    cout << "最终留下的是" << "第" << result + 1 << "个同学" << endl;
    system("pause");
    return 0;
}