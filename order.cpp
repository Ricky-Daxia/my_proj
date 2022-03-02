#include "order.h"

order:: order (string order_id, string commodity_id, float trade_price,
            int sold_num, string trade_time, string trader_id, string buyer_id) {
                this->order_id = order_id;
                this->commodity_id = commodity_id;
                this->trade_price = trade_price;
                this->sold_num = sold_num;
                this->trade_time = trade_time;
                this->trader_id = trader_id;
                this->buyer_id = buyer_id; 
            }

void display_order_list (vector<order*>& order_list) {
    cout << "*******************************************************************************" << endl;
    cout << "订单ID   商品ID   交易单价   数量   交易时间   卖家ID   买家ID" << endl;
    for (vector<order*>::iterator it = order_list.begin(); it != order_list.end(); ++it)
        cout << (*it)->order_id << "   " << (*it)->commodity_id << "   "
            << fixed << setprecision(1) <<(*it)->trade_price << "   " << setprecision(0) << (*it)->sold_num << "   "
            << (*it)->trade_time << "   " << (*it)->trader_id << "   "
            << (*it)->buyer_id << endl;
    cout << "*******************************************************************************" << endl;
    cout << endl;
}

void display_trader_orders (vector<order*>& order_list, string UID) { //展示卖家订单
    cout << "******************************************************" << endl;
    cout << "订单ID  商品ID  交易单价  数量   交易时间   买家ID" << endl;
    for (vector<order*>::iterator it = order_list.begin(); it != order_list.end(); ++it) 
        if ((*it)->trader_id == UID)
            cout << (*it)->order_id << "   " << (*it)->commodity_id << "   " 
                << fixed << setprecision(1) <<(*it)->trade_price << "  " << setprecision(0) <<(*it)->sold_num << "  "
                << (*it)->trade_time << "  " << (*it)->buyer_id << endl;
    cout << "******************************************************" << endl;
    cout << endl;
}

void display_buyer_order (vector<order*> order_list, string UID) {
    cout << "******************************************************" << endl;
    cout << "订单ID  商品ID  交易单价  数量   交易时间   卖家ID" << endl;
    for (vector<order*>::iterator it = order_list.begin(); it != order_list.end(); ++it) 
        if ((*it)->buyer_id == UID)
            cout << (*it)->order_id << "   " << (*it)->commodity_id << "   " 
                << fixed << setprecision(1) << (*it)->trade_price << "  " << setprecision(0) <<(*it)->sold_num << "  "
                << (*it)->trade_time << "  " << (*it)->trader_id << endl;
    cout << "******************************************************" << endl;
    cout << endl;  
}

