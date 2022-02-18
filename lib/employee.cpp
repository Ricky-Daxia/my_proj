#include "employee.h"

employee::employee(int id, string name, int did) {
    this->m_id = id;
    this->name = name;
    this->d_id = did;
}

//display info
void employee:: showinfo () {
    cout << this->m_id << ' ' << this->name << ' ' << this->getdept() << ' ' << this->d_id << endl;
}

//display department
string employee:: getdept () {
    return string("Employee:");
}