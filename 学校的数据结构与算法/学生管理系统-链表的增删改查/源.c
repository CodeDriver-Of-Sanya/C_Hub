#include <stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<stdbool.h>

/*
学生管理系统：
	数据项包括：
		学号(long long int)
		姓名(char[11])
		性别(char[3])
		年龄(int)
		学号不能重复，姓名可重复
	存储结构：
		有头有尾的双向链表，方便操作
		头节点中用 学号 这一数据项去记录有效数据节点的个数
	主要功能：
		1.增加学生
			1.1尾插
				在表的最末尾插入学生
			1.2插入指定学号后面
				插入到指定的已存在的学号后面一位，不存在则让用户重新输入学号
			1.3插入指定姓名后面
				将所有重名的学生都输出出来，让用户选择插入到谁的后面
		2.删除学生
			2.1尾删
				删除表的最末尾的学生
			2.2根据学号删除学生
				删除指定的已存在的学生，不存在则让用户重新输入学号
			2.3根据姓名删除学生
				将所有重名的学生都输出出来，让用户选择删除谁
		3.修改学生
			3.1根据学号修改学生信息
				修改指定的已存在的学生，不存在则让用户重新输入学号
			3.2根据姓名修改学生信息
				将所有重名的学生都输出出来，让用户选择修改谁
				可以选择跳过单个数据项的修改
		4.查询学生
			4.1根据学号查询学生信息
				修改指定的已存在的学生，不存在则让用户重新输入学号
			4.2根据姓名查询学生信息
				将所有重名的学生都输出出来
		5.文件存储
			程序运行时在初始化中读取本地文件 stuInfo.txt 中的数据到表中
			退出时将表中数据存储到本地文件 stuInfo.txt 中
*/

//学生的结构类型
struct student
{
	long long int ID;		//学号
	char name[11];			//姓名
	char gender[3];			//性别
	int age;				//年龄
};

//存学生的节点类型
struct node {
	struct student stu;
	struct node* pNext;
	struct node* pParent;
};

//存学生的链表类型
struct list {
	//头节点
	struct node* pHead;
	//尾节点
	struct node* tail;
};

//创建空节点
struct node* createNodeNULL();

//创建节点
struct node* createNode(long long int ID, char* name, char* gender, int age);

//创建链表类型
struct list* createList();

//初始化链表（文件操作）
void initList(struct list* l);

//学生管理主菜单
void stuMainMenu(struct list* list);

//学生添加菜单
void stuInsertMenu(struct list* list);

//学生删除菜单
void stuDelMenu(struct list* list);

//学生修改菜单
void stuModifyMenu(struct list* list);

//学生查询菜单
void stuSearchMenu(struct list* list);

//尾插
void push(struct list* l, struct node* n);

//根据学号中间插
void midInsertByID(struct list* l, struct node* n, long long int ID);

//根据姓名中间插（如果有重名默认插在第一个的后面）
void midInsertByName(struct list* l, struct node* n, char* name);

//遍历
void travel(struct list* l);

//根据学号遍历(返回下标)
struct node* travelByID(struct list* l, long long int _ID);

//根据姓名遍历（返回下标）
struct node* travelByName(struct list* l, char* _name);

//尾删
void pop(struct list* l);

//根据学号删除学生
void delStuByID(struct list* l, long long int ID);

//根据姓名删除学生
void delStuByName(struct list* l, char* name);

//根据学号修改学生信息
void modifyByID(struct list* l, long long int ID);

//根据姓名修改学生信息
void modifyByName(struct list* l, char* name);

//文件操作
//退出系统的时候保存到本地文件 stuInfo.txt 中
void saveToFile(struct list* l);

//退出前销毁顺序表
void destory(struct list* l);

int main() {
	//创建链表(顺便用list->pHead->stu.ID存储目前已有的节点数量，不包括头节点)
	struct list* list = createList();
	//初始化链表
	initList(list);
	//主程序
	while (true)
	{
		stuMainMenu(list);
	}
	return 0;
}

//创建空节点
struct node* createNodeNULL()
{
	struct node* pNew = malloc(sizeof(struct node));
	while (NULL == pNew) {
		pNew = malloc(sizeof(struct node));
	}
	//全赋空值
	memset(pNew, 0, sizeof(struct node));
	return pNew;
}

