#include "trading_platform.h"

int main() {
    trading_platform tp;
    int res = 0;
    string choice = "";
    vector<sub_user_info> login_info;
    
    while (true) {
        system("cls");
        tp.show_menu ();
        cout << endl << "请输入选择:" << endl;
        cin.sync();
        getline (cin, choice);
        while (choice.size() > 1 || (choice[0] != '1' && choice[0] != '2' && choice[0] != '3' && choice[0] != '4')) {
            cout << endl << "无效输入!请重新输入选择:";
            choice.resize(0);
            cin.sync();
            getline (cin, choice);
        }

        switch (stoi(choice))
        {
        case 1: {
            res = tp.admin_login ();
            Delay (1000);
            system ("cls");
            if (res == 1) tp.admin_menu ();
            break;
        }
        case 2:
            tp.sign_up ();
            system("pause");
            break;
        case 3: {
            login_info = tp.user_login ();
            if (!login_info.empty()) {
                while (res != 4) {
                    system("cls");
                    res = tp.sub_user_menu ();
                    if (res == 1) tp.trader_menu (login_info[0].UID);
                    else if (res == 2) tp.buyer_menu (login_info[0].UID, login_info[0].cur_balance);
                    else if (res == 3) tp.manage_user_info (login_info[0].UID);
                }
            }
            break;
        }
        case 4:
            cout << "欢迎下次使用!" << endl;
            exit(0); 
        default:
            break;
        }
    }
    return 0;
}