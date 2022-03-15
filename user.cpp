#include "user.h"

bool contain_all_nums (string& val) { //ע�ắ���ĸ���
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
        cout << "���������벻���Ĵ���!" << endl;
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

    if (words[0] == "UPDATE" && words[1] == "user") {
        for (auto& tmp: user_list)
            if (tmp->UID == words[words.size() - 1])
                {tmp->status = "���";
                save_sql_ban(command);
                }
        
    }
    cout << "�޷�������sqlָ��!" << endl;
}




void show_admin_menu () {
    cout << "======================================================================================" << endl;
    cout << "1.�鿴������Ʒ 2.������Ʒ 3.�¼���Ʒ 4.�鿴���ж��� 5.�鿴�����û� 6.����û� 7.ע��" << endl;
    cout << "======================================================================================" << endl;
    cout << endl;
}

void display_user_list (vector<user*>& user_list) { //չʾ�û��б�
    cout << "*********************************************************************************************************************" << endl;
    cout << "�û�ID     �û���        ��ϵ��ʽ                  ��ַ                                        Ǯ�����    �û�״̬" << endl;
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

int ban_user (vector<user*>& user_list, string UID) { //����û�
    for (vector<user*>::iterator it = user_list.begin(); it != user_list.end(); ++it) {
        if ((*it)->UID == UID && (*it)->status == "����") {
            cout << "ȷ��Ҫ������û���?" << endl;
            cout << "*************************************************************************************************************" << endl;
            cout << "�û�ID     �û���        ��ϵ��ʽ                  ��ַ                                        Ǯ�����" << endl;
            cout << left << setw(4) << (*it)->UID << "       ";
            cout << left << setw(10) << (*it)->user_name << "    ";
            cout << left << setw(20) << (*it)->contact << "      ";
            cout << left << setw(40) << (*it)->address << "     ";
            cout << left << fixed << setprecision(1) <<(*it)->balance << endl;
            cout << "*************************************************************************************************************" << endl;
            cout << "��ѡ��(y/n):";
            string choice = "";
            while (true) {
                getline (cin, choice);
                while (!cin || choice.size() <= 0 || choice.size() > 1) {
                    cout << endl << "�������벻���Ĵ���!����������ѡ��(y/n):";
                    cin.clear();
                    cin.sync();
                    getline (cin, choice);
                }
                cout << endl;
                if (choice[0] == 'y') {
                    string ban = "UPDATE user SET ״̬=��� WHERE ID= " + UID;
                    parse_ban ({ban}, user_list);
                    cout << "����ɹ�!" << endl;
                    cout << endl;
                    return 1;
                }
                else if (choice[0] == 'n') {
                    cout << "��ȡ��" << endl;
                    cout << endl;
                    return -1;
                } 
                else cout << "��������!" << endl;
            }
        }
    }
    cout << "δ�ҵ����û�����û��ѱ����!" << endl;
    cout << endl;
    return -1;
}

void display_user_menu () {
    cout << "================================================" << endl;
    cout << "1.�������� 2.������� 3.������Ϣ���� 4.ע����¼" << endl;
    cout << "================================================" << endl;
    cout << endl;
}

void display_buyer_menu () {
    cout << "=========================================================================================" << endl;
    cout << "1.�鿴��Ʒ�б� 2.������Ʒ 3.������Ʒ 4.�鿴��ʷ���� 5.�鿴��Ʒ��ϸ��Ϣ 6.�����û�������" << endl;
    cout << "=========================================================================================" << endl;
    cout << endl;
}

void display_trader_menu () {
    cout << "=====================================================================================" << endl;
    cout << "1.������Ʒ 2.�鿴������Ʒ 3.�޸���Ʒ��Ϣ 4.�¼���Ʒ 5.�鿴��ʷ���� 6.�����û�������" << endl;
    cout << "=====================================================================================" << endl;
    cout << endl;
}

void user_info_menu () {
    cout << "===============================================" << endl;
    cout << "1.�鿴��Ϣ 2.�޸���Ϣ 3.��ֵ 4.�����û�������" << endl;
    cout << "===============================================" << endl;
    cout << endl;
}

void show_user_info (vector<user*> user_list, string UID) {
    for (vector<user*>::iterator it = user_list.begin(); it != user_list.end(); ++it)
        if ((*it)->UID == UID) {
            cout << "*********************" << endl;
            cout << "�û���: " << (*it)->user_name << endl;
            cout << "��ϵ��ʽ: " << (*it)->contact << endl;
            cout << "��ַ: " << (*it)->address << endl;
            cout << "Ǯ�����: " << fixed << setprecision(1) <<(*it)->balance << endl;
            cout << "*********************" << endl;
            cout << endl;
        }
}

void modify_user_info (vector<user*> user_list, string UID, vector<string> name_list) {
    for (vector<user*>::iterator it = user_list.begin(); it != user_list.end(); ++it)
        if ((*it)->UID == UID) {
            cout << "��ѡ���޸ĵ����� (1.�û��� 2.��ϵ��ʽ 3.��ַ) : ";
            string choice = "";
            while (true) {
                cin.sync();
                getline (cin, choice);
                while (!cin || choice.size() <= 0 || choice.size() > 1) {
                    cout << "�������벻���Ĵ���!����������:";
                    cin.clear();
                    cin.sync();
                    getline (cin, choice);
                }
                if (choice[0] != '1' && choice[0] != '2' && choice[0] != '3') {
                    cout << "��Ч����!���������� (1.�û��� 2.��ϵ��ʽ 3.��ַ) :";
                    cin.sync();
                }
                else break;
            }
            cin.sync();
            if (choice[0] == '1') {
                string pre_name = (*it)->user_name;
                cout << "��ѡ���޸ĺ���û���: ";
                string new_name = ""; 
                cin.sync();
                getline (cin, new_name);
                while (new_name.size() > 20 || new_name.size() <= 0) {
                    cout << "�û������Ϸ�!" << endl << "�����������û���(������10���ַ�):";
                    new_name.resize (0);
                    cin.sync();
                    getline (cin, new_name);
                }
                if (!name_list.empty()) { //��֤�û���Ψһ
                    bool is_only = false;
                    while (!is_only){
                        is_only = true;
                        for (vector<string>::iterator it = name_list.begin(); it != name_list.end(); ++it)
                            if (new_name == *it) {
                                cout << endl << "�û����Ѵ���!�����������û���:";
                                cin.sync();
                                getline (cin, new_name);
                                while (new_name.size() > 20 || new_name.size() <= 0) {
                                    cout << endl << "�û������Ϸ�!�����������û���:";
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
                cout << "�������޸ĺ����ϵ��ʽ: ";
                string new_contact = "";
                cin.sync();
                getline (cin, new_contact);
                while (new_contact.size() > 20 || new_contact.size() <= 0 || !contain_all_nums (new_contact)) {
                    cout << endl << "��������!����������: ";
                    new_contact.resize (0);
                    cin.sync();
                    getline (cin, new_contact);
                }
                (*it)->contact = new_contact;
            }
            else {
                cout << "�������޸ĺ�ĵ�ַ: ";
                string new_address = "";
                cin.sync();
                getline (cin, new_address);
                while (new_address.size() > 20 || new_address.size() <= 0) {
                    cout << endl << "��������!����������: ";
                    new_address.resize (0);
                    cin.sync();
                    getline (cin, new_address);
                }
                (*it)->address = new_address;
            }
        }
    cout << endl << "�޸ĳɹ�!" << endl;
}

void deposit (vector<user*> user_list, string UID) {
    for (vector<user*>::iterator it = user_list.begin(); it != user_list.end(); ++it)
        if ((*it)->UID == UID) {
            cout << "�������ֵ���: ";
            float amount = 0;
            while (true) {
                cin >> amount;
                while (!cin) {
                    cout << "�������벻���Ĵ���!����������:";
                    cin.clear();
                    cin.sync();
                    cin >> amount;
                }
                cin.sync();
                bool vaildity = true;
                if (amount * 10 - int(amount * 10) != 0)
                    vaildity = false;
                if (vaildity) break;
                else cout << endl << "�����Ϲ淶!������������: ";
            }
            float new_amount = (*it)->balance + amount;
            (*it)->balance = new_amount;
            cout << "��ֵ�ɹ�,��ǰ���: " << new_amount << endl;
        } 
}
