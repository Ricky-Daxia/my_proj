#include "trading_platform.h"
#include<fstream>
#include<ctime>
#include<conio.h>
#include<iomanip>
vector<user*> user_list = {};
vector<string> name_list = {};
vector<commodity*> commodity_list = {};
vector<order*> order_list = {};
int user_num = 0;
int commodity_num = 0;
int order_num = 0;


void Delay(int   time)//time*1000为秒数 
{ 
    clock_t   now   =   clock(); 

    while(   clock()   -   now   <   time   ); 
} 

inline bool contain_space (string& str) {
    for (int i = 0; i < str.size(); ++i)
        if (str[i] == ' ') return true;
    return false;
}

bool parse_perchase_commodity (vector<string> commands) {
    if (commands.size() < 2 || commands[0].size() < 3) return false;
    cout << "生成的指令为: " << commands[0] << endl;
    Delay (1000);
    //system("cls");
    string command = commands[0], identity = commands[1], tmp;
    vector<string> words;
    for (int i = 0; i < command.size(); ++i) {
        if (command[i] != ' ') tmp += command[i];
        else {
            words.push_back (tmp);
            tmp.resize (0);
        }
    }
    words.push_back (tmp); //先把命令语句分块

    if (words.size() > 4 && words[0] == sql_INSERT && words[3] == "VALUES" && words[2] == sql_order) {
        //卖家发布商品和买家购买商品时调用
        //INSERT INTO commodity VALUES (val1, val2...)
        //INSERT INTO order VALUES (val1, val2...)
        return true;
        
    }
    cout << "无法解析的sql指令!" << endl;return false;
}

void parse_update (vector<string> commands) {
    if (commands.size() < 2 || commands[0].size() < 3) return;
    cout << "生成的指令为: " << commands[0] << endl;
    Delay (1000);
    //system("cls");
    string command = commands[0], identity = commands[1], tmp;
    vector<string> words;
    for (int i = 0; i < command.size(); ++i) {
        if (command[i] != ' ') tmp += command[i];
        else {
            words.push_back (tmp);
            tmp.resize (0);
        }
    }
    words.push_back (tmp); //先把命令语句分块

    if (words.size() > 4 && words[0] == sql_UPDATE && words[2] == "SET" && words[4] == "WHERE") {
        //管理员
        //下架 UPDATE commodity SET 状态 = 已下架 WHERE ID = ...
        //封禁用户 UPDATE commodity SET 状态 = 已下架 WHERE ID = ...
        //         UPDATE user SET 状态 = 封禁 WHERE ID = ...

        //用户
        //卖家
        //下架商品 UPDATE commodity SET 状态 = 已下架 WHERE ID = ...
        //修改商品 UPDATE commodity SET ... WHERE ID = ...
        //买家 
        //购买 UPDATE commodity SET 数量 = ... WHERE ID = ...
        //若数量为0 则生成 UPDATE commodity SET 状态 = 已下架 WHERE ID = ...
        if (words[1] == sql_commodity) {
            if (identity == sql_admin) {
                for (auto& tmp1: commodity_list) 
                    if (tmp1->trader_id == words[words.size() - 1])
                        tmp1->commodity_status = COMMODITY_OUT;
            }
            else if (identity == sql_trader) {return;}
            else if (identity == sql_buyer) {
                for (auto& tmp1: commodity_list) 
                    if (tmp1->commodity_id == words[words.size() - 1])
                        tmp1->commodity_status = COMMODITY_OUT;
            }
            else {cout << "无法解析的sql指令!" << endl;return;}
        }
        else if (words[1] == sql_user) {
            if (identity == sql_admin) {return;}
            else {cout << "无法解析的sql指令!" << endl;return;}
        }
        else {cout << "无法解析的sql指令!" << endl;return;}
    }
    else {cout << "无法解析的sql指令!" << endl;return;}//无法解析
}





















