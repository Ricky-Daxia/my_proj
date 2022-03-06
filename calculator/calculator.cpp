#include "calculator.h"

string filter (string expr1) {
    string expr;
    int x = 0;
    while (x < expr1.size()) {
        expr += expr1[x];
        if (expr[x] == ' ')
            while (x + 1 < expr1.size() && expr1[x + 1] == ' ') ++x; //ȥ���м���������Ŀո�
        if (x + 1 < expr1.size() && expr1[x] >= '0' && expr1[x] <= '9' && operators.find(expr1[x + 1]) != operators.end()) expr += ' '; //���ֺͲ�����֮���޿ո�ͼ�һ���ո�
        if (x + 1 < expr1.size() && operators.find(expr1[x]) != operators.end() && expr1[x + 1] >= '0' && expr1[x + 1] <= '9') expr += ' '; //����������������֮��Ŀո�
        if (x + 1 < expr1.size() && operators.find(expr1[x]) != operators.end() && operators.find(expr1[x + 1]) != operators.end()) expr += ' '; //������֮���޿ո�Ͳ��ո�
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
        } //�ұջ�
        if (j == 0) { //�γɱջ� �ж��������Ƿ���β
            if (k == expr.size() - 1) return expr_validity (expr.substr(i + 1, k - 1)); //��β
            //����
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
    // } //�Ȱ���׺���ʽ�ֿ�
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
                if (p == 6) { //������
                    while (q != 5) {
                        suffix_expr += operator_stk.top();
                        operator_stk.pop();
                        q = operators.find(operator_stk.top())->second;
                    } //�������������ż�ķ������
                    operator_stk.pop(); //�����ų�ջ
                }
                else if (q < p) operator_stk.push(*it); //ջ��Ԫ�����ȼ��ϵ�
                else {//ջ��Ԫ�����ȼ����� 
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
    
    cout << "����һ������� ֧�ֵ��������ͣ�����������ȷ��һλС�������������վ�ȷ��һλС�����������룩" << endl;
    cout << "ʹ������: 1 + 2 - 3 ��� 0.0" << endl;
    cout << "ʹ������: 2 * 3 / 4 ��� 1.5" << endl;
    cout << "ʹ������: (2 + 4 * 3.5) * 6 ��� 96.0" << endl;
    cout << "ʹ������: ((4 * 3 + 2) / (6.4 - 2.4) - 10) * (6.4 - 7.2) + (-2) * 4 ��� -2.8" << endl;
    cout << "===================================" << endl;
    cout << "��������: 1++1 ��� ����������" << endl;
    cout << "ʹ������: ((1 + 1) * (2 - 1) ��� Բ���Ų�ƥ��" << endl;
    cout << "ʹ������: 1..1+1 ��� ���ָ�ʽ����" << endl;
    cout << "ʹ������: 1 / (2 * 4 - 8) ��� ����Ϊ��" << endl;
    cout << "===================================" << endl;
    cout << "�������� 1 + 2 3 * 4 �����ʶ��Ϊ 1 + 23 * 4 ������Ϊ�Ǵ���" << endl;
    cout << "���������������ַ���������ֵֹĶ�������֤������Ƚ���,����Ҫ��Ҫ��������!" << endl;
    cout << "Դ�ļ������� https://github.com/Ricky-Daxia/my_proj/tree/3_2_2/calculator ��" << endl;
    cout << "===================================" << endl;
    cout << endl << endl << "������Ҫ����ı��ʽ:";
    cin.sync();
    getline (cin, test);

    if (expr_validity(filter(test)))
        eval (infix_to_suffix(generate_expr(filter(test))));

    cout << "�ڼ���������֤����öԲ���?" << endl;
    cout << "��ӭ�´�ʹ��!" << endl;



    system("pause");
}
