#include "workermanager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

int main() {

    // worker * worker = NULL;
    // worker = new employee (1, "alice", 1);
    // worker->showinfo();
    // delete worker;
    // worker = new manager (2, "bob", 2);
    // worker->showinfo();
    // delete worker;
    // worker = new boss (3, "cathy", 3);
    // worker->showinfo();
    // delete worker;


    workermanager wm;

    
    int choice = 0;
    while (true) {
        wm.showmenu();
        cout << "Please input your choice:" << endl;
        cin >> choice;

        switch (choice) {
            case 0:
                wm.exitsystem ();
                break; //exit
            case 1:
                wm.addemp ();
                break; //add employee
            case 2:
                wm.showemp ();
                break; //display employee
            case 3:
                wm.delemp ();
                break; //delete employee
            case 4:
                wm.modemp ();
                break; //modify employee
            case 5:
                wm.findemp ();
                break; //search employee
            case 6:
                //wm.sortemp ();
                cout << "Haven't finished!" << endl;
                break; //sort employee
            case 7:
                wm.cleanfile ();
                break; //delete all
            default:
                system("pause");
                break;
        }
    }
    system("pause");
    return 0;
}