//创建节点
struct node* createNode(long long int _ID, char* _name, char* _gender, int _age)
{
	struct node* pNew = malloc(sizeof(struct node));
	while (NULL == pNew) {
		pNew = malloc(sizeof(struct node));
	}
	//赋值
	pNew->stu.ID = _ID;
	strcpy(pNew->stu.name, _name);
	strcpy(pNew->stu.gender, _gender);
	pNew->stu.age = _age;
	//指针指向空防止指向奇怪的地方
	pNew->pNext = NULL;
	pNew->pParent = NULL;
	//返回出去
	return pNew;
}

//创建链表类型
struct list* createList()
{
	struct list* pNew = malloc(sizeof(struct list));
	pNew->pHead = createNodeNULL();
	//尾节点指向最末尾的节点
	pNew->tail = pNew->pHead;
	return pNew;
}

//初始化链表（文件操作）
void initList(struct list* l)
{
	//将本地文件 stuInfo.txt 里的学生信息填入顺序表
	FILE* fp = fopen("stuInfo.txt", "r+");
	while (NULL == fp)
	{
		printf("文件打开失败，正在重试...\n");
		fp = fopen("stuInfo.txt", "w+");
	}
	struct node* n = createNodeNULL();
	while (EOF != fscanf(fp, "%lld %s %s %d", &n->stu.ID, n->stu.name, n->stu.gender, &n->stu.age)) {
		push(l, n);
		n = createNodeNULL();
	}
	//关闭文件
	fclose(fp);
}

//学生管理主菜单
void stuMainMenu(struct list* l)
{
	//菜单选择
	int select;
	system("cls");
	printf("========================  学生管理系统  ========================\n");
	printf("\t\t -------------------------------\n");
	printf("\t\t|                               |\n");
	printf("\t\t|          1.学生添加           |\n");
	printf("\t\t|                               |\n");
	printf("\t\t|          2.学生删除           |\n");
	printf("\t\t|                               |\n");
	printf("\t\t|          3.学生修改           |\n");
	printf("\t\t|                               |\n");
	printf("\t\t|          4.学生查询           |\n");
	printf("\t\t|                               |\n");
	printf("\t\t|          5.全部学生           |\n");
	printf("\t\t|                               |\n");
	printf("\t\t|          0.保存退出           |\n");
	printf("\t\t|                               |\n");
	printf("\t\t -------------------------------\n");
	printf("\n\t\t请输入你的选择：");
	scanf("%d", &select);
	switch (select)
	{
	case 0:
		//先将改完的表保存到文件
		saveToFile(l);
		//再销毁顺序表
		destory(l);
		//最后退出
		exit(0);
		break;
	case 1:
		stuInsertMenu(l);
		break;
	case 2:
		stuDelMenu(l);
		break;
	case 3:
		stuModifyMenu(l);
		break;
	case 4:
		stuSearchMenu(l);
		break;
	case 5:
		travel(l);
		break;
	default:
		printf("输入选项有误，请重新输入！");
		system("pause");
		system("cls");
		break;
	}
}

