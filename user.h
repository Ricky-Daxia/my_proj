#pragma once
#include<string>
#include<string.h>
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
