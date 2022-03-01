#include "trading_platform.h"
#include<fstream>
#include<ctime>
#include<conio.h>
#include<iomanip>

void Delay(int   time)//time*1000为秒数 
{ 
    clock_t   now   =   clock(); 

    while(   clock()   -   now   <   time   ); 
} 

inline bool contain_all_nums (string& val) { //注册函数的辅助
    for (int i = 0; i < val.size(); ++i)
        if (val[i] < '0' || val[i] > '9') return false;
    return true;
}

inline bool contain_space (string& str) {
    for (int i = 0; i < str.size(); ++i)
        if (str[i] == ' ') return true;
    return false;
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
                user_list.push_back(new user(attributes[0], attributes[1], attributes[2], attributes[3], attributes[4], stof(attributes[5]), temp));
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
            commodity_list.push_back(new commodity(attributes[0], attributes[1], stof(attributes[2]), stoi(attributes[3]), attributes[4], attributes[5], attributes[6], temp));
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
            order_list.push_back(new order(attributes[0], attributes[1], stof(attributes[2]), stoi(attributes[3]), attributes[4], attributes[5], temp));
            temp = "", attributes = {}, buffer = "";
            }
        }
    }
    ifs.close();
}

trading_platform:: ~trading_platform () {
    
}

void trading_platform:: show_menu () {
    cout << "============================================" << endl;
    cout << "冬奥纪念品交易平台 为中国奥运健儿加油" << endl;
    cout << "1.管理员登录 2.用户注册 3.用户登录 4.退出程序" << endl;
    cout << "============================================" << endl;
    cout << endl;
}
//1 o
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
//2 o
void trading_platform:: sign_up () { //基本完成检查(不能查中文)
    string user_password = "", contact = "";
    string user_name = "", address = "";
    float balance = 0.0;

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
//3 o
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
    return {};
}

