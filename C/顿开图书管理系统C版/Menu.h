#ifndef _MENU_H_
#define _MENU_H_

//菜单

//主菜单
int mainMenu();

//用户管理菜单
int userMenu();

//读者管理菜单
int readerMenu();

//图书管理菜单
int bookMenu();

//图书查询菜单
int bookSearchMenu();

//图书流通菜单
int bookCirculateMenu();

//操作

//菜单选项选择
int select();

//系统退出
void quit();

#endif // !MENU_H_
