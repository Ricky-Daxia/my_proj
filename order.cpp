#include "order.h"

order:: order (string order_id, string commodity_id, double trade_price,
            int sold_num, string trade_time, string trader_id, string buyer_id) {
                this->order_id = order_id;
                this->commodity_id = commodity_id;
                this->trade_price = trade_price;
                this->sold_num = sold_num;
                this->trade_time = trade_time;
                this->trader_id = trader_id;
                this->buyer_id = buyer_id; 
            }

void display_order_list (vector<order*>& order_list) {
    cout << "*******************************************************************************" << endl;
    cout << "����ID   ��ƷID   ���׵���   ����   ����ʱ��   ����ID   ���ID" << endl;
    for (vector<order*>::iterator it = order_list.begin(); it != order_list.end(); ++it){
        cout << left << setw(4) << (*it)->order_id << "     ";
        cout << left << setw(4) << (*it)->commodity_id << "       ";
        cout << fixed << setprecision(1) <<(*it)->trade_price << "       " << setprecision(0) << (*it)->sold_num << "     ";
        cout << left << setw(10) << (*it)->trade_time << "   ";
        cout << left << (*it)->trader_id << "     ";
        cout << left << (*it)->buyer_id << endl;}
    cout << "*******************************************************************************" << endl;
    cout << endl;
}

void display_trader_orders (vector<order*>& order_list, string UID) { //չʾ���Ҷ���
    cout << "******************************************************" << endl;
    cout << "����ID   ��ƷID   ���׵���   ����   ����ʱ��   ���ID" << endl;
    for (vector<order*>::iterator it = order_list.begin(); it != order_list.end(); ++it) 
        if ((*it)->trader_id == UID){            
            cout << left << setw(4) << (*it)->order_id << "     "; 
            cout << left << setw(4) << (*it)->commodity_id << "       ";
            cout << fixed << setprecision(1) <<(*it)->trade_price << "       " << setprecision(0) << (*it)->sold_num << "     ";
            cout << left << setw(10) << (*it)->trade_time << "   ";
            cout << left << (*it)->buyer_id << endl;}
    cout << "******************************************************" << endl;
    cout << endl;
}

void display_buyer_order (vector<order*> order_list, string UID) {
    cout << "******************************************************" << endl;
    cout << "����ID   ��ƷID   ���׵���   ����   ����ʱ��   ����ID" << endl;
    for (vector<order*>::iterator it = order_list.begin(); it != order_list.end(); ++it) 
        if ((*it)->buyer_id == UID)
            {            
            cout << left << setw(4) << (*it)->order_id << "     "; 
            cout << left << setw(4) << (*it)->commodity_id << "       ";
            cout << fixed << setprecision(1) <<(*it)->trade_price << "       " << setprecision(0) << (*it)->sold_num << "     ";
            cout << left << setw(10) << (*it)->trade_time << "   ";
            cout << left << (*it)->trader_id << endl;}
    cout << "******************************************************" << endl;
    cout << endl;  
}

