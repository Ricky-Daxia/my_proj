#include "trading_platform.h"
#include<fstream>
#include<ctime>
#include<conio.h>
#include<iomanip>

void Delay(int   time)//time*1000Ϊ���� 
{ 
    clock_t   now   =   clock(); 

    while(   clock()   -   now   <   time   ); 
} 

inline bool contain_all_nums (string& val) { //ע�ắ���ĸ���
    for (int i = 0; i < val.size(); ++i)
        if (val[i] < '0' || val[i] > '9') return false;
    return true;
}

inline bool contain_space (string& str) {
    for (int i = 0; i < str.size(); ++i)
        if (str[i] == ' ') return true;
    return false;
}

trading_platform:: trading_platform () { //���û���Ʒ��ʼ��������˽�к���Ȼ�����
    user_num = -1, commodity_num = -1, order_num = -1;
    user_list = {}, name_list = {}, commodity_list = {}, order_list = {};
    string buffer = "", temp = "";
    vector<string> attributes = {};
    //��ʼ���û�
    ifstream ifs;
    ofstream ofs;
    ifs.open(USER, ios::in);
    if (!ifs.is_open()){
        ofs.open (USER, ios::out);
        ofs << "�û�ID,�û���,����,��ϵ��ʽ,��ַ,Ǯ�����,�û�״̬" << endl;
        ofs.close();
        user_num = 0;
    }
    else { //��ȡ��ǰ���û���  
        while (getline(ifs, buffer)) {
            ++user_num;
            if (user_num > 0) {
                for (int i = 0; i < buffer.size(); ++i) { //7�����Դ���������
                    if (buffer[i] == ',')  {
                        attributes.push_back(temp); 
                        temp = "";
                    }
                    else temp.append(1, buffer[i]);
                }
                //����
                user_list.push_back(new user(attributes[0], attributes[1], attributes[2], attributes[3], attributes[4], stof(attributes[5]), temp));
                name_list.push_back(attributes[1]);
                temp = "", attributes = {}, buffer = ""; //���
            }
        }
    }
    ifs.close();

    //��ʼ����Ʒ
    ifs.open (COMMORDITY, ios::in);
    if (!ifs.is_open()) {
        ofs.open (COMMORDITY, ios::out);
        ofs << "��ƷID,����,�۸�,����,����,����ID,�ϼ�ʱ��,��Ʒ״̬" << endl;
        ofs.close();
        commodity_num = 0;
    }
    else {
        while (getline(ifs, buffer)) {
            ++commodity_num;
            if (commodity_num > 0) {
                for (int i = 0; i < buffer.size(); ++i) { //7�����Դ���������
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

    //��ʼ������
    ifs.open (ORDER, ios::in);
    if (!ifs.is_open()) {
        ofs.open (ORDER, ios::out);
        ofs << "����ID,��ƷID,���׵���,����,����ʱ��,����ID,���ID" << endl;
        ofs.close();
        order_num = 0;
    }
    else {
        while (getline(ifs, buffer)) {
            ++order_num;
            if (order_num > 0) {
                for (int i = 0; i < buffer.size(); ++i) { //7�����Դ���������
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
    cout << "���¼���Ʒ����ƽ̨ Ϊ�й����˽�������" << endl;
    cout << "1.����Ա��¼ 2.�û�ע�� 3.�û���¼ 4.�˳�����" << endl;
    cout << "============================================" << endl;
    cout << endl;
}
//1 o
int trading_platform:: admin_login () {
    string input_name;
    string input_password;

    cout << "���������Ա����:";
    cin.sync ();
    getline(cin, input_name);
    cout << "����������:";
    
    char ch;
    while ((ch = getch()) != '\r'){
        input_password.append(1, char(ch)); //������
        }

    cout << endl;

    if (input_name == ADMIN_NAME) {
        if (input_password == ADMIN_PASSWORD){
            cout << "-----��¼�ɹ�!-----" << endl;
            return 1;
        }
        else cout << "�������!" << endl;
    }
    else cout << "����Ա��������!" << endl;
    return -1;
}

void trading_platform:: save_user () { //�����û����ļ���
    ofstream ofs;
    ofs.open (USER, ios::trunc);
    if (!ofs.is_open()) {
        cout << "Unexpected Error!";
        exit(-1);
    }
    else {
        ofs << "�û�ID,�û���,����,��ϵ��ʽ,��ַ,Ǯ�����,�û�״̬" << endl;
        for (vector<user*>::iterator it = user_list.begin(); it != user_list.end(); ++it)
            ofs << (*it)->UID << ',' << (*it)->user_name << ','
                << (*it)->user_password << ',' << (*it)->contact << ','
                << (*it)->address << ',' << fixed << setprecision(1) <<(*it)->balance << ','
                << (*it)->status << endl;
    }
    ofs.close();
}
//2 o
void trading_platform:: sign_up () { //������ɼ��(���ܲ�����)
    string user_password = "", contact = "";
    string user_name = "", address = "";
    float balance = 0.0;

    cout << "�������û���(������10���ַ�):";
    cin.sync();
    getline (cin, user_name);
    while (user_name.size() > 20 || user_name.size() <= 0 || contain_space (user_name)) {
        cout << "�û������Ϸ�!" << endl << "�����������û���(������10���ַ�):";
        user_name.resize (0);
        cin.sync();
        getline (cin, user_name);
    }
    
    cout << "����������(������20���ַ�,��Сд��ĸ���������):";
    char ch;
    while ((ch = getch())){
        if (ch == '\r' || user_password.size() >= 20) break; //�乻�˾Ͳ�����������
        else if ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z')) {//�Ϸ��Լ��
            user_password.append(1, char(ch)); //ע�⺯������
            cout.put('*');
        }
        else {
            cout << endl << "�����к��в��Ϸ��ַ�!" << endl;
            user_password.resize (0);
            cout << "��������������(������20���ַ�,��Сд��ĸ���������):" ;
        }
    }

    cout << endl << "��������ϵ��ʽ(������20���ַ�,���������):";
    cin.sync ();
    getline (cin, contact);
    while (contact.size() > 20 || contact.size() <= 0 || !contain_all_nums (contact) || contain_space (contact)) {
        cout << "��������!" << endl << "������������ϵ��ʽ(������20���ַ�,���������):";
        contact.resize (0);
        cin.sync ();
        getline (cin, contact);
    }

    cout << "�������ַ(������20���ַ�,���ĺ��ֻ�Ӣ����ĸ):";
    cin.sync ();
    getline (cin, address);
    while (address.size() > 20 || contain_space (address)) {
        cout << "��������!" << endl << "�����������ַ(������20���ַ�,���ĺ��ֻ�Ӣ����ĸ):";
        address.resize (0);
        cin.sync ();
        getline (cin, address);
    }

    if (!name_list.empty()) { //��֤�û���Ψһ
        bool is_only = false;
        while (!is_only){
            is_only = true;
            for (vector<string>::iterator it = name_list.begin(); it != name_list.end(); ++it)
                if (user_name == *it) {
                    cout << "�û����Ѵ���!" << endl << "�����������û���:";
                    getline (cin, user_name);
                    while (user_name.size() > 20 || user_name.size() <= 0) {
                        cout << "�û������Ϸ�!" << endl << "�����������û���:";
                        user_name.resize (0);
                        cin.sync ();
                        getline (cin, user_name);
                    }
                    is_only = false;
                    break;
                }
        }
    } 

    //�����û��б���
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
    cout << "ע��ɹ�!" << endl;
}
//3 o
vector<sub_user_info> trading_platform:: user_login () { //�û���¼����UID�����
    string user_name, user_password;
    
    cout << "�������û���:";
    cin.sync();
    getline (cin, user_name);

    cout << "����������:";
    char ch;
    while ((ch = getch()) != '\r'){
        user_password.append(1, char(ch)); //ע�⺯������
        cout.put('*');
    }
    cout << endl;

    for (vector<user*>::iterator it = user_list.begin(); it != user_list.end(); ++it) {
        if ((*it)->user_name == user_name && (*it)->status == "����") {
            if ((*it)->user_password == user_password) {
                cout << "-----��¼�ɹ�-----" << endl;
                cout << endl;
                return {sub_user_info ((*it)->UID, (*it)->balance)};
            }
            else cout << "-----�������-----" << endl << endl;
            return {};
        }
    }
    cout << "-----�û������ڻ��ѱ����!-----" << endl << endl;
    return {};
}

void show_admin_menu () {
    cout << "======================================================================================" << endl;
    cout << "1.�鿴������Ʒ 2.������Ʒ 3.�¼���Ʒ 4.�鿴���ж��� 5.�鿴�����û� 6.����û� 7.ע��" << endl;
    cout << "======================================================================================" << endl;
    cout << endl;
}

void trading_platform:: save_commodity () { //������Ʒ
    ofstream ofs;
    ofs.open (COMMORDITY, ios::trunc);
    if (!ofs.is_open()) {
        cout << "Unexpected Error!";
        exit(-1);
    }
    else {
        ofs << "��ƷID,����,�۸�,����,����,����ID,�ϼ�ʱ��,��Ʒ״̬" << endl;
        for (vector<commodity*>::iterator it = commodity_list.begin(); it != commodity_list.end(); ++it)
            ofs << (*it)->commodity_id << ',' << (*it)->commodity_name << ','
                << fixed << setprecision(1) <<(*it)->price << ',' << setprecision(0) <<(*it)->stock 
                << ',' << (*it)->text << ',' << (*it)->trader_id
                << ',' << (*it)->launch_time << ',' << (*it)->commodity_status << endl;
        ofs.close();
    }
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
//4 o
void search_commodity (vector<commodity*>& commodity_list) { //������Ʒ
    cout << "��������Ʒ����:";
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
//5 o
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
                while (!cin || choice.size() <= 0 || choice.size() > 1 || (choice[0] != 'y' || choice[0] != 'n')) {
                    cout << endl << "���������벻���Ĵ���!����������ѡ��(y/n):";
                    cin.clear();
                    cin.sync();
                    getline (cin, choice);
                }
                 
                if (choice[0] == 'y') {
                    cout << "�¼ܳɹ�!" << endl;
                    (*it)->commodity_status = "���¼�";
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

void display_order_list (vector<order*>& order_list) {
    cout << "*******************************************************************************" << endl;
    cout << "����ID   ��ƷID   ���׵���   ����   ����ʱ��   ����ID   ���ID" << endl;
    for (vector<order*>::iterator it = order_list.begin(); it != order_list.end(); ++it)
        cout << (*it)->order_id << "   " << (*it)->commodity_id << "   "
            << fixed << setprecision(1) <<(*it)->trade_price << "   " << setprecision(0) << (*it)->sold_num << "   "
            << (*it)->trade_time << "   " << (*it)->trader_id << "   "
            << (*it)->buyer_id << endl;
    cout << "*******************************************************************************" << endl;
    cout << endl;
}

void display_user_list (vector<user*>& user_list) { //չʾ�û��б�
    cout << "*******************************************************************************" << endl;
    for (vector<user*>::iterator it = user_list.begin(); it != user_list.end(); ++it) {
        cout << "�û�ID         �û���        ��ϵ��ʽ        ��ַ        Ǯ�����" << endl;
        cout << (*it)->UID << "     " << (*it)->user_name << "     " << (*it)->contact << "     "
            << (*it)->address << "     " << fixed << setprecision(1) << (*it)->balance << endl;
    }
    cout << "*******************************************************************************" << endl;
    cout << endl;
}
//6 o
int ban_user (vector<user*>& user_list) { //����û�
    cout << "������Ҫ������û�ID:";
    string UID = "";
    cin.sync();
    getline (cin, UID);
    for (vector<user*>::iterator it = user_list.begin(); it != user_list.end(); ++it) {
        if ((*it)->UID == UID && (*it)->status == "����") {
            cout << "ȷ��Ҫ������û���?" << endl;
            cout << "*******************************************************************************" << endl;
            cout << "�û�ID         �û���        ��ϵ��ʽ        ��ַ        Ǯ�����" << endl;
            cout << (*it)->UID << "     " << (*it)->user_name << "     " << (*it)->contact << "     "
                << (*it)->address << "     " << fixed << setprecision(1) <<(*it)->balance << endl;
            cout << "*******************************************************************************" << endl;
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
                    (*it)->status = "���";
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
//7 o
void trading_platform:: admin_menu () {

    int res = 0;
    string choice = "";
    
    while (true) {
        system("cls");
        show_admin_menu ();
        cout << "���������:";
        cin.sync();
        getline (cin, choice);
        while (choice.size() > 1 || choice.size() <= 0 || (choice[0] != '1' && choice[0] != '2' && choice[0] != '3' && choice[0] != '4' && choice[0] != '5' && choice[0] != '6' && choice[0] != '7')) {
            cout << endl << "��Ч����!����������ѡ��:";
            cin.clear(); 
            cin.sync();
            getline (cin, choice);
        }
        switch (stoi(choice))
        {
            case 1: //�鿴������Ʒ
                display_commodity_list (commodity_list);
                system("pause");
                break;
            case 2: //������Ʒ
                search_commodity (commodity_list);
                system("pause");
                break;
            case 3: //�¼���Ʒ
                res = remove_commodity (commodity_list, "");
                if (res == 1) this->save_commodity();
                system("pause");
                break;
            case 4: //�鿴���ж���
                display_order_list (order_list);
                system("pause");
                break;
            case 5: //�鿴�����û�
                display_user_list (user_list);
                system("pause");
                break;
            case 6: {//����û�
                res = ban_user (user_list);
                if (res == 1) this->save_user();
                system("pause");
                break;
            }
            case 7: { //ע��ģ��
                cout << "-----ȷ���˳�?-----" << endl;
                cout << "-----��'1'ȷ��,������������-----" << endl;
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
//8 o
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

    bool vaildity = true;
    if (commodity_name.size() <= 0 || commodity_name.size() > 10) vaildity = false;
    else if (price < 0 || (price * 10) - int(price * 10) != 0) vaildity = false;
    else if (num <= 0) vaildity = false;
    else if (text.size() > 100) vaildity = false;

    if (vaildity) {
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
//9 o
int modify_commodity (vector<commodity*>& commodity_list, string UID) { //�����޸���Ʒ
    string commodity_id = "";
    float modify_price = 0; 
    string modify_text = "";
    cout << "�����뱻�޸���Ʒ��ID:";
    cin.sync();
    getline (cin, commodity_id);
    for (vector<commodity*>::iterator it = commodity_list.begin(); it != commodity_list.end(); ++it) 
        if ((*it)->commodity_id == commodity_id) {
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
            if (choice[0] == 1) {
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
            cout << "��ƷID: " << UID << endl;
            cout << "��Ʒ����: " << (*it)->commodity_name << endl;
            if (choice[0] == 1) {
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
            }
            if (c[0] == 'y') {
                if (choice[0] == 1) (*it)->price = modify_price;
                else (*it)->text = modify_text;
                cout << "�޸ĳɹ�!" << endl << endl;
                return 1;
            }
            else break;
        }
    cout << "û���ҵ�����Ʒ!" << endl << endl;
    return 0;
}

void display_trader_orders (vector<order*>& order_list, string UID) { //չʾ���Ҷ���
    cout << "******************************************************" << endl;
    cout << "����ID  ��ƷID  ���׵���  ����   ����ʱ��   ���ID" << endl;
    for (vector<order*>::iterator it = order_list.begin(); it != order_list.end(); ++it) 
        if ((*it)->trader_id == UID)
            cout << (*it)->order_id << "   " << (*it)->commodity_id << "   " 
                << fixed << setprecision(1) <<(*it)->trade_price << "  " << setprecision(0) <<(*it)->sold_num << "  "
                << (*it)->trade_time << "  " << (*it)->buyer_id << endl;
    cout << "******************************************************" << endl;
    cout << endl;
}
//1 o
void trading_platform:: trader_menu (string cur_UID) { //���ҽ���
    int res = 0;
    string choice = "";

    while (true) {
        system("cls");
        display_trader_menu ();
        cout << "���������:";
        cin.sync();
        getline (cin, choice);
        while (choice.size() > 1 || (choice[0] != '1' && choice[0] != '2' && choice[0] != '3' && choice[0] != '4' && choice[0] != '5' && choice[0] != '6')) {
            cout << "��������!����������:";
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
                cout << "��Ч����!" << endl;
                break;
        } 
    }
}
//2 o
int trading_platform:: sub_user_menu () {
    display_user_menu ();
    string choice = "";
    cout << "���������:";
    cin.sync();
    getline (cin, choice);
    while (choice.size() > 1 || (choice[0] != '1' && choice[0] != '2' && choice[0] != '3' && choice[0] != '4')) {
        cout << "��������!����������:";
        cin.sync();
        choice.resize(0);
        getline (cin, choice);
        }

    return stoi(choice);
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
//3 o
float purchase_commodity (vector<user*> user_list, string UID, vector<commodity*>& commodity_list, vector<order*>& order_list) {
    float cur_balance = 0;
    for (vector<user*>::iterator it1 = user_list.begin(); it1 != user_list.end(); ++it1)
        if ((*it1)->UID == UID) {
            cur_balance = (*it1)->balance; 
            cout << "��������ƷID:";
            string search_id;
            cin.sync();
            getline (cin, search_id);
            cout << "����������:";
            int perchase_num;
            cin >> perchase_num;
            while (!cin) {
                    cout << "�������벻���Ĵ���!����������:";
                    cin.clear();
                    cin.sync();
                    cin >> perchase_num;
                }
            cin.sync();
            cout << "**************************************************" << endl;
            
            for (vector<commodity*>::iterator it = commodity_list.begin(); it != commodity_list.end(); ++it) 
                if ((*it)->commodity_id == search_id && (*it)->commodity_status == COMMODITY_NORMAL) {
                    if ((*it)->stock < perchase_num)
                        cout << "��Ʒ��治��!" << endl;
                    else if (cur_balance < (*it)->price * perchase_num)
                        cout << "����!" << endl;
                    else {
                        cout << "��������!" << endl;
                        //���ɽ���ʱ����µ����
                        time_t now = time (0);
                        tm* ltime = localtime (&now);
                        string trade_date = to_string(ltime->tm_year + 1900) + "-" + to_string(1 + ltime->tm_mon) + 
                            "-" + to_string(ltime->tm_mday);
                        cout << "����ʱ��: " << trade_date << endl;
                        cout << "���׵���: " << fixed << setprecision(1) <<(*it)->price << endl;
                        cout << "��������: " << perchase_num << endl;
                        cout << "����״̬: ���׳ɹ�" << endl;
                        float new_balance = cur_balance - (*it)->price * perchase_num;
                        cout << "�������: " << fixed << setprecision(1) <<new_balance << endl;
                        //����Ʒ�޸�
                        int rest = (*it)->stock - perchase_num;
                        (*it)->stock = rest;
                        if (rest == 0) (*it)->commodity_status = COMMODITY_OUT; 
                        //�Զ����޸�
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
            cout << "û���ҵ�����Ʒ!" << endl;
            cout << "**************************************************" << endl;
    }
    return cur_balance;
}
//4 o
void search_on_sale (vector<commodity*>& commodity_list) { 
    cout << "��������Ʒ����:";
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

void display_buyer_order (vector<order*> order_list, string UID) {
    cout << "******************************************************" << endl;
    cout << "����ID  ��ƷID  ���׵���  ����   ����ʱ��   ����ID" << endl;
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
    cout << "����������Ҫ�鿴����ƷID: ";
    string search_id;
    cin.sync();
    getline (cin, search_id);
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
//6 o
void trading_platform:: buyer_menu (string cur_UID, float cur_balance) { //
    int res = 0;
    string choice = "";
    float return_info = 0;

    while (true) {
        system("cls");
        display_buyer_menu ();
        cout << "���������:";
        getline (cin, choice);
        while (!cin || choice.size() <=  0 || choice.size() > 1 || (choice[0] != '1' && choice[0] != '2' && choice[0] != '3' && choice[0] != '4' && choice[0] != '5' && choice[0] != '6')) {
            cout << "�������벻���Ĵ���!����������:";
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
                cout << "��Ч����!" << endl;
                break;
        } 
    }
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
//7 o
void modify_user_info (vector<user*> user_list, string UID, vector<string> name_list) {
    for (vector<user*>::iterator it = user_list.begin(); it != user_list.end(); ++it)
        if ((*it)->UID == UID) {
            cout << "��ѡ���޸ĵ����� (1.�û��� 2.��ϵ��ʽ 3.��ַ) : ";
            string choice = "";
            while (true) {
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
//8 o
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
//9 o
void trading_platform:: manage_user_info (string cur_UID) {
    string choice = "";

    while (true) {
        system("cls");
        user_info_menu ();
        cout << "���������: " << endl;
        while (true) {
            getline (cin, choice);
            while (!cin) {
                cout << "�������벻���Ĵ���!����������:";
                cin.clear();
                cin.sync();
                getline (cin, choice);
            }
            if (choice.size() <= 0 || choice.size() > 1 || (choice[0] != '1' && choice[0] != '2' && choice[0] != '3' && choice[0] != '4'))
                cout << "��Ч����!����������: " << endl;
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
        ofs << "����ID,��ƷID,���׵���,����,����ʱ��,����ID,���ID" << endl;
        for (vector<order*>::iterator it = order_list.begin(); it != order_list.end(); ++it)
            ofs << (*it)->order_id << ',' << (*it)->commodity_id << ','
                << fixed << setprecision(1) << (*it)->trade_price << ',' << (*it)->sold_num << ','
                << (*it)->trade_time << ',' <<(*it)->trader_id << ','
                << (*it)->buyer_id << endl;
    }
    ofs.close();
}