void show_admin_menu () {
    cout << "======================================================================================" << endl;
    cout << "1.查看所有商品 2.搜索商品 3.下架商品 4.查看所有订单 5.查看所有用户 6.封禁用户 7.注销" << endl;
    cout << "======================================================================================" << endl;
    cout << endl;
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

void display_commodity_list (vector<commodity*>& commodity_list) { //展示商品列表
    cout << "*******************************************************************************" << endl;
    cout << "商品ID     名称     价格     数量    卖家ID     上架时间     商品状态" << endl;
    for (vector<commodity*>::iterator it = commodity_list.begin(); it != commodity_list.end(); ++it) {
        cout << (*it)->commodity_id << "  " << (*it)->commodity_name << "  " << fixed << setprecision(1) <<(*it)->price << "    "
            << setprecision(0) <<(*it)->stock << "  " << (*it)->trader_id << "   " << (*it)->launch_time
            << "   " << (*it)->commodity_status << endl;
    }
    cout << "*******************************************************************************" << endl;
    cout << endl;
}
//4 o
void search_commodity (vector<commodity*>& commodity_list) { //搜索商品
    cout << "请输入商品名称:";
    string key_word = "";
    cin.sync();
    getline (cin, key_word);
    cout << "*******************************************************************************" << endl;
    bool is_found = false, flag = true, column = false;
    for (vector<commodity*>::iterator it = commodity_list.begin(); it != commodity_list.end(); ++it) {
        for (int i = 0; i < (*it)->commodity_name.size(); ++i) {
            if (key_word[0] == (*it)->commodity_name[i]) {
                for (int j = 0; j < key_word.size(); ++j)
                    if (i + j >= (*it)->commodity_name.size() || key_word[j] != (*it)->commodity_name[i + j]) {
                        flag = false;
                        break;
                    }
                if (flag) is_found = true;
                break;
            }
        }
        if (is_found) {
            if (!column) {
                cout << "商品ID     名称     价格     数量     描述     卖家ID     上架时间     商品状态" << endl;
                column = true;
            }
             cout << (*it)->commodity_id << "  " << (*it)->commodity_name << "  " << fixed << setprecision(1) << (*it)->price << "    "
                << setprecision(0) <<(*it)->stock << "  " << (*it)->text << "  " << (*it)->trader_id << "   " << (*it)->launch_time
                << "   " << (*it)->commodity_status << endl;
        }
    }
    if (!column) cout << "没有找到您想要的商品!即将返回初始界面" << endl;
    cout << "*******************************************************************************" << endl;
    cout << endl;
}
//5 o
int remove_commodity (vector<commodity*>& commodity_list, string UID) {
    cout << "请输入要下架的商品ID:" << endl;
    string commodity_id = "";
    cin.sync();
    getline (cin, commodity_id);
    for (vector<commodity*>::iterator it = commodity_list.begin(); it != commodity_list.end(); ++it)
        if ((UID == "" && (*it)->commodity_id == commodity_id) || ((*it)->trader_id == UID && (*it)->commodity_id == commodity_id)) {
            cout << "要确定下架该商品吗?" << endl;
            cout << "*******************************************************************************" << endl;
            cout << "商品ID     名称     价格     数量     卖家ID     上架时间     商品状态" << endl;
            cout << (*it)->commodity_id << "  " << (*it)->commodity_name << "  " << fixed << setprecision(1) <<(*it)->price << "    "
                << setprecision(0) << (*it)->stock << "  " << (*it)->trader_id << "   " << (*it)->launch_time
                << "   " << (*it)->commodity_status << endl;
            cout << "*******************************************************************************" << endl;

            cout << "请选择(y/n):";
            string choice = "";
            while (true) { 
                cin.sync();
                getline (cin, choice);
                while (!cin || choice.size() <= 0 || choice.size() > 1 || (choice[0] != 'y' || choice[0] != 'n')) {
                    cout << endl << "发生了意想不到的错误!请重新输入选择(y/n):";
                    cin.clear();
                    cin.sync();
                    getline (cin, choice);
                }
                 
                if (choice[0] == 'y') {
                    cout << "下架成功!" << endl;
                    (*it)->commodity_status = "已下架";
                    return 1;
                }
                else if (choice[0] == 'n') return -1;
                else cout << "无效选择!请重新输入:" << endl;
            }
        }
    cout << "没有找到此商品!" << endl;
    cout << endl;
    return -1;
}

void display_order_list (vector<order*>& order_list) {
    cout << "*******************************************************************************" << endl;
    cout << "订单ID   商品ID   交易单价   数量   交易时间   卖家ID   买家ID" << endl;
    for (vector<order*>::iterator it = order_list.begin(); it != order_list.end(); ++it)
        cout << (*it)->order_id << "   " << (*it)->commodity_id << "   "
            << fixed << setprecision(1) <<(*it)->trade_price << "   " << setprecision(0) << (*it)->sold_num << "   "
            << (*it)->trade_time << "   " << (*it)->trader_id << "   "
            << (*it)->buyer_id << endl;
    cout << "*******************************************************************************" << endl;
    cout << endl;
}

void display_user_list (vector<user*>& user_list) { //展示用户列表
    cout << "*******************************************************************************" << endl;
    for (vector<user*>::iterator it = user_list.begin(); it != user_list.end(); ++it) {
        cout << "用户ID         用户名        联系方式        地址        钱包余额" << endl;
        cout << (*it)->UID << "     " << (*it)->user_name << "     " << (*it)->contact << "     "
            << (*it)->address << "     " << fixed << setprecision(1) << (*it)->balance << endl;
    }
    cout << "*******************************************************************************" << endl;
    cout << endl;
}
//6 o
int ban_user (vector<user*>& user_list) { //封禁用户
    cout << "请输入要封禁的用户ID:";
    string UID = "";
    cin.sync();
    getline (cin, UID);
    for (vector<user*>::iterator it = user_list.begin(); it != user_list.end(); ++it) {
        if ((*it)->UID == UID && (*it)->status == "正常") {
            cout << "确定要封禁该用户吗?" << endl;
            cout << "*******************************************************************************" << endl;
            cout << "用户ID         用户名        联系方式        地址        钱包余额" << endl;
            cout << (*it)->UID << "     " << (*it)->user_name << "     " << (*it)->contact << "     "
                << (*it)->address << "     " << fixed << setprecision(1) <<(*it)->balance << endl;
            cout << "*******************************************************************************" << endl;
            cout << "请选择(y/n):";
            string choice = "";
            while (true) {
                getline (cin, choice);
                while (!cin || choice.size() <= 0 || choice.size() > 1) {
                    cout << endl << "发生意想不到的错误!请重新输入选择(y/n):";
                    cin.clear();
                    cin.sync();
                    getline (cin, choice);
                }
                cout << endl;
                if (choice[0] == 'y') {
                    (*it)->status = "封禁";
                    cout << "封禁成功!" << endl;
                    cout << endl;
                    return 1;
                }
                else if (choice[0] == 'n') {
                    cout << "已取消" << endl;
                    cout << endl;
                    return -1;
                } 
                else cout << "输入有误!" << endl;
            }
        }
    }
    cout << "未找到该用户或该用户已被封禁!" << endl;
    cout << endl;
    return -1;
}
//7 o
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
            case 1: //查看所有商品
                display_commodity_list (commodity_list);
                system("pause");
                break;
            case 2: //搜索商品
                search_commodity (commodity_list);
                system("pause");
                break;
            case 3: //下架商品
                res = remove_commodity (commodity_list, "");
                if (res == 1) this->save_commodity();
                system("pause");
                break;
            case 4: //查看所有订单
                display_order_list (order_list);
                system("pause");
                break;
            case 5: //查看所有用户
                display_user_list (user_list);
                system("pause");
                break;
            case 6: {//封禁用户
                res = ban_user (user_list);
                if (res == 1) this->save_user();
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

void display_user_menu () {
    cout << "================================================" << endl;
    cout << "1.我是卖家 2.我是买家 3.个人信息管理 4.注销登录" << endl;
    cout << "================================================" << endl;
    cout << endl;
}

void display_buyer_menu () {
    cout << "=========================================================================================" << endl;
    cout << "1.查看商品列表 2.购买商品 3.搜索商品 4.查看历史订单 5.查看商品详细信息 6.返回用户主界面" << endl;
    cout << "=========================================================================================" << endl;
    cout << endl;
}

void display_trader_menu () {
    cout << "=====================================================================================" << endl;
    cout << "1.发布商品 2.查看发布商品 3.修改商品信息 4.下架商品 5.查看历史订单 6.返回用户主界面" << endl;
    cout << "=====================================================================================" << endl;
    cout << endl;
}
//8 o
int launch_commodity (vector<commodity*>& commodity_list, string UID) { //卖家发布商品
    string commodity_name = "", text = "";
    float price = 0;
    int num = 0;
    cout << "请输入商品名称(不超过10个字符):";
    cin.sync();
    getline (cin, commodity_name);

    cout << "请输入商品价格(1位小数):";
    cin >> price;
    while (!cin) {
        cout << "发生意想不到的错误!请重新输入:";
        cin.clear();
        cin.sync();
        cin >> price;
    }
    cin.sync();
    cout << "请输入商品数量:";
    cin >> num;
    while (!cin) {
        cout << "发生意想不到的错误!请重新输入:";
        cin.clear();
        cin.sync();
        cin >> num;
    }
    cout << "请输入商品描述(不超过100个字符):";
    cin.sync();
    getline (cin, text);

    bool vaildity = true;
    if (commodity_name.size() <= 0 || commodity_name.size() > 10) vaildity = false;
    else if (price < 0 || (price * 10) - int(price * 10) != 0) vaildity = false;
    else if (num <= 0) vaildity = false;
    else if (text.size() > 100) vaildity = false;

    if (vaildity) {
        cout << "请确定发布的商品信息无误!" << endl;
        for (int i = 0; i < text.size() + 5; ++i) cout << '*';
        cout << endl;
        cout << "商品名称:" << commodity_name << endl;
        cout << "商品价格:" << fixed << setprecision(1) << price << endl;
        cout << "商品数量:" << setprecision(0) <<num << endl;
        cout << "商品描述:" << text << endl; 
        for (int i = 0; i < text.size() + 5; ++i) cout << '*';
        cout << endl << endl;
        cout << "您确定要发布商品吗? (y/n)";
        string choice = "";
        while (true) {
            getline (cin, choice);
            while (!cin || choice.size() <= 0 || choice.size() > 1) {
                cout << "发生意想不到的错误!请重新输入:";
                cin.clear();
                cin.sync();
                getline (cin, choice);
            }
            if (choice[0] == 'y') {
                cout << "发布成功!" << endl;
                break;
            }
            else if (choice[0] == 'n') return -1;
            else
                cout << "无效输入!请重新输入:";
        }
        cin.sync();
        time_t now = time (0);
        tm* ltime = localtime (&now);
        string launch_date = to_string(ltime->tm_year + 1900) + "-" + to_string(1 + ltime->tm_mon) + 
            "-" + to_string(ltime->tm_mday);
        
        string commodity_id = "M";
        int commodity_num = commodity_list.size();
        if (commodity_num < 9) commodity_id += "00" + to_string(commodity_num + 1);
        else if (commodity_num < 99) commodity_id += "0" + to_string(commodity_num + 1);
        else commodity_id += to_string(commodity_num + 1);

        commodity_list.push_back (new commodity(commodity_id, commodity_name, price, num, text, UID, launch_date, COMMODITY_NORMAL));
        return 1;
    }
    cout << "商品信息不符合格式!" << endl;
    return 0;
}

void display_launched_commodity (vector<commodity*>& commodity_list, string UID) { //展示卖家商品列表
    cout << "**************************************************************************" << endl;
    cout << "商品ID     名称     价格     数量    上架时间     商品状态" << endl;
    for (vector<commodity*>::iterator it = commodity_list.begin(); it != commodity_list.end(); ++it) 
        if ((*it)->trader_id == UID)
            cout << (*it)->commodity_id << "  " << (*it)->commodity_name << "  " << fixed << setprecision(1) <<(*it)->price << "    "
                << setprecision(0) << (*it)->stock << "  " << (*it)->launch_time << "   " << (*it)->commodity_status << endl;
    cout << "**************************************************************************" << endl;
    cout << endl;

}
//9 o
int modify_commodity (vector<commodity*>& commodity_list, string UID) { //卖家修改商品
    string commodity_id = "";
    float modify_price = 0; 
    string modify_text = "";
    cout << "请输入被修改商品的ID:";
    cin.sync();
    getline (cin, commodity_id);
    for (vector<commodity*>::iterator it = commodity_list.begin(); it != commodity_list.end(); ++it) 
        if ((*it)->commodity_id == commodity_id) {
            cout << "请输入被修改商品的属性(1.价格 2.描述):";
            string choice = "";
            while (true) {
                getline (cin, choice);
                while (!cin || choice.size() <= 0 || choice.size() > 1) {
                    cout << "发生意想不到的错误!请重新输入:";
                    cin.clear();
                    cin.sync();
                    getline (cin, choice);
                }
                if (choice[0] == '1' || choice[0] == '2') break;
                else cout << "无效输入!请重新输入:";
            }
            if (choice[0] == 1) {
                cout << "请输入被修改商品的价格:";
                cin >> modify_price;
                while (!cin || modify_price < 0 || (modify_price * 10) - int(modify_price * 10) != 0) {
                    cout << "输入有误!请重新输入:";
                    modify_price = 0;
                    if (!cin) {
                        cin.clear();
                        cin.sync();
                    }
                    cin >> modify_price;
                }
            }
            else {
                cout << "请输入被修改商品的描述:";
                cin.sync();
                getline (cin, modify_text);
                while (modify_text.size() > 100) {
                    cout << "输入有误!请重新输入:";
                    modify_text.resize(0);
                    cin.sync();
                    getline (cin, modify_text);
                }
            }
            cout << endl;
            cout << "请确认被修改的商品信息无误!" << endl;
            for (int i = 0; i < 25; ++i) cout << '*';
            cout << endl;
            cout << "商品ID: " << UID << endl;
            cout << "商品名称: " << (*it)->commodity_name << endl;
            if (choice[0] == 1) {
                cout << "商品价格: " << fixed << setprecision(1) << modify_price << endl;
                cout << "商品描述: " << (*it)->text << endl;
            }
            else {
                cout << "商品价格: " << fixed << setprecision(1) << (*it)->price << endl;
                cout << "商品描述: " << modify_text << endl;
            }
            for (int i = 0; i < 25; ++i) cout << '*';
            cout << endl;
            cout << "确认修改? (y/n)";
            string c = "";
            while (true) {
                cin.sync();
                getline (cin, c);
                while (!cin || c.size() <= 0 || c.size() > 1) {
                    cout << "发生意想不到的错误!请重新输入:";
                    cin.clear();
                    cin.sync();
                    getline (cin, c);
                }
                if (c[0] != 'y' && c[0] != 'n')
                    cout << "无效输入!请重新输入 (y/n) ";
            }
            if (c[0] == 'y') {
                if (choice[0] == 1) (*it)->price = modify_price;
                else (*it)->text = modify_text;
                cout << "修改成功!" << endl << endl;
                return 1;
            }
            else break;
        }
    cout << "没有找到该商品!" << endl << endl;
    return 0;
}

void display_trader_orders (vector<order*>& order_list, string UID) { //展示卖家订单
    cout << "******************************************************" << endl;
    cout << "订单ID  商品ID  交易单价  数量   交易时间   买家ID" << endl;
    for (vector<order*>::iterator it = order_list.begin(); it != order_list.end(); ++it) 
        if ((*it)->trader_id == UID)
            cout << (*it)->order_id << "   " << (*it)->commodity_id << "   " 
                << fixed << setprecision(1) <<(*it)->trade_price << "  " << setprecision(0) <<(*it)->sold_num << "  "
                << (*it)->trade_time << "  " << (*it)->buyer_id << endl;
    cout << "******************************************************" << endl;
    cout << endl;
}
//1 o
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
                display_launched_commodity (commodity_list ,cur_UID);
                system("pause");
                break;
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
                display_trader_orders (order_list, cur_UID);
                system("pause");
                break;
            case 6:
                return;
            default:
                cout << "无效操作!" << endl;
                break;
        } 
    }
}
//2 o
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

