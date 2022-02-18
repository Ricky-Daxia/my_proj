#include "boss.h"
boss:: boss(int id, string name, int did) {
    this->m_id = id;
    this->name = name;
    this->d_id = did;
}

    //display info
void boss:: showinfo (){
    cout << this->m_id << ' ' << this->name << ' ' << this->getdept() << ' ' << this->d_id << endl;
}

    //display department
string boss:: getdept () {
    return string("Boss:");
}