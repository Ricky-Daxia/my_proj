#include "manager.h"

manager:: manager(int id, string name, int did) {
    this->m_id = id;
    this->name = name;
    this->d_id = did;
}

    //display info
void manager:: showinfo (){
    cout << this->m_id << ' ' << this->name << ' ' << this->getdept() << ' ' << this->d_id << endl;
}

    //display department
string manager:: getdept () {
    return string("Manager:");
}