void best_selling (vector<commodity*>& commodity_list) {
    cout << "*******************************************************************************" << endl;
    cout << "商品ID     名称     价格     上架时间     卖家ID" << endl;
    for (vector<commodity*>::iterator it = commodity_list.begin(); it != commodity_list.end(); ++it) {
        if ((*it)->commodity_status == COMMODITY_NORMAL)
            cout << (*it)->commodity_id << "  " << (*it)->commodity_name << "  " << fixed << setprecision(1) << (*it)->price 
                << "   " << (*it)->launch_time << "   " << (*it)->trader_id << endl;
    }
    cout << "*******************************************************************************" << endl;
    cout << endl;  
}
//3 o
float purchase_commodity (vector<user*> user_list, string UID, vector<commodity*>& commodity_list, vector<order*>& order_list) {
    float cur_balance = 0;
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
                if ((*it)->commodity_id == search_id && (*it)->commodity_status == COMMODITY_NORMAL) {
                    if ((*it)->stock < perchase_num)
                        cout << "商品库存不足!" << endl;
                    else if (cur_balance < (*it)->price * perchase_num)
                        cout << "余额不足!" << endl;
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
                        float new_balance = cur_balance - (*it)->price * perchase_num;
                        cout << "您的余额: " << fixed << setprecision(1) <<new_balance << endl;
                        //对商品修改
                        int rest = (*it)->stock - perchase_num;
                        (*it)->stock = rest;
                        if (rest == 0) (*it)->commodity_status = COMMODITY_OUT; 
                        //对订单修改
                        string order_id = "T";
                        int order_cur_size = order_list.size();
                        if (order_cur_size < 9) order_id += "00" + to_string(order_cur_size + 1);
                        else if (order_cur_size < 99) order_id += "0" + to_string(order_cur_size + 1);
                        else order_id += to_string(order_cur_size + 1);
                        order_list.push_back(new order(order_id, (*it)->commodity_id, (*it)->price, perchase_num, trade_date, (*it)->trader_id,UID));
                        (*it1)->balance = new_balance;
                        return new_balance;
                    }
                    cout << "**************************************************" << endl;
                    return cur_balance;
                }
            cout << "没有找到该商品!" << endl;
            cout << "**************************************************" << endl;
    }
    return cur_balance;
}
//4 o
void search_on_sale (vector<commodity*>& commodity_list) { 
    cout << "请输入商品名称:";
    string key_word = "";
    cin.sync();
    getline (cin, key_word);
    cout << "*******************************************************************************" << endl;
    bool is_found = false, flag = true, column = false;
    for (vector<commodity*>::iterator it = commodity_list.begin(); it != commodity_list.end(); ++it) {
        for (int i = 0; i < (*it)->commodity_name.size(); ++i) {
            if (key_word[0] == (*it)->commodity_name[i]) {
                for (int j = 0; j < key_word.size(); ++j)
                    if (i + j >= (*it)->commodity_name.size() || key_word[j] != (*it)->commodity_name[i + j]) {
                        flag = false;
                        break;
                    }
                if (flag) is_found = true;
                break;
            }
        }
        if (is_found && (*it)->commodity_status == COMMODITY_NORMAL) {
            if (!column) {
                cout << "商品ID     名称     价格     卖家ID     上架时间" << endl;
                column = true;
            }
            cout << (*it)->commodity_id << "   " << (*it)->commodity_name << "   " << fixed << setprecision(1) << (*it)->price << "    "
                        << (*it)->trader_id << "   " << (*it)->launch_time << endl;
        }
        is_found = false, flag = true;
    }
        
    if (!column) cout << "没有找到您想要的商品!即将返回初始界面" << endl;
    cout << "*******************************************************************************" << endl;
    cout << endl;
}

