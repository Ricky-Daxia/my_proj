#pragma once
#include<iostream>
#include<string.h>
#include<string>
#include<vector>
#include<iomanip>
#include<ctime>
#include<fstream>
using namespace std;
#define COMMODITY_NORMAL "销售中"
#define COMMODITY_OUT "已下架"



class commodity {
public:
    string commodity_id;
    string commodity_name;
    double price;
    string launch_time;
    string trader_id;
    int stock;
    string commodity_status;
    string text;

    commodity (string commodity_id, string commodity_name, 
                double price, int stock, string text, 
                string trader_id, string launch_time, string commodity_status);
};

void display_commodity_list (vector<commodity*>& commodity_list);

void search_commodity (vector<commodity*>& commodity_list,string key_word);

int remove_commodity (vector<commodity*>& commodity_list, string UID);

int launch_commodity (vector<commodity*>& commodity_list, string UID);

void display_launched_commodity (vector<commodity*>& commodity_list, string UID);

int modify_commodity (vector<commodity*>& commodity_list, string UID);

void best_selling (vector<commodity*>& commodity_list);

void search_on_sale (vector<commodity*>& commodity_list, string key_word);

void display_details (vector<commodity*> commodity_list, string search_id);

//string sql_generator (vector<commodity*>&, vector<user*> user_list, vector<order*> order_list);

//void sql_analyser (string sql);

//void calculator (vector<user*> user_list);


