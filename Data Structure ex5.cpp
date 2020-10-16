/*
1：算术表达式的计算，支持的运算符号有：+ - * / % ( )

输入格式：一行一个算术表达式，可以输入若干行
输出格式：一行一个输出结果
样例：
输入样例：
2*（3 + 4）
6+ 2 * 8 /4
输出样例
14
10

【基本要求】运算对象均为整数
【选作内容】运算对象扩充为可以是带小数位的浮点数


*/

#include <math.h>
#include "Stack.h"
#include <string>
#include <regex>

using namespace std;

class Calculator
{
    //对从键盘读入的后缀表达式求值
    public:
        //Calculator(int sz):s(sz){}                          构造函数
        void Run();                                         //执行表达式计算
        void Clear();
    private:
        SeqStack<double> s;                                 //存储操作数的栈
        string infix;                                       //中缀表达式
        string postfix;                                     //后缀表达式
        void AddOperand(double value);                      //进操作数栈
        bool get2Operand(double &left, double &right);      //从栈中退出两个操作数
        void DoOperator(char op);                           //形成运算指令， 进行计算
        void toPostfix();                                   //将中缀表达式转换为后缀表达式

};

//进行运算
void Calculator::DoOperator(char op)
{
    double left, right, value; int result;
    result = get2Operand(left, right);
    if (result)
        switch(op)
        {
            case '+': value = left + right; s.Push(value); break;
            case '-': value = left - right; s.Push(value); break;
            case '*': value = left * right; s.Push(value); break;
            case '/': if (right == 0.0)
                      {cerr << "Divide by 0!" << endl; Clear();}
                      else {value = left / right; s.Push(value);}
                      break;
        }
    else Clear();
}

//从栈里取两个操作数
bool Calculator::get2Operand(double &left, double &right)
{
    if (s.IsEmpty()) {cerr << "缺少右操作数！" << endl; return false;}
    s.Pop(right);           //先提取右操作数
    if (s.IsEmpty()) {cerr << "缺少左操作数！" << endl; return false;}
    s.Pop(left);            //再提取左操作数
    return true;
};

//将操作数压入栈中
void Calculator::AddOperand(double value)
{s.Push(value);}

//清空栈所有的数据
void Calculator::Clear()
{s.makeEmpty();}

void Calculator::Run()
{
    char ch; double newOperand, result;
    int i = 0;
    while (ch = postfix[i++], ch != '#')
        switch(ch)
        {
            case '+': case '-': case '*': case '/': DoOperator(ch); break;      //判断是操作符，执行计算
            default: cin.putback(ch);               //将字符放回输入流
                     cin >> newOperand;             //重新读操作数
                     AddOperand(newOperand);        //将操作数放入栈中
        }
    s.Pop(result);
    cout << "\n" << result << endl;
}


//栈内(in stack priority)优先数
int isp(char ch)
{
    switch(ch)
    {
        case '#' : return 0;
        case '(' : return 1;
        case '*': case '/': case '%': return 5;
        case '+': case '-': return 3;
        case ')': return 6;
        default: cerr << "不是合法操作符！" << endl; exit(1);
    };
}

//栈外(in coming priority)优先数
int icp(char ch)
{
    switch(ch)
    {
        case '#': case '=': return 0;
        case '(' : return 6;
        case '*': case '/': case '%': return 4;
        case '+': case '-': return 2;
        case ')': return 1;
        default: cerr << "不是合法操作符！" << endl; exit(1);
    };
}

//将中缀表达式e转换成后缀表达式并输出之。设定e中最后一个符号是“#”，而且“#”一开始先放在栈s的栈底
void Calculator::toPostfix()
{
    SeqStack<char> operand;                                     //存储操作符的栈
    string postfix[50];                                         //返回的后缀表达式字符数组
    char read = '#', top, op;                                   //read为当前读取的字符，top为栈顶字符，op为操作符
    int i = 0, j = 0, k = 0;                                //i用于遍历中缀表达式每个字符，j表示后缀表达式的第几个字符
    regex pn("\\d+.?\\d*");                                     //匹配正数的正则表达式
    smatch result;                                              //保存匹配结果的实例对象
    string::const_iterator iterstart = infix.begin();           //迭代器开始部分
    string::const_iterator iterend = infix.end();               //迭代器结束部分

    operand.Push(read); read = infix[i++];                      //栈底放一个“#”， 读入一个字符
    while (!s.IsEmpty() && read != '\0')                        //连续处理，栈不为空且中缀表达式未读完
        if (isdigit(read))                                      //当前读到的字符是数字
        {
            if (regex_search(iterstart, iterend, result, pn))   //正则表达式匹配这个数字
            {
                postfix[k++] = result[0];
                iterstart = result[0].second;
                read = infix[i++];
            }
            else {cerr << "未匹配到操作数!"; exit(1);}
        }
        else
        {
            operand.getTop(top);                                //取栈顶操作符
            if (isp(top) < icp(read))                           //新输入操作符read优先级高
            {
                operand.Push(read);            //进栈
                if (read == '(' && !isdigit(infix[i + 1]))           //判断括号后跟的不是数字，默认判断为负数
                {
                    if (regex_search(iterstart, iterend, result, pn))
                    {
                        postfix[k++] = result[0];
                        iterstart = result[0].second;
                    }
                    else {cerr << "未匹配到操作数!"; exit(1);}
                }
                read = infix[i++];            //读入下一个字符
            }
            else if(isp(top) > icp(read))              //新输入操作符ch优先级高
                {operand.Pop(op); cout << op;}      //退栈，并输出
            else
            {
                operand.Pop(op);                      //输入操作符优先级等于栈顶优先级
                if (op == '(') read = infix[i++];
            }
        }
}

int main()
{
    string infix;
    cout << infix;
    /*Calculator cl;
    cl.Run();*/
    system("pause");
    return 0;
}