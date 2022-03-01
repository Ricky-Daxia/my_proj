#pragma once
#include<iostream>
#include<string.h>
using namespace std;

class commodity {
public:
    string commodity_id;
    string commodity_name;
    float price;
    string launch_time;
    string trader_id;
    int stock;
    string commodity_status;
    string text;

    commodity (string commodity_id, string commodity_name, 
                float price, int stock, string text, 
                string trader_id, string launch_time, string commodity_status);
};
