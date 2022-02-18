#pragma once
#include<iostream>
using namespace std;
#include<string.h>

class worker {
public:

    //display info
    virtual void showinfo () = 0;

    //display department
    virtual string getdept () = 0;
    //id, name, department_id
    int m_id;
    string name;
    int d_id;
};