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



bool parse_launch_commodity (vector<string> commands, string commodity_name, float price, int num, string text) {
    if (commands.size() < 2 || commands[0].size() < 3) return false;
    cout << "���ɵ�ָ��Ϊ: " << commands[0] << endl;
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
    words.push_back (tmp); //�Ȱ��������ֿ�

    if (words.size() > 4 && words[0] == "INSERT" && words[3] == "VALUES") {
        //���ҷ�����Ʒ����ҹ�����Ʒʱ����
        //INSERT INTO commodity VALUES (val1, val2...)
        //INSERT INTO order VALUES (val1, val2...)
        if (words[2] == "commodity") {
            //�жϷ�����Ʒ�ϲ��Ϸ�
            bool vaildity = true;
            if (commodity_name.size() <= 0 || commodity_name.size() > 10) vaildity = false;
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

void save_sql (string commmands) {
    ofstream ofs;
    ofs.open ("commands.txt", ios::app);
    if (!ofs.is_open()) {
        cout << "���������벻���Ĵ���!" << endl;
        exit(-1);
    }
    ofs << sql_time_2() << commmands << endl;
    ofs.close();
}




void parse_modify_commodity_info (vector<string> commands, vector<commodity*>& commodity_list) {
    //{"UPDATE commodity SET ..=.. WHERE ID= 000", "1", "INFO"}
    if (commands.size() < 2 || commands[0].size() < 3) return;
    cout << "���ɵ�ָ��Ϊ: " << commands[0] << endl;
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
    words.push_back (tmp); //�Ȱ��������ֿ�

    if (words.size() > 4 && words[0] == "UPDATE" && words[2] == "SET" && words[4] == "WHERE") {
        //����Ա
        //�¼� UPDATE commodity SET ״̬ = ���¼� WHERE ID = ...
        //����û� UPDATE commodity SET ״̬ = ���¼� WHERE ID = ...
        //         UPDATE user SET ״̬ = ��� WHERE ID = ...

        //�û�
        //����
        //�¼���Ʒ UPDATE commodity SET ״̬ = ���¼� WHERE ID = ...
        //�޸���Ʒ UPDATE commodity SET ... WHERE ID = ...
        //��� 
        //���� UPDATE commodity SET ���� = ... WHERE ID = ...
        //������Ϊ0 ������ UPDATE commodity SET ״̬ = ���¼� WHERE ID = ...
        if (words[1] == "commodity") {
            string ID = words[words.size() - 1];
            if (commands[1] == "1") {
                for (auto& tmp: commodity_list)
                    if (tmp->commodity_id == ID)
                        {tmp->price = stof(commands[2]);
                        save_sql(command);
                        }
            } //�޸ļ۸�
            else if (commands[1] == "2") {
                for (auto& tmp: commodity_list)
                    if (tmp->commodity_id == ID)
                        {tmp->text = commands[2];save_sql(command);}
            }//�޸�����
            else if (commands[1] == "3") {
                for (auto& tmp: commodity_list)
                    if (tmp->commodity_id == ID)
                        {tmp->commodity_status = COMMODITY_OUT;save_sql(command);}
            }//�¼� 
        }
        else {cout << "�޷�������sqlָ��!" << endl;return;}
    }
    else {cout << "�޷�������sqlָ��!" << endl;return;}//�޷�����
}






void display_commodity_list (vector<commodity*>& commodity_list) { //չʾ��Ʒ�б�
    cout << "*******************************************************************************" << endl;
    cout << "��ƷID     ����     �۸�     ����    ����ID     �ϼ�ʱ��     ��Ʒ״̬" << endl;
    for (vector<commodity*>::iterator it = commodity_list.begin(); it != commodity_list.end(); ++it) {
        cout << (*it)->commodity_id << "  " << (*it)->commodity_name << "  " << fixed << setprecision(1) <<(*it)->price << "    "
            << setprecision(0) <<(*it)->stock << "  " << (*it)->trader_id << "   " << (*it)->launch_time
            << "   " << (*it)->commodity_status << endl;
    }
    cout << "*******************************************************************************" << endl;
    cout << endl;
}

void search_commodity (vector<commodity*>& commodity_list,string key_word) { //������Ʒ
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
                cout << "��ƷID     ����     �۸�     ����     ����     ����ID     �ϼ�ʱ��     ��Ʒ״̬" << endl;
                column = true;
            }
             cout << (*it)->commodity_id << "  " << (*it)->commodity_name << "  " << fixed << setprecision(1) << (*it)->price << "    "
                << setprecision(0) <<(*it)->stock << "  " << (*it)->text << "  " << (*it)->trader_id << "   " << (*it)->launch_time
                << "   " << (*it)->commodity_status << endl;
        }
    }
    if (!column) cout << "û���ҵ�����Ҫ����Ʒ!�������س�ʼ����" << endl;
    cout << "*******************************************************************************" << endl;
    cout << endl;
}