trading_platform:: trading_platform () { //把用户商品初始化变成类的私有函数然后调用
    user_num = -1, commodity_num = -1, order_num = -1;
    user_list = {}, name_list = {}, commodity_list = {}, order_list = {};
    string buffer = "", temp = "";
    vector<string> attributes = {};
    //初始化用户
    ifstream ifs;
    ofstream ofs;
    ifs.open(USER, ios::in);
    if (!ifs.is_open()){
        ofs.open (USER, ios::out);
        ofs << "用户ID,用户名,密码,联系方式,地址,钱包余额,用户状态" << endl;
        ofs.close();
        user_num = 0;
    }
    else { //读取当前的用户数  
        while (getline(ifs, buffer)) {
            ++user_num;
            if (user_num > 0) {
                for (int i = 0; i < buffer.size(); ++i) { //7个属性存入数组中
                    if (buffer[i] == ',')  {
                        attributes.push_back(temp); 
                        temp = "";
                    }
                    else temp.append(1, buffer[i]);
                }
                //存入
                user_list.push_back(new user(attributes[0], attributes[1], attributes[2], attributes[3], attributes[4], stod(attributes[5]), temp));
                name_list.push_back(attributes[1]);
                temp = "", attributes = {}, buffer = ""; //清空
            }
        }
    }
    ifs.close();

    //初始化商品
    ifs.open (COMMORDITY, ios::in);
    if (!ifs.is_open()) {
        ofs.open (COMMORDITY, ios::out);
        ofs << "商品ID,名称,价格,数量,描述,卖家ID,上架时间,商品状态" << endl;
        ofs.close();
        commodity_num = 0;
    }
    else {
        while (getline(ifs, buffer)) {
            ++commodity_num;
            if (commodity_num > 0) {
                for (int i = 0; i < buffer.size(); ++i) { //7个属性存入数组中
                    if (buffer[i] == ',')  {
                        attributes.push_back(temp); 
                        temp = "";
                    }
                    else temp.append(1, buffer[i]);
                }
            commodity_list.push_back(new commodity(attributes[0], attributes[1], stod(attributes[2]), stoi(attributes[3]), attributes[4], attributes[5], attributes[6], temp));
            temp = "", attributes = {}, buffer = "";
            }
        }
    }
    ifs.close();

    //初始化订单
    ifs.open (ORDER, ios::in);
    if (!ifs.is_open()) {
        ofs.open (ORDER, ios::out);
        ofs << "订单ID,商品ID,交易单价,数量,交易时间,卖家ID,买家ID" << endl;
        ofs.close();
        order_num = 0;
    }
    else {
        while (getline(ifs, buffer)) {
            ++order_num;
            if (order_num > 0) {
                for (int i = 0; i < buffer.size(); ++i) { //7个属性存入数组中
                    if (buffer[i] == ',')  {
                        attributes.push_back(temp); 
                        temp = "";
                    }
                    else temp.append(1, buffer[i]);
                }
            order_list.push_back(new order(attributes[0], attributes[1], stod(attributes[2]), stoi(attributes[3]), attributes[4], attributes[5], temp));
            temp = "", attributes = {}, buffer = "";
            }
        }
    }
    ifs.close();

}

trading_platform:: ~trading_platform () {
    user_list.clear();
    commodity_list.clear();
    order_list.clear();
    name_list.clear();
}

void trading_platform:: show_menu () {
    cout << "============================================" << endl;
    cout << "冬奥纪念品交易平台 为中国奥运健儿加油" << endl;
    cout << "1.管理员登录 2.用户注册 3.用户登录 4.退出程序" << endl;
    cout << "============================================" << endl;
    cout << endl;
}

int trading_platform:: admin_login () {
    string input_name;
    string input_password;

    cout << "请输入管理员姓名:";
    cin.sync ();
    getline(cin, input_name);
    cout << "请输入密码:";
    
    char ch;
    while ((ch = getch()) != '\r'){
        input_password.append(1, char(ch)); //不回显
        }

    cout << endl;

    if (input_name == ADMIN_NAME) {
        if (input_password == ADMIN_PASSWORD){
            cout << "-----登录成功!-----" << endl;
            return 1;
        }
        else cout << "密码错误!" << endl;
    }
    else cout << "管理员姓名错误!" << endl;
    return -1;
}