//学生插入菜单
void stuInsertMenu(struct list* l)
{
	//要添加的学生信息
	long long int _ID;
	int _age;
	char _name[11];
	char _gender[3];
	//判断学号是否存在
	struct node* isExit;
	//某学号
	long long int selectID;
	//某姓名
	char selectName[11];
	//要添加的学生节点
	struct node* n = createNodeNULL();
	//输入的菜单选项
	int select;
	//临时用于清除缓冲区的
	int c;
	//控制菜单循环
	bool isShow = true;
	while (isShow)
	{
		system("cls");
		printf("========================  学生管理系统  ========================\n");
		printf("\t\t -------------------------------\n");
		printf("\t\t|                               |\n");
		printf("\t\t|          1.直接添加           |\n");
		printf("\t\t|                               |\n");
		printf("\t\t|          2.添加到某学号后面   |\n");
		printf("\t\t|                               |\n");
		printf("\t\t|          3.添加到某姓名后面   |\n");
		printf("\t\t|                               |\n");
		printf("\t\t|          0.返回上级           |\n");
		printf("\t\t|                               |\n");
		printf("\t\t -------------------------------\n");
		printf("\n\t\t请输入你的选择：");
		scanf("%d", &select);
		switch (select)
		{
		case 0:
			isShow = false;
			break;
		case 1:
			printf("请输入添加学生的学号（必须输入且不能重复）：");
			scanf("%lld", &_ID);
			while ((c = getchar()) != '\n' && c != EOF);
			//判断要插入的学号有没有重复
			isExit = travelByID(l, _ID);
			while (NULL != isExit) {
				//有重复，重新输入
				printf("输入的学号已存在，请重新输入：");
				scanf("%lld", &_ID);
				while ((c = getchar()) != '\n' && c != EOF);
				isExit = travelByID(l, _ID);
			}
			printf("请输入添加学生的姓名：");
			scanf("%s", _name);
			while ((c = getchar()) != '\n' && c != EOF);
			printf("请输入添加学生的性别：");
			scanf("%2s", _gender);
			while ((c = getchar()) != '\n' && c != EOF);
			printf("请输入添加学生的年龄：");
			scanf("%d", &_age);
			//system("pause");
			//printf("%lld %s %s %d\n", _ID, _name, _gender, _age);
			//system("pause");
			n = createNode(_ID, _name, _gender, _age);
			push(l, n);
			printf("添加成功!\n");
			system("pause");
			break;
		case 2:
			printf("请输入添加学生的学号：");
			scanf("%lld", &_ID);
			while ((c = getchar()) != '\n' && c != EOF);
			//判断要插入的学号有没有重复
			isExit = travelByID(l, _ID);
			while (NULL != isExit) {
				//有重复，重新输入
				printf("输入的学号已存在，请重新输入：");
				scanf("%lld", &_ID);
				while ((c = getchar()) != '\n' && c != EOF);
				isExit = travelByID(l, _ID);
			}
			printf("请输入添加学生的姓名：");
			scanf("%s", _name);
			while ((c = getchar()) != '\n' && c != EOF);
			printf("请输入添加学生的性别：");
			scanf("%2s", _gender);
			while ((c = getchar()) != '\n' && c != EOF);
			printf("请输入添加学生的年龄：");
			scanf("%d", &_age);
			printf("请输入某学号：");
			scanf("%lld", &selectID);
			//system("pause");
			//printf("%lld %s %s %d\n", _ID, _name, _gender, _age);
			//system("pause");
			n = createNode(_ID, _name, _gender, _age);
			midInsertByID(l, n, selectID);
			break;
		case 3:
			printf("请输入添加学生的学号：");
			scanf("%lld", &_ID);
			while ((c = getchar()) != '\n' && c != EOF);
			//判断要插入的学号有没有重复
			isExit = travelByID(l, _ID);
			while (NULL != isExit) {
				//有重复，重新输入
				printf("输入的学号已存在，请重新输入：");
				scanf("%lld", &_ID);
				while ((c = getchar()) != '\n' && c != EOF);
				isExit = travelByID(l, _ID);
			}
			printf("请输入添加学生的姓名：");
			scanf("%s", _name);
			while ((c = getchar()) != '\n' && c != EOF);
			printf("请输入添加学生的性别：");
			scanf("%2s", _gender);
			while ((c = getchar()) != '\n' && c != EOF);
			printf("请输入添加学生的年龄：");
			scanf("%d", &_age);
			printf("请输入某学生的姓名：");
			scanf("%s", selectName);
			n = createNode(_ID, _name, _gender, _age);
			midInsertByName(l, n, selectName);
			break;
		default:
			printf("输入选项有误，请重新输入！\n");
			system("pause");
			system("cls");
			break;
		}
	}
}

//学生删除菜单
void stuDelMenu(struct list* l)
{
	//要删除学号
	long long int selectID;
	//要删除姓名
	char selectName[11];
	//输入的菜单选项
	int select;
	//控制菜单循环
	bool isShow = true;
	while (isShow)
	{
		system("cls");
		printf("========================  学生管理系统  ========================\n");
		printf("\t\t -------------------------------\n");
		printf("\t\t|                               |\n");
		printf("\t\t|          1.尾部删除           |\n");
		printf("\t\t|                               |\n");
		printf("\t\t|          2.根据学号删除       |\n");
		printf("\t\t|                               |\n");
		printf("\t\t|          3.根据姓名删除       |\n");
		printf("\t\t|                               |\n");
		printf("\t\t|          0.返回上级           |\n");
		printf("\t\t|                               |\n");
		printf("\t\t -------------------------------\n");
		printf("\n\t\t请输入你的选择：");
		scanf("%d", &select);
		switch (select)
		{
		case 0:
			isShow = false;
			break;
		case 1:
			pop(l);
			break;
		case 2:
			printf("请输入要删除的学生学号：");
			scanf("%lld", &selectID);
			delStuByID(l, selectID);
			break;
		case 3:
			printf("请输入要删除的学生姓名：");
			scanf("%s", selectName);
			delStuByName(l, selectName);
			break;
		default:
			printf("输入选项有误，请重新输入！\n");
			system("pause");
			system("cls");
			break;
		}
	}
}

