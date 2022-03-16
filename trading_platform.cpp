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


void Delay(int   time)//time*1000Ϊ���� 
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
    cout << "���ɵ�ָ��Ϊ: " << commands[0] << endl;
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
    words.push_back (tmp); //�Ȱ��������ֿ�

    if (words.size() > 4 && words[0] == sql_INSERT && words[3] == "VALUES" && words[2] == sql_order) {
        //���ҷ�����Ʒ����ҹ�����Ʒʱ����
        //INSERT INTO commodity VALUES (val1, val2...)
        //INSERT INTO order VALUES (val1, val2...)
        return true;
        
    }
    cout << "�޷�������sqlָ��!" << endl;return false;
}

void parse_update (vector<string> commands) {
    if (commands.size() < 2 || commands[0].size() < 3) return;
    cout << "���ɵ�ָ��Ϊ: " << commands[0] << endl;
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
    words.push_back (tmp); //�Ȱ��������ֿ�

    if (words.size() > 4 && words[0] == sql_UPDATE && words[2] == "SET" && words[4] == "WHERE") {
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
            else {cout << "�޷�������sqlָ��!" << endl;return;}
        }
        else if (words[1] == sql_user) {
            if (identity == sql_admin) {return;}
            else {cout << "�޷�������sqlָ��!" << endl;return;}
        }
        else {cout << "�޷�������sqlָ��!" << endl;return;}
    }
    else {cout << "�޷�������sqlָ��!" << endl;return;}//�޷�����
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
                user_list.push_back(new user(attributes[0], attributes[1], attributes[2], attributes[3], attributes[4], stod(attributes[5]), temp));
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
            commodity_list.push_back(new commodity(attributes[0], attributes[1], stod(attributes[2]), stoi(attributes[3]), attributes[4], attributes[5], attributes[6], temp));
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
    cout << "���¼���Ʒ����ƽ̨ Ϊ�й����˽�������" << endl;
    cout << "1.����Ա��¼ 2.�û�ע�� 3.�û���¼ 4.�˳�����" << endl;
    cout << "============================================" << endl;
    cout << endl;
}

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

void trading_platform:: sign_up () { //������ɼ��(���ܲ�����)
    string user_password = "", contact = "";
    string user_name = "", address = "";
    double balance = 0.0;

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
    Delay (1000);
    return {};
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
            case 1: {//�鿴������Ʒ
                string admin_sql_1 = "SELECT * FROM commodity";
                parse_sql_command ({admin_sql_1, "admin"});
                //display_commodity_list (commodity_list);
                system("pause");
                break;}
            case 2: //������Ʒ
                {   cout << "��������Ʒ����:";
                    string key_word = "";
                    cin.sync();
                    getline (cin, key_word);
                    string admin_sql_2 = "SELECT * FROM commodity WHERE ���� CONTAINS ";
                    admin_sql_2 += key_word;
                    parse_sql_command ({admin_sql_2, "admin", key_word});
                    //search_commodity (commodity_list, key_word);
                system("pause");
                break;}
            case 3: //�¼���Ʒ
                res = remove_commodity (commodity_list, "");
                if (res == 1) this->save_commodity();
                system("pause");
                break;
            case 4: //�鿴���ж���
                {string admin_sql_4 = "SELECT * FROM order";
                parse_sql_command ({admin_sql_4, "admin"});
                //display_order_list (order_list);
                system("pause");
                break;}
            case 5: //�鿴�����û�
                {string admin_sql_5 = "SELECT * FROM user";
                parse_sql_command ({admin_sql_5, "admin"});
                //display_user_list (user_list);
                system("pause");
                break;}
            case 6: {//����û�
                    cout << "������Ҫ������û�ID:";
                    string UID = "";
                    cin.sync();
                    getline (cin, UID);
                    res = ban_user (user_list, UID);
                    if (res == 1) {
                        this->save_user();
                        string update = "UPDATE commodity SET ״̬=���¼� WHERE ID= " + UID;
                        parse_update ({update, "admin"});
                        this->save_commodity();
                    }
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
                cout << "��Ч����!" << endl;
                break;
        } 
    }
}

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

double purchase_commodity (vector<user*> user_list, string UID, vector<commodity*>& commodity_list, vector<order*>& order_list) {
    double cur_balance = 0, new_balance = 0;
    bool has_perchased = false, is_found = false;
    string trader_UID = "", deal = "";
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
                if ((*it)->commodity_id == search_id && (*it)->commodity_status == COMMODITY_NORMAL && (*it)->trader_id != UID) {
                    is_found = true;
                    if ((*it)->stock < perchase_num)
                        {cout << "��Ʒ��治��!" << endl;
                        cout << "**************************************************" << endl;}
                    else if (cur_balance < (*it)->price * perchase_num)
                        {cout << "����!" << endl;
                        cout << "**************************************************" << endl;}
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
                        trader_UID = (*it)->trader_id;
                        deal = to_string(perchase_num) + "*" + to_string((*it)->price).substr(0, to_string((*it)->price).find('.') + 2);
                        (*it1)->expr += "-" + deal;
                        new_balance = cur_balance - (*it)->price * perchase_num;
                        //new_balance = API(str_new_balance)[0];
                        cout << "�������: " << fixed << setprecision(1) << new_balance << endl;
                        //����Ʒ�޸�
                        int rest = (*it)->stock - perchase_num;
                        (*it)->stock = rest;
                        if (rest == 0) {
                            string update_order = "UPDATE commodity SET ����=0 WHERE ID= " + (*it)->commodity_id;
                            parse_update ({update_order, "buyer"});
                        } 
                        //�Զ����޸�
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
            if (!is_found) {cout << "û���ҵ�����Ʒ!" << endl;
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
                {   cout << "��������Ʒ����:";
                    string key_word = "";
                    cin.sync();
                    getline (cin, key_word);
                    string buyer_sql_2 = "SELECT * FROM commodity WHERE ���� CONTAINS ";
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
                {   cout << "����������Ҫ�鿴����ƷID: ";
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
                cout << "��Ч����!" << endl;
                break;
        } 
    }
}

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










