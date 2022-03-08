#pragma once
#include "commodity.h"
#include "user.h"
#include "order.h"
#include "trading_platform.h"

#define sql_SELECT "SELECT"
#define sql_INSERT "INSERT"
#define sql_UPDATE "UPDATE"
#define sql_commodity "commodity"
#define sql_user "user"
#define sql_order "order"
#define sql_buyer "buyer"
#define sql_trader "trader"
#define sql_admin "admin"


extern vector<user*> user_list;
extern vector<string> name_list;
extern vector<commodity*> commodity_list;
extern vector<order*> order_list;
extern int user_num;
extern int commodity_num;
extern int order_num;

void parse_sql_command (vector<string> commands);