//学生修改菜单
void stuModifyMenu(struct list* l)
{
	//根据学号修改
	long long int selectID;
	//根据姓名修改
	char selectName[11];
	//输入的菜单选项
	int select;
	//控制菜单循环
	bool isShow = true;
	while (isShow)
	{
		system("cls");
		printf("========================  学生管理系统  ========================\n");
		printf("\t\t -------------------------------\n");
		printf("\t\t|                               |\n");
		printf("\t\t|          1.根据学号修改       |\n");
		printf("\t\t|                               |\n");
		printf("\t\t|          2.根据姓名修改       |\n");
		printf("\t\t|                               |\n");
		printf("\t\t|          0.返回上级           |\n");
		printf("\t\t|                               |\n");
		printf("\t\t -------------------------------\n");
		printf("\n\t\t请输入你的选择：");
		scanf("%d", &select);
		switch (select)
		{
		case 0:
			isShow = false;
			break;
		case 1:
			printf("请输入要修改信息的学生学号：");
			scanf("%lld", &selectID);
			modifyByID(l, selectID);
			break;
		case 2:
			printf("请输入要修改信息的学生姓名：");
			scanf("%s", selectName);
			modifyByName(l, selectName);
			break;
		default:
			printf("输入选项有误，请重新输入！\n");
			system("pause");
			system("cls");
			break;
		}
	}
}

//学生查询菜单
void stuSearchMenu(struct list* l)
{
	//要查询的学号
	long long int selectID = 0;
	//要查询的姓名
	char selectName[11] = { 0 };
	//查询学生姓名可能遇见重复,用数组记录
	struct node* sameName[50] = { 0 };
	//输入的菜单选项
	int select;
	//控制菜单循环
	bool isShow = true;
	while (isShow)
	{
		system("cls");
		printf("========================  学生管理系统  ========================\n");
		printf("\t\t -------------------------------\n");
		printf("\t\t|                               |\n");
		printf("\t\t|          1.根据学号查询       |\n");
		printf("\t\t|                               |\n");
		printf("\t\t|          2.根据姓名查询       |\n");
		printf("\t\t|                               |\n");
		printf("\t\t|          0.返回上级           |\n");
		printf("\t\t|                               |\n");
		printf("\t\t -------------------------------\n");
		printf("\n\t\t请输入你的选择：");
		scanf("%d", &select);
		switch (select)
		{
		case 0:
			isShow = false;
			break;
		case 1:
			printf("\t\t请输入要查询的学号：");
			scanf("%lld", &selectID);
			struct node* searched = travelByID(l, selectID);
			while (NULL == searched) {
				printf("\t\t输入的学号不存在，请重新输入（输入-2结束）：");
				scanf("%lld", &selectID);
				if (-2 == selectID) {
					break;
				}
				searched = travelByID(l, selectID);
				printf("\t\t查询到学号为【%lld】的学生信息：\n", searched->stu.ID);
				printf("\t\t学      号    姓    名   性别   年龄  \n");
				printf("\t\t%10lld  %10s   %4s   %4d  \n", searched->stu.ID, searched->stu.name, searched->stu.gender, searched->stu.age);
				system("pause");
			}
			break;
		case 2:
			printf("请输入要查询信息的学生姓名：");
			scanf("%s", selectName);
			//需要将所有同名的都要显示出来，遍历单独写
			//判断表是否存在
			if (NULL == l) {
				printf("表不存在！");
				system("pause");
				return;
			}
			//开始遍历
			int idx = 0;//记录有多少个重名的
			struct node* pTemp = l->pHead->pNext;
			while (pTemp) {
				if (0 == strcmp(pTemp->stu.name, selectName)) {
					sameName[idx++] = pTemp;
				}
				pTemp = pTemp->pNext;
			}
			//遍历完成，开始输出
			printf("以下是学生姓名为【%s】的学生：\n", selectName);
			printf("\t\t学      号    姓    名   性别   年龄  \n");
			for (int i = 0; i < idx; i++)
			{
				printf("\t\t%10lld  %10s   %4s   %4d  \n", sameName[i]->stu.ID, sameName[i]->stu.name, sameName[i]->stu.gender, sameName[i]->stu.age);
			}
			printf("\n");
			system("pause");
			break;
		default:
			printf("输入选项有误，请重新输入！\n");
			system("pause");
			system("cls");
			break;
		}
	}
}

