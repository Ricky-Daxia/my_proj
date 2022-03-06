#include "calculator.h"

string filter (string expr1) {
    string expr;
    int x = 0;
    while (x < expr1.size()) {
        expr += expr1[x];
        if (expr[x] == ' ')
            while (x + 1 < expr1.size() && expr1[x + 1] == ' ') ++x; //去除中间多于两个的空格
        if (x + 1 < expr1.size() && expr1[x] >= '0' && expr1[x] <= '9' && operators.find(expr1[x + 1]) != operators.end()) expr += ' '; //数字和操作符之间无空格就加一个空格
        if (x + 1 < expr1.size() && operators.find(expr1[x]) != operators.end() && expr1[x + 1] >= '0' && expr1[x + 1] <= '9') expr += ' '; //操作符与后面的数字之间的空格
        if (x + 1 < expr1.size() && operators.find(expr1[x]) != operators.end() && operators.find(expr1[x + 1]) != operators.end()) expr += ' '; //操作符之间无空格就补空格
        ++x; 
    }

    for (int i = 0; i < expr.size(); ++i) {
        if (i + 2 < expr.size() && expr[i] == '.' && (expr[i + 1] >= '0' && expr[i + 2] <= '9')) return "";
        if (i + 2 < expr.size() && (expr[i] >= '0' && expr[i] <= '9') && expr[i + 1] == ' ' && (expr[i + 2] >= '0' && expr[i + 2] <= '9')) return "";
        if (i + 2 < expr.size() && expr[i] == ')' && expr[i + 1] == ' ' && (expr[i + 2] >= '0' && expr[i + 2] <= '9')) return "";
    }
    vector<char> container;
    string filtered = "";
    if (expr[0] == '-') filtered += '0';
    for (int i = 0; i < expr.size(); ++i) {
        if (i + 1 < expr.size() && expr[i] == '(' && expr[i + 1] == '-') {
            container.push_back(expr[i]);
            container.push_back('0');
        }
        else if (expr[i] == ' ') continue;
        else container.push_back(expr[i]);
    }
    
    for (vector<char>:: iterator it = container.begin(); it != container.end(); ++it)
        filtered += (*it);
    return filtered;
}