void display_buyer_order (vector<order*> order_list, string UID) {
    cout << "******************************************************" << endl;
    cout << "订单ID  商品ID  交易单价  数量   交易时间   卖家ID" << endl;
    for (vector<order*>::iterator it = order_list.begin(); it != order_list.end(); ++it) 
        if ((*it)->buyer_id == UID)
            cout << (*it)->order_id << "   " << (*it)->commodity_id << "   " 
                << fixed << setprecision(1) << (*it)->trade_price << "  " << setprecision(0) <<(*it)->sold_num << "  "
                << (*it)->trade_time << "  " << (*it)->trader_id << endl;
    cout << "******************************************************" << endl;
    cout << endl;  
}
//5 o
void display_details (vector<commodity*> commodity_list) {
    cout << "请输入您想要查看的商品ID: ";
    string search_id;
    cin.sync();
    getline (cin, search_id);
    cout << "*******************************************" << endl;
    bool is_found = false;
    for (vector<commodity*>::iterator it = commodity_list.begin(); it != commodity_list.end(); ++it) 
        if ((*it)->commodity_id == search_id && (*it)->commodity_status == COMMODITY_NORMAL) {
            cout << "商品ID: " << (*it)->commodity_id << endl;
            cout << "商品名称: " << (*it)->commodity_name << endl;
            cout << "商品价格: " << fixed << setprecision(1) << (*it)->price << endl;
            cout << "上架时间: " << (*it)->launch_time << endl;
            cout << "商品描述: " << (*it)->text << endl;
            cout << "商品卖家: " << (*it)->trader_id << endl;
            is_found = true;
            break;
        }
    if (!is_found) cout << "没有找到该商品!" << endl;
    cout << "*******************************************" << endl;   
}
//6 o
void trading_platform:: buyer_menu (string cur_UID, float cur_balance) { //
    int res = 0;
    string choice = "";
    float return_info = 0;

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
                best_selling (commodity_list);
                system("pause");
                break;
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
                search_on_sale (commodity_list);
                system("pause");
                break;
            case 4:
                display_buyer_order (order_list, cur_UID);
                system("pause");
                break;
            case 5:
                display_details (commodity_list);
                system("pause");
                break;
            case 6:
                return;
            default:
                cout << "无效操作!" << endl;
                break;
        } 
    }
}