void trading_platform:: save_user () { //保存用户到文件中
    ofstream ofs;
    ofs.open (USER, ios::trunc);
    if (!ofs.is_open()) {
        cout << "Unexpected Error!";
        exit(-1);
    }
    else {
        ofs << "用户ID,用户名,密码,联系方式,地址,钱包余额,用户状态" << endl;
        for (vector<user*>::iterator it = user_list.begin(); it != user_list.end(); ++it)
            ofs << (*it)->UID << ',' << (*it)->user_name << ','
                << (*it)->user_password << ',' << (*it)->contact << ','
                << (*it)->address << ',' << fixed << setprecision(1) <<(*it)->balance << ','
                << (*it)->status << endl;
    }
    ofs.close();
}

void trading_platform:: sign_up () { //基本完成检查(不能查中文)
    string user_password = "", contact = "";
    string user_name = "", address = "";
    double balance = 0.0;

    cout << "请输入用户名(不超过10个字符):";
    cin.sync();
    getline (cin, user_name);
    while (user_name.size() > 20 || user_name.size() <= 0 || contain_space (user_name)) {
        cout << "用户名不合法!" << endl << "请重新输入用户名(不超过10个字符):";
        user_name.resize (0);
        cin.sync();
        getline (cin, user_name);
    }
    
    cout << "请输入密码(不超过20个字符,由小写字母和数字组成):";
    char ch;
    while ((ch = getch())){
        if (ch == '\r' || user_password.size() >= 20) break; //输够了就不能再输入了
        else if ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z')) {//合法性检查
            user_password.append(1, char(ch)); //注意函数参数
            cout.put('*');
        }
        else {
            cout << endl << "密码中含有不合法字符!" << endl;
            user_password.resize (0);
            cout << "请重新输入密码(不超过20个字符,由小写字母和数字组成):" ;
        }
    }

    cout << endl << "请输入联系方式(不超过20个字符,由数字组成):";
    cin.sync ();
    getline (cin, contact);
    while (contact.size() > 20 || contact.size() <= 0 || !contain_all_nums (contact) || contain_space (contact)) {
        cout << "输入有误!" << endl << "请重新输入联系方式(不超过20个字符,由数字组成):";
        contact.resize (0);
        cin.sync ();
        getline (cin, contact);
    }

    cout << "请输入地址(不超过20个字符,中文汉字或英文字母):";
    cin.sync ();
    getline (cin, address);
    while (address.size() > 20 || contain_space (address)) {
        cout << "输入有误!" << endl << "请重新输入地址(不超过20个字符,中文汉字或英文字母):";
        address.resize (0);
        cin.sync ();
        getline (cin, address);
    }

    if (!name_list.empty()) { //保证用户名唯一
        bool is_only = false;
        while (!is_only){
            is_only = true;
            for (vector<string>::iterator it = name_list.begin(); it != name_list.end(); ++it)
                if (user_name == *it) {
                    cout << "用户名已存在!" << endl << "请重新输入用户名:";
                    getline (cin, user_name);
                    while (user_name.size() > 20 || user_name.size() <= 0) {
                        cout << "用户名不合法!" << endl << "请重新输入用户名:";
                        user_name.resize (0);
                        cin.sync ();
                        getline (cin, user_name);
                    }
                    is_only = false;
                    break;
                }
        }
    } 

    //存入用户列表中
    if (user_list.empty())
        user_list.push_back(new user("U001", user_name, user_password, contact, address, balance, NORMAL));
    else {
        int i = user_list.size();
        string UID;
        if (i > 0 && i < 10) UID = "U00";
        else if (i < 100) UID = "U0";
        else UID = "U";
        
        UID.append(to_string(i + 1));
        user_list.push_back(new user(UID, user_name, user_password, contact, address, balance, NORMAL));
    }
    this->save_user();
    ++user_num;
    cout << "注册成功!" << endl;
}

