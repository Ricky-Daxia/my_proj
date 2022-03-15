#include "user.h"

bool contain_all_nums (string& val) { //注册函数的辅助
    for (int i = 0; i < val.size(); ++i)
        if (val[i] < '0' || val[i] > '9') return false;
    return true;
}

string sql_time () {
    time_t rawtime = time(0);
    struct tm localtm = *localtime(&rawtime);
    int year = localtm.tm_year + 1900;
    int month = localtm.tm_mon + 1;
    int day = localtm.tm_mday;
    int hour = localtm.tm_hour;
    int min = localtm.tm_min;
    int sec = localtm.tm_sec;
    string d1, d2, d3;
    d1 = to_string(year) + "-";
    if (month < 10) d1 += "0";
    d2 = to_string(month) + "-";
    if (day < 10) d2 += "0";
    d3 = to_string(day);
    d1 += d2 + d3;
    string h, m, s;
    if (hour < 10) h = "0" + to_string(hour);
    else h = to_string(hour);
    if (min < 10) m = "0" + to_string(min);
    else m = to_string(min);
    if (sec < 10) s = "0" + to_string(sec);
    else s = to_string(sec);
    return d1 + " " + h + ":" + m + ":" + s + ": ";
}

void save_sql_ban (string commmands) {
    ofstream ofs;
    ofs.open ("commands.txt", ios::app);
    if (!ofs.is_open()) {
        cout << "出现了意想不到的错误!" << endl;
        exit(-1);
    }
    ofs << sql_time << commmands << endl;
    ofs.close();
}

user:: user (string UID, string user_name, string user_password, string contact, string address, float balance, string status) {
    this->UID = UID;
    this->user_name = user_name;
    this->user_password = user_password;
    this->contact = contact;
    this->address = address;
    this->balance = balance;
    this->status = status;
}

void parse_ban (vector<string> commands, vector<user*>& user_list) {
    if (commands.size() < 2 || commands[0].size() < 3) return;
    cout << "生成的指令为: " << commands[0] << endl;
    //Delay (1000);
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

    if (words[0] == "UPDATE" && words[1] == "user") {
        for (auto& tmp: user_list)
            if (tmp->UID == words[words.size() - 1])
                {tmp->status = "封禁";
                save_sql_ban(command);
                }
        
    }
    cout << "无法解析的sql指令!" << endl;
}




void show_admin_menu () {
    cout << "======================================================================================" << endl;
    cout << "1.查看所有商品 2.搜索商品 3.下架商品 4.查看所有订单 5.查看所有用户 6.封禁用户 7.注销" << endl;
    cout << "======================================================================================" << endl;
    cout << endl;
}

void display_user_list (vector<user*>& user_list) { //展示用户列表
    cout << "*********************************************************************************************************************" << endl;
    cout << "用户ID     用户名        联系方式                  地址                                        钱包余额    用户状态" << endl;
    for (vector<user*>::iterator it = user_list.begin(); it != user_list.end(); ++it) {
            cout << left << setw(4) << (*it)->UID << "       ";
            cout << left << setw(10) << (*it)->user_name << "    ";
            cout << left << setw(20) << (*it)->contact << "      ";
            cout << left << setw(40) << (*it)->address << "     ";
            cout << left << fixed << setprecision(1) << setw(10) << (*it)->balance << "   ";
            cout << left << setw(10) <<(*it)->status << endl;
    }
    cout << "*********************************************************************************************************************" << endl;
    cout << endl;
}

int ban_user (vector<user*>& user_list, string UID) { //封禁用户
    for (vector<user*>::iterator it = user_list.begin(); it != user_list.end(); ++it) {
        if ((*it)->UID == UID && (*it)->status == "正常") {
            cout << "确定要封禁该用户吗?" << endl;
            cout << "*************************************************************************************************************" << endl;
            cout << "用户ID     用户名        联系方式                  地址                                        钱包余额" << endl;
            cout << left << setw(4) << (*it)->UID << "       ";
            cout << left << setw(10) << (*it)->user_name << "    ";
            cout << left << setw(20) << (*it)->contact << "      ";
            cout << left << setw(40) << (*it)->address << "     ";
            cout << left << fixed << setprecision(1) <<(*it)->balance << endl;
            cout << "*************************************************************************************************************" << endl;
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
                    string ban = "UPDATE user SET 状态=封禁 WHERE ID= " + UID;
                    parse_ban ({ban}, user_list);
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

void modify_user_info (vector<user*> user_list, string UID, vector<string> name_list) {
    for (vector<user*>::iterator it = user_list.begin(); it != user_list.end(); ++it)
        if ((*it)->UID == UID) {
            cout << "请选择修改的属性 (1.用户名 2.联系方式 3.地址) : ";
            string choice = "";
            while (true) {
                cin.sync();
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
                else break;
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
