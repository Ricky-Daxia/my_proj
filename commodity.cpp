#include "commodity.h"

commodity:: commodity (string commodity_id, string commodity_name, float price, 
                        int stock, string text, string trader_id, 
                        string launch_time, string commodity_status) {
                            this->commodity_id = commodity_id;
                            this->commodity_name = commodity_name;
                            this->price = price;
                            this->launch_time = launch_time;
                            this->trader_id = trader_id;
                            this->stock = stock;
                            this->commodity_status = commodity_status;
                            this->text = text;
                        }