vector<sub_user_info> trading_platform:: user_login () { //用户登录返回UID和余额
    string user_name, user_password;
    
    cout << "请输入用户名:";
    cin.sync();
    getline (cin, user_name);

    cout << "请输入密码:";
    char ch;
    while ((ch = getch()) != '\r'){
        user_password.append(1, char(ch)); //注意函数参数
        cout.put('*');
    }
    cout << endl;

    for (vector<user*>::iterator it = user_list.begin(); it != user_list.end(); ++it) {
        if ((*it)->user_name == user_name && (*it)->status == "正常") {
            if ((*it)->user_password == user_password) {
                cout << "-----登录成功-----" << endl;
                cout << endl;
                return {sub_user_info ((*it)->UID, (*it)->balance)};
            }
            else cout << "-----密码错误-----" << endl << endl;
            return {};
        }
    }
    cout << "-----用户不存在或已被封禁!-----" << endl << endl;
    Delay (1000);
    return {};
}

void trading_platform:: save_commodity () { //保存商品
    ofstream ofs;
    ofs.open (COMMORDITY, ios::trunc);
    if (!ofs.is_open()) {
        cout << "Unexpected Error!";
        exit(-1);
    }
    else {
        ofs << "商品ID,名称,价格,数量,描述,卖家ID,上架时间,商品状态" << endl;
        for (vector<commodity*>::iterator it = commodity_list.begin(); it != commodity_list.end(); ++it)
            ofs << (*it)->commodity_id << ',' << (*it)->commodity_name << ','
                << fixed << setprecision(1) <<(*it)->price << ',' << setprecision(0) <<(*it)->stock 
                << ',' << (*it)->text << ',' << (*it)->trader_id
                << ',' << (*it)->launch_time << ',' << (*it)->commodity_status << endl;
        ofs.close();
    }
}

void trading_platform:: admin_menu () {

    int res = 0;
    string choice = "";
    
    while (true) {
        system("cls");
        show_admin_menu ();
        cout << "请输入操作:";
        cin.sync();
        getline (cin, choice);
        while (choice.size() > 1 || choice.size() <= 0 || (choice[0] != '1' && choice[0] != '2' && choice[0] != '3' && choice[0] != '4' && choice[0] != '5' && choice[0] != '6' && choice[0] != '7')) {
            cout << endl << "无效输入!请重新输入选择:";
            cin.clear(); 
            cin.sync();
            getline (cin, choice);
        }
        switch (stoi(choice))
        {
            case 1: {//查看所有商品
                string admin_sql_1 = "SELECT * FROM commodity";
                parse_sql_command ({admin_sql_1, "admin"});
                //display_commodity_list (commodity_list);
                system("pause");
                break;}
            case 2: //搜索商品
                {   cout << "请输入商品名称:";
                    string key_word = "";
                    cin.sync();
                    getline (cin, key_word);
                    string admin_sql_2 = "SELECT * FROM commodity WHERE 名称 CONTAINS ";
                    admin_sql_2 += key_word;
                    parse_sql_command ({admin_sql_2, "admin", key_word});
                    //search_commodity (commodity_list, key_word);
                system("pause");
                break;}
            case 3: //下架商品
                res = remove_commodity (commodity_list, "");
                if (res == 1) this->save_commodity();
                system("pause");
                break;
            case 4: //查看所有订单
                {string admin_sql_4 = "SELECT * FROM order";
                parse_sql_command ({admin_sql_4, "admin"});
                //display_order_list (order_list);
                system("pause");
                break;}
            case 5: //查看所有用户
                {string admin_sql_5 = "SELECT * FROM user";
                parse_sql_command ({admin_sql_5, "admin"});
                //display_user_list (user_list);
                system("pause");
                break;}
            case 6: {//封禁用户
                    cout << "请输入要封禁的用户ID:";
                    string UID = "";
                    cin.sync();
                    getline (cin, UID);
                    res = ban_user (user_list, UID);
                    if (res == 1) {
                        this->save_user();
                        string update = "UPDATE commodity SET 状态=已下架 WHERE ID= " + UID;
                        parse_update ({update, "admin"});
                        this->save_commodity();
                    }
                system("pause");
                break;
            }
            case 7: { //注销模块
                cout << "-----确定退出?-----" << endl;
                cout << "-----按'1'确定,按其它键返回-----" << endl;
                // cin >> res;
                // if (!cin || res != 1) 
                //     break;
                // else {
                //     system("cls");
                //     return;
                char c = getch();
                if (c == '1') {
                    system("cls");
                    return;
                }
                else break;
                }
            default:
                break;
            }
            
        }
}

