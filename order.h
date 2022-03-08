#pragma once
#include<iostream>
#include<string.h>
#include<vector>
#include<iomanip>
using namespace std;




class order {
public:
    string order_id;
    string commodity_id;
    float trade_price;
    int sold_num;
    string trade_time;
    string trader_id;
    string buyer_id;

    order (string order_id, string commodity_id, float trade_price,
            int sold_num, string trade_time, string trader_id, string buyer_id);
};

void display_order_list (vector<order*>& order_list);

void display_trader_orders (vector<order*>& order_list, string UID);

void display_buyer_order (vector<order*> order_list, string UID);