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
                if (identity == sql_admin) {display_commodity_list (commodity_list); return;}
                else if (identity == sql_trader) {display_launched_commodity (commodity_list, words[2]); return;}
                else if (identity == sql_buyer) {best_selling (commodity_list); return;}
                else {cout << "无法解析的sql指令!" << endl;return;}
            }//调用对应的函数
            else if (words[3] == sql_user && identity == sql_admin) {display_user_list (user_list);return;}//调用对应的函数
            else if (words[3] == sql_order) {
                if (identity == sql_admin) {display_order_list (order_list);return;}
                else if (identity == sql_trader) {display_trader_orders (order_list, words[2]);return;}
                else if (identity == sql_buyer) {display_buyer_order (order_list, words[2]);return;}
                else {cout << "无法解析的sql指令!" << endl;return;}
            }//调用对应的函数
        }
        //SELECT * FROM commodity WHERE ID CONTAINS ...
        else if (words.size() > 7 && words[4] == "WHERE" && words[6] == "CONTAINS") {
            if (words[3] == sql_commodity) {
                if (identity == sql_buyer && words[5] == "ID") {display_details (commodity_list, words[7]);return;}
                else if (identity == sql_admin && words[5] == "名称") {search_commodity (commodity_list, words[7]);return;}
                else if (identity == sql_buyer && words[5] == "名称") {search_on_sale (commodity_list, words[7]);return;}
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
