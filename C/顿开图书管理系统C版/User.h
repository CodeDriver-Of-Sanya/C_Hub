#ifndef _USER_H_
#define _USER_H_
#include"Configure.h"

//先来枚举一下用户类型
enum UserType
{
	UT_SysAdmin = 1,//系统管理员
	UT_BookAdmin,//图书管理员
	UT_CommentUser//普通用户
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

#endif // !_USER_H_