int remove_commodity (vector<commodity*>& commodity_list, string UID) {
    cout << "������Ҫ�¼ܵ���ƷID:" << endl;
    string commodity_id = "";
    cin.sync();
    getline (cin, commodity_id);
    for (vector<commodity*>::iterator it = commodity_list.begin(); it != commodity_list.end(); ++it)
        if ((UID == "" && (*it)->commodity_id == commodity_id) || ((*it)->trader_id == UID && (*it)->commodity_id == commodity_id)) {
            cout << "Ҫȷ���¼ܸ���Ʒ��?" << endl;
            cout << "*******************************************************************************" << endl;
            cout << "��ƷID     ����     �۸�     ����     ����ID     �ϼ�ʱ��     ��Ʒ״̬" << endl;
            cout << (*it)->commodity_id << "  " << (*it)->commodity_name << "  " << fixed << setprecision(1) <<(*it)->price << "    "
                << setprecision(0) << (*it)->stock << "  " << (*it)->trader_id << "   " << (*it)->launch_time
                << "   " << (*it)->commodity_status << endl;
            cout << "*******************************************************************************" << endl;

            cout << "��ѡ��(y/n):";
            string choice = "";
            while (true) { 
                cin.sync();
                getline (cin, choice);
                while (!cin || choice.size() <= 0 || choice.size() > 1 || (choice[0] != 'y' && choice[0] != 'n')) {
                    cout << endl << "���������벻���Ĵ���!����������ѡ��(y/n):";
                    cin.clear();
                    cin.sync();
                    getline (cin, choice);
                }
                 
                if (choice[0] == 'y') {
                    //(*it)->commodity_status = "���¼�";
                    string modify_info = "UPDATE commodity SET ״̬=���¼� WHERE ID= " + commodity_id;
                    parse_modify_commodity_info ({modify_info, "3"}, commodity_list);
                    cout << "�¼ܳɹ�!" << endl;
                    return 1;
                }
                else if (choice[0] == 'n') return -1;
                else cout << "��Чѡ��!����������:" << endl;
            }
        }
    cout << "û���ҵ�����Ʒ!" << endl;
    cout << endl;
    return -1;
}

