#include "workermanager.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include<fstream>
#include<algorithm>
#define FILENAME "empfile.txt"

workermanager:: workermanager () {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    if (!ifs.is_open()) {
        cout << "Not existed!" << endl;
        this->empnum = 0;
        this->emparray = NULL;
        this->isempty = true;
        ifs.close();
        return;
    }

    char ch;
    ifs >> ch;
    if (ifs.eof()) {
        cout << "Empty!" << endl;
        this->empnum = 0;
        this->emparray = NULL;
        this->isempty = true;
        ifs.close();
        return;
    }
    
    int num = this->getempnum();
    cout << "Number:" << num << endl;
    this->empnum = num;
    this->isempty = false;

    this->emparray = new worker*[this->empnum];
    this->initemp();
}

void workermanager:: showemp () {
    if (this->isempty) cout << "Not existed or empty!" << endl;
    else {
        for (int i = 0; i < empnum; ++i) 
            this->emparray[i]->showinfo();
        
        system("pause");
        system("cls");
    }
}

void workermanager:: sortemp () {
    if (this->isempty) cout << "Not existed or empty!" << endl;
    else {
        cout << "Select 1.desc or 2.asc:" << endl;
        int select = 0;
        cin >> select;
        //if (select == 1)
            //sort(this->emparray, empnum, [](worker& x, worker& y){return x.m_id > y.m_id;})

    }
}

void workermanager:: cleanfile () {
    cout << "Sure? 1.Sure 2.Return" << endl;
    int select = 0;
    cin >> select;
    if (select == 1) {
        ofstream ofs (FILENAME, ios::trunc);
        ofs.close();

        if (this->emparray != NULL) {
            for (int i = 0; i < empnum; ++i) {
            if (this->emparray[i] != NULL)
                delete this->emparray[i];
                this->emparray[i] = NULL;
            }
            delete[] this->emparray;
            this->emparray = NULL;
            this->empnum = 0;
            this->isempty = true;
            cout << "Cleaned!" << endl;
        }
    }
    system("pause");
    system("cls");
}

workermanager:: ~workermanager () {
    if (this->emparray != NULL) {
    
        for (int i = 0; i < empnum; ++i) {
            if (this->emparray[i] != NULL)
                delete this->emparray[i];
        }
        delete[] this->emparray;
        this->emparray = NULL;
    }
}

void workermanager:: showmenu () { 
    cout << "**********" << endl;
}

void workermanager:: exitsystem () {
    cout << "Welcome your next use!" << endl;
    system("pause");
    exit(0);
}

void workermanager:: addemp () {
    cout << "Please input number:" << endl;
    int addnum = 0;
    cin >> addnum;

    if (addnum > 0) {
        int newsize = this->empnum + addnum;
        worker** newspace = new worker*[newsize]; 
        if (this->emparray != NULL) {
            for (int i = 0; i < this->empnum; ++i)
                newspace[i] = this->emparray[i];
        }
        else {
            for (int i = 0; i < addnum; ++i) {
                int id;
                string name;
                int dept;
                cout << "Please input No.:" << i + 1 << endl;
                cin >> id;
                cout << "Please input name:" << endl;
                cin >> name;
                cout << "Please choose dept:" << endl;
                cout << "1. Employee" << endl;
                cout << "2. Manager" << endl;
                cout << "3. Boss" << endl;
                cin >> dept;

                worker*  worker1 = NULL;
                switch (dept) {
                    case 1:
                        worker1 = new employee(id, name, dept);
                        break;
                    case 2:
                        worker1 = new manager(id, name, dept);
                        break;
                    case 3:
                        worker1 = new boss(id, name, dept);
                        break;
                }

                newspace[this->empnum + i] = worker1;
            }
            delete[] this->emparray;
            this->emparray = newspace;
            this->empnum = newsize;
            cout << "Successfully added " << addnum << "employees" << endl;
            this->isempty = false;
            this->save();
        }
    }
    else cout << "Error!" << endl;
}

