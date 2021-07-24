#include <iostream>
#include <string>
#include <stack>
#include <map>
#include "Solution.h"
using namespace std;


int to_postfix(string s)
{
    int i = 0;

    stack<int> num;
    stack<char> op;
    map<char, int> priority;
    priority['+'] = 0;
    priority['-'] = 0;
    priority['*'] = 1;
    priority['/'] = 1;
    priority['('] = 2;
    priority[')'] = -1;
    map<char, int> in;
    in['('] = -2;
    in[')'] = 3;
    in['+'] = 0;
    in['-'] = 0;
    in['*'] = 1;
    in['/'] = 1;

    bool flag = false;
    int multiply = 1;
    while (i < s.size())
    {

        while (i < s.size() && s[i] == ' ') i++;
        if (i == s.size()) break;
        if (s[i] == '-' && (flag || (i == 0)))
        {
            multiply *= -1;
            i++;
        }
        else if (s[i] <= '9' && s[i] >= '0')
        {
            int temp = 0;
            while (i < s.size() && s[i] <= '9' && s[i] >= '0')
            {
                temp = temp * 10 + s[i] - '0';
                i++;
            }
            num.push(multiply * temp);
            multiply = 1;
            //cout << "num = " << temp << endl;
        }
        else
        {
            char curr = s[i];
            //cout << "op is " << curr << endl;


            while (!op.empty() && priority[curr] <= in[op.top()])
            {

                int num1 = num.top();
                num.pop();
                int num2 = num.top();
                num.pop();
                int sum;
                switch (op.top())
                {
                case '+':
                    sum = num1 + num2;
                    break;
                case '-':
                    sum = num2 - num1;
                    break;
                case '*':
                    sum = num1 * num2;
                    break;
                case '/':
                    sum = num2 / num1;
                    break;
                default:
                    break;
                }
                num.push(sum);
                //cout << "sum = " << sum << endl;
                op.pop();
                flag = false;
            }
            op.push(s[i]);
            i++;
            flag = true;
        }
    }
    while (!op.empty() && num.size() > 1)
    {
        if (op.top() == ')' || op.top() == '(')
        {
            op.pop();
            continue;
        }
        int num1 = num.top();
        num.pop();
        int num2 = num.top();
        num.pop();
        //cout<<"1. "<<num2<<" "<<op.top()<<"  2."<<num1<<endl;

        int sum;
        switch (op.top())
        {
        case '+':
            sum = num1 + num2;
            break;
        case '-':
            sum = num2 - num1;
            break;
        case '*':
            sum = num1 * num2;
            break;
        case '/':
            sum = num2 / num1;
            break;
        default:
            break;
        }

        op.pop();
        num.push(sum);
    }
    return num.top();

}

int Solution::calculate(string s) {
    s = s.substr(1);
    return to_postfix(s);
}