//尾插
void push(struct list* l, struct node* n)
{ 
	//判断表是否存在
	if (NULL == l) {
		printf("表不存在！");
		system("pause");
		return;
	}
	//先让尾节点的next指向新节点
	l->tail->pNext = n;
	//接着让新的节点的pParent指向尾节点
	n->pParent = l->tail;
	//更新尾节点
	l->tail = n;
	//头节点计数+1
	l->pHead->stu.ID++;
}

//根据学号中间插
void midInsertByID(struct list* l, struct node* n, long long int _ID)
{
	//判断表是否存在
	if (NULL == l) {
		printf("表不存在！");
		system("pause");
		return;
	}
	//遍历找到目标学号
	struct node* pTemp = travelByID(l, _ID);
	if (NULL == pTemp) {//没找到
		printf("未找到目标学号，插入失败！\n");
		system("pause");
		return;
	}
	else {//找到了目标节点，开始往他后面插
		//先判断是不是最后一个
		if (pTemp == l->tail) {
			//如果是，就去尾插
			push(l, n);
		}
		else {//如果不是，就正常插入
			//新节点对接目标节点的下一个
			n->pNext = pTemp->pNext;
			//目标节点的下一个更新为新节点
			pTemp->pNext = n;
			//新节点的父节点更新为目标节点
			n->pParent = pTemp;
			//新节点的下一个节点的父节点更新为新节点（旧的是指向目标节点的）
			n->pNext->pParent = n;
			//链表头节点计数器++
			l->pHead->stu.ID++;
		}
	}
	printf("添加成功!\n");
	system("pause");
	return;
}

//根据姓名中间插
void midInsertByName(struct list* l, struct node* n, char* _name)
{
	//判断表是否存在
	if (NULL == l) {
		printf("表不存在！");
		system("pause");
		return;
	}
	//遍历检查是否存在该姓名
	if (NULL == travelByName(l, _name)) {
		printf("未找到目标姓名，插入失败！\n");
		system("pause");
		return;
	}
	else {//目标学号存在，循环遍历将同名的都遍历出来
		//准备一个放同名学生的数组
		struct node* sameArr[50] = { 0 };
		//累计共有多少个同名的
		int idx = 0;
		//开始遍历记录
		struct node* pTemp = l->pHead->pNext;
		while (pTemp) {
			if (0 == strcmp(pTemp->stu.name, _name)) {
				sameArr[idx++] = pTemp;
			}
			pTemp = pTemp->pNext;
		}
		//遍历输出数组，让用户选择
		int select = 0;
		printf("以下是名为【%s】的学生：\n", _name);
		printf("\t\t    学     号    姓    名   性别   年龄  \n");
		for (int i = 0; i < idx; i++)
		{
			printf("\t\t %d.%10lld  %10s   %4s   %4d  \n", i+1, sameArr[i]->stu.ID, sameArr[i]->stu.name, sameArr[i]->stu.gender, sameArr[i]->stu.age);
		}
		printf("\n");
		printf("请选择目标学生信息序号：");
		scanf("%d", &select);
		select--;
		while (select < 0 || select >= idx) {
			printf("输入的范围有误！请重新输入：");
			scanf("%d", &select);
		}
		pTemp = sameArr[select];
		//开始进行插入流程
		//先判断是不是最后一个
		if (pTemp == l->tail) {
			//如果是，就去尾插
			push(l, n);
		}
		else {//如果不是，就正常插入
			//新节点对接目标节点的下一个
			n->pNext = pTemp->pNext;
			//目标节点的下一个更新为新节点
			pTemp->pNext = n;
			//新节点的父节点更新为目标节点
			n->pParent = pTemp;
			//新节点的下一个节点的父节点更新为新节点（旧的是指向目标节点的）
			n->pNext->pParent = n;
			//链表头节点计数器++
			l->pHead->stu.ID++;
		}
	}	
	printf("添加成功!\n");
	system("pause");
	return;
}