void trading_platform:: trader_menu (string cur_UID) { //卖家界面
    int res = 0;
    string choice = "";

    while (true) {
        system("cls");
        display_trader_menu ();
        cout << "请输入操作:";
        cin.sync();
        getline (cin, choice);
        while (choice.size() > 1 || (choice[0] != '1' && choice[0] != '2' && choice[0] != '3' && choice[0] != '4' && choice[0] != '5' && choice[0] != '6')) {
            cout << "输入有误!请重新输入:";
            choice.resize(0);
            cin.sync();
            getline (cin, choice);
        }
        system("cls");
        switch (stoi(choice)) {
            case 1:
                res = launch_commodity (commodity_list, cur_UID);
                if (res == 1) this->save_commodity();
                system("pause");
                break;
            case 2:
                {string trader_sql_2 = "SELECT * FROM commodity";
                parse_sql_command ({trader_sql_2, "trader", cur_UID});
                //display_launched_commodity (commodity_list ,cur_UID);
                system("pause");
                break;}
            case 3:
                res = modify_commodity (commodity_list, cur_UID);
                if (res == 1) this->save_commodity();
                system("pause");
                break;
            case 4:
                res = remove_commodity (commodity_list, cur_UID);
                if (res == 1) this->save_commodity();
                system("pause");
                break;
            case 5:
                {string trader_sql_5 = "SELECT * FROM order";
                parse_sql_command ({trader_sql_5, "trader", cur_UID});
                //display_trader_orders (order_list, cur_UID);
                system("pause");
                break;}
            case 6:
                return;
            default:
                cout << "无效操作!" << endl;
                break;
        } 
    }
}

int trading_platform:: sub_user_menu () {
    display_user_menu ();
    string choice = "";
    cout << "请输入操作:";
    cin.sync();
    getline (cin, choice);
    while (choice.size() > 1 || (choice[0] != '1' && choice[0] != '2' && choice[0] != '3' && choice[0] != '4')) {
        cout << "输入有误!请重新输入:";
        cin.sync();
        choice.resize(0);
        getline (cin, choice);
        }

    return stoi(choice);
}

