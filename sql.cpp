#include "sql.h"

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

vector<string> INSERT () {
    //���ҷ�����Ʒ����ҹ�����Ʒʱ����
    //INSERT INTO commodity VALUES (val1, val2...)
    //INSERT INTO order VALUES (val1, val2...)
}

vector<string> UPDATE () {
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
}
