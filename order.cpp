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