double purchase_commodity (vector<user*> user_list, string UID, vector<commodity*>& commodity_list, vector<order*>& order_list) {
    double cur_balance = 0, new_balance = 0;
    bool has_perchased = false, is_found = false;
    string trader_UID = "", deal = "";
    for (vector<user*>::iterator it1 = user_list.begin(); it1 != user_list.end(); ++it1)
        if ((*it1)->UID == UID) {
            cur_balance = (*it1)->balance; 
            cout << "请输入商品ID:";
            string search_id;
            cin.sync();
            getline (cin, search_id);
            cout << "请输入数量:";
            int perchase_num;
            cin >> perchase_num;
            while (!cin) {
                    cout << "发生意想不到的错误!请重新输入:";
                    cin.clear();
                    cin.sync();
                    cin >> perchase_num;
                }
            cin.sync();
            cout << "**************************************************" << endl;
            
            for (vector<commodity*>::iterator it = commodity_list.begin(); it != commodity_list.end(); ++it) 
                if ((*it)->commodity_id == search_id && (*it)->commodity_status == COMMODITY_NORMAL && (*it)->trader_id != UID) {
                    is_found = true;
                    if ((*it)->stock < perchase_num)
                        {cout << "商品库存不足!" << endl;
                        cout << "**************************************************" << endl;}
                    else if (cur_balance < (*it)->price * perchase_num)
                        {cout << "余额不足!" << endl;
                        cout << "**************************************************" << endl;}
                    else {
                        cout << "交易提醒!" << endl;
                        //生成交易时间和新的余额
                        time_t now = time (0);
                        tm* ltime = localtime (&now);
                        string trade_date = to_string(ltime->tm_year + 1900) + "-" + to_string(1 + ltime->tm_mon) + 
                            "-" + to_string(ltime->tm_mday);
                        cout << "交易时间: " << trade_date << endl;
                        cout << "交易单价: " << fixed << setprecision(1) <<(*it)->price << endl;
                        cout << "交易数量: " << perchase_num << endl;
                        cout << "交易状态: 交易成功" << endl;
                        trader_UID = (*it)->trader_id;
                        deal = to_string(perchase_num) + "*" + to_string((*it)->price).substr(0, to_string((*it)->price).find('.') + 2);
                        (*it1)->expr += "-" + deal;
                        new_balance = cur_balance - (*it)->price * perchase_num;
                        //new_balance = API(str_new_balance)[0];
                        cout << "您的余额: " << fixed << setprecision(1) << new_balance << endl;
                        //对商品修改
                        int rest = (*it)->stock - perchase_num;
                        (*it)->stock = rest;
                        if (rest == 0) {
                            string update_order = "UPDATE commodity SET 数量=0 WHERE ID= " + (*it)->commodity_id;
                            parse_update ({update_order, "buyer"});
                        } 
                        //对订单修改
                        string order_id = "T";
                        int order_cur_size = order_list.size();
                        if (order_cur_size < 9) order_id += "00" + to_string(order_cur_size + 1);
                        else if (order_cur_size < 99) order_id += "0" + to_string(order_cur_size + 1);
                        else order_id += to_string(order_cur_size + 1);
                        order_list.push_back(new order(order_id, (*it)->commodity_id, (*it)->price, perchase_num, trade_date, (*it)->trader_id,UID));
                        string buyer_sql_2 = "INSERT INTO order VALUES ";
                        buyer_sql_2 += "(" + order_id + "," + (*it)->commodity_id + "," + to_string((*it)->price) + "," + to_string(perchase_num) + "," + trade_date + "," + (*it)->trader_id + "," + UID + ")";
                        (*it1)->balance = new_balance;
                        if (parse_perchase_commodity ({buyer_sql_2, "buyer"}))
                            has_perchased = true;
                    }
                }
            if (!is_found) {cout << "没有找到该商品!" << endl;
            cout << "**************************************************" << endl;}
    }
    if (has_perchased)
    {for (vector<user*>::iterator it1 = user_list.begin(); it1 != user_list.end(); ++it1)
        if ((*it1)->UID == trader_UID)
            //cout << to_string((*it1)->balance).substr(0, to_string((*it1)->balance).find('.') + 2) + deal << endl;
            {(*it1)->balance = API(to_string((*it1)->balance).substr(0, to_string((*it1)->balance).find('.') + 2) + "+" + deal)[0];
            (*it1)->expr += "+" + deal;}
        return new_balance;
        }
    else return cur_balance;
}

