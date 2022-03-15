#include "sql.h"

// vector<string> SELECT_ALL (int user_type, int column) {
//     //type == 1 管理员 对应调用 display_commodity_list (commodity_list)
//     //type == 2 卖家 对应调用 display_launched_commodity (commodity_list ,cur_UID)
//     //type == 3 买家 对应调用 best_selling (commodity_list)
//     //column == 1 找commodity_list
//     //column == 2 找order
//     //column == 3 找user
// }

// vector<string> SELECT_DETAIL () {
//     //SELECT * FROM commodity WHERE ID CONTAINS ...
// }

// vector<string> SELECT_SEARCH () {
//     //SELECT * FROM commodity WHERE name CONTAINS ...
//     //管理员可以看到全部
//     //用户只能看到在售中
// }

// vector<string> INSERT () {
//     //卖家发布商品和买家购买商品时调用
//     //INSERT INTO commodity VALUES (val1, val2...)
//     //INSERT INTO order VALUES (val1, val2...)
// }

// vector<string> UPDATE () {
//     //管理员
//     //下架 UPDATE commodity SET 状态 = 已下架 WHERE ID = ...
//     //封禁用户 UPDATE commodity SET 状态 = 已下架 WHERE ID = ...
//     //         UPDATE user SET 状态 = 封禁 WHERE ID = ...

//     //用户
//     //卖家
//     //下架商品 UPDATE commodity SET 状态 = 已下架 WHERE ID = ...
//     //修改商品 UPDATE commodity SET ... WHERE ID = ...
//     //买家 
//     //购买 UPDATE commodity SET 数量 = ... WHERE ID = ...
//     //若数量为0 则生成 UPDATE commodity SET 状态 = 已下架 WHERE ID = ...
// }

// string generate_sql_command () {
//     //生成SELECT INSERT UPDATE三种
//     //生成每一种都需要什么信息?
// }


string sql_time_1 () {
    time_t rawtime = time(0);
    struct tm localtm = *localtime(&rawtime);
    int year = localtm.tm_year + 1900;
    int month = localtm.tm_mon + 1;
    int day = localtm.tm_mday;
    int hour = localtm.tm_hour;
    int min = localtm.tm_min;
    int sec = localtm.tm_sec;
    string d1, d2, d3;
    d1 = to_string(year) + "-";
    if (month < 10) d1 += "0";
    d2 = to_string(month) + "-";
    if (day < 10) d2 += "0";
    d3 = to_string(day);
    d1 += d2 + d3;
    string h, m, s;
    if (hour < 10) h = "0" + to_string(hour);
    else h = to_string(hour);
    if (min < 10) m = "0" + to_string(min);
    else m = to_string(min);
    if (sec < 10) s = "0" + to_string(sec);
    else s = to_string(sec);
    return d1 + " " + h + ":" + m + ":" + s + ": ";
}

void sql_save (string commmands) {
    ofstream ofs;
    ofs.open ("commands.txt", ios::app);
    if (!ofs.is_open()) {
        cout << "出现了意想不到的错误!" << endl;
        exit(-1);
    }
    ofs << sql_time_1() << commmands << endl;
    ofs.close();
}





