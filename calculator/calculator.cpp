#include "calculator.h"

string filter (string expr) {
    vector<char> container;
    for (int i = 0; i < expr.size(); ++i) {
        if (i + 1 < expr.size() && expr[i] == '(' && expr[i + 1] == '-') {
            container.push_back(expr[i]);
            container.push_back('0');
        }
        if (expr[i] == ' ') continue;
        container.push_back(expr[i]);
    }
    string filtered = "";
    for (vector<char>:: iterator it = container.begin(); it != container.end(); ++it)
        filtered += (*it);
    return filtered;
}

bool expr_validity (string expr) {
    // if (expr.size() == 1)
    //     if (expr[0] >= '0' && expr[0] <= '9') return true;
    //     else return false;
    // else {
    //     int i = 0, j = 0;
    //     while (i < expr.size() && (expr[i] >= '0' && expr[i] <= '9') || expr[i] == '.') ++i;
    //     if (operators.find(to_string(expr[i])) != operators.end())
    //         return expr_validity(expr.substr(j, i)) && expr_validity(expr.substr(i + 1));
    //     if (expr[i] == '(') {
            
    //     }
    // }
    int dot_num = 0, i = 0, j = 0;
    if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/' || expr[i] == ')') {
        cout << "Incorrect use of operators!" << endl;
        return false;
    }
    else if (expr[i] == '(') {
        for (j = expr.size() - 1; j > i; --j) {
            if (expr[j] == ')' && j == expr.size() - 1) return expr_validity (expr.substr(i + 1, j - 1));
            else if (expr[j] == ')') return expr_validity (expr.substr(i + 1, j - 1)) && expr_validity (expr.substr(j + 1));
            if (expr[j] == '(') {
                cout << "Parentheses not matched!" << endl;
                return false; 
            }
        }
        cout << "Parentheses not matched!" << endl;
        return false; 
    }
    while (i < expr.size() && ((expr[i] >= '0' && expr[i] <= '9') || expr[i] == '.')) {
        ++i;
        if (expr[i] == '.') ++dot_num;
    }
    if (dot_num > 1) {
        cout << "Invaild numbers!" << endl;
        return false;
    }
    else if (i == expr.size()) return true;
    else return expr_validity (expr.substr(i + 1));
}

string infix_to_suffix (string expr) {
    vector<string> elem;
    string suffix_expr;
    stack<string> operator_stk;
    int i = 0, j = expr.find_first_of(' ', i);
    while (i < expr.size() && j != -1) {
        elem.push_back(expr.substr(i, j - i));
        i = j + 1;
        j = expr.find_first_of(' ', i);
    } //先把中缀表达式分块
    elem.push_back(expr.substr(i));
    //for_each (elem.begin(), elem.end(), [](string& s) {cout << s << endl;});
    for (vector<string>::iterator it = elem.begin(); it != elem.end(); ++it) {
        if (operators.find(*it) == operators.end()) 
            suffix_expr.append(*it);
        else {
            if (operator_stk.empty()) operator_stk.push(*it);
            else {
                int p = operators.find((*it))->second, q = operators.find(operator_stk.top())->second;
                if (p == 6) { //右括号
                    while (q != 5) {
                        suffix_expr.append(operator_stk.top());
                        operator_stk.pop();
                        q = operators.find(operator_stk.top())->second;
                    } //右括号至左括号间的符号输出
                    operator_stk.pop(); //左括号出栈
                }
                else if (q < p) operator_stk.push(*it); //栈顶元素优先级较低
                else {//栈顶元素优先级更高 
                    while (!operator_stk.empty() && operators.find(operator_stk.top())->second != 5 && operators.find(operator_stk.top())->second >= p) {
                        suffix_expr.append(operator_stk.top());
                        operator_stk.pop();
                    }
                    operator_stk.push(*it);
                }
            } 
        }
    }
    while (!operator_stk.empty()) {
        suffix_expr.append(operator_stk.top());
        operator_stk.pop();
    }
    return suffix_expr;
}

vector<float> eval (string expr) {
    stack<float> stk;
    vector<float> res;

    for (int i = 0; i < expr.size(); ++i) {
        if (expr[i] != '+' && expr[i] != '-' && expr[i] != '*' && expr[i] != '/')
            stk.push(operands.find(expr[i])->second);
        else {
            switch (expr[i])
            {
            case '+':
                {
                    float a = stk.top();
                    stk.pop();
                    float b = stk.top();
                    stk.pop();
                    float c = a + b;
                    stk.push(c);
                    break;
                }
            case '-':
                {
                    float a = stk.top();
                    stk.pop();
                    float b = stk.top();
                    stk.pop();
                    float c = a - b;
                    stk.push(c);
                    break;
                }
            case '*':
                {
                    float a = stk.top();
                    stk.pop();
                    float b = stk.top();
                    stk.pop();
                    float c = a * b;
                    stk.push(c);
                    break;
                }
            case '/':
                {
                    float a = stk.top();
                    stk.pop();
                    float b = stk.top();
                    stk.pop();
                    if (b == 0) {
                        cout << "divided by zero!" << endl;
                        return {};
                    }
                    float c = a / b;
                    stk.push(c);
                    break;
                }
            default:
                break;
            }
        }
    }
    cout << fixed << setprecision(2) << stk.top() << endl;
    return {stk.top()};
}

int main() {
    // string test = "a + b * c + ( d * e + f ) * g"; //测试成功
    // //等价于 1.1+1.2*1.3+(1.4*1.5+1.6)*1.7
    // string res = infix_to_suffix(test);
    // eval(res);

    string test1 = "1 + + 1";
    string test2 = "((1 + 1) * (2 - 1)";
    string test3 = "1..1+1";
    string test4 = "1 / (2 * 4 - 8)";
    
    if (expr_validity(filter(test4))) {
        //string s = filter(test4);
        string s1 = infix_to_suffix(test4);
        eval (s1);
    }
    else cout << "-1" << endl;


    system("pause");
}



