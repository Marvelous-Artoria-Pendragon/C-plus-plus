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
        Calculator() {infix = ""; operand_arr = new char[20];}            //���캯��,��ʼ����
        ~Calculator() {delete operand_arr;}
        double Run();                                                     //ִ�б��ʽ����
        void Clear();                                                     //��ղ�����ջ�Ͳ���������
        void readinfix(string str) {infix = str;}                         //��ȡ��׺���ʽ
    private:
        void toPostfix();                                                 //����׺���ʽת��Ϊ��׺���ʽ
        SeqStack<double> number;                                          //�洢��������ջ
        string infix;                                                     //��׺���ʽ
        char *operand_arr;                                                //�洢������������
        bool get2Operand(double num[]);                                   //��ջ���˳�����������
        void DoOperator(char op);                                         //�γ�����ָ���һ�����������м���
};

//��һ����������������
void Calculator::DoOperator(char op)
{
    double num[2]; int result;                                          //num[0]��ʾ���������num[1]Ϊ�Ҳ�����
    result = get2Operand(num);                                          //�ж��Ƿ��ȡ�ɹ�
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

//��ջ��ȡ����������
bool Calculator::get2Operand(double num[])
{
    if (number.IsEmpty()) {cerr << "ȱ���Ҳ�������" << endl; return false;}
    number.Pop(num[1]);            //����ȡ�Ҳ�����
    if (number.IsEmpty()) {cerr << "ȱ�����������" << endl; return false;}
    number.Pop(num[0]);            //����ȡ�������
    return true;
};

//���ջ���е�����
void Calculator::Clear()
{
    number.makeEmpty();
    memset(operand_arr, 0, 20);
}

//�Ա��ʽ��������
double Calculator::Run()
{
    toPostfix();
    char op; double result; int i = 0;
    while (op = operand_arr[i++], op != '#')
        switch(op)
        {
            case '+': case '-': case '*': case '/': DoOperator(op); break;      //�ж��ǲ�������ִ�м���
            default: {cerr << "�ǺϷ���������" << endl; exit(1);}
        }
    number.Pop(result);
    Clear(); return result;
}

//ջ��(in stack priority)������
int isp(char ch)
{
    switch(ch)
    {
        case '#': return 0;
        case '(': return 1;
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
        case '(': return 6;
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
    char read = '#', top, op;                                   //readΪ��ǰ��ȡ���ַ���topΪջ���ַ���opΪ������
    int i = 0, j = 0;                                           //i���ڱ�����׺���ʽÿ���ַ���j��ʾ���������
    regex pn("-?\\d+\\.?\\d*");                                 //ƥ��������������ʽ
    smatch result;                                              //����ƥ������ʵ������
    string::const_iterator iterstart = infix.begin();           //��������ʼ����
    string::const_iterator iterend = infix.end();               //��������������

    operand.Push(read); read = infix[i];                        //ջ�׷�һ����#���� ����һ���ַ�
    while (!operand.IsEmpty() && read != '\0')                  //��������ջ��Ϊ������׺���ʽδ����
    {
        if (read == ' ') {read = infix[++i]; iterstart++; continue;}    //����ո�����
        if (isdigit(read))                                      //��ǰ�������ַ�������
        {
            if (regex_search(iterstart, iterend, result, pn))   //������ʽƥ���������
            {
                number.Push(stof(result[0].str()));             //��������ѹ�������ջ��
                iterstart = result[0].second;                   //��һ�δ�ƥ�䵽�ַ�����ĩλ�ÿ�ʼƥ��
                i += result[0].length();
                read = infix[i];                                //������ȡ�ַ�
            }
            else {cerr << "δƥ�䵽������!"; exit(1);}
        }
        else
        {
            operand.getTop(top);                                //ȡջ��������
            if (isp(top) < icp(read))                           //�����������read���ȼ���
            {
                operand.Push(read);                             //��ջ
                if (read == '(')
                {
                    if (!isdigit(infix[i + 1]))                 //�ж����ź���Ĳ������֣�Ĭ���ж�Ϊ����
                    {
                        if (regex_search(iterstart, iterend, result, pn))
                        {
                            number.Push(stof(result[0].str()));
                            iterstart = result[0].second - 1;
                            i += result[0].length();
                        }
                        else {cerr << "δƥ�䵽������!"; exit(1);}
                    }
                }
                iterstart++;
                read = infix[++i];                              //������һ���ַ�
            }
            else if(isp(top) > icp(read))                       //�����������read���ȼ���
                {   
                    operand.Pop(op);                            //��������ջ
                    operand_arr[j++] = op;                      //������������operand_arr������
                }
            else
            {
                operand.Pop(op);                                //������������ȼ�����ջ�����ȼ�(ȡ����Ե�����)
                if (op == '(') {read = infix[++i]; iterstart++;}
            }
        }
    }
    operand_arr[j] = '#';                                       //���һ��'#'��Ϊ�������
}

int main()
{
    Calculator cl;
    string infix; int n;
    cout << "��������Ҫ����ı��ʽ������"; cin >> n;
    double *result = new double[n];
    cout << "������������ʽ��" << endl;
    getline(cin, infix);                        //��cin���µĻ���\n��ȡ
    for (int i = 0; i < n; i++)                 //ѭ��������ʽ�����𰸴�����result������
    {
        getline(cin, infix);
        cl.readinfix(infix + "=");
        result[i] = cl.Run();
    }
    for (int i = 0; i < n; i++)                 //ѭ�������
    cout << result[i] << endl;
    system("pause");
    return 0;
}

//6.23+(9*(-1.5)-4)/0.4