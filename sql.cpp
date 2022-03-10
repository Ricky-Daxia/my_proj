#include "sql.h"

// vector<string> SELECT_ALL (int user_type, int column) {
//     //type == 1 ����Ա ��Ӧ���� display_commodity_list (commodity_list)
//     //type == 2 ���� ��Ӧ���� display_launched_commodity (commodity_list ,cur_UID)
//     //type == 3 ��� ��Ӧ���� best_selling (commodity_list)
//     //column == 1 ��commodity_list
//     //column == 2 ��order
//     //column == 3 ��user
// }

// vector<string> SELECT_DETAIL () {
//     //SELECT * FROM commodity WHERE ID CONTAINS ...
// }

// vector<string> SELECT_SEARCH () {
//     //SELECT * FROM commodity WHERE name CONTAINS ...
//     //����Ա���Կ���ȫ��
//     //�û�ֻ�ܿ���������
// }

// vector<string> INSERT () {
//     //���ҷ�����Ʒ����ҹ�����Ʒʱ����
//     //INSERT INTO commodity VALUES (val1, val2...)
//     //INSERT INTO order VALUES (val1, val2...)
// }

// vector<string> UPDATE () {
//     //����Ա
//     //�¼� UPDATE commodity SET ״̬ = ���¼� WHERE ID = ...
//     //����û� UPDATE commodity SET ״̬ = ���¼� WHERE ID = ...
//     //         UPDATE user SET ״̬ = ��� WHERE ID = ...

//     //�û�
//     //����
//     //�¼���Ʒ UPDATE commodity SET ״̬ = ���¼� WHERE ID = ...
//     //�޸���Ʒ UPDATE commodity SET ... WHERE ID = ...
//     //��� 
//     //���� UPDATE commodity SET ���� = ... WHERE ID = ...
//     //������Ϊ0 ������ UPDATE commodity SET ״̬ = ���¼� WHERE ID = ...
// }

// string generate_sql_command () {
//     //����SELECT INSERT UPDATE����
//     //����ÿһ�ֶ���Ҫʲô��Ϣ?
// }

void parse_sql_command (vector<string> commands) {
    if (commands.size() < 2 || commands[0].size() < 3) return;
    cout << "���ɵ�ָ��Ϊ: " << commands[0] << endl;
    Delay (1000);
    system("cls");
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
    if (words.size() > 3 && words[0] == sql_SELECT && words[1] == "*" && words[2] == "FROM") {
        /*
        vector<string> SELECT_ALL (int user_type, int column) {
            //type == 1 ����Ա ��Ӧ���� display_commodity_list (commodity_list)
            //type == 2 ���� ��Ӧ���� display_launched_commodity (commodity_list ,cur_UID)
            //type == 3 ��� ��Ӧ���� best_selling (commodity_list)
            //column == 1 ��commodity_list
            //column == 2 ��order
            //column == 3 ��user
        }

        vector<string> SELECT_DETAIL () {
            //SELECT * FROM commodity WHERE ID CONTAINS ...
        }

        vector<string> SELECT_SEARCH () {
            //SELECT * FROM commodity WHERE name CONTAINS ...
            //����Ա���Կ���ȫ��
            //�û�ֻ�ܿ���������
        }
        */

        //SELECT * FROM commodity
        if (words.size() == 4) {
            if (words[3] == sql_commodity) {
                if (identity == sql_admin) {display_commodity_list (commodity_list); return;}
                else if (identity == sql_trader) {display_launched_commodity (commodity_list, words[2]); return;}
                else if (identity == sql_buyer) {best_selling (commodity_list); return;}
                else {cout << "�޷�������sqlָ��!" << endl;return;}
            }//���ö�Ӧ�ĺ���
            else if (words[3] == sql_user && identity == sql_admin) {display_user_list (user_list);return;}//���ö�Ӧ�ĺ���
            else if (words[3] == sql_order) {
                if (identity == sql_admin) {display_order_list (order_list);return;}
                else if (identity == sql_trader) {display_trader_orders (order_list, words[2]);return;}
                else if (identity == sql_buyer) {display_buyer_order (order_list, words[2]);return;}
                else {cout << "�޷�������sqlָ��!" << endl;return;}
            }//���ö�Ӧ�ĺ���
        }
        //SELECT * FROM commodity WHERE ID CONTAINS ...
        else if (words.size() > 7 && words[4] == "WHERE" && words[6] == "CONTAINS") {
            if (words[3] == sql_commodity) {
                if (identity == sql_buyer && words[5] == "ID") {display_details (commodity_list, words[7]);return;}
                else if (identity == sql_admin && words[5] == "����") {search_commodity (commodity_list, words[7]);return;}
                else if (identity == sql_buyer && words[5] == "����") {search_on_sale (commodity_list, words[7]);return;}
                else {cout << "�޷�������sqlָ��!" << endl;return;}
            }//���ö�Ӧ�ĺ���
            //else if (words[3] == sql_user) {}//���ö�Ӧ�ĺ���
            //else if (words[3] == sql_order) {}//���ö�Ӧ�ĺ���
            else {cout << "�޷�������sqlָ��!" << endl;return;}
        }
        else {cout << "�޷�������sqlָ��!" << endl;return;}
    }
    else if (words.size() > 4 && words[0] == sql_INSERT && words[3] == "VALUE") {
        //���ҷ�����Ʒ����ҹ�����Ʒʱ����
        //INSERT INTO commodity VALUES (val1, val2...)
        //INSERT INTO order VALUES (val1, val2...)
        if (words[2] == sql_commodity) {return;}
        else if (words[2] == sql_order) {return;}
        else {cout << "�޷�������sqlָ��!" << endl;return;}
    }
    else if (words.size() > 4 && words[0] == sql_UPDATE && words[2] == "SET" && words[4] == "WHERE") {
        //����Ա
        //�¼� UPDATE commodity SET ״̬ = ���¼� WHERE ID = ... =
        //����û� UPDATE commodity SET ״̬ = ���¼� WHERE ID = ...
        //         UPDATE user SET ״̬ = ��� WHERE ID = ...

        //�û�
        //����
        //�¼���Ʒ UPDATE commodity SET ״̬ = ���¼� WHERE ID = ... =
        //�޸���Ʒ UPDATE commodity SET ... WHERE ID = ... =
        //��� 
        //���� UPDATE commodity SET ���� = ... WHERE ID = .. . =
        //������Ϊ0 ������ UPDATE commodity SET ״̬ = ���¼� WHERE ID = ... =
        if (words[1] == sql_commodity) {
            if (identity == sql_admin) {return;}
            else if (identity == sql_trader) {return;}
            else if (identity == sql_buyer) {return;}
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