//遍历
void travel(struct list* l)
{
	system("cls");
	printf("\t\t -------------全部学生信息--------------\n");
	printf("\t\t| 学      号    姓    名   性别   年龄 |\n");
	struct node* pTemp = l->pHead->pNext;
	while (pTemp) {
		printf("\t\t| %10lld  %10s   %4s   %4d |\n", pTemp->stu.ID, pTemp->stu.name, pTemp->stu.gender, pTemp->stu.age);
		pTemp = pTemp->pNext;
	}
	printf("\t\t -----------------结束-----------------\n");
	system("pause");
}

//根据学号遍历(找到返回目标指针，找不到返回NULL)
struct node* travelByID(struct list* l, long long int _ID)
{
	//判断表是否存在
	if (NULL == l) {
		printf("表不存在！");
		system("pause");
		return;
	}
	//开始遍历
	struct node* pTemp = l->pHead->pNext;
	while (pTemp) {
		if (_ID == pTemp->stu.ID)return pTemp;
		pTemp = pTemp->pNext;
	}
	//遍历完之后都没有的话就返回-1
	return NULL;
}

//根据姓名遍历(找到返回目标指针，找不到返回NULL)
struct node* travelByName(struct list* l, char* _name)
{
	//判断表是否存在
	if (NULL == l) {
		printf("表不存在！");
		system("pause");
		return;
	}
	//开始遍历
	struct node* pTemp = l->pHead->pNext;
	while (pTemp) {
		if (0 == (strcmp(pTemp->stu.name, _name)))return pTemp;
		pTemp = pTemp->pNext;
	}
	//遍历完之后都没有的话就返回-1
	return NULL;
}

//尾删
void pop(struct list* l)
{
	//判断表是否存在
	if (NULL == l) {
		printf("表不存在！");
		system("pause");
		return;
	}
	if (0 == l->pHead->stu.ID) {
		printf("表中已无数据，无法继续删除！\n");
		system("pause");
		return;
	}
	//将尾部要删除的节点记录下来
	struct node* delNode = l->tail;
	//更新尾节点，指向前一个节点
	l->tail = l->tail->pParent;
	//新的尾节点next指针置空
	l->tail->pNext = NULL;
	//释放要删除的节点
	free(delNode);
	//头节点的计数器--
	l->pHead->stu.ID--;
	printf("删除成功!\n");
	system("pause");
}

//根据学号删除学生
void delStuByID(struct list* l, long long int _ID)
{
	//判断表是否存在
	if (NULL == l) {
		printf("表不存在！");
		system("pause");
		return;
	}
	//找到要删除的学号的下标
	struct node* pTemp = travelByID(l, _ID);
	if (NULL == pTemp) {//没找到
		printf("未找到学号为【%lld】的学生！\n", _ID);
		system("pause");
		return;
	}
	else {//找到了
		//先判断是不是最后一个
		if (pTemp == l->tail) {
			//如果是，就去尾删
			pop(l);
			//然后直接结束
			return;
		}
		else {//如果不是，就正常删除
			//待删节点的父节点的next指向待删节点的next（跳过待删节点）
			pTemp->pParent->pNext = pTemp->pNext;
			//待删节点的next节点的父节点指向待删节点的父节点（跳过待删节点）
			pTemp->pNext->pParent = pTemp->pParent;
			//释放
			free(pTemp);
			//链表头节点计数器--
			l->pHead->stu.ID--;
		}
	}
	printf("删除成功!\n");
	system("pause");
}

