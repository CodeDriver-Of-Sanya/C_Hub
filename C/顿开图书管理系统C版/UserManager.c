#include "UserManager.h"
#include"Menu.h"
#include<string.h>

void userManager_init(UserManager* um)
{
	list_init(&um->userList);//初始化用户list
	um->curUser = NULL;//最开始还没登录，所以初始化为NULL
	userManager_loadData(um, "./data/user.txt");
}

void userManager_loadData(UserManager* um, const char* filename)
{
	FILE* fp = fopen(filename, "r");
	if (!fp)
	{
		perror("%s open failed!\n", filename);
		return;
	}

	//获取数据
	char buf[BUFSIZ] = { 0 };
	fgets(buf, BUFSIZ, fp);//第一次先把表头读出来

	//然后开始获取数据
	while (!feof(fp))
	{
		fgets(buf, BUFSIZ, fp);
		//拆分字符串
		User* u = createEmptyUser();
		if (sscanf(buf, "%llu %s %d", &u->ID, u->password, &u->type) <= 0)
		{
			printf("sscanf failed!\n");
			free(u);

			break;
		}
		list_pushBack(&um->userList, u);
	}

	fclose(fp);
}

static bool cmpUser(User* u1, User* u2) {//不能被外部访问的静态成员函数
	return (u1->ID == u2->ID && strcmp(u1->password, u2->password) == 0);
}
bool userManager_login(UserManager* um, unsigned long long _ID, const char* _password)
{
	User u;
	u.ID = _ID;
	strcpy(u.password, _password);
	//查找_ID和password是否存在
	User* end = list_search(&um->userList, cmpUser, &u);//返回的是一个User指针
	if (!end)return false;

	//登录成功了就保存一下登录的用户信息
	um->curUser = end;

	return true;
}

void userManager_operation(UserManager* um)
{
	bool isCyc = true;
	while (isCyc)
	{
		system("cls");
		switch (userMenu())
		{
		case 0:
			isCyc = false;
			break;
		case 1:
			userManager_add(um);
			break;
		case 2:
			userManager_modify(um);
			break;
		case 3:
			userManager_remove(um);
			break;
		case 4:
			userManager_show(um);
			break;
		case 5:
			userManager_modifyPassword(um);
			break;
		default:
			printf("输入的选项有误！请重新输入！\n");
			system("pause");
			break;
		}
	}
}

void userManager_add(UserManager* um)
{
	printf("请输入要新添加的用户（ID 密码 类型）：");
	User* u = createEmptyUser();
	if (3 == scanf("%llu %s %d", &u->ID, u->password, u->type))
	{
		list_pushBack(&um->userList, u);
		printf("用户添加成功！\n");
	}

}

bool user_cmp(variant v1, variant v2) 
{
	User* u = v1;
	unsigned long long _ID = v2;
	return (u->ID == _ID);
}
void userManager_modify(UserManager* um)
{
	unsigned long long ID = -1;
	printf("请输入你要修改的用户ID：");
	scanf("%llu", &ID);
	//查找
	User* u = list_search(&um->userList, user_cmp, ID);
	if (u)
	{
		printf("请输入新的用户类型（1，2，3）：");
		if (scanf("%d", &u->type) == 1)
		{
			printf("修改成功！\n");
		}
	}
	else {
		printf("未找到ID是 %llu 的用户！\n", ID);
		system("pause");
		return;
	}
}

void userManager_remove(UserManager* um)
{
	unsigned long long ID = -1;
	printf("请输入你要删除的用户ID：");
	scanf("%llu", &ID);
	//查找
	User* u = list_search(&um->userList, user_cmp, ID);
	if (!u)
	{
		printf("未找到ID是 %llu 的用户！\n", ID);
		system("pause");
		return;
	}
	list_removeOne(&um->userList, u);
	printf("用户删除成功！\n");

}

void userManager_show(UserManager* um)
{
	printf("%-10s %-10s %s\n", "用户ID","用户密码","用户类型");
	list_transfrom(&um->userList, user_print);
	system("pause");
}

void userManager_modifyPassword(UserManager* um)
{
	if (!um->curUser)
	{
		printf("无登录用户信息！\n");
		system("pause");
		return;
	}

	printf("请输入想要设置的新密码：");
	//gets_s(um->curUser->password, 10);
	scanf("%s", um->curUser->password);
	printf("修改成功！\n新密码是：%s\n", um->curUser->password);
	system("pause");
	return;

}
