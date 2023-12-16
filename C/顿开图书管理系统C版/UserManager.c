#include "UserManager.h"
#include"Menu.h"

void userManager_init(UserManager* um)
{
	list_init(&um->userList);//初始化用户list
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

	}
	else {
		printf("未找到ID是 %llu 的用户！\n", ID);
		system("pause");
		return;
	}
}

void userManager_remove(UserManager* um)
{
}

void userManager_show(UserManager* um)
{
	printf("%-10s %-10s %s\n", "用户ID","用户密码","用户类型");
	list_transfrom(&um->userList, user_print);
	system("pause");
}

void userManager_modifyPassword(UserManager* um)
{
}