void user_info_menu () {
    cout << "===============================================" << endl;
    cout << "1.查看信息 2.修改信息 3.充值 4.返回用户主界面" << endl;
    cout << "===============================================" << endl;
    cout << endl;
}

void show_user_info (vector<user*> user_list, string UID) {
    for (vector<user*>::iterator it = user_list.begin(); it != user_list.end(); ++it)
        if ((*it)->UID == UID) {
            cout << "*********************" << endl;
            cout << "用户名: " << (*it)->user_name << endl;
            cout << "联系方式: " << (*it)->contact << endl;
            cout << "地址: " << (*it)->address << endl;
            cout << "钱包余额: " << fixed << setprecision(1) <<(*it)->balance << endl;
            cout << "*********************" << endl;
            cout << endl;
        }
}
//7 o
void modify_user_info (vector<user*> user_list, string UID, vector<string> name_list) {
    for (vector<user*>::iterator it = user_list.begin(); it != user_list.end(); ++it)
        if ((*it)->UID == UID) {
            cout << "请选择修改的属性 (1.用户名 2.联系方式 3.地址) : ";
            string choice = "";
            while (true) {
                getline (cin, choice);
                while (!cin || choice.size() <= 0 || choice.size() > 1) {
                    cout << "发生意想不到的错误!请重新输入:";
                    cin.clear();
                    cin.sync();
                    getline (cin, choice);
                }
                if (choice[0] != '1' && choice[0] != '2' && choice[0] != '3') {
                    cout << "无效操作!请重新输入 (1.用户名 2.联系方式 3.地址) :";
                    cin.sync();
                }
            }
            cin.sync();
            if (choice[0] == '1') {
                string pre_name = (*it)->user_name;
                cout << "请选择修改后的用户名: ";
                string new_name = ""; 
                cin.sync();
                getline (cin, new_name);
                while (new_name.size() > 20 || new_name.size() <= 0) {
                    cout << "用户名不合法!" << endl << "请重新输入用户名(不超过10个字符):";
                    new_name.resize (0);
                    cin.sync();
                    getline (cin, new_name);
                }
                if (!name_list.empty()) { //保证用户名唯一
                    bool is_only = false;
                    while (!is_only){
                        is_only = true;
                        for (vector<string>::iterator it = name_list.begin(); it != name_list.end(); ++it)
                            if (new_name == *it) {
                                cout << endl << "用户名已存在!请重新输入用户名:";
                                cin.sync();
                                getline (cin, new_name);
                                while (new_name.size() > 20 || new_name.size() <= 0) {
                                    cout << endl << "用户名不合法!请重新输入用户名:";
                                    new_name.resize (0);
                                    cin.sync();
                                    getline (cin, new_name);
                                }
                                is_only = false;
                                break;
                            }   
                    }   
                }
                (*it)->user_name = new_name;
                for (vector<string>::iterator it2 = name_list.begin(); it2 != name_list.end(); ++it2)
                    if (*it2 == pre_name) *it2 = new_name;
            }
            else if (choice[0] == '2') {
                cout << "请输入修改后的联系方式: ";
                string new_contact = "";
                cin.sync();
                getline (cin, new_contact);
                while (new_contact.size() > 20 || new_contact.size() <= 0 || !contain_all_nums (new_contact)) {
                    cout << endl << "输入有误!请重新输入: ";
                    new_contact.resize (0);
                    cin.sync();
                    getline (cin, new_contact);
                }
                (*it)->contact = new_contact;
            }
            else {
                cout << "请输入修改后的地址: ";
                string new_address = "";
                cin.sync();
                getline (cin, new_address);
                while (new_address.size() > 20 || new_address.size() <= 0) {
                    cout << endl << "输入有误!请重新输入: ";
                    new_address.resize (0);
                    cin.sync();
                    getline (cin, new_address);
                }
                (*it)->address = new_address;
            }
        }
    cout << endl << "修改成功!" << endl;
}
//8 o
void deposit (vector<user*> user_list, string UID) {
    for (vector<user*>::iterator it = user_list.begin(); it != user_list.end(); ++it)
        if ((*it)->UID == UID) {
            cout << "请输入充值金额: ";
            float amount = 0;
            while (true) {
                cin >> amount;
                while (!cin) {
                    cout << "发生意想不到的错误!请重新输入:";
                    cin.clear();
                    cin.sync();
                    cin >> amount;
                }
                cin.sync();
                bool vaildity = true;
                if (amount * 10 - int(amount * 10) != 0)
                    vaildity = false;
                if (vaildity) break;
                else cout << endl << "金额不符合规范!请重新输入金额: ";
            }
            float new_amount = (*it)->balance + amount;
            (*it)->balance = new_amount;
            cout << "充值成功,当前余额: " << new_amount << endl;
        } 
}
//9 o
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