#pragma once
#include<iostream>
#include<vector>
#include "user.h"
#include "commodity.h"
#include "order.h"
using namespace std;
#define USER "user.txt"
#define COMMORDITY "commodity.txt"
#define ORDER "order.txt"
#define NORMAL "Õý³£"
#define ADMIN_NAME "admin"
#define ADMIN_PASSWORD "123456"

class sub_user_info {
public:
    string UID;
    float cur_balance;
    
    sub_user_info (string _UID, float _cur_balance): UID(_UID), cur_balance(_cur_balance) {}
};
void Delay(int   time);

class trading_platform {
public:
    trading_platform ();
    
    ~trading_platform ();
    
    void show_menu ();

    int sub_user_menu ();

    void trader_menu (string cur_UID);

    void buyer_menu (string cur_UID, float cur_balance);

    int admin_login ();

    void sign_up ();

    int user_num;

    vector<user*> user_list;

    vector<string> name_list;

    void save_user ();

    vector<sub_user_info> user_login ();

    void admin_menu ();

    int commodity_num;

    vector<commodity*> commodity_list;

    void save_commodity ();

    int order_num;

    vector<order*> order_list;

    void save_order ();

    void manage_user_info (string cur_UID);
};