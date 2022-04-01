# **用户手册**

------

![image](https://user-images.githubusercontent.com/92281688/161219250-43ab70f7-ba50-4698-99fb-08a8bce9194b.png)

2022年2月10日，2022北京冬奥会在“鸟巢”落下帷幕。在本届冬奥会上，不仅中国运动健儿们创造了一项项佳绩，吉祥物“冰墩墩”也是吸足了眼球，成为冬奥会的“顶流”。在本届冬奥会结束之后，我们推出了一个冬奥纪念品交易平台，大家可以在这个平台上发布各种有趣的纪念品，也可以与他人进行交易，购买自己喜欢的纪念品，说不定还可以抢到“冰墩墩”哦！希望大家喜欢！

进入交易平台，我们可以根据菜单选择不同的选项：

```c++
=========================================================
冬奥纪念品交易平台 为中国奥运健儿加油
1.管理员登录 2.用户注册 3.用户登录 4.今日新闻 5.退出程序
=========================================================

请输入选择:

```

接下来，我们将一一介绍不同的功能。

------



## 管理员模式

------

选择选项1，将提示您登录管理员账号。

管理员账号只有一个：admin

管理员密码请牢记：123456

注意，在windows终端下输入管理员密码是不会把字符回显到屏幕上的，因此请按顺序正确输入哦，输入错误的话是不可以退格的，只能返回主界面后重新进入管理员登录。

成功登录之后，就会进入到管理员菜单目录：

```c++
======================================================================================
1.查看所有商品 2.搜索商品 3.下架商品 4.查看所有订单 5.查看所有用户 6.封禁用户 7.注销
======================================================================================
```



### 查看所有商品

输入选择1，屏幕上会短暂打印出生成的SQL指令。别担心，我们只是在展示您的操作背后是如何与数据库之间进行交互的。之后，屏幕上就会展示出三个选项：

```c++
请输入展示顺序: 1.按系统默认排序 2.按价格升序 3.按价格降序

```

输入对应的选择，系统会根据您选择的顺序展示所有商品。

例如：

```c++
*******************************************************************************
商品ID     名称                  价格    数量   卖家ID  上架时间   商品状态
M002       滑雪板                5.5     5      U001   2022-3-30   销售中
M001       金牌                 10.5     3      U001   2022-3-30   销售中
M003       冬奥饭堂啃鸡鸡        35.0     8      U001   2022-3-30   销售中
*******************************************************************************
```



### 搜索商品

输入选择2进入搜索商品模式，系统会提示您输入商品名称，输入商品名称后屏幕会短暂显示生成的SQL指令，接下来则会自动匹配商品列表中含有您输入的名称的商品并打印在屏幕上。

我们的搜索功能默认支持模糊匹配，即所有名称中含有您输入内容的商品都会展示在屏幕上。

例如在输入“金牌”之后：

```c++
*******************************************************************************
商品ID     名称                  价格    数量    卖家ID   上架时间    商品状态
M001       金牌                  10.5     3      U001   2022-3-30   销售中
*******************************************************************************
```



### 下架商品

输入选择3，系统会提示您输入要下架的商品ID，输入ID后若该商品存在且未被下架，则会在屏幕上打印出商品信息并询问您是否确认下架，输入'y'则表示确定下架，之后会打印出SQL指令和“下架成功”的信息。输入'n'则自动返回上一级菜单。

```c++
请输入操作:3
请输入要下架的商品ID:
M001
要确定下架该商品吗?
*******************************************************************************
商品ID     名称                  价格    数量     卖家ID  上架时间   商品状态
M001       金牌                  10.5     3      U001   2022-3-30   销售中
*******************************************************************************
请选择(y/n):y
生成的指令为: UPDATE commodity SET 状态=已下架 WHERE ID= M001
下架成功!
```



### 查看所有订单

输入选择4，会短暂显示生成的SQL指令，之后会打印出所有的订单记录。

```c++
*******************************************************************************
订单ID   商品ID   交易单价   数量   交易时间   卖家ID   买家ID
T001    M001      2.5       2    2022-3-18   U001    U004
T002    M003      5.0       1    2022-3-18   U004    U001
*******************************************************************************

```



### 查看所有用户

输入选择5，会短暂显示生成的SQL指令，之后会打印出所有的用户。

```c++
*******************************************************************************
用户ID   用户名  联系方式     地址                钱包余额      用户状态
U001     南大    12345       仙林大道163号         0.0          正常
*******************************************************************************

```



### 封禁用户

输入选择6，系统会提示您输入需要封禁的用户ID，输入ID后若该用户存在且未被封禁，则会打印出该用户的信息并询问您是否确认封禁，输入'y'则会生成对应的SQL指令并打印“下架成功”的信息，输入'n'则取消并返回上一级菜单。

```c++
请输入操作:6请输入要封禁的用户ID:U001确定要封禁该用户吗?
*******************************************************************************
用户ID   用户名  联系方式     地址                钱包余额      用户状态
U001     南大    12345       仙林大道163号         0.0          正常
*******************************************************************************
请选择(y/n):y
生成的指令为: UPDATE user SET 状态=封禁 WHERE ID= U001
封禁成功!
生成的指令为: UPDATE commodity SET 状态=已下架 WHERE ID= U001
```



### 注销

输入7后系统会进一步询问您是否确定退出管理员模式，按下1后则自动返回主菜单，按其他键则返回到管理员菜单。

```c++
请输入操作:7
-----确定退出?-----
-----按'1'确定,按其它键返回-----
```

------



## 用户注册

------

选择选项2，将提示您输入用户的基本信息：

```c++
请输入选择:2请输入用户名(不超过10个字符):力古
请输入密码(不超过20个字符,由小写字母和数字组成):******
请输入联系方式(不超过20个字符,由数字组成):1234512345
请输入地址(不超过20个字符,中文汉字或英文字母):召唤师峡谷
注册成功!
```

在正确输入对应的信息后会显示注册成功，若输入的信息不符合规范，则会输出对应项的错误信息并提示您重新输入。

需要注意：

1.输入的用户名必须是未被注册过的，且不能超过10字符，否则将提示出错。
2.输入的密码将以“*”符号回显在屏幕上，并且不能退格和更改。
3.密码需由数字或小写字母组成，输入其他字符将会提示出错。

注册成功后，您的钱包余额将被初始化为0。

------



## 用户登录

------

选择选项2，将提示您输入用户名和密码，您需要正确输入用户名和密码。

若您已被封禁，则不能登录。

输入密码的过程中您输入的字符将以“*”字符的形式回显在屏幕上，并且不能退格和更改。

```c++
请输入选择:3
请输入用户名:力古
请输入密码:******
```

登录成功则进入用户菜单：

```c++
================================================
1.我是卖家 2.我是买家 3.个人信息管理 4.注销登录
================================================
```



### 忘记密码

若您输入的密码错误，可以选择“忘记密码”或“返回主界面”。

若选择“忘记密码”，则系统会打印出您设置的密保问题，您需要正确输入密保问题的答案，若输入正确则验证成功，之后需要设置新的密码，在这个过程中您需要再次确认您的密码（为了提醒您记住密码），设置完成后您可以重新登录。

若选择“返回主界面”或未设置密保问题或第二次确认密码时输入错误，都会自动返回交易平台主界面。

在这里输入的密码同样被“*”保护起来，并且不能退格和更改。

```c++
请输入选择:3
请输入用户名:力古
请输入密码:*
-----密码错误-----
请输入选项: 1.忘记密码 0.返回主界面:1
密保问题为: 生日
请输入答案:3.31
验证成功!
请输入新的密码:******
请再次确认您的密码:******
修改成功!
```



------



### 我是卖家

选择选项1进入卖家模式，系统将会展示卖家菜单：

```c++
==========================================================================================
1.发布商品 2.查看发布商品 3.修改商品信息 4.下架商品 5.查看历史订单 6.评论区 7.返回用户主界面
==========================================================================================
```



#### 发布商品

输入1发布商品，您需要根据系统提示按要求输入商品的信息。

商品的价格最多只能为1位小数。

输入商品信息后系统会根据您输入的信息将商品信息打印在屏幕上并询问您是否确定发布商品，输入'y'则成功发布商品，输入'n'则取消发布。

```c++
请输入商品名称(不超过10个字符):冰墩墩
请输入商品价格(1位小数):5.5
请输入商品数量:10
请输入商品描述(不超过100个字符):吉祥物
生成的指令为: INSERT INTO commodity VALUES (冰墩墩,5.5,10,吉祥物)
请确定发布的商品信息无误!
***********
商品名称:冰墩墩
商品价格:5.5
商品数量:10
商品描述:吉祥物
***********
您确定要发布商品吗? (y/n)y
发布成功!
```



#### 查看发布商品

输入2查看发布商品，短暂显示生成的SQL指令后，您可以选择不同的顺序展示您发布过的所有商品。

```c++
请输入展示顺序: 1.按系统默认排序 2.按价格升序 3.按价格降序
1
*******************************************************************************
商品ID     名称                  价格    数量     上架时间    商品状态
M004       冰墩墩                5.5      10     2022-3-31   销售中
*******************************************************************************
```



#### 修改商品信息

输入3修改商品信息，首先您需要正确输入您发布过的一件在售商品的ID，然后您可以修改这件商品的价格或者商品描述，修改后的商品信息会打印在屏幕上，系统会询问您是否确认修改，输入'y'则会打印生成的SQL指令并提示修改成功，输入'n'则放弃此次修改。

```c++
请输入被修改商品的ID:M004
请输入被修改商品的属性(1.价格 2.描述):1
请输入被修改商品的价格:6.5
请确认被修改的商品信息无误!
*************************
商品ID: M004
商品名称: 冰墩墩
商品价格: 6.5
商品描述: 吉祥物
*************************
确认修改? (y/n)y
生成的指令为: UPDATE commodity SET 价格=6.5 WHERE ID= M004
修改成功!
```



#### 下架商品

输入4下架商品，您需要输入一件您发布过的在售中的商品ID，之后系统会打印该商品的信息，并询问您是否确认下架该商品，输入'y'则显示生成的SQL指令并成功下架商品，输入'n'则放弃下架。

嘿，在您下架商品前，请想想可能有人非常喜欢您发布的这件商品呢！

```c++
请输入要下架的商品ID:M005
要确定下架该商品吗?
*******************************************************************************
商品ID     名称                  价格     数量    卖家ID  上架时间   商品状态
M005       测试                  10.0     10     U002   2022-3-31   销售中*******************************************************************************
请选择(y/n):y
生成的指令为: UPDATE commodity SET 状态=已下架 WHERE ID= M005
下架成功!
```



#### 查看历史订单

输入5，会短暂显示生成的SQL指令，之后会打印出所有与您相关的订单记录。

```c++
*******************************************************************************
订单ID   商品ID   交易单价   数量   交易时间   买家ID
T001    M001      2.5       2    2022-3-18   U001 
*******************************************************************************
```



#### 评论区

见下方。

#### 返回用户主界面

返回用户菜单界面。

------



### 我是买家

选择选项2进入买家模式，系统将会展示买家菜单：

```c++
===========================================================================================
1.查看商品列表 2.购买商品 3.搜索商品 4.查看历史订单 5.查看商品详细信息 6.评论区 7.返回用户主界面
===========================================================================================
```



#### 查看商品列表

输入1会短暂显示生成的SQL指令，并打印出当前在售的商品列表。

```c++
请输入展示顺序: 1.按系统默认排序 2.按价格升序 3.按价格降序
1
*******************************************************************************
商品ID     名称                  价格    卖家ID  上架时间
M004       冰墩墩                6.5      U002   2022-3-31
*******************************************************************************
```



#### 购买商品

输入2购买商品，您需要输入您想购买的商品ID并输入购买的数量，若商品库存充足且您的余额足够支付时，系统会打印出相关的交易信息和生成的SQL指令。

```c++
请输入商品ID:M004
请输入数量:2
**************************************************
交易提醒!
交易时间: 2022-3-31
交易单价: 6.5
交易数量: 2
交易状态: 交易成功
您的余额: 87.0
生成的指令为: INSERT INTO order VALUES (T001,M004,6.500000,2,2022-3-31,U002,U003)
```



#### 搜索商品

输入3搜索商品，系统会提示您输入商品名称，输入商品名称后屏幕会短暂显示生成的SQL指令，接下来则会自动匹配商品列表中含有您输入的名称的商品并打印在屏幕上。

我们的搜索功能默认支持模糊匹配，即所有名称中含有您输入内容的商品都会展示在屏幕上。

例如，输入“冰墩墩”后：

```c++
*******************************************************************************
商品ID     名称                  价格    卖家ID  上架时间
M004       冰墩墩                6.5     U002   2022-3-31
*******************************************************************************
```



#### 查看历史订单

输入4，会短暂显示生成的SQL指令，之后会打印出所有与您相关的订单记录。

```c++
*******************************************************************************
订单ID   商品ID   交易单价   数量   交易时间   卖家ID 
T001     M004       6.5      2    2022-3-31  U002
*******************************************************************************
```



#### 查看商品详细信息

输入5可以查看您感兴趣的商品的详细信息，您需要输入商品ID，若该商品在售，则会打印出该商品的详细信息。

```c++
*******************************************
商品ID: M004
商品名称: 冰墩墩
商品价格: 6.5
上架时间: 2022-3-31
商品描述: 吉祥物
商品卖家: U002
*******************************************
```



#### 评论区

见下方。

#### 返回用户主界面

返回用户菜单界面。

------



### 个人信息管理

选择选项3进入个人信息管理页面，系统展示个人信息管理菜单：

```c++
==============================================================
1.查看信息 2.修改信息 3.充值 4.设置密保问题 5.返回用户主界面
==============================================================
```



#### 查看信息

输入1会展示当前用户的个人信息。

```c++
*********************
用户名: 力古
联系方式: 1234512345
地址: 召唤师峡谷
钱包余额: 13.0
*********************
```



#### 修改信息

输入2可以选择您要修改的属性，您可以修改用户名、联系方式和地址。

新修改的用户名不能与已经注册的用户名重复。

```c++
请选择修改的属性 (1.用户名 2.联系方式 3.地址) : 2
请输入修改后的联系方式: 12345678
修改成功!
```



#### 充值

输入3可以往您的账户充值，您的金额最多为1位小数。

```c++
请输入充值金额: 100
充值成功,当前余额: 113.0
```



#### 设置密保问题

为了在您忘记密码的时候可以找回您的密码，您可以在注册后为自己设置一个密保问题，输入对应的答案（您需要记住您的答案，否则忘记密码之后就找不回了）。之后在“忘记密码”功能中输入您的密保问题的答案，回答正确则可以重新设置密码。

```c++
请输入密保问题:生日
请输入答案:3.31
```



#### 返回用户主界面

返回用户菜单界面。

------

## 

### 注销登录

返回交易平台主界面。

------



## 评论区

无论是卖家模式还是买家模式，都可以在对应的菜单进入评论区，在这里您可以：

1.管理已发表的评论
2.进入某一商品的评论区



若选择管理已发表的评论，您可以看到您发表过的所有评论，之后您可以选择删除某些评论。

```c++
请输入您的选择(1.管理我的评论 2.进入商品评论区): 1
=================================================================
003  2022-03-31 22:07:25: U002 敏感肌能用吗         点赞数:2
004  2022-03-31 22:10:58: U002 孩子已经买了一箱了   点赞数:0
=================================================================
请输入您的选择(1.删除评论 2.返回上一级界面): 1
请输入您要删除的评论的序号: 004
删除成功!
```



若选择进入商品评论区，则首先打印该商品的详细信息，之后会打印该商品的所有用户评论。

您可以选择发表自己的评论，或者回复某一条评论，或者为某一条评论点赞。（评论前的三位数字即为评论的序号）

```c++
请输入您的选择(1.管理我的评论 2.进入商品评论区): 2
请输入商品ID: M004
*******************************************
商品ID: M004
商品名称: 冰墩墩
商品价格: 6.5
上架时间: 2022-3-31
商品描述: 吉祥物
商品卖家: U002
*******************************************

评论区:
================================================================================
003  2022-03-31 22:07:25: U002 敏感肌能用吗         点赞数:1
回复003 2022-03-31 22:10:58: U002 孩子已经买了一箱了
================================================================================
请选择您的操作(1.发表评论 2.回复评论 3.点赞评论 4.返回上一级): 3
请输入您要点赞的评论的序号: 003
点赞成功!
```



请留下友善的评论哦！

------



## 今日新闻

选择选项4可以查看冬奥会上的精彩新闻！新闻内容与冬奥密切相关，意在展示中国运动健儿们在冬奥赛场上取得的佳绩，有利于增进我们对体育盛事的关注，增强文化自信。

```c++
请输入选择:4
2月12日,在北京冬奥会速度滑冰男子500米决赛中,高亭宇破纪录夺冠,赢得中国第四金。
此前,国家速滑馆“冰丝带”已见证多项世界纪录、奥运会纪录的诞生!
```



------



## 一些问答

1.若我输入的错误的选项/错误的信息，系统会因此而产生意想不到的错误吗？

答：我们在设计平台时考虑过用户可能输入一些“神奇”的内容，因此我们在检查用户输入正确性上做了一定的努力，我们认为您的大部分输入都不会引起程序的异常，但由于我们的程序员能力有限，我们无法保证程序在任何输入下都能正确运行，因此请您尽可能不要“故意”输入错误的信息来调戏程序。

2.程序运行过程中为什么要生成SQL指令？我又不关心程序背后的实现，这不是多此一举吗？

答：我们设计的初衷除了一个基本的交易平台外，我们也希望能够将程序与数据库的交互这一块“有趣”的内容向用户展示出来，对于那些对这个过程感兴趣的用户来说，他们能够从中了解更多！

3.请问这个程序能够在Linux系统下运行吗？

答：目前我们的版本只支持在windows系统下运行，对于可行的Linux版本，我们也许(?)会在不久的未来推出，对您造成的不便我们深感抱歉。

4.我觉得你们做得很好，我可以通过什么渠道向你们表达我内心的支持？

答：感谢支持！如果您认为我们做得很好，您可以在应用商店给我们评满分，也可以联系作者给予资金上的支持。再次感谢！（狗头）
