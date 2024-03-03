#ifndef _USER_H_
#define _USER_H_
#include"Configure.h"

//先来枚举一下用户类型
enum UserType
{
	UT_SysAdmin = 1,//系统管理员
	UT_BookAdmin,//图书管理员
	UT_CommonUser//普通用户
};

typedef struct User
{
	unsigned long long ID;//编号
	char password[10];//密码
	int type;//用户类型
}User;

//创建一个空的User
User* createEmptyUser();

//输出用户信息
void user_print(User u);

//保存用户信息
void user_save(User* u, FILE* f);

//判断用户是否是普通用户
bool is_commomUser(User* u);

//判断用户是否是图书管理员
bool is_bookAdmin(User* u);

//判断用户是否是系统管理员
bool is_systemAdmin(User* u);


#endif // !_USER_H_
