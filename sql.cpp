#include "sql.h"

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

vector<string> INSERT () {
    //卖家发布商品和买家购买商品时调用
    //INSERT INTO commodity VALUES (val1, val2...)
    //INSERT INTO order VALUES (val1, val2...)
}

vector<string> UPDATE () {
    //管理员
    //下架 UPDATE commodity SET 状态 = 已下架 WHERE ID = ...
    //封禁用户 UPDATE commodity SET 状态 = 已下架 WHERE ID = ...
    //         UPDATE user SET 状态 = 封禁 WHERE ID = ...

    //用户
    //卖家
    //下架商品 UPDATE commodity SET 状态 = 已下架 WHERE ID = ...
    //修改商品 UPDATE commodity SET ... WHERE ID = ...
    //买家 
    //购买 UPDATE commodity SET 数量 = ... WHERE ID = ...
    //若数量为0 则生成 UPDATE commodity SET 状态 = 已下架 WHERE ID = ...
}
