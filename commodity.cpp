#include "commodity.h"


commodity:: commodity (string commodity_id, string commodity_name, float price, 
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
                while (!cin || choice.size() <= 0 || choice.size() > 1 || (choice[0] != 'y' && choice[0] != 'n')) {
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
                else break;
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


