#include "commodity.h"


commodity:: commodity (string commodity_id, string commodity_name, double price, 
                        int stock, string text, string trader_id, 
                        string launch_time, string commodity_status) {
                            this->commodity_id = commodity_id;
                            this->commodity_name = commodity_name;
                            this->price = price;
                            this->launch_time = launch_time;
                            this->trader_id = trader_id;
                            this->stock = stock;
                            this->commodity_status = commodity_status;
                            this->text = text;
                        }

comment:: comment(string index, string reply, string time, string UID, string MID, string content, int num, string status) {
    this->index = index;
    this->content = content;
    this->MID = MID;
    this->num = num;
    this->reply = reply;
    this->status = status;
    this->time = time;
    this->UID = UID;
}


bool parse_launch_commodity (vector<string> commands, string commodity_name, double price, int num, string text) {
    if (commands.size() < 2 || commands[0].size() < 3) return false;
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

    if (words.size() > 4 && words[0] == "INSERT" && words[3] == "VALUES") {
        //卖家发布商品和买家购买商品时调用
        //INSERT INTO commodity VALUES (val1, val2...)
        //INSERT INTO order VALUES (val1, val2...)
        if (words[2] == "commodity") {
            //判断发布商品合不合法
            bool vaildity = true;
            if (commodity_name.size() <= 0 || commodity_name.size() > 20) vaildity = false;
            else if (price < 0 || (price * 10) - int(price * 10) != 0) vaildity = false;
            else if (num <= 0) vaildity = false;
            else if (text.size() > 100) vaildity = false;
            return vaildity;
        }
    }
    return false;
}