void parse_sql_command (vector<string> commands) {
    if (commands.size() < 2 || commands[0].size() < 3) return;
    cout << "生成的指令为: " << commands[0] << endl;
    Delay (1000);
    system("cls");
    string command = commands[0], identity = commands[1], tmp;
    vector<string> words;
    for (int i = 0; i < command.size(); ++i) {
        if (command[i] != ' ') tmp += command[i];
        else {
            words.push_back (tmp);
            tmp.resize (0);
        }
    }
    words.push_back (tmp); //先把命令语句分块
    if (words.size() > 3 && words[0] == sql_SELECT && words[1] == "*" && words[2] == "FROM") {
        /*
        vector<string> SELECT_ALL (int user_type, int column) {
            //type == 1 管理员 对应调用 display_commodity_list (commodity_list)
            //type == 2 卖家 对应调用 display_launched_commodity (commodity_list ,cur_UID)
            //type == 3 买家 对应调用 best_selling (commodity_list)
            //column == 1 找commodity_list
            //column == 2 找order
            //column == 3 找user
        }

        vector<string> SELECT_DETAIL () {
            //SELECT * FROM commodity WHERE ID CONTAINS ...
        }

        vector<string> SELECT_SEARCH () {
            //SELECT * FROM commodity WHERE name CONTAINS ...
            //管理员可以看到全部
            //用户只能看到在售中
        }
        */

        //SELECT * FROM commodity
        if (words.size() == 4) {
            if (words[3] == sql_commodity) {
                if (identity == sql_admin) {sql_save(command);display_commodity_list (commodity_list); return;}
                else if (identity == sql_trader) {sql_save(command);display_launched_commodity (commodity_list, commands[2]); return;}
                else if (identity == sql_buyer) {sql_save(command);best_selling (commodity_list); return;}
                else {cout << "无法解析的sql指令!" << endl;return;}
            }//调用对应的函数
            else if (words[3] == sql_user && identity == sql_admin) {sql_save(command);display_user_list (user_list);return;}//调用对应的函数
            else if (words[3] == sql_order) {
                if (identity == sql_admin) {sql_save(command);display_order_list (order_list);return;}
                else if (identity == sql_trader) {sql_save(command);display_trader_orders (order_list, commands[2]);return;}
                else if (identity == sql_buyer) {sql_save(command);display_buyer_order (order_list, commands[2]);return;}
                else {cout << "无法解析的sql指令!" << endl;return;}
            }//调用对应的函数
        }
        //SELECT * FROM commodity WHERE ID CONTAINS ...
        else if (words.size() > 7 && words[4] == "WHERE" && words[6] == "CONTAINS") {
            if (words[3] == sql_commodity) {
                if (identity == sql_buyer && words[5] == "ID") {sql_save(command);display_details (commodity_list, words[7]);return;}
                else if (identity == sql_admin && words[5] == "名称") {sql_save(command);search_commodity (commodity_list, words[7]);return;}
                else if (identity == sql_buyer && words[5] == "名称") {sql_save(command);search_on_sale (commodity_list, words[7]);return;}
                else {cout << "无法解析的sql指令!" << endl;return;}
            }//调用对应的函数
            //else if (words[3] == sql_user) {}//调用对应的函数
            //else if (words[3] == sql_order) {}//调用对应的函数
            else {cout << "无法解析的sql指令!" << endl;return;}
        }
        else {cout << "无法解析的sql指令!" << endl;return;}
    }
    else if (words.size() > 4 && words[0] == sql_INSERT && words[3] == "VALUE") {
        //卖家发布商品和买家购买商品时调用
        //INSERT INTO commodity VALUES (val1, val2...)
        //INSERT INTO order VALUES (val1, val2...)
        if (words[2] == sql_commodity) {return;}
        else if (words[2] == sql_order) {return;}
        else {cout << "无法解析的sql指令!" << endl;return;}
    }
    else if (words.size() > 4 && words[0] == sql_UPDATE && words[2] == "SET" && words[4] == "WHERE") {
        //管理员
        //下架 UPDATE commodity SET 状态 = 已下架 WHERE ID = ... =
        //封禁用户 UPDATE commodity SET 状态 = 已下架 WHERE ID = ...
        //         UPDATE user SET 状态 = 封禁 WHERE ID = ...

        //用户
        //卖家
        //下架商品 UPDATE commodity SET 状态 = 已下架 WHERE ID = ... =
        //修改商品 UPDATE commodity SET ... WHERE ID = ... =
        //买家 
        //购买 UPDATE commodity SET 数量 = ... WHERE ID = .. . =
        //若数量为0 则生成 UPDATE commodity SET 状态 = 已下架 WHERE ID = ... =
        if (words[1] == sql_commodity) {
            if (identity == sql_admin) {return;}
            else if (identity == sql_trader) {return;}
            else if (identity == sql_buyer) {return;}
            else {cout << "无法解析的sql指令!" << endl;return;}
        }
        else if (words[1] == sql_user) {
            if (identity == sql_admin) {return;}
            else {cout << "无法解析的sql指令!" << endl;return;}
        }
        else {cout << "无法解析的sql指令!" << endl;return;}
    }
    else {cout << "无法解析的sql指令!" << endl;return;}//无法解析
}