bool expr_validity (string expr) {
    if (expr.empty() || expr[0] == '.') {
        cout << "Incorrect expression!" << endl;
        return false;
    }
    for (int init = 0; init < expr.size(); ++init) {
        if( expr[init] == '+' || expr[init] == '-' || expr[init] == '*' || expr[init] == '/' || expr[init] == ')' || expr[init] == '(' || expr[init] == '.' || (expr[init] >= '0' && expr[init] <= '9'))
            continue;
        else {
            cout << "Invalid symbols!" << endl;
            return false;
        }
    }
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
    int dot_num = 0, i = 0, j = 0, k = 0;
    if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/' || expr[i] == ')') {
        cout << "Incorrect use of operators!" << endl;
        return false;
    }
    else if (expr[i] == '(') {
        // for (j = expr.size() - 1; j > i; --j) {
        //     if (expr[j] == ')' && j == expr.size() - 1) return expr_validity (expr.substr(i + 1, j - 1));
        //     else if (expr[j] == ')') return expr_validity (expr.substr(i + 1, j - 1)) && (operators.find(expr[j + 1]) != operators.end() && expr_validity (expr.substr(j + 2)));
        //     if (expr[j] == '(') {
        //         cout << "Parentheses not matched!" << endl;
        //         return false; 
        //     }
        // }
        ++j;
        for (k = i + 1; k < expr.size(); ++k) {
            if (expr[k] == ')') --j;
            if (expr[k] == '(') ++j;
            if (j == 0) break;
        } //找闭环
        if (j == 0) { //形成闭环 判断右括号是否在尾
            if (k == expr.size() - 1) return expr_validity (expr.substr(i + 1, k - 1)); //在尾
            //不在
            else if (k + 1 < expr.size() && operators.find(expr[k + 1]) != operators.end())
                return expr_validity (expr.substr(i + 1, k - 1)) && expr_validity (expr.substr(k + 2));
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

string generate_expr (string expr) {
    string tmp, res;
    int j = 0;
    for (int i = 0; i < expr.size(); ++i) {
        if (operators.find(expr[i]) == operators.end()) tmp += expr[i];
        else {
            if (!tmp.empty()) {
                operands.insert({char(97 + j), stof(tmp)});
                tmp.resize(0);
                res += char(97 + j);
                ++j;
            }
            res += expr[i];
        }
    }
    if (!tmp.empty()) {
        operands.insert({char(97 + j), stof(tmp)});
        tmp.resize(0);
        res += char(97 + j);
    }
    return res;
}

string infix_to_suffix (string expr) {
    vector<char> elem;
    string suffix_expr;
    stack<char> operator_stk;
    // int i = 0, j = expr.find_first_of(' ', i);
    // while (i < expr.size() && j != -1) {
    //     elem.push_back(expr.substr(i, j - i));
    //     i = j + 1;
    //     j = expr.find_first_of(' ', i);
    // } //先把中缀表达式分块
    // elem.push_back(expr.substr(i));
    for (int i = 0; i < expr.size(); ++i) elem.push_back(expr[i]);
        
    //for_each (elem.begin(), elem.end(), [](string& s) {cout << s << endl;});
    for (vector<char>::iterator it = elem.begin(); it != elem.end(); ++it) {
        if (operators.find(*it) == operators.end()) 
            suffix_expr += *it;
        else {
            if (operator_stk.empty()) operator_stk.push(*it);
            else {
                int p = operators.find(*it)->second, q = operators.find(operator_stk.top())->second;
                if (p == 6) { //右括号
                    while (q != 5) {
                        suffix_expr += operator_stk.top();
                        operator_stk.pop();
                        q = operators.find(operator_stk.top())->second;
                    } //右括号至左括号间的符号输出
                    operator_stk.pop(); //左括号出栈
                }
                else if (q < p) operator_stk.push(*it); //栈顶元素优先级较低
                else {//栈顶元素优先级更高 
                    while (!operator_stk.empty() && operators.find(operator_stk.top())->second != 5 && operators.find(operator_stk.top())->second >= p) {
                        suffix_expr += operator_stk.top();
                        operator_stk.pop();
                    }
                    operator_stk.push(*it);
                }
            } 
        }
    }
    while (!operator_stk.empty()) {
        suffix_expr += operator_stk.top();
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
                    float c = b - a;
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
                    float b = stk.top();
                    stk.pop();
                    float a = stk.top();
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
    cout << stk.top() << endl;
    return {stk.top()};
}

int main() {

    string test;
    
    cout << "这是一款计算器 支持的数据类型：浮点数，精确到一位小数，计算结果最终精确到一位小数（四舍五入）" << endl;
    cout << "使用样例: 1 + 2 - 3 输出 0.0" << endl;
    cout << "使用样例: 2 * 3 / 4 输出 1.5" << endl;
    cout << "使用样例: (2 + 4 * 3.5) * 6 输出 96.0" << endl;
    cout << "使用样例: ((4 * 3 + 2) / (6.4 - 2.4) - 10) * (6.4 - 7.2) + (-2) * 4 输出 -2.8" << endl;
    cout << "===================================" << endl;
    cout << "错误样例: 1++1 输出 操作符误用" << endl;
    cout << "使用样例: ((1 + 1) * (2 - 1) 输出 圆括号不匹配" << endl;
    cout << "使用样例: 1..1+1 输出 数字格式有误" << endl;
    cout << "使用样例: 1 / (2 * 4 - 8) 输出 除数为零" << endl;
    cout << "===================================" << endl;
    cout << "例如输入 1 + 2 3 * 4 程序会识别为 1 + 23 * 4 而不认为是错误" << endl;
    cout << "您可以输入其它字符或者奇奇怪怪的东西来验证程序的稳健性,但最要不要这样做啦!" << endl;
    cout << "源文件放在了 https://github.com/Ricky-Daxia/my_proj/tree/3_2_2/calculator 中" << endl;
    cout << "===================================" << endl;
    cout << endl << endl << "请输入要计算的表达式:";
    cin.sync();
    getline (cin, test);

    if (expr_validity(filter(test)))
        eval (infix_to_suffix(generate_expr(filter(test))));

    cout << "在计算器中验证下算得对不对?" << endl;
    cout << "欢迎下次使用!" << endl;



    system("pause");
}