void trading_platform:: buyer_menu (string cur_UID, double cur_balance) { //
    int res = 0;
    string choice = "";
    double return_info = 0;

    while (true) {
        system("cls");
        display_buyer_menu ();
        cout << "请输入操作:";
        getline (cin, choice);
        while (!cin || choice.size() <=  0 || choice.size() > 1 || (choice[0] != '1' && choice[0] != '2' && choice[0] != '3' && choice[0] != '4' && choice[0] != '5' && choice[0] != '6')) {
            cout << "发生意想不到的错误!请重新输入:";
            cin.clear();
            cin.sync();
            getline (cin, choice);
        }
        cin.sync();
        system("cls");
        switch (stoi(choice)) {
            case 1:
                {string buyer_sql_1 = "SELECT * FROM commodity";
                parse_sql_command ({buyer_sql_1, "buyer"});
                //best_selling (commodity_list);
                system("pause");
                break;}
            case 2:
                return_info = purchase_commodity (user_list, cur_UID, commodity_list, order_list);
                if (return_info != cur_balance) {
                    this->save_user();
                    this->save_commodity();
                    this->save_order();
                }
                system("pause");
                break;
            case 3:
                {   cout << "请输入商品名称:";
                    string key_word = "";
                    cin.sync();
                    getline (cin, key_word);
                    string buyer_sql_2 = "SELECT * FROM commodity WHERE 名称 CONTAINS ";
                    buyer_sql_2 += key_word;
                    parse_sql_command ({buyer_sql_2, "buyer", key_word});
                    //search_on_sale (commodity_list);
                system("pause");
                break;}
            case 4:
                {string buyer_sql_4 = "SELECT * FROM order";
                parse_sql_command ({buyer_sql_4, "buyer", cur_UID});
                //display_buyer_order (order_list, cur_UID);
                system("pause");
                break;}
            case 5:
                {   cout << "请输入您想要查看的商品ID: ";
                    string search_id;
                    cin.sync();
                    getline (cin, search_id);
                    string buyer_sql_5 = "SELECT * FROM commodity WHERE ID CONTAINS ";
                    buyer_sql_5 += search_id;
                    parse_sql_command ({buyer_sql_5, "buyer", search_id});
                    //display_details (commodity_list);
                system("pause");
                break;}
            case 6:
                return;
            default:
                cout << "无效操作!" << endl;
                break;
        } 
    }
}

void trading_platform:: manage_user_info (string cur_UID) {
    string choice = "";

    while (true) {
        system("cls");
        user_info_menu ();
        cout << "请输入操作: " << endl;
        while (true) {
            getline (cin, choice);
            while (!cin) {
                cout << "发生意想不到的错误!请重新输入:";
                cin.clear();
                cin.sync();
                getline (cin, choice);
            }
            if (choice.size() <= 0 || choice.size() > 1 || (choice[0] != '1' && choice[0] != '2' && choice[0] != '3' && choice[0] != '4'))
                cout << "无效操作!请重新输入: " << endl;
            else break;
        }
        cin.sync();
        system("cls");
        switch (stoi(choice)) {
            case 1:
                show_user_info (user_list, cur_UID);
                system("pause");
                break;
            case 2:
                modify_user_info (user_list, cur_UID, name_list);
                this->save_user();
                system("pause");
                break;
            case 3:
                deposit (user_list, cur_UID);
                this->save_user();
                system("pause");
                break;
            case 4:
                return;
            default: break;
        }
    }
}

void trading_platform:: save_order () {

    ofstream ofs;
    ofs.open (ORDER, ios::trunc);
    if (!ofs.is_open()) {
        cout << "Unexpected Error!";
        exit(-1);
    }
    else {
        ofs << "订单ID,商品ID,交易单价,数量,交易时间,卖家ID,买家ID" << endl;
        for (vector<order*>::iterator it = order_list.begin(); it != order_list.end(); ++it)
            ofs << (*it)->order_id << ',' << (*it)->commodity_id << ','
                << fixed << setprecision(1) << (*it)->trade_price << ',' << (*it)->sold_num << ','
                << (*it)->trade_time << ',' <<(*it)->trader_id << ','
                << (*it)->buyer_id << endl;
    }
    ofs.close();
}










