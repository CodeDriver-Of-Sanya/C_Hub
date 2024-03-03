#include <stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<stdbool.h>

/*
学生管理系统：
包括学号，姓名，性别，年龄,学分
主要功能：
增加学生
	尾插
	插入指定学号后面
	插入指定姓名后面
	需要输入学生的学号，姓名，性别，年龄，学分
		学号必须输入并且不能有重复
		其他的不输入就给默认值
	每次插入完一个学生就进行一次全排序
删除学生
	尾删
	根据学号删除学生
	根据姓名删除学生
修改学生
	根据学号修改学生信息
	根据姓名修改学生信息
查询学生
	根据学号查询学生信息
	根据姓名查询学生信息
		如有相同姓名则一并展示出来
文件存储到本地 stuInfo.txt 中
*/

//创建学生结构
struct student
{
	long long int ID;		//学号
	char name[11];			//姓名
	char gender[3];			//性别
	int age;				//年龄
	double credit;			//学分
};

//创建存学生的顺序表
struct stuSqList {
	struct student* parr;
	int curSize;			//数组中当前已经存储的学生信息数量
	int maxSize;			//数组的总大小
};

//创建学生顺序表函数
struct stuSqList* createSqList();

//初始化顺序表函数
void initSqList(struct stuSqList* l);

//创建学生类型
struct student createStu(long long int ID, char* name, char* gender, int age, double credit);

//学生添加菜单
void stuInsertMenu(struct stuSqList* list);

//学生删除菜单
void stuDelMenu(struct stuSqList* list);

//学生修改菜单
void stuModifyMenu(struct stuSqList* list);

//学生查询菜单
void stuSearchMenu(struct stuSqList* list);

//尾插
void push(struct stuSqList* l, struct student s);

//根据学号中间插
void midInsertByID(struct stuSqList* l, struct student s, long long int ID);

//根据姓名中间插（如果有重名默认插在第一个的后面）
void midInsertByName(struct stuSqList* l, struct student s, char* name);

//遍历
void travel(struct stuSqList* list);

//根据学号遍历(返回下标)
int travelByID(struct stuSqList* l, long long int ID);

//根据姓名遍历（返回下标）
int travelByName(struct stuSqList* l,char* name);

//尾删
void pop(struct stuSqList* l);

//根据学号删除学生
void delStuByID(struct stuSqList* l, long long int ID);

//根据姓名删除学生
void delStuByName(struct stuSqList* l, char* name);

//根据学号修改学生信息
void modifyByID(struct stuSqList* l, long long int ID);

//根据姓名修改学生信息
void modifyByName(struct stuSqList* l, char* name);

//根据学分进行升序排序
void sort(struct stuSqList* l);

//文件操作
//退出系统的时候保存到本地文件 stuInfo.txt 中
void saveToFile(struct stuSqList* l);

//退出前销毁顺序表
void destory(struct stuSqList* l);

int main() {
	//创建顺序表
	struct stuSqList* list = createSqList();
	//初始化顺序表
	initSqList(list);
	//菜单选择
	int select;
	while (true)
	{
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
			saveToFile(list);
			//再销毁顺序表
			destory(list);
			//最后退出
			exit(0);
			break;
		case 1:
			stuInsertMenu(list);
			break;
		case 2:
			stuDelMenu(list);
			break;
		case 3:
			stuModifyMenu(list);
			break;
		case 4:
			stuSearchMenu(list);
			break;
		case 5:
			travel(list);
			break;
		default:
			printf("输入选项有误，请重新输入！");
			system("pause");
			system("cls");
			break;
		}
	}
	return 0;
}

//创建学生顺序表函数
struct stuSqList* createSqList(){
	struct stuSqList* pNew = malloc(sizeof(struct stuSqList));
	while (NULL == pNew) {
		pNew = malloc(sizeof(struct stuSqList));
	}
	return pNew;
}

//初始化顺序表函数
void initSqList(struct stuSqList* l) {
	l->parr = malloc(1 * sizeof(struct student));
	l->curSize = 0;
	l->maxSize = 1;
	//文件操作，将本地文件 stuInfo.txt 里的学生信息填入顺序表
	FILE* fp = fopen("stuInfo.txt", "r+");
	while (NULL == fp)
	{
		printf("文件打开失败，正在重试...\n");
		fp = fopen("stuInfo.txt", "r+");
	}
	struct student s;
	while (EOF != fscanf(fp, "%lld %s %s %d %lf", &s.ID, s.name, s.gender, &s.age, &s.credit))
	{
		push(l, s);
	}
	//关闭文件
	fclose(fp);
}

