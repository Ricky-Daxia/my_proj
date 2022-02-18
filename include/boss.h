#pragma once
#include<iostream>
using namespace std;
#include "worker.h"

class boss :public worker {
public:

    boss(int id, string name, int did);

    //display info
    virtual void showinfo ();

    //display department
    virtual string getdept ();
};