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
        Calculator() {infix = ""; operand_arr = new char[20];}            //构造函数,初始化数
        ~Calculator() {delete operand_arr;}
        double Run();                                                     //执行表达式计算
        void Clear();                                                     //清空操作数栈和操作符数组
        void readinfix(string str) {infix = str;}                         //读取中缀表达式
    private:
        void toPostfix();                                                 //将中缀表达式转换为后缀表达式
        SeqStack<double> number;                                          //存储操作数的栈
        string infix;                                                     //中缀表达式
        char *operand_arr;                                                //存储操作符的数组
        bool get2Operand(double num[]);                                   //从栈中退出两个操作数
        void DoOperator(char op);                                         //形成运算指令，对一个操作符进行计算
};

//对一个操作符进行运算
void Calculator::DoOperator(char op)
{
    double num[2]; int result;                                          //num[0]表示左操作数，num[1]为右操作数
    result = get2Operand(num);                                          //判断是否获取成功
    if (result)
        switch(op)
        {
            case '+': number.Push(num[0] + num[1]); break;
            case '-': number.Push(num[0] - num[1]); break;
            case '*': number.Push(num[0] * num[1]); break;
            case '/': if (num[1] == 0.0)
                      {cerr << "Divide by 0!" << endl; Clear();}
                      else number.Push(num[0] / num[1]);
                      break;
        }
    else Clear();
}

//从栈里取两个操作数
bool Calculator::get2Operand(double num[])
{
    if (number.IsEmpty()) {cerr << "缺少右操作数！" << endl; return false;}
    number.Pop(num[1]);            //先提取右操作数
    if (number.IsEmpty()) {cerr << "缺少左操作数！" << endl; return false;}
    number.Pop(num[0]);            //再提取左操作数
    return true;
};

//清空栈所有的数据
void Calculator::Clear()
{
    number.makeEmpty();
    memset(operand_arr, 0, 20);
}

//对表达式进行运算
double Calculator::Run()
{
    toPostfix();
    char op; double result; int i = 0;
    while (op = operand_arr[i++], op != '#')
        switch(op)
        {
            case '+': case '-': case '*': case '/': DoOperator(op); break;      //判断是操作符，执行计算
            default: {cerr << "非合法操作符！" << endl; exit(1);}
        }
    number.Pop(result);
    Clear(); return result;
}

//栈内(in stack priority)优先数
int isp(char ch)
{
    switch(ch)
    {
        case '#': return 0;
        case '(': return 1;
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
        case '(': return 6;
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
    char read = '#', top, op;                                   //read为当前读取的字符，top为栈顶字符，op为操作符
    int i = 0, j = 0;                                           //i用于遍历中缀表达式每个字符，j表示操作符序号
    regex pn("-?\\d+\\.?\\d*");                                 //匹配正数的正则表达式
    smatch result;                                              //保存匹配结果的实例对象
    string::const_iterator iterstart = infix.begin();           //迭代器开始部分
    string::const_iterator iterend = infix.end();               //迭代器结束部分

    operand.Push(read); read = infix[i];                        //栈底放一个“#”， 读入一个字符
    while (!operand.IsEmpty() && read != '\0')                  //连续处理，栈不为空且中缀表达式未读完
    {
        if (read == ' ') {read = infix[++i]; iterstart++; continue;}    //处理空格，跳过
        if (isdigit(read))                                      //当前读到的字符是数字
        {
            if (regex_search(iterstart, iterend, result, pn))   //正则表达式匹配这个数字
            {
                number.Push(stof(result[0].str()));             //将操作数压入操作数栈中
                iterstart = result[0].second;                   //下一次从匹配到字符串的末位置开始匹配
                i += result[0].length();
                read = infix[i];                                //继续读取字符
            }
            else {cerr << "未匹配到操作数!"; exit(1);}
        }
        else
        {
            operand.getTop(top);                                //取栈顶操作符
            if (isp(top) < icp(read))                           //新输入操作符read优先级高
            {
                operand.Push(read);                             //进栈
                if (read == '(')
                {
                    if (!isdigit(infix[i + 1]))                 //判断括号后跟的不是数字，默认判断为负数
                    {
                        if (regex_search(iterstart, iterend, result, pn))
                        {
                            number.Push(stof(result[0].str()));
                            iterstart = result[0].second - 1;
                            i += result[0].length();
                        }
                        else {cerr << "未匹配到操作数!"; exit(1);}
                    }
                }
                iterstart++;
                read = infix[++i];                              //读入下一个字符
            }
            else if(isp(top) > icp(read))                       //新输入操作符read优先级低
                {   
                    operand.Pop(op);                            //操作符退栈
                    operand_arr[j++] = op;                      //将操作符放入operand_arr数组中
                }
            else
            {
                operand.Pop(op);                                //输入操作符优先级等于栈顶优先级(取出配对的括号)
                if (op == '(') {read = infix[++i]; iterstart++;}
            }
        }
    }
    operand_arr[j] = '#';                                       //添加一个'#'作为结束标记
}

int main()
{
    Calculator cl;
    string infix; int n;
    cout << "请输入需要计算的表达式数量："; cin >> n;
    double *result = new double[n];
    cout << "请依次输入表达式：" << endl;
    getline(cin, infix);                        //把cin留下的缓冲\n读取
    for (int i = 0; i < n; i++)                 //循环计算表达式，将答案储存在result数组中
    {
        getline(cin, infix);
        cl.readinfix(infix + "=");
        result[i] = cl.Run();
    }
    for (int i = 0; i < n; i++)                 //循环输出答案
    cout << result[i] << endl;
    system("pause");
    return 0;
}

//6.23+(9*(-1.5)-4)/0.4