#pragma once
#include<string>
#include<string.h>
#include<iomanip>
#include<vector>
#include<iostream>
using namespace std;

class user {
public:
    string user_name;
    string user_password;

    string UID;
    string contact;
    string address;
    float balance;
    string status;

    user (string UID, string user_name, string user_password, string contact, string address, float balance, string status);

    
};

void show_admin_menu ();

void display_user_list (vector<user*>& user_list);

int ban_user (vector<user*>& user_list);

void display_user_menu ();

void display_buyer_menu ();

void display_trader_menu ();

void user_info_menu ();

void show_user_info (vector<user*> user_list, string UID);

void modify_user_info (vector<user*> user_list, string UID, vector<string> name_list);

void deposit (vector<user*> user_list, string UID);

bool contain_all_nums (string& val);