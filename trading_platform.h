#pragma once
#include<iostream>
#include<vector>
#include "user.h"
#include "commodity.h"
#include "order.h"
#include "sql.h"
using namespace std;
#define USER "user.txt"
#define COMMORDITY "commodity.txt"
#define ORDER "order.txt"
#define NORMAL "Õý³£"
#define ADMIN_NAME "admin"
#define ADMIN_PASSWORD "123456"


extern vector<user*> user_list;
extern vector<string> name_list;
extern vector<commodity*> commodity_list;
extern vector<order*> order_list;
extern int user_num;
extern int commodity_num;
extern int order_num;

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

    void save_user ();

    vector<sub_user_info> user_login ();

    void admin_menu ();

    void save_commodity ();

    void save_order ();

    void manage_user_info (string cur_UID);
};