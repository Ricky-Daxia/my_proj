#pragma once
#include "calculator.h"
#include<conio.h>
#include<bits/stdc++.h>
using namespace std;


class user {
public:
    string user_name;
    string user_password;

    string UID;
    string contact;
    string address;
    double balance;
    string status;

    string expr;
    string question;
    string answer;

    user (string UID, string user_name, string user_password, string contact, string address, double balance, string status, string question, string ans);

};

void show_admin_menu ();

void display_user_list (vector<user*>& user_list);

int ban_user (vector<user*>& user_list, string UID);

void display_user_menu ();

void display_buyer_menu ();

void display_trader_menu ();

void user_info_menu ();

void show_user_info (vector<user*> user_list, string UID);

void modify_user_info (vector<user*> user_list, string UID, vector<string> name_list);

void deposit (vector<user*> user_list, string UID);

bool contain_all_nums (string& val);

void set_question (vector<user*> user_list, string UID);

int forget_password (vector<user*>& user_list, string UID);