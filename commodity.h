#pragma once
#include<iostream>
#include<string.h>
#include<string>
#include<vector>
#include<iomanip>
#include<ctime>
#include<fstream>
#include<algorithm>
using namespace std;
#define COMMODITY_NORMAL "������"
#define COMMODITY_OUT "���¼�"



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

class comment {
public:
    string index;
    string reply;
    string time;
    string UID;
    string MID;
    string content;
    int num;
    string status;
    comment(string, string, string, string, string, string, int, string);
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

void comments (vector<commodity*>&, vector<comment*>&, string);