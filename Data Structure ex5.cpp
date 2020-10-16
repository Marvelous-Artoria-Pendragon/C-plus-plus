/*
1���������ʽ�ļ��㣬֧�ֵ���������У�+ - * / % ( )

�����ʽ��һ��һ���������ʽ����������������
�����ʽ��һ��һ��������
������
����������
2*��3 + 4��
6+ 2 * 8 /4
�������
14
10

������Ҫ����������Ϊ����
��ѡ�����ݡ������������Ϊ�����Ǵ�С��λ�ĸ�����


*/

#include <math.h>
#include "Stack.h"
#include <string>
#include <regex>

using namespace std;

class Calculator
{
    //�ԴӼ��̶���ĺ�׺���ʽ��ֵ
    public:
        //Calculator(int sz):s(sz){}                          ���캯��
        void Run();                                         //ִ�б��ʽ����
        void Clear();
    private:
        SeqStack<double> s;                                 //�洢��������ջ
        string infix;                                       //��׺���ʽ
        string postfix;                                     //��׺���ʽ
        void AddOperand(double value);                      //��������ջ
        bool get2Operand(double &left, double &right);      //��ջ���˳�����������
        void DoOperator(char op);                           //�γ�����ָ� ���м���
        void toPostfix();                                   //����׺���ʽת��Ϊ��׺���ʽ

};

//��������
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

//��ջ��ȡ����������
bool Calculator::get2Operand(double &left, double &right)
{
    if (s.IsEmpty()) {cerr << "ȱ���Ҳ�������" << endl; return false;}
    s.Pop(right);           //����ȡ�Ҳ�����
    if (s.IsEmpty()) {cerr << "ȱ�����������" << endl; return false;}
    s.Pop(left);            //����ȡ�������
    return true;
};

//��������ѹ��ջ��
void Calculator::AddOperand(double value)
{s.Push(value);}

//���ջ���е�����
void Calculator::Clear()
{s.makeEmpty();}

void Calculator::Run()
{
    char ch; double newOperand, result;
    int i = 0;
    while (ch = postfix[i++], ch != '#')
        switch(ch)
        {
            case '+': case '-': case '*': case '/': DoOperator(ch); break;      //�ж��ǲ�������ִ�м���
            default: cin.putback(ch);               //���ַ��Ż�������
                     cin >> newOperand;             //���¶�������
                     AddOperand(newOperand);        //������������ջ��
        }
    s.Pop(result);
    cout << "\n" << result << endl;
}


//ջ��(in stack priority)������
int isp(char ch)
{
    switch(ch)
    {
        case '#' : return 0;
        case '(' : return 1;
        case '*': case '/': case '%': return 5;
        case '+': case '-': return 3;
        case ')': return 6;
        default: cerr << "���ǺϷ���������" << endl; exit(1);
    };
}

//ջ��(in coming priority)������
int icp(char ch)
{
    switch(ch)
    {
        case '#': case '=': return 0;
        case '(' : return 6;
        case '*': case '/': case '%': return 4;
        case '+': case '-': return 2;
        case ')': return 1;
        default: cerr << "���ǺϷ���������" << endl; exit(1);
    };
}

//����׺���ʽeת���ɺ�׺���ʽ�����֮���趨e�����һ�������ǡ�#�������ҡ�#��һ��ʼ�ȷ���ջs��ջ��
void Calculator::toPostfix()
{
    SeqStack<char> operand;                                     //�洢��������ջ
    string postfix[50];                                         //���صĺ�׺���ʽ�ַ�����
    char read = '#', top, op;                                   //readΪ��ǰ��ȡ���ַ���topΪջ���ַ���opΪ������
    int i = 0, j = 0, k = 0;                                //i���ڱ�����׺���ʽÿ���ַ���j��ʾ��׺���ʽ�ĵڼ����ַ�
    regex pn("\\d+.?\\d*");                                     //ƥ��������������ʽ
    smatch result;                                              //����ƥ������ʵ������
    string::const_iterator iterstart = infix.begin();           //��������ʼ����
    string::const_iterator iterend = infix.end();               //��������������

    operand.Push(read); read = infix[i++];                      //ջ�׷�һ����#���� ����һ���ַ�
    while (!s.IsEmpty() && read != '\0')                        //��������ջ��Ϊ������׺���ʽδ����
        if (isdigit(read))                                      //��ǰ�������ַ�������
        {
            if (regex_search(iterstart, iterend, result, pn))   //������ʽƥ���������
            {
                postfix[k++] = result[0];
                iterstart = result[0].second;
                read = infix[i++];
            }
            else {cerr << "δƥ�䵽������!"; exit(1);}
        }
        else
        {
            operand.getTop(top);                                //ȡջ��������
            if (isp(top) < icp(read))                           //�����������read���ȼ���
            {
                operand.Push(read);            //��ջ
                if (read == '(' && !isdigit(infix[i + 1]))           //�ж����ź���Ĳ������֣�Ĭ���ж�Ϊ����
                {
                    if (regex_search(iterstart, iterend, result, pn))
                    {
                        postfix[k++] = result[0];
                        iterstart = result[0].second;
                    }
                    else {cerr << "δƥ�䵽������!"; exit(1);}
                }
                read = infix[i++];            //������һ���ַ�
            }
            else if(isp(top) > icp(read))              //�����������ch���ȼ���
                {operand.Pop(op); cout << op;}      //��ջ�������
            else
            {
                operand.Pop(op);                      //������������ȼ�����ջ�����ȼ�
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