string sql_time_2 () {
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

string comment_time () {
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
    return d1 + " " + h + ":" + m + ":" + s + ":";
}


void save_sql (string commmands) {
    ofstream ofs;
    ofs.open ("commands.txt", ios::app);
    if (!ofs.is_open()) {
        cout << "出现了意想不到的错误!" << endl;
        exit(-1);
    }
    ofs << sql_time_2() << commmands << endl;
    ofs.close();
}

void save_comments (vector<comment*>& comment_list) {
    // ifstream ifs;
    // int cur_num = 0;
    // ifs.open ("comments.txt", ios::in);
    //     if (!ifs.is_open()) {
    //     cout << "出现了意想不到的错误!" << endl;
    //     exit(-1);
    // }
    // string buffer;
    // while (getline(ifs, buffer)) ++cur_num;
    // ifs.close();

    ofstream ofs;
    ofs.open ("comments.txt", ios::trunc);
    if (!ofs.is_open()) {
        cout << "出现了意想不到的错误!" << endl;
        exit(-1);
    }
    // string index;
    // if (cur_num + 1 < 10) index = "00" + to_string(cur_num + 1);
    // else if (cur_num + 1 < 100) index = "0" + to_string(cur_num + 1);
    // else index = to_string(cur_num + 1);
    
    for (auto& c: comment_list) 
        ofs << c->index << " " << c->reply << " " << c->time << " " << c->UID << " " << c->MID << " " << c->content << " " << c->num << " " << c->status << endl;
    
    ofs.close(); 
}


void parse_modify_commodity_info (vector<string> commands, vector<commodity*>& commodity_list) {
    //{"UPDATE commodity SET ..=.. WHERE ID= 000", "1", "INFO"}
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

    if (words.size() > 4 && words[0] == "UPDATE" && words[2] == "SET" && words[4] == "WHERE") {
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
        if (words[1] == "commodity") {
            string ID = words[words.size() - 1];
            if (commands[1] == "1") {
                for (auto& tmp: commodity_list)
                    if (tmp->commodity_id == ID)
                        {tmp->price = stof(commands[2]);
                        save_sql(command);
                        }
            } //修改价格
            else if (commands[1] == "2") {
                for (auto& tmp: commodity_list)
                    if (tmp->commodity_id == ID)
                        {tmp->text = commands[2];save_sql(command);}
            }//修改描述
            else if (commands[1] == "3") {
                for (auto& tmp: commodity_list)
                    if (tmp->commodity_id == ID)
                        {tmp->commodity_status = COMMODITY_OUT;save_sql(command);}
            }//下架 
        }
        else {cout << "无法解析的sql指令!" << endl;return;}
    }
    else {cout << "无法解析的sql指令!" << endl;return;}//无法解析
}


void display_commodity_list (vector<commodity*>& commodity_list) { //展示商品列表
    // cout << "*******************************************************************************" << endl;
    // cout << "商品ID     名称                  价格    数量   卖家ID  上架时间   商品状态" << endl;
    // for (vector<commodity*>::iterator it = commodity_list.begin(); it != commodity_list.end(); ++it) {
    //     cout << (*it)->commodity_id << "       ";
    //     cout << left << setw(20) << (*it)->commodity_name << "  ";
    //     cout << left << setw(5) << fixed << setprecision(1) <<(*it)->price << "    ";
    //     cout << left << setw(5) <<(*it)->stock << "  ";
    //     cout << left << setw(4) << (*it)->trader_id << "   ";
    //     cout << left << setw(10) << (*it)->launch_time << "  ";
    //     cout << left << setw(10) << (*it)->commodity_status << endl;
    // }
    // cout << "*******************************************************************************" << endl;
    // cout << endl;
    cout << "请输入展示顺序: 1.按系统默认排序 2.按价格升序 3.按价格降序" << endl;
    string choice;
    cin.sync();
    getline(cin, choice);
    while (choice != "1" && choice != "2" && choice != "3") {
        cout << "输入有误!请重新输入:";
        cin.sync();
        getline(cin, choice);
    }
    switch (stoi(choice))
    {
    case 1:
        {
            cout << "*******************************************************************************" << endl;
            cout << "商品ID     名称                  价格    数量   卖家ID  上架时间   商品状态" << endl;
            for (vector<commodity*>::iterator it = commodity_list.begin(); it != commodity_list.end(); ++it) {
                cout << (*it)->commodity_id << "       ";
                cout << left << setw(20) << (*it)->commodity_name << "  ";
                cout << left << setw(5) << fixed << setprecision(1) <<(*it)->price << "    ";
                cout << left << setw(5) <<(*it)->stock << "  ";
                cout << left << setw(4) << (*it)->trader_id << "   ";
                cout << left << setw(10) << (*it)->launch_time << "  ";
                cout << left << setw(10) << (*it)->commodity_status << endl;
            }
            cout << "*******************************************************************************" << endl;
            cout << endl;
        break;}
    case 2:
        {
            vector<commodity*> tmp;
            for (auto& i: commodity_list) {commodity* t = i; tmp.push_back(t);}    
            sort(tmp.begin(), tmp.end(), [](commodity* i, commodity* j)->bool {return i->price < j->price;});
            cout << "*******************************************************************************" << endl;
            cout << "商品ID     名称                  价格    数量   卖家ID  上架时间   商品状态" << endl;
            for (auto& it: tmp) 
                {
                cout << it->commodity_id << "       ";
                cout << left << setw(20) << it->commodity_name << "  ";
                cout << left << setw(5) << fixed << setprecision(1) << it->price << "    ";
                cout << left << setw(5) <<it->stock << "  ";
                cout << left << setw(4) << it->trader_id << "   ";
                cout << left << setw(10) << it->launch_time << "  ";
                cout << left << setw(10) << it->commodity_status << endl;
                }
            cout << "*******************************************************************************" << endl;
            cout << endl;
            tmp.clear();   
            break;  
        }
    case 3:
        {
            vector<commodity*> tmp;
            for (auto& i: commodity_list) {commodity* t = i; tmp.push_back(t);}    
            sort(tmp.begin(), tmp.end(), [](commodity* i, commodity* j)->bool {return i->price > j->price;});
            cout << "*******************************************************************************" << endl;
            cout << "商品ID     名称                  价格    数量   卖家ID  上架时间   商品状态" << endl;
            for (auto& it: tmp) 
                {
                cout << it->commodity_id << "       ";
                cout << left << setw(20) << it->commodity_name << "  ";
                cout << left << setw(5) << fixed << setprecision(1) << it->price << "    ";
                cout << left << setw(5) <<it->stock << "  ";
                cout << left << setw(4) << it->trader_id << "   ";
                cout << left << setw(10) << it->launch_time << "  ";
                cout << left << setw(10) << it->commodity_status << endl;
                }
            cout << "*******************************************************************************" << endl;
            cout << endl;
            tmp.clear();  
            break;
        }
    default:
        break;
    }
}

void search_commodity (vector<commodity*>& commodity_list,string key_word) { //搜索商品
    cout << "*******************************************************************************" << endl;
    bool is_found = false, column = false;
    for (vector<commodity*>::iterator it = commodity_list.begin(); it != commodity_list.end(); ++it) {
        // for (int i = 0; i < (*it)->commodity_name.size(); ++i) {
        //     if (key_word[0] == (*it)->commodity_name[i]) {
        //         for (int j = 0; j < key_word.size(); ++j)
        //             if (i + j >= (*it)->commodity_name.size() || key_word[j] != (*it)->commodity_name[i + j]) {
        //                 flag = false;
        //                 break;
        //             }
        //         if (flag) is_found = true;
        //         break;
        //     }
        // }
        if ((*it)->commodity_name.find(key_word) != string::npos) {
            if (!column) {
                cout << "商品ID     名称                  价格    数量   卖家ID  上架时间   商品状态" << endl;
                column = true;
            }
            cout << (*it)->commodity_id << "       ";
            cout << left << setw(20) << (*it)->commodity_name << "  ";
            cout << left << setw(5) << fixed << setprecision(1) <<(*it)->price << "    ";
            cout << left << setw(5) <<(*it)->stock << "  ";
            cout << left << setw(4) << (*it)->trader_id << "   ";
            cout << left << setw(10) << (*it)->launch_time << "  ";
            cout << left << setw(10) << (*it)->commodity_status << endl;
        }
    }
    if (!column) cout << "没有找到您想要的商品!即将返回初始界面" << endl;
    cout << "*******************************************************************************" << endl;
    cout << endl;
}

int remove_commodity (vector<commodity*>& commodity_list, string UID) {
    cout << "请输入要下架的商品ID:" << endl;
    string commodity_id = "";
    cin.sync();
    getline (cin, commodity_id);
    for (vector<commodity*>::iterator it = commodity_list.begin(); it != commodity_list.end(); ++it)
        if ((UID == "" && (*it)->commodity_id == commodity_id && (*it)->commodity_status == COMMODITY_NORMAL) || ((*it)->trader_id == UID && (*it)->commodity_id == commodity_id && (*it)->commodity_status == COMMODITY_NORMAL)) {
            cout << "要确定下架该商品吗?" << endl;
            cout << "*******************************************************************************" << endl;
            cout << "商品ID     名称                  价格    数量   卖家ID  上架时间   商品状态" << endl;
            cout << (*it)->commodity_id << "       ";
            cout << left << setw(20) << (*it)->commodity_name << "  ";
            cout << left << setw(5) << fixed << setprecision(1) <<(*it)->price << "    ";
            cout << left << setw(5) <<(*it)->stock << "  ";
            cout << left << setw(4) << (*it)->trader_id << "   ";
            cout << left << setw(10) << (*it)->launch_time << "  ";
            cout << left << setw(10) << (*it)->commodity_status << endl;
            cout << "*******************************************************************************" << endl;

            cout << "请选择(y/n):";
            string choice = "";
            while (true) { 
                cin.sync();
                getline (cin, choice);
                while (!cin || choice.size() <= 0 || choice.size() > 1 || (choice[0] != 'y' && choice[0] != 'n')) {
                    cout << endl << "发生了意想不到的错误!请重新输入选择(y/n):";
                    cin.clear();
                    cin.sync();
                    getline (cin, choice);
                }
                 
                if (choice[0] == 'y') {
                    //(*it)->commodity_status = "已下架";
                    string modify_info = "UPDATE commodity SET 状态=已下架 WHERE ID= " + commodity_id;
                    parse_modify_commodity_info ({modify_info, "3"}, commodity_list);
                    cout << "下架成功!" << endl;
                    return 1;
                }
                else if (choice[0] == 'n') return -1;
                else cout << "无效选择!请重新输入:" << endl;
            }
        }
    cout << "没有找到此商品或此商品已下架!" << endl;
    cout << endl;
    return -1;
}

int launch_commodity (vector<commodity*>& commodity_list, string UID) { //卖家发布商品
    string commodity_name = "", text = "";
    double price = 0;
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

    string price_sql = to_string(price);
    int index = 0;
    while (index < price_sql.size() && price_sql[index] != '.') ++index;
    if (index != price_sql.size()) {
        int k = price_sql.size() - 1;
        while (price_sql[k] == '0' && price_sql[k - 1] != '.') {
            --k;
            price_sql.pop_back();
        }
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

    string trader_sql_1 = "INSERT INTO commodity VALUES ";
    trader_sql_1 += "(" + commodity_name + "," + price_sql + "," + to_string(num) + "," + text + ")";
    bool validity = parse_launch_commodity ({trader_sql_1, "trader"}, commodity_name, price, num, text);

    // bool vaildity = true;
    // if (commodity_name.size() <= 0 || commodity_name.size() > 10) vaildity = false;
    // else if (price < 0 || (price * 10) - int(price * 10) != 0) vaildity = false;
    // else if (num <= 0) vaildity = false;
    // else if (text.size() > 100) vaildity = false;

    if (validity) {
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
    cout << "请输入展示顺序: 1.按系统默认排序 2.按价格升序 3.按价格降序" << endl;
    string choice;
    cin.sync();
    getline(cin, choice);
    while (choice != "1" && choice != "2" && choice != "3") {
        cout << "输入有误!请重新输入:";
        cin.sync();
        getline(cin, choice);
    }
    switch (stoi(choice))
    {
    case 1:
        {
            cout << "*******************************************************************************" << endl;
            cout << "商品ID     名称                  价格    数量   上架时间   商品状态" << endl;
            for (vector<commodity*>::iterator it = commodity_list.begin(); it != commodity_list.end(); ++it) 
                if ((*it)->trader_id == UID)
                    {
                        cout << (*it)->commodity_id << "       ";
                        cout << left << setw(20) << (*it)->commodity_name << "  ";
                        cout << left << setw(5) << fixed << setprecision(1) <<(*it)->price << "    ";
                        cout << left << setw(5) <<(*it)->stock << "  ";
                        cout << left << setw(10) << (*it)->launch_time << "  ";
                        cout << left << setw(10) << (*it)->commodity_status << endl;
                    }
            cout << "*******************************************************************************" << endl;
            cout << endl;
        break;}
    case 2:
        {
            vector<commodity*> tmp;
            for (auto& i: commodity_list) {commodity* t = i; tmp.push_back(t);}    
            sort(tmp.begin(), tmp.end(), [](commodity* i, commodity* j)->bool {return i->price < j->price;});
            cout << "*******************************************************************************" << endl;
            cout << "商品ID     名称                  价格    数量   上架时间   商品状态" << endl;
            for (auto& it: tmp) 
                if (it->trader_id == UID)
                    {
                        cout << it->commodity_id << "       ";
                        cout << left << setw(20) << it->commodity_name << "  ";
                        cout << left << setw(5) << fixed << setprecision(1) <<it->price << "    ";
                        cout << left << setw(5) <<it->stock << "  ";
                        cout << left << setw(10) << it->launch_time << "  ";
                        cout << left << setw(10) << it->commodity_status << endl;
                    }
            cout << "*******************************************************************************" << endl;
            cout << endl;
            tmp.clear();     
            break;
        }
    case 3:
        {
            vector<commodity*> tmp;
            for (auto& i: commodity_list) {commodity* t = i; tmp.push_back(t);}    
            sort(tmp.begin(), tmp.end(), [](commodity* i, commodity* j)->bool {return i->price > j->price;});
            cout << "*******************************************************************************" << endl;
            cout << "商品ID     名称                  价格    数量   上架时间   商品状态" << endl;
            for (auto& it: tmp) 
                if (it->trader_id == UID)
                    {
                        cout << it->commodity_id << "       ";
                        cout << left << setw(20) << it->commodity_name << "  ";
                        cout << left << setw(5) << fixed << setprecision(1) <<it->price << "    ";
                        cout << left << setw(5) <<it->stock << "  ";
                        cout << left << setw(10) << it->launch_time << "  ";
                        cout << left << setw(10) << it->commodity_status << endl;
                    }
            cout << "*******************************************************************************" << endl;
            cout << endl;
            tmp.clear(); 
            break; 
        }
    default:
        break;
    }
}

int modify_commodity (vector<commodity*>& commodity_list, string UID) { //卖家修改商品
    string commodity_id = "";
    double modify_price = 0; 
    string modify_text = "";
    cout << "请输入被修改商品的ID:";
    cin.sync();
    getline (cin, commodity_id);
    for (vector<commodity*>::iterator it = commodity_list.begin(); it != commodity_list.end(); ++it) 
        if ((*it)->commodity_id == commodity_id && (*it)->trader_id == UID && (*it)->commodity_status == COMMODITY_NORMAL) {
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
            if (choice[0] == '1') {
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
            cout << "商品ID: " << commodity_id << endl;
            cout << "商品名称: " << (*it)->commodity_name << endl;
            if (choice[0] == '1') {
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
                else break;
            }
            if (c[0] == 'y') {
                // if (choice[0] == 1) (*it)->price = modify_price;
                // else (*it)->text = modify_text;
                if (choice[0] == '1') {
                    string price_sql = to_string(modify_price);
                    int index = 0;
                    while (index < price_sql.size() && price_sql[index] != '.') ++index;
                    if (index != price_sql.size()) {
                        int k = price_sql.size() - 1;
                        while (price_sql[k] == '0' && price_sql[k - 1] != '.') {
                            --k;
                            price_sql.pop_back();
                        }
                    }
                    string update_sql = "UPDATE commodity SET 价格=" + price_sql + " WHERE ID= " + (*it)->commodity_id;
                    parse_modify_commodity_info ({update_sql, "1", price_sql}, commodity_list);
                }
                else {
                    string update_sql = "UPDATE commodity SET 描述=" + modify_text + " WHERE ID= " + (*it)->commodity_id;
                    parse_modify_commodity_info ({update_sql, "2", modify_text}, commodity_list);
                }
                cout << "修改成功!" << endl << endl;
                return 1;
            }
            else return 0;
        }
    cout << "没有找到该商品!" << endl << endl;
    return 0;
}

void best_selling (vector<commodity*>& commodity_list) {
    // cout << "*******************************************************************************" << endl;
    // cout << "商品ID     名称                  价格    卖家ID  上架时间" << endl;
    // for (vector<commodity*>::iterator it = commodity_list.begin(); it != commodity_list.end(); ++it) {
    //     if ((*it)->commodity_status == COMMODITY_NORMAL)
    //         {cout << (*it)->commodity_id << "       ";
    //         cout << left << setw(20) << (*it)->commodity_name << "  ";
    //         cout << left << setw(5) << fixed << setprecision(1) <<(*it)->price << "    ";
    //         cout << left << setw(4) << (*it)->trader_id << "   ";
    //         cout << left << setw(10) << (*it)->launch_time << "  ";
    //         cout << endl;}
    // }
    // cout << "*******************************************************************************" << endl;
    // cout << endl;  
    cout << "请输入展示顺序: 1.按系统默认排序 2.按价格升序 3.按价格降序" << endl;
    string choice;
    cin.sync();
    getline(cin, choice);
    while (choice != "1" && choice != "2" && choice != "3") {
        cout << "输入有误!请重新输入:";
        cin.sync();
        getline(cin, choice);
    }
    switch (stoi(choice))
    {
    case 1:
        {
            cout << "*******************************************************************************" << endl;
            cout << "商品ID     名称                  价格    卖家ID  上架时间" << endl;
            for (auto& it: commodity_list) {
                if (it->commodity_status == COMMODITY_NORMAL)
                    {cout << it->commodity_id << "       ";
                    cout << left << setw(20) << it->commodity_name << "  ";
                    cout << left << setw(5) << fixed << setprecision(1) <<it->price << "    ";
                    cout << left << setw(4) << it->trader_id << "   ";
                    cout << left << setw(10) << it->launch_time << "  ";
                    cout << endl;}
            }
            cout << "*******************************************************************************" << endl;
            cout << endl;  
        break;}
    case 2:
        {
            vector<commodity*> tmp;
            for (auto& i: commodity_list) {commodity* t = i; tmp.push_back(t);}    
            sort(tmp.begin(), tmp.end(), [](commodity* i, commodity* j)->bool {return i->price < j->price;});
            cout << "*******************************************************************************" << endl;
            cout << "商品ID     名称                  价格    数量   上架时间   商品状态" << endl;
            for (auto& it: tmp) 
                if (it->commodity_status == COMMODITY_NORMAL)
                    {cout << it->commodity_id << "       ";
                    cout << left << setw(20) << it->commodity_name << "  ";
                    cout << left << setw(5) << fixed << setprecision(1) <<it->price << "    ";
                    cout << left << setw(4) << it->trader_id << "   ";
                    cout << left << setw(10) << it->launch_time << "  ";
                    cout << endl;}
            cout << "*******************************************************************************" << endl;
            cout << endl;
            tmp.clear();     
            break;
        }
    case 3:
        {
            vector<commodity*> tmp;
            for (auto& i: commodity_list) {commodity* t = i; tmp.push_back(t);}    
            sort(tmp.begin(), tmp.end(), [](commodity* i, commodity* j)->bool {return i->price > j->price;});
            cout << "*******************************************************************************" << endl;
            cout << "商品ID     名称                  价格    数量   上架时间   商品状态" << endl;
            for (auto& it: tmp) 
                if (it->commodity_status == COMMODITY_NORMAL)
                    {cout << it->commodity_id << "       ";
                    cout << left << setw(20) << it->commodity_name << "  ";
                    cout << left << setw(5) << fixed << setprecision(1) <<it->price << "    ";
                    cout << left << setw(4) << it->trader_id << "   ";
                    cout << left << setw(10) << it->launch_time << "  ";
                    cout << endl;}
            cout << "*******************************************************************************" << endl;
            cout << endl;
            tmp.clear();  
            break;
        }
    default:
        break;
    }
}

void search_on_sale (vector<commodity*>& commodity_list, string key_word) { 

    cout << "*******************************************************************************" << endl;
    bool is_found = false, column = false;
    for (vector<commodity*>::iterator it = commodity_list.begin(); it != commodity_list.end(); ++it) {
        // for (int i = 0; i < (*it)->commodity_name.size(); ++i) {
        //     // if (key_word[0] == (*it)->commodity_name[i]) {
        //     //     // for (int j = 0; j < key_word.size(); ++j)
        //     //     //     if (i + j >= (*it)->commodity_name.size() || key_word[j] != (*it)->commodity_name[i + j]) {
        //     //     //         flag = false;
        //     //     //         break;
        //     //     //     }
        //     //     // if (flag) is_found = true;
        //     //     break;
        //     // }
        // }
        if ((*it)->commodity_name.find(key_word) != string::npos && (*it)->commodity_status == COMMODITY_NORMAL) {
            if (!column) {
                cout << "商品ID     名称                  价格    卖家ID  上架时间" << endl;
                column = true;
            }
            cout << (*it)->commodity_id << "       ";
            cout << left << setw(20) << (*it)->commodity_name << "  ";
            cout << left << setw(5) << fixed << setprecision(1) <<(*it)->price << "    ";
            cout << left << setw(4) << (*it)->trader_id << "   ";
            cout << left << setw(10) << (*it)->launch_time << "  ";
            cout << endl;}
    }
        
    if (!column) cout << "没有找到您想要的商品!即将返回初始界面" << endl;
    cout << "*******************************************************************************" << endl;
    cout << endl;
}

void display_details (vector<commodity*> commodity_list, string search_id) {
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


void comments (vector<commodity*>& commodity_list, vector<comment*>& comment_list, string UID) {
    cout << "请输入您的选择(1.管理我的评论 2.进入商品评论区): ";
    string my_choice;
    cin.sync();
    getline(cin, my_choice);
    while (my_choice.size() <= 0 || (my_choice != "1" && my_choice != "2")) {
        cout << "输入有误! 请重新输入: ";
        cin.sync();
        getline(cin, my_choice);
    }
    if (my_choice == "1") {
        cout << "=================================================================" << endl;
        for (auto& t: comment_list) {
            if (t->UID == UID && t->status == "normal") {
                cout << t->index << "  " << t->time << " " << t->UID << " " << left << setw(20) << t->content << " ";
                cout << "点赞数:" << t->num << endl;
            }
        }
        cout << "=================================================================" << endl;
        cout << "请输入您的选择(1.删除评论 2.返回上一级界面): ";
        string new_choice;
        cin.sync();
        getline(cin, new_choice);
        while (new_choice.size() <= 0 || (new_choice != "1" && new_choice != "2")) {
            cout << "输入有误! 请重新输入: ";
            cin.sync();
            getline(cin, new_choice);
        }
        if (new_choice == "1") {
            cout << "请输入您要删除的评论的序号: ";
            string del_id;
            cin.sync();
            getline(cin, del_id);
            for (auto& c: comment_list) {
                if (c->index == del_id) {
                    c->status = "deleted";
                    save_comments(comment_list);
                    cout << "删除成功!" << endl;
                    system("pause");
                    return;
                }
            } 
            cout << "删除失败!" << endl;
        }
        else return;
    }

    else {    
    cout << "请输入商品ID: ";
    string MID;
    cin.sync();
    getline(cin, MID);
    display_details (commodity_list, MID);
    //先展示商品信息
    cout << endl << "评论区:" << endl;
    cout << "============================================================================================================" << endl;
    for (auto& t: comment_list) {
        if (t->MID == MID && t->status == "normal" && t->reply == "000") {
            cout << t->index << "  " << t->time << " " << t->UID << " " << left << setw(20) << t->content << " ";
            cout << "点赞数:" << t->num << endl;
            for (auto& c: comment_list) {
                if (c->reply == t->index && c->status == "normal") {
                    cout << "回复" << c->reply << " " << c->time << " " << c->UID << " " << left << setw(20) << c->content << endl;
                }
            }
        }
    }
    cout << "============================================================================================================" << endl;

    cout << "请选择您的操作(1.发表评论 2.回复评论 3.点赞评论 4.返回上一级): ";
    string choice;
    cin.sync();
    getline(cin, choice);
    while (choice.size() <= 0 || (choice != "1" && choice != "2" && choice != "3" && choice != "4")) {
        cout << "输入有误!" << endl;
        cin.sync();
        cout << "请重新输入: ";
        getline(cin, choice);
    }
    cout << endl;
    switch (stoi(choice)) {
        case 1:
            {
                cout << "留下一条友善的评论叭(不超过20个字符): ";
                string my_comment;
                cin.sync();
                getline(cin, my_comment);
                if (my_comment.size() > 20) {cout << "评论字数超出限制!" << endl; system("pause");}
                else {
                        int cur_num = comment_list.size();
                        string index;
                        if (cur_num + 1 < 10) index = "00" + to_string(cur_num + 1);
                        else if (cur_num + 1 < 100) index = "0" + to_string(cur_num + 1);
                        else index = to_string(cur_num + 1);
                        comment_list.push_back(new comment(index, "000", comment_time(), UID, MID, my_comment, 0, "normal"));
                        save_comments(comment_list);
                        cout << "评论成功!" << endl;
                        system("pause");
                }
                break;
            }
        case 2:
            {
                cout << "请输入您要回复的评论的序号: ";
                string Id;
                cin.sync();
                getline(cin, Id);
                bool found = false;
                for (auto& c: comment_list) {
                    if (c->index == Id && c->reply == "000" && c->status == "normal") {
                        found = true;
                        cout << "请留下您的回复(不超过20个字符): ";
                        string my_comment;
                        cin.sync();
                        getline(cin, my_comment);
                        if (my_comment.size() > 20) {cout << "评论字数超出限制!" << endl; system("pause");}
                        else {
                                int cur_num = comment_list.size();
                                string index;
                                if (cur_num + 1 < 10) index = "00" + to_string(cur_num + 1);
                                else if (cur_num + 1 < 100) index = "0" + to_string(cur_num + 1);
                                else index = to_string(cur_num + 1);
                                comment_list.push_back(new comment(index, Id, comment_time(), UID, MID, my_comment, 0, "normal"));
                                save_comments(comment_list);
                                cout << "回复成功!" << endl;
                                system("pause");
                        }
                    }
                }
                if (!found) {cout << "没有找到此评论!" << endl;
                            system("pasue");}
                break;
            }
        case 3:
            {
                cout << "请输入您要点赞的评论的序号: ";
                string Id;
                cin.sync();
                getline(cin, Id);
                for (auto& c: comment_list) {
                    if (c->index == Id && c->status == "normal") {
                        c->num += 1;
                        save_comments(comment_list);
                        cout << "点赞成功!" << endl;
                        break;
                    }
                }
                system("pause");
                break;
            }
        case 4: break;
        default: break;
    }}
}