int launch_commodity (vector<commodity*>& commodity_list, string UID) { //���ҷ�����Ʒ
    string commodity_name = "", text = "";
    float price = 0;
    int num = 0;
    cout << "��������Ʒ����(������10���ַ�):";
    cin.sync();
    getline (cin, commodity_name);

    cout << "��������Ʒ�۸�(1λС��):";
    cin >> price;
    while (!cin) {
        cout << "�������벻���Ĵ���!����������:";
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
    cout << "��������Ʒ����:";
    cin >> num;
    while (!cin) {
        cout << "�������벻���Ĵ���!����������:";
        cin.clear();
        cin.sync();
        cin >> num;
    }
    cout << "��������Ʒ����(������100���ַ�):";
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
        cout << "��ȷ����������Ʒ��Ϣ����!" << endl;
        for (int i = 0; i < text.size() + 5; ++i) cout << '*';
        cout << endl;
        cout << "��Ʒ����:" << commodity_name << endl;
        cout << "��Ʒ�۸�:" << fixed << setprecision(1) << price << endl;
        cout << "��Ʒ����:" << setprecision(0) <<num << endl;
        cout << "��Ʒ����:" << text << endl; 
        for (int i = 0; i < text.size() + 5; ++i) cout << '*';
        cout << endl << endl;
        cout << "��ȷ��Ҫ������Ʒ��? (y/n)";
        string choice = "";
        while (true) {
            getline (cin, choice);
            while (!cin || choice.size() <= 0 || choice.size() > 1) {
                cout << "�������벻���Ĵ���!����������:";
                cin.clear();
                cin.sync();
                getline (cin, choice);
            }
            if (choice[0] == 'y') {
                cout << "�����ɹ�!" << endl;
                break;
            }
            else if (choice[0] == 'n') return -1;
            else
                cout << "��Ч����!����������:";
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
    cout << "��Ʒ��Ϣ�����ϸ�ʽ!" << endl;
    return 0;
}

void display_launched_commodity (vector<commodity*>& commodity_list, string UID) { //չʾ������Ʒ�б�
    cout << "**************************************************************************" << endl;
    cout << "��ƷID     ����     �۸�     ����    �ϼ�ʱ��     ��Ʒ״̬" << endl;
    for (vector<commodity*>::iterator it = commodity_list.begin(); it != commodity_list.end(); ++it) 
        if ((*it)->trader_id == UID)
            cout << (*it)->commodity_id << "  " << (*it)->commodity_name << "  " << fixed << setprecision(1) <<(*it)->price << "    "
                << setprecision(0) << (*it)->stock << "  " << (*it)->launch_time << "   " << (*it)->commodity_status << endl;
    cout << "**************************************************************************" << endl;
    cout << endl;

}

int modify_commodity (vector<commodity*>& commodity_list, string UID) { //�����޸���Ʒ
    string commodity_id = "";
    float modify_price = 0; 
    string modify_text = "";
    cout << "�����뱻�޸���Ʒ��ID:";
    cin.sync();
    getline (cin, commodity_id);
    for (vector<commodity*>::iterator it = commodity_list.begin(); it != commodity_list.end(); ++it) 
        if ((*it)->commodity_id == commodity_id && (*it)->trader_id == UID && (*it)->commodity_status == COMMODITY_NORMAL) {
            cout << "�����뱻�޸���Ʒ������(1.�۸� 2.����):";
            string choice = "";
            while (true) {
                getline (cin, choice);
                while (!cin || choice.size() <= 0 || choice.size() > 1) {
                    cout << "�������벻���Ĵ���!����������:";
                    cin.clear();
                    cin.sync();
                    getline (cin, choice);
                }
                if (choice[0] == '1' || choice[0] == '2') break;
                else cout << "��Ч����!����������:";
            }
            if (choice[0] == '1') {
                cout << "�����뱻�޸���Ʒ�ļ۸�:";
                cin >> modify_price;
                while (!cin || modify_price < 0 || (modify_price * 10) - int(modify_price * 10) != 0) {
                    cout << "��������!����������:";
                    modify_price = 0;
                    if (!cin) {
                        cin.clear();
                        cin.sync();
                    }
                    cin >> modify_price;
                }
            }
            else {
                cout << "�����뱻�޸���Ʒ������:";
                cin.sync();
                getline (cin, modify_text);
                while (modify_text.size() > 100) {
                    cout << "��������!����������:";
                    modify_text.resize(0);
                    cin.sync();
                    getline (cin, modify_text);
                }
            }
            cout << endl;
            cout << "��ȷ�ϱ��޸ĵ���Ʒ��Ϣ����!" << endl;
            for (int i = 0; i < 25; ++i) cout << '*';
            cout << endl;
            cout << "��ƷID: " << commodity_id << endl;
            cout << "��Ʒ����: " << (*it)->commodity_name << endl;
            if (choice[0] == '1') {
                cout << "��Ʒ�۸�: " << fixed << setprecision(1) << modify_price << endl;
                cout << "��Ʒ����: " << (*it)->text << endl;
            }
            else {
                cout << "��Ʒ�۸�: " << fixed << setprecision(1) << (*it)->price << endl;
                cout << "��Ʒ����: " << modify_text << endl;
            }
            for (int i = 0; i < 25; ++i) cout << '*';
            cout << endl;
            cout << "ȷ���޸�? (y/n)";
            string c = "";
            while (true) {
                cin.sync();
                getline (cin, c);
                while (!cin || c.size() <= 0 || c.size() > 1) {
                    cout << "�������벻���Ĵ���!����������:";
                    cin.clear();
                    cin.sync();
                    getline (cin, c);
                }
                if (c[0] != 'y' && c[0] != 'n')
                    cout << "��Ч����!���������� (y/n) ";
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
                    string update_sql = "UPDATE commodity SET �۸�=" + price_sql + " WHERE ID= " + (*it)->commodity_id;
                    parse_modify_commodity_info ({update_sql, "1", price_sql}, commodity_list);
                }
                else {
                    string update_sql = "UPDATE commodity SET ����=" + modify_text + " WHERE ID= " + (*it)->commodity_id;
                    parse_modify_commodity_info ({update_sql, "2", modify_text}, commodity_list);
                }
                cout << "�޸ĳɹ�!" << endl << endl;
                return 1;
            }
            else return 0;
        }
    cout << "û���ҵ�����Ʒ!" << endl << endl;
    return 0;
}

void best_selling (vector<commodity*>& commodity_list) {
    cout << "*******************************************************************************" << endl;
    cout << "��ƷID     ����     �۸�     �ϼ�ʱ��     ����ID" << endl;
    for (vector<commodity*>::iterator it = commodity_list.begin(); it != commodity_list.end(); ++it) {
        if ((*it)->commodity_status == COMMODITY_NORMAL)
            cout << (*it)->commodity_id << "  " << (*it)->commodity_name << "  " << fixed << setprecision(1) << (*it)->price 
                << "   " << (*it)->launch_time << "   " << (*it)->trader_id << endl;
    }
    cout << "*******************************************************************************" << endl;
    cout << endl;  
}

void search_on_sale (vector<commodity*>& commodity_list, string key_word) { 

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
                cout << "��ƷID     ����     �۸�     ����ID     �ϼ�ʱ��" << endl;
                column = true;
            }
            cout << (*it)->commodity_id << "   " << (*it)->commodity_name << "   " << fixed << setprecision(1) << (*it)->price << "    "
                        << (*it)->trader_id << "   " << (*it)->launch_time << endl;
        }
        is_found = false, flag = true;
    }
        
    if (!column) cout << "û���ҵ�����Ҫ����Ʒ!�������س�ʼ����" << endl;
    cout << "*******************************************************************************" << endl;
    cout << endl;
}

void display_details (vector<commodity*> commodity_list, string search_id) {

    cout << "*******************************************" << endl;
    bool is_found = false;
    for (vector<commodity*>::iterator it = commodity_list.begin(); it != commodity_list.end(); ++it) 
        if ((*it)->commodity_id == search_id && (*it)->commodity_status == COMMODITY_NORMAL) {
            cout << "��ƷID: " << (*it)->commodity_id << endl;
            cout << "��Ʒ����: " << (*it)->commodity_name << endl;
            cout << "��Ʒ�۸�: " << fixed << setprecision(1) << (*it)->price << endl;
            cout << "�ϼ�ʱ��: " << (*it)->launch_time << endl;
            cout << "��Ʒ����: " << (*it)->text << endl;
            cout << "��Ʒ����: " << (*it)->trader_id << endl;
            is_found = true;
            break;
        }
    if (!is_found) cout << "û���ҵ�����Ʒ!" << endl;
    cout << "*******************************************" << endl;   
}