void workermanager:: save () {
    ofstream ofs;
    ofs.open (FILENAME, ios:: out);

    for (int i = 0; i < this->empnum; ++i) {
        ofs << this->emparray[i]->m_id << ' '
            << this->emparray[i]->name << ' '
            << this->emparray[i]->d_id << endl;
    }
    ofs.close();
}

int workermanager:: getempnum () {
    ifstream ifs;
    ifs.open (FILENAME, ios::in);

    int id;
    string name;
    int did;

    int num = 0;

    while (ifs >> id && ifs >> name && ifs >> did)
        ++num;
    
    ifs.close();
    return num;
}

void workermanager:: initemp () {
    ifstream ifs;
    ifs.open (FILENAME, ios::in);

    int id;
    string name;
    int did;
    int index = 0;

    while (ifs >> id && ifs >> name && ifs >> did) {
        worker * worker1 = NULL;
        if (did == 1) 
            worker1 = new employee(id ,name, did);
        else if (did == 2)
            worker1 = new manager(id, name, did);
        else worker1 = new boss(id, name, did);

        this->emparray[index] = worker1;
        ++index;
    }

    ifs.close();
}

void workermanager:: delemp () {
    if (this->isempty) cout << "Not existed!" << endl;
    else {
        cout << "Who to delete?" << endl;
        int id = 0;
        cin >> id;
        int index = this->isexist (id);
        if (index != -1) {
            for (int i = index; i < this->empnum - 1; ++i) 
                this->emparray[i] = this->emparray[i + 1];
            this->empnum--;
            this->save();
            cout << "Successfully deleted" << endl;
        }
        else cout << "Couldn't find him." << endl;
        system("pause");
        system("cls");
    }
}

int workermanager:: isexist (int id1) {
    int index = -1;
    for (int i = 0; i < this->empnum; ++i)
        if (this->emparray[i]->m_id == id1) {
            index = i;
            break;
        }
    return index;
}

void workermanager:: modemp () {
    if (this->isempty) cout << "Not existed!" << endl;
    else {
        cout << "Please input number:" << endl;
        int id;
        cin >> id;
        int res = this->isexist(id);
        if (res != -1) {
            delete this->emparray[res];
            int newid = 0;
            string newname = "";
            int newdid = 0;

            cout << "Found No." << id << "Please input new id: " << endl;
            cin >> newid;
            cout << "New name: " << endl;
            cin >> newname;
            cout << "Dept? " << endl;
            cin >> newdid;

            worker* worker1 = NULL;
            switch (newdid) {
                case 1:
                    worker1 = new employee(newid, newname, newdid);
                    break;
                case 2:
                    worker1 = new manager(newid, newname, newdid);
                    break;
                case 3:
                    worker1 = new boss(newid, newname, newdid);
                    break;
                default: break;
            }
            this->emparray[res] = worker1;
            cout << "Succeeded!" << endl;
            this->save();
        }
        else cout << "Not found." << endl;
    }
    system("pause");
    system("cls");
}

void workermanager:: findemp () {
    if (this->isempty) cout << "Not existed!" << endl;
    else {
        cout << "Please input 1. id or 2. name: " << endl;
        int select = 0;
        cin >> select;
        if (select == 1) {
            int id;
            cout << "Please input id: " << endl;
            cin >> id;
            int res = isexist(id);
            if (res != -1) {
                cout << "Found." << endl;
                this->emparray[res]->showinfo();
            }
            else cout << "Not found!" << endl;
        }
        else if (select == 2) {
            string name;
            cout << "Please input name: " << endl;
            cin >> name;
            bool flag = false;
            for (int i = 0; i < empnum; ++i) {
                if (this->emparray[i]->name == name) {
                    this->emparray[i]->showinfo();
                    flag = true;
                }
            if (!flag) cout << "Not found." << endl;   
            }
        }
        else cout << "Error!" << endl;
        
        system("pause");    
        system("cls");
    }
}

