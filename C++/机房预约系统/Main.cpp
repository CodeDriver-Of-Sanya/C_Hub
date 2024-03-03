#include<iostream>
#include<fstream>
#include<string>
#include"globalFile.h"


using namespace std;

//登录函数
void login(string fileName, int type);
//管理员菜单
void managerMenu(Identity* &manager);
//学生菜单
void studentMenu(Identity*& student);
//教师菜单
void teacherMenu(Identity*& teacher);

int main() {
	//用户选择
	int select = 0;
	while (true)
	{
		system("cls");
		cout << "========================  机房预约系统  ====================="<< endl;
		cout << "\t\t ---------请选择您的身份--------\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          1.学    生           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          2.教    师           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          3.管    理           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          0.退    出           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t -------------------------------\n";
		cout << "输入您的选择: ";
		cin >> select;
		switch (select)
		{
		case 0://退出
			cout << "欢迎下次使用！" << endl;
			exit(0);
			break;
		case 1://学生
			login(STUDENT_FILE, 1);
			break;
		case 2://教师
			login(TEACHER_FILE, 2);
			break;
		case 3://管理员
			login(ADMIN_FILE, 3);
			break;
		default:
			cout << "无此选项！请重新输入！" << endl;
			system("pause");
			break;
		}
	}

	return 0;
}

void login(string fileName, int type)
{
	//可能要输入的数据
	int id = 0;//学号 或 职工号
	string name;//用户名
	string pwd;//密码
	//保存从文件中读取的学号，姓名，密码
	int fId;
	string fName;
	string fPwd;
	//创建一个人基类指针
	Identity* person = NULL;

	//打开对应文件
	ifstream ifs;
	ifs.open(fileName, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		system("pause");
		ifs.close();
		return;
	}

	//通过type判断id输入的是 学号 还是 职工号 还是 不输入（管理员登录）
	if (1 == type)	//学生登录
	{
		cout << "请输入你的学号：";
		cin >> id;
	}
	else if (2 == type) //教师登录
	{
		cout << "请输入你的职工号：";
		cin >> id;
	}
	//不管谁登录都要输入 用户名 和 密码
	cout << "请输入用户名：";
	cin >> name;
	cout << "请输入密码：";
	cin >> pwd;

	//输入完后进行对应的登录验证
	if (type == 1)
	{
		//学生登录验证
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			//cout << fId << " " << fName << " " << fPwd << endl;
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "学生验证登录成功!" << endl;
				system("pause");
				//学生登陆，所以给new一个学生类，将登录人的信息放进去
				person = new Student(id, name, pwd);
				studentMenu(person);
				return;
			}
		}
	}
	else if (type == 2)
	{
		//教师登录验证
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "教师验证登录成功!" << endl;
				system("pause");
				person = new Teacher(id, name, pwd);
				teacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		//管理员登录验证
		while (ifs >> fName && ifs >> fPwd) {
			if (name == fName && pwd == fPwd)
			{
				cout << "管理员验证登录成功!" << endl;
				system("pause");
				person = new Manager(name, pwd);
				managerMenu(person);
				return;
			}
		}
	}
	//出来说明登录验证失败了
	cout << "验证登录失败!" << endl;
	system("pause");

	//记得关闭文件
	ifs.close();
	return;
}

void managerMenu(Identity*& manager)
{
	//因为manager是Identity类，Manager类的功能函数没有，所以需要转成Manager类
	Manager* mg = (Manager*)manager;
	//用户输入的选项
	int select;
	//控制循环的
	bool show = true;

	while (show)
	{
		//调用管理类的菜单
		mg->operMenu();
		//开始选择
		cin >> select;
		switch (select)
		{
		case 0:
			delete mg;
			cout << "注销成功" << endl;
			system("pause");
			show = false;
			break;
		case 1:
			mg->addPerson();//添加账号
			break;
		case 2:
			mg->showPerson();//查看账号
			break;
		case 3:
			mg->showComputer();//查看机房
			break;
		case 4:
			mg->cleanFile();//清空预约
			break;
		default:
			cout << "无此选项！请重新输入！" << endl;
			system("pause");
			break;
		}

	}
}

void studentMenu(Identity*& student)
{
	Student* stu = (Student*)student;
	//用户输入的选项
	int select;
	//控制循环的
	bool show = true;

	while (show)
	{
		//调用管理类的菜单
		stu->operMenu();
		//开始选择
		cin >> select;
		switch (select)
		{
		case 0:
			delete stu;
			cout << "注销成功" << endl;
			system("pause");
			show = false;
			break;
		case 1:
			stu->applyOrder();//申请预约
			break;
		case 2:
			stu->showMyOrder();//查看我的预约
			break;
		case 3:
			stu->showAllOrder();//查看所有预约
			break;
		case 4:
			stu->cancelOrder();//取消预约
			break;
		default:
			cout << "无此选项！请重新输入！" << endl;
			system("pause");
			break;
		}
	}
}

//教师菜单
void teacherMenu(Identity*& teacher)
{
	Teacher* t = (Teacher*)teacher;
	while (true)
	{
		//教师菜单
		t->operMenu();

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			//查看所有预约
			t->showAllOrder();
		}
		else if (select == 2)
		{
			//审核预约
			t->validOrder();
		}
		else
		{
			delete t;
			cout << "注销成功" << endl;
			system("pause");
			return;
		}

	}
}