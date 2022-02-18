#pragma once
#include "worker.h"

class workermanager{
public:
    workermanager();

    ~workermanager();

    void showmenu ();

    void exitsystem ();

    int empnum;

    worker ** emparray;

    void addemp ();

    void save();

    bool isempty;

    int getempnum ();

    void initemp ();

    void showemp ();

    void delemp ();

    int isexist (int id1);

    void modemp ();

    void findemp ();

    void sortemp ();

    void cleanfile ();
};