//根据姓名删除学生
void delStuByName(struct list* l, char* _name)
{
	int select = 0;
	//判断表是否存在
	if (NULL == l) {
		printf("表不存在！");
		system("pause");
		return;
	}
	//判断待删学生是否存在
	if (NULL == travelByName(l, _name)) {//不存在
		printf("未找到姓名为【%s】的学生！\n", _name);
		system("pause");
		return;
	}
	else {//存在
		//准备一个放同名学生的数组
		struct node* sameArr[50] = { 0 };
		//累计共有多少个同名的
		int idx = 0;
		//开始遍历记录
		struct node* pTemp = l->pHead->pNext;
		while (pTemp) {
			if (0 == strcmp(pTemp->stu.name, _name)) {
				sameArr[idx++] = pTemp;
			}
			pTemp = pTemp->pNext;
		}
		//遍历输出数组，让用户选择
		int select = 0;
		printf("以下是名为【%s】的学生：\n", _name);
		printf("\t\t    学     号    姓    名   性别   年龄  \n");
		for (int i = 0; i < idx; i++)
		{
			printf("\t\t %d.%10lld  %10s   %4s   %4d  \n", i + 1, sameArr[i]->stu.ID, sameArr[i]->stu.name, sameArr[i]->stu.gender, sameArr[i]->stu.age);
		}
		printf("\n");
		printf("请选择目标学生信息序号：");
		scanf("%d", &select);
		select--;
		while (select < 0 || select >= idx) {
			printf("输入的范围有误！请重新输入：");
			scanf("%d", &select);
		}
		pTemp = sameArr[select];
		//找到了目标节点
		//先判断是不是最后一个
		if (pTemp == l->tail) {
			//如果是，就去尾删
			pop(l);
			//然后直接结束
			return;
		}
		else {//如果不是，就正常删除
			//待删节点的父节点的next指向待删节点的next（跳过待删节点）
			pTemp->pParent->pNext = pTemp->pNext;
			//待删节点的next节点的父节点指向待删节点的父节点（跳过待删节点）
			pTemp->pNext->pParent = pTemp->pParent;
			//释放
			free(pTemp);
			//链表头节点计数器--
			l->pHead->stu.ID--;
		}
	}
	printf("删除成功!\n");
	system("pause");
}

//根据学号修改学生信息
void modifyByID(struct list* l, long long int ID)
{
	//修改后的信息临时存储
	long long int _ID = -1;
	char _name[11] = "-1";
	char _gender[3] = "-1";
	int _age = -1;
	//用于清空缓冲区
	int c;
	//判断表是否存在
	if (NULL == l) {
		printf("表不存在！");
		system("pause");
		return;
	}
	//找到要修改的学号的下标
	struct node* modNode = travelByID(l, ID);
	if (NULL == modNode) {
		printf("未找到学号为【%lld】的学生！", ID);
		return;
	}
	else {
		printf("当前学号：%lld\n", modNode->stu.ID);
		printf("请输入修改后的学号（输入-1取消修改）：");
		scanf("%lld", &_ID);
		if (-1 == _ID) {
			printf("已取消修改学号！\n");
		}
		else {
			modNode->stu.ID = _ID;
		}
		printf("当前姓名：%s\n", modNode->stu.name);
		printf("请输入修改后的姓名（输入-1取消修改）：");
		scanf("%s", &_name);
		if (0 == (strcmp(_name, "-1"))) {
			printf("已取消修改姓名！\n");
		}
		else {
			strcpy(modNode->stu.name, _name);
		}
		printf("当前性别：%s\n", modNode->stu.gender);
		printf("请输入修改后的姓名（输入-1取消修改）：");
		scanf("%2s", &_gender);
		while ((c = getchar()) != '\n' && c != EOF);
		if (0 == (strcmp(_gender, "-1"))) {
			printf("已取消修改性别！\n");
		}
		else {
			strcpy(modNode->stu.gender, _gender);
		}
		printf("当前年龄：%d\n", modNode->stu.age);
		printf("请输入修改后的年龄（输入-1取消修改）：");
		scanf("%d", &_age);
		if (-1 == _age) {
			printf("已取消修改年龄！\n");
		}
		else {
			modNode->stu.age = _age;
		}
	}
	printf("修改完成!\n");
	system("pause");
}

