#pragma once
#include<iostream>
#include<string.h>
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