//创建学生类型
struct student createStu(long long int ID, char* name, char* gender, int age, double credit)
{
	struct student s;
	s.ID = ID;
	strcpy(s.name, name);
	strcpy(s.gender, gender);
	s.age = age;
	s.credit = credit;
	//返回出去
	return s;
}

//学生插入菜单
void stuInsertMenu(struct stuSqList* list)
{
	//要添加的学生信息
	long long int _ID;
	int _age;
	char _name[11];
	char _gender[3];
	double _credit;
	//判断学号是否存在
	int isExit;
	//某学号
	long long int selectID;
	//某姓名
	char selectName[11];
	//要添加的学生
	struct student s;
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
			getchar();
			//判断要插入的学号有没有重复
			isExit = travelByID(list, _ID);
			while (-1 != isExit) {
				//有重复，重新输入
				printf("输入的学号已存在，请重新输入：");
				scanf("%lld", &_ID);
				getchar();
				isExit = travelByID(list, _ID);
			}
			printf("请输入添加学生的姓名：");
			scanf("%s", _name);
			getchar();
			printf("请输入添加学生的性别：");
			scanf("%s", _gender);
			printf("请输入添加学生的年龄：");
			scanf("%d", &_age);
			printf("请输入添加学生的学分：");
			scanf("%lf", &_credit);
			//printf("\t\t -------------------------------\n");
			//system("pause");
			//printf("%lld %s %s %d\n", _ID, _name, _gender, _age);
			//system("pause");
			s = createStu(_ID, _name, _gender, _age,_credit);
			push(list, s);
			printf("添加成功!\n");
			system("pause");
			break;
		case 2:
			printf("请输入添加学生的学号：");
			scanf("%lld", &_ID);
			getchar();
			//判断要插入的学号有没有重复
			isExit = travelByID(list, _ID);
			while (-1 != isExit) {
				//有重复，重新输入
				printf("输入的学号已存在，请重新输入：");
				scanf("%lld", &_ID);
				getchar();
				isExit = travelByID(list, _ID);
			}
			printf("请输入添加学生的姓名：");
			scanf("%s", _name);
			getchar();
			printf("请输入添加学生的性别：");
			scanf("%s", _gender);
			printf("请输入添加学生的年龄：");
			scanf("%d", &_age);
			printf("请输入某学号：");
			scanf("%lld", &selectID);
			printf("请输入添加学生的学分：");
			scanf("%lf", &_credit);

			//printf("\t\t -------------------------------\n");
			//system("pause");
			//printf("%lld %s %s %d\n", _ID, _name, _gender, _age);
			//system("pause");
			s = createStu(_ID, _name, _gender, _age,_credit);
			midInsertByID(list, s, selectID);
			break;
		case 3:
			printf("请输入添加学生的学号：");
			scanf("%lld", &_ID);
			getchar();
			//判断要插入的学号有没有重复
			isExit = travelByID(list, _ID);
			while (-1 != isExit) {
				//有重复，重新输入
				printf("输入的学号已存在，请重新输入：");
				scanf("%lld", &_ID);
				getchar();
				isExit = travelByID(list, _ID);
			}
			printf("请输入添加学生的姓名：");
			scanf("%s", _name);
			getchar();
			printf("请输入添加学生的性别：");
			scanf("%s", _gender);
			printf("请输入添加学生的年龄：");
			scanf("%d", &_age);
			printf("请输入某学生的姓名：");
			scanf("%s", selectName);
			printf("请输入添加学生的学分：");
			scanf("%lf", &_credit);
			s = createStu(_ID, _name, _gender, _age,_credit);
			midInsertByName(list, s, selectName);
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
void stuDelMenu(struct stuSqList* list)
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
			pop(list);
			break;
		case 2:
			printf("请输入要删除的学生学号：");
			scanf("%lld", &selectID);
			delStuByID(list, selectID);
			break;
		case 3:
			printf("请输入要删除的学生姓名：");
			scanf("%s", selectName);
			delStuByName(list, selectName);
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
void stuModifyMenu(struct stuSqList* list)
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
			modifyByID(list, selectID);
			break;
		case 2:
			printf("请输入要修改信息的学生姓名：");
			scanf("%s", selectName);
			modifyByName(list, selectName);
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
void stuSearchMenu(struct stuSqList* list)
{
	//要查询的学号
	long long int selectID;
	//要查询的姓名
	char selectName[11];
	//查询学生姓名可能遇见重复,用数组记录下标
	int nameIdx[100] = { 0 };

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
			printf("请输入要查询信息的学生学号：");
			scanf("%lld", &selectID);
			int idx = travelByID(list, selectID);
			while (-1 == idx) {
				printf("输入的学号不存在，请重新输入（输入-2结束）：");
				scanf("%lld", &selectID);
				if (-2 == selectID) {
					break;
				}
				idx = travelByID(list, selectID);
			}
			if (idx >= 0) {
				printf("以下是学生学号为【%s】的学生：\n", selectID);
				printf("%lld %s %s %d\n",list->parr[idx].ID, list->parr[idx].name, list->parr[idx].gender, list->parr[idx].age);
			}
			system("pause");

			break;
		case 2:
			printf("请输入要查询信息的学生姓名：");
			scanf("%s", selectName);
			//需要将所有同名的都要显示出来，遍历单独写
			//判断表是否存在
			if (NULL == list) {
				printf("表不存在！");
				system("pause");
				return;
			}
			//控制重名数组中的下标移动
			int index = 0;
			//开始遍历
			for (int i = 0; i < list->curSize; i++)
			{
				if (0 == (strcmp(list->parr[i].name, selectName))) {
					nameIdx[index++] = i;
				}
			}
			//遍历完成，开始输出
			printf("以下是学生姓名为【%s】的学生：\n", selectName);
			for (int i = 0; i < index; i++) {
				printf("%lld %s %s %d\n", list->parr[i].ID, list->parr[i].name, list->parr[i].gender, list->parr[i].age);
			}
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
void push(struct stuSqList* l, struct student s)
{
	//printf("%lld %s %s %d\n", s.ID, s.name,s.gender, s.age);
	//判断表是否存在
	if (NULL == l) {
		printf("表不存在！");
		system("pause");
		return;
	}
	//判断表是否存满了
	if (l->curSize >= l->maxSize) {
		//存满了就重新开辟内存
		int maxSizeTemp = (l->maxSize / 2 > 1 ? l->maxSize / 2 : 1) + l->maxSize;
		//申请新内存
		struct student* pNew = malloc(maxSizeTemp * sizeof(struct student));
		while (NULL == pNew) {
			pNew = malloc(maxSizeTemp * sizeof(struct student));
		}
		//将老内存数据存到新内存
		memcpy(pNew, l->parr, l->curSize * sizeof(struct student));
		//释放老内存
		free(l->parr);
		//指向新内存
		l->parr = pNew;
		//更新最大容量
		l->maxSize = maxSizeTemp;
	}
	//没满直接存
	l->parr[l->curSize].ID = s.ID;
	strcpy(l->parr[l->curSize].name, s.name);
	strcpy(l->parr[l->curSize].gender, s.gender);
	l->parr[l->curSize].age = s.age;
	l->parr[l->curSize].credit = s.credit;
	l->curSize++;
	sort(l);//排序
}

//根据学号中间插
void midInsertByID(struct stuSqList* l, struct student s, long long int ID)
{
	//判断表是否存在
	if (NULL == l) {
		printf("表不存在！");
		system("pause");
		return;
	}
	//遍历找到目标学号的下标
	int distIdx = travelByID(l, ID);
	if (-1 == distIdx) {
		printf("未找到目标学号，插入失败！\n");
		system("pause");
		return;
	}
	//判断表是否存满了
	if (l->curSize >= l->maxSize) {
		//存满了就重新开辟内存
		int maxSizeTemp = (l->maxSize / 2 > 1 ? l->maxSize / 2 : 1) + l->maxSize;
		//申请新内存
		struct student* pNew = malloc(maxSizeTemp * sizeof(struct student));
		while (NULL == pNew) {
			pNew = malloc(maxSizeTemp * sizeof(struct student));
		}
		//将老内存数据存到新内存
		memcpy(pNew, l->parr, l->curSize * sizeof(struct student));
		//释放老内存
		free(l->parr);
		//指向新内存
		l->parr = pNew;
		//更新最大容量
		l->maxSize = maxSizeTemp;
	}
	//如果刚好是插入到倒数第一个就直接写上
	if (distIdx == l->curSize-1) {
		l->parr[l->curSize].ID = s.ID;
		strcpy(l->parr[l->curSize].name, s.name);
		strcpy(l->parr[l->curSize].gender, s.gender);
		l->parr[l->curSize].age = s.age;
		l->curSize++;
		printf("添加成功!\n");
		system("pause");
		return;
	}
	//正常情况的插入
	for (int i = l->curSize - 1; i > distIdx; i--)
	{
		l->parr[i + 1] = l->parr[i];
	}
	l->parr[distIdx + 1].ID = s.ID;
	strcpy(l->parr[distIdx + 1].name, s.name);
	strcpy(l->parr[distIdx + 1].gender, s.gender);
	l->parr[distIdx + 1].age = s.age;
	l->curSize++;
	printf("添加成功!\n");
	system("pause");
	return;
}

//根据姓名中间插
void midInsertByName(struct stuSqList* l, struct student s, char* name)
{
	//判断表是否存在
	if (NULL == l) {
		printf("表不存在！");
		system("pause");
		return;
	}
	//遍历找到目标姓名的下标
	int distIdx = travelByName(l, name);
	if (-1 == distIdx) {
		printf("未找到目标姓名，插入失败！\n");
		system("pause");
		return;
	}
	//判断表是否存满了
	if (l->curSize >= l->maxSize) {
		//存满了就重新开辟内存
		int maxSizeTemp = (l->maxSize / 2 > 1 ? l->maxSize / 2 : 1) + l->maxSize;
		//申请新内存
		struct student* pNew = malloc(maxSizeTemp * sizeof(struct student));
		while (NULL == pNew) {
			pNew = malloc(maxSizeTemp * sizeof(struct student));
		}
		//将老内存数据存到新内存
		memcpy(pNew, l->parr, l->curSize * sizeof(struct student));
		//释放老内存
		free(l->parr);
		//指向新内存
		l->parr = pNew;
		//更新最大容量
		l->maxSize = maxSizeTemp;
	}
	//如果刚好是插入到倒数第一个就直接写上
	if (distIdx == l->curSize - 1) {
		l->parr[l->curSize].ID = s.ID;
		strcpy(l->parr[l->curSize].name, s.name);
		strcpy(l->parr[l->curSize].gender, s.gender);
		l->parr[l->curSize].age = s.age;
		l->curSize++;
		printf("添加成功!\n");
		system("pause");
		return;
	}
	//正常情况的插入
	for (int i = l->curSize - 1; i > distIdx; i--)
	{
		l->parr[i + 1] = l->parr[i];
	}
	l->parr[distIdx + 1].ID = s.ID;
	strcpy(l->parr[distIdx + 1].name, s.name);
	strcpy(l->parr[distIdx + 1].gender, s.gender);
	l->parr[distIdx + 1].age = s.age;
	l->curSize++;
	printf("添加成功!\n");
	system("pause");
	return;
}

//遍历
void travel(struct stuSqList* list)
{
	system("cls");
	printf("\t\t ---------------全部学生信息-----------------\n");
	printf("\t\t| 学      号    姓    名   性别   年龄  学分 |\n");
	for (int i = 0; i < list->curSize; i++)
	{
		printf("\t\t| %10lld  %10s   %4s   %4d  %.1lf  |\n", list->parr[i].ID, list->parr[i].name, list->parr[i].gender, list->parr[i].age, list->parr[i].credit);
	}
	printf("\t\t -------------------结束--------------------\n");
	system("pause");
}

//根据学号遍历(返回下标)
int travelByID(struct stuSqList* l, long long int ID)
{
	//判断表是否存在
	if (NULL == l) {
		printf("表不存在！");
		system("pause");
		return;
	}
	//开始遍历
	for (int i = 0; i < l->curSize; i++)
	{
		if (ID == l->parr[i].ID)return i;
	}
	//遍历完之后都没有的话就返回-1
	return -1;
}

//根据姓名遍历（返回下标）
int travelByName(struct stuSqList* l,char* name)
{
	//判断表是否存在
	if (NULL == l) {
		printf("表不存在！");
		system("pause");
		return;
	}
	//开始遍历
	for (int i = 0; i < l->curSize; i++)
	{
		if (0 == (strcmp(l->parr[i].name,name)))return i;
	}
	//遍历完之后都没有的话就返回-1
	return -1;
}

//尾删
void pop(struct stuSqList* l)
{
	//判断表是否存在
	if (NULL == l) {
		printf("表不存在！");
		system("pause");
		return;
	}
	if (0 == l->curSize) {
		printf("表中已无数据，无法继续删除！\n");
		system("pause");
		return;
	}
	l->curSize--;
	printf("删除成功!\n");
	system("pause");
}

//根据学号删除学生
void delStuByID(struct stuSqList* l,long long int ID)
{
	//判断表是否存在
	if (NULL == l) {
		printf("表不存在！");
		system("pause");
		return;
	}
	//找到要删除的学号的下标
	int delIdx = travelByID(l, ID);
	if (-1 == delIdx) {
		printf("未找到学号为【%lld】的学生！\n", ID);
		system("pause");
		return;
	}
	//删除
	for (int i = delIdx; i < l->curSize-1; i++)
	{
		l->parr[i] = l->parr[i + 1];
	}
	l->curSize--;
	printf("删除成功!\n");
	system("pause");
}

//根据姓名删除学生
void delStuByName(struct stuSqList* l, char* name)
{
	int nameArr[100] = { 0 };
	int select;
	//判断表是否存在
	if (NULL == l) {
		printf("表不存在！");
		system("pause");
		return;
	}
	//找到要删除的姓名的下标
	int delIdx = travelByName(l, name);
	if (-1 == delIdx) {
		printf("未找到姓名为【%s】的学生！\n", name);
		system("pause");
		return;
	}
	int idx = 0;
	//开始遍历查找
	for (int i = 0; i < l->curSize; i++)
	{
		if (0 == (strcmp(l->parr[i].name, name))) {
			nameArr[idx++] = i;
		}
	}
	//开始遍历输出
	printf("根据姓名【%s】找到以下学生：\n", name);
	for (int i = 0; i < idx; i++)
	{
		printf("%d. %lld %s %s %d\n", i+1,l->parr[nameArr[i]].ID, l->parr[nameArr[i]].name, l->parr[nameArr[i]].gender, l->parr[nameArr[i]].age);
	}
	printf("请选择你要删除的学生（输入-1取消删除）：");
	scanf("%d", &select);
	if (-1 == select)return;
	select--;
	while (select<0 || select>idx - 1) {
		printf("选项不存在！请重新输入！\n");
		printf("请选择你要删除的学生：");
		scanf("%d", &select);
	}
	//删除
	for (int i = nameArr[select]; i < l->curSize - 1; i++)
	{
		l->parr[i] = l->parr[i + 1];
	}
	l->curSize--;
	printf("删除成功!\n");
	system("pause");
}

//根据学号修改学生信息
void modifyByID(struct stuSqList* l, long long int ID)
{
	//判断表是否存在
	if (NULL == l) {
		printf("表不存在！");
		system("pause");
		return;
	}
	//找到要修改的学号的下标
	int modIdx = travelByID(l, ID);
	if (-1 == modIdx) {
		printf("未找到学号为【%lld】的学生！", ID);
		return;
	}
	long long int _ID = -1;
	char _name[11] = "-1";
	char _gender[3] = "-1";
	int _age = -1;
	printf("当前学号：%lld\n", l->parr[modIdx].ID);
	printf("请输入修改后的学号（输入-1取消修改）：");
	scanf("%lld", &_ID);
	if (-1 == _ID) {
		printf("已取消修改学号！\n");
	}
	else {
		l->parr[modIdx].ID = _ID;
	}
	printf("当前姓名：%s\n", l->parr[modIdx].name);
	printf("请输入修改后的姓名（输入-1取消修改）：");
	scanf("%s", &_name);
	if (0==(strcmp(_name,"-1"))) {
		printf("已取消修改姓名！\n");
	}
	else {
		strcpy(l->parr[modIdx].name, _name);
	}
	printf("当前性别：%s\n", l->parr[modIdx].gender);
	printf("请输入修改后的姓名（输入-1取消修改）：");
	scanf("%s", &_gender);
	if (0 == (strcmp(_gender, "-1"))) {
		printf("已取消修改性别！\n");
	}
	else {
		strcpy(l->parr[modIdx].gender, _gender);
	}
	printf("当前年龄：%d\n", l->parr[modIdx].age);
	printf("请输入修改后的年龄（输入-1取消修改）：");
	scanf("%d", &_age);
	if (-1 == _age) {
		printf("已取消修改年龄！\n");
	}
	else {
		l->parr[modIdx].age = _age;
	}
	printf("修改完成!\n");
	system("pause");
}

//根据姓名修改学生信息
void modifyByName(struct stuSqList* l, char* name)
{
	//判断表是否存在
	if (NULL == l) {
		printf("表不存在！");
		system("pause");
		return;
	}
	//找到要修改的学号的下标
	int modIdx = travelByName(l, name);
	if (-1 == modIdx) {
		printf("未找到姓名为【%s】的学生！", name);
		return;
	}
	long long int _ID = -1;
	char _name[11] = "-1";
	char _gender[3] = "-1";
	int _age = -1;
	printf("当前学号：%lld\n", l->parr[modIdx].ID);
	printf("请输入修改后的学号（输入-1取消修改）：");
	scanf("%lld", &_ID);
	if (-1 == _ID) {
		printf("已取消修改学号！\n");
	}
	else {
		l->parr[modIdx].ID = _ID;
	}
	printf("当前姓名：%s\n", l->parr[modIdx].name);
	printf("请输入修改后的姓名（输入-1取消修改）：");
	scanf("%s", &_name);
	if (0 == (strcmp(_name, "-1"))) {
		printf("已取消修改姓名！\n");
	}
	else {
		strcpy(l->parr[modIdx].name, _name);
	}
	printf("当前性别：%s\n", l->parr[modIdx].gender);
	printf("请输入修改后的姓名（输入-1取消修改）：");
	scanf("%s", &_gender);
	if (0 == (strcmp(_gender, "-1"))) {
		printf("已取消修改性别！\n");
	}
	else {
		strcpy(l->parr[modIdx].gender, _gender);
	}
	printf("当前年龄：%d\n", l->parr[modIdx].age);
	printf("请输入修改后的年龄（输入-1取消修改）：");
	scanf("%d", &_age);
	if (-1 == _age) {
		printf("已取消修改年龄！\n");
	}
	else {
		l->parr[modIdx].age = _age;
	}
	printf("修改完成!\n");
	system("pause");
}

//进行升序排序
void sort(struct stuSqList* l)
{
	struct student temp = { 0 };
	for (int i = 0; i < l->curSize-1; i++)
	{
		for (int j = 0; j < l->curSize - i - 1; j++)
		{
			double one = l->parr[j].credit;
			double two = l->parr[j + 1].credit;
			if (one > two)
			{
				memcpy(&temp, &(l->parr[j + 1]), sizeof(struct student));
				memcpy(&(l->parr[j + 1]), &(l->parr[j]), sizeof(struct student));
				memcpy(&(l->parr[j]), &temp, sizeof(struct student));
			}
		}
	}
}

//文件操作
//退出系统的时候保存到本地文件 stuInfo.txt 中
void saveToFile(struct stuSqList* l)
{
	//用写入模式打开stuInfo.txt文件
	FILE* fp = fopen("stuInfo.txt", "w+");
	while (NULL == fp)
	{
		printf("文件打开失败，正在重试...\n");
		fp = fopen("stuInfo.txt", "w+");
	}
	//将表中的数据写入文件
	for (int i = 0; i < l->curSize; i++)
	{
		fprintf(fp, "%lld %s %s %d %lf\n", l->parr[i].ID, l->parr[i].name, l->parr[i].gender, l->parr[i].age, l->parr[i].credit);
	}
	//最后记得关闭文件
	fclose(fp);
}

//退出前销毁顺序表
void destory(struct stuSqList* l)
{
	//没有表了就不用销毁了
	if (NULL == l)return;
	if (NULL == l->parr)return;
	free(l->parr);
	free(l);
}
