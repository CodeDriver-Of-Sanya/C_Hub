#ifndef _USERMANAGER_H_
#define _USERMANAGER_H_
#include"User.h"
#include"List.h"//用链表存所有的用户数据

typedef struct UserManager
{
	User userList;
}UserManager;

//初始化管理结构
void userManager_init(UserManager* um);

//加载用户数据
void userManager_loadData(UserManager* um,const char* filename);

//用户管理操作
void userManager_operation(UserManager* um);

//用户信息添加
void userManager_add(UserManager* um);

//用户信息修改
void userManager_modify(UserManager* um);

//用户信息删除
void userManager_remove(UserManager* um);

//用户信息显示
void userManager_show(UserManager* um);

//用户密码修改
void userManager_modifyPassword(UserManager* um);

#endif // !_USERMANAGER_H_