//根据姓名修改学生信息
void modifyByName(struct list* l, char* name)
{
	//修改后的信息临时存储
	long long int _ID = -1;
	char _name[11] = "-1";
	char _gender[3] = "-1";
	int _age = -1;
	//用于清空缓冲区
	int c;
	//判断表是否存在
	if (NULL == l) {
		printf("表不存在！");
		system("pause");
		return;
	}
	//判断是否存在
	if (NULL == travelByName(l, name)) {//不存在
		printf("未找到姓名为【%s】的学生！", name);
		return;
	}
	else {//存在
		//准备一个放同名学生的数组
		struct node* sameArr[50] = { 0 };
		//累计共有多少个同名的
		int idx = 0;
		//开始遍历记录
		struct node* modNode = l->pHead->pNext;
		while (modNode) {
			if (0 == strcmp(modNode->stu.name, _name)) {
				sameArr[idx++] = modNode;
			}
			modNode = modNode->pNext;
		}
		//遍历输出数组，让用户选择
		int select = 0;
		printf("以下是名为【%s】的学生：\n", _name);
		printf("\t\t    学     号    姓    名   性别   年龄  \n");
		for (int i = 0; i < idx; i++)
		{
			printf("\t\t %d.%10lld  %10s   %4s   %4d  \n", i + 1, sameArr[i]->stu.ID, sameArr[i]->stu.name, sameArr[i]->stu.gender, sameArr[i]->stu.age);
		}
		printf("\n");
		printf("请选择目标学生信息序号：");
		scanf("%d", &select);
		select--;
		while (select < 0 || select >= idx) {
			printf("输入的范围有误！请重新输入：");
			scanf("%d", &select);
		}
		modNode = sameArr[select];
		printf("开始修改：\n");
		printf("当前学号：%lld\n", modNode->stu.ID);
		printf("请输入修改后的学号（输入-1取消修改）：");
		scanf("%lld", &_ID);
		if (-1 == _ID) {
			printf("已取消修改学号！\n");
		}
		else {
			modNode->stu.ID = _ID;
		}
		printf("当前姓名：%s\n", modNode->stu.name);
		printf("请输入修改后的姓名（输入-1取消修改）：");
		scanf("%s", &_name);
		if (0 == (strcmp(_name, "-1"))) {
			printf("已取消修改姓名！\n");
		}
		else {
			strcpy(modNode->stu.name, _name);
		}
		printf("当前性别：%s\n", modNode->stu.gender);
		printf("请输入修改后的姓名（输入-1取消修改）：");
		scanf("%2s", &_gender);
		while ((c = getchar()) != '\n' && c != EOF);
		if (0 == (strcmp(_gender, "-1"))) {
			printf("已取消修改性别！\n");
		}
		else {
			strcpy(modNode->stu.gender, _gender);
		}
		printf("当前年龄：%d\n", modNode->stu.age);
		printf("请输入修改后的年龄（输入-1取消修改）：");
		scanf("%d", &_age);
		if (-1 == _age) {
			printf("已取消修改年龄！\n");
		}
		else {
			modNode->stu.age = _age;
		}
	}
	printf("修改完成!\n");
	system("pause");
}

//文件操作
//退出系统的时候保存到本地文件 stuInfo.txt 中
void saveToFile(struct list* l)
{
	//用写入模式打开stuInfo.txt文件
	FILE* fp = fopen("stuInfo.txt", "w+");//先打开是为了能清空文件里的旧数据
	//判断链表里有没有数据，没有就不用存入文件了
	if (0 == l->pHead->stu.ID) {
		fclose(fp);
		return;
	}
	while (NULL == fp)
	{
		printf("文件打开失败，正在重试...\n");
		fp = fopen("stuInfo.txt", "w+");
	}
	//将表中的数据写入文件
	struct node* pTemp = l->pHead->pNext;
	while (pTemp) {
		fprintf(fp, "%lld %s %s %d\n", pTemp->stu.ID, pTemp->stu.name, pTemp->stu.gender, pTemp->stu.age);
		pTemp = pTemp->pNext;
	}
	//最后记得关闭文件
	fclose(fp);
}

//退出前销毁链表
void destory(struct list* l)
{
	if (NULL == l)return;
	if (0 == l->pHead->stu.ID) {
		//没有有效数据，将头节点和链表的内存释放就行了
		free(l->pHead);
		free(l);
		return;
	}
	//循环遍历释放节点
	struct node* pTemp = l->tail;
	struct node* delNode;//要删除的节点
	while (pTemp) {
		delNode = pTemp;
		pTemp = pTemp->pParent;//从尾往前走
		free(delNode);
		delNode = NULL;//防止指向奇怪的地方
	}
	//释放链表
	free(l);
}
//code by zmq