#include<fstream>
#include<algorithm>
#include "Manager.h"
#include"globalFile.h"

Manager::Manager()
{
}

Manager::Manager(string name, string pwd)
{
	this->m_Name = name;
	this->m_Pwd = pwd;
	//初始化容器
	this->initVector();
}

void Manager::operMenu()
{
	system("cls");
	cout << "欢迎管理员：" << this->m_Name << " 登录！" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.添加账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.查看账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.查看机房            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.清空预约            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.注销登录            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "请选择您的操作：";
}

void Manager::addPerson()
{
	//准备进行文件操作
	ofstream ofs;
	//根据选项来决定要传入学生文件还是老师文件
	string fileName;
	//存储要输入的数据
	int id;
	string name;
	string pwd;
	//菜单选项
	int select;
	//控制是否循环展示菜单
	bool show = true;

	while (show) {
		system("cls");
		cout << "\t\t ---------------------------------\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t|          1.添加学生            |\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t|          2.添加老师            |\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t|          0.返    回            |\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t ---------------------------------\n";
		cout << "\t\t请选择您的操作：";
		cin >> select;
		if (1 == select) {
			fileName = STUDENT_FILE;
			cout << "请输入学号：";
			cin >> id;
			if (this->checkRepeat(id, 1)) {//有重复
				cout << "输入的学号已存在！添加失败！"<<endl;
				system("pause");
			}
			else {
				show = false;
			}
		}
		else if (2 == select) {
			fileName = TEACHER_FILE;
			cout << "请输入职工号：";
			cin >> id;
			if (this->checkRepeat(id, 2)) {//有重复
				cout << "输入的职工号已存在！添加失败！" << endl;
				system("pause");
			}
			else {
				show = false;
			}
		}
		else if (0 == select) {
			return;
		}
		else {
			cout << "无此选项！请重新输入！" << endl;
		}
	}
	//知道要打开哪个文件了，就可以打开了（模式：只写|追加写）
	ofs.open(fileName, ios::out | ios::app);
	//接着把都要输入的用户名和密码输入了
	cout << "请输入姓名：";
	cin >> name;
	cout << "请输入密码：";
	cin >> pwd;
	//开始往文件里写
	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "添加成功" << endl;
	//更新容器
	this->initVector();
	system("pause");
	//最后记得关闭文件
	ofs.close();
}

//两个仅在本cpp中使用的函数
void _printStudent(Student& s)
{
	cout << "学号： " << s.m_Id << " 姓名： " << s.m_Name << " 密码：" << s.m_Pwd << endl;
}
void _printTeacher(Teacher& t)
{
	cout << "职工号： " << t.m_EmpId << " 姓名： " << t.m_Name << " 密码：" << t.m_Pwd << endl;
}

void Manager::showPerson()
{
	int select;
	bool show = true;

	
	while (show) {
		system("cls");
		cout << "\t\t ----------请选择查看内容---------\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t|          1.查看所有学生        |\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t|          2.查看所有老师        |\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t|          0.返        回        |\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t ---------------------------------\n";
		cout << "\t\t请选择您的操作：";
		cin >> select;
		if (1 == select) {
			system("cls");
			cout << "所有学生信息如下：" << endl;
			for_each(vStu.begin(), vStu.end(), _printStudent);
			show = false;
		}
		else if (2 == select) {
			system("cls");
			cout << "所有老师信息如下：" << endl;
			for_each(vTea.begin(), vTea.end(), _printTeacher);
			show = false;
		}
		else if (0 == select) {
			return;
		}
		else {
			cout << "输入选项有误！" << endl;
			system("pause");
		}
	}//end of while (show)
	system("pause");
}

void Manager::showComputer()
{
	cout << "机房信息如下： " << endl;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
	{
		cout << "机房编号： " << it->m_ComId << " 机房最大容量： " << it->m_MaxNum << endl;
	}
	system("pause");
}

void Manager::cleanFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();

	cout << "清空成功！" << endl;
	system("pause");
}

void Manager::initVector()
{
	//先清空表，防止上次的数据污染表
	this->vStu.clear();
	this->vTea.clear();
	//临时保存从文件中读取出来的数据
	Student s;
	Teacher t;
	ComputerRoom c;
	//打开学生和教师文件，将账号信息分别放入对应的vector里
	//读学生
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败！" << endl;
		return;
	}
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}
	cout << "当前学生数量为： " << vStu.size() << endl;
	system("pause");
	ifs.close();

	//读教师
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败！" << endl;
		return;
	}
	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}
	cout << "当前教师数量为： " << vTea.size() << endl;
	system("pause");
	ifs.close();

	//读机房
	ifs.open(COMPUTER_FILE, ios::in);
	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
	{
		vCom.push_back(c);
	}
	cout << "当前机房数量为： " << vCom.size() << endl;
	system("pause");
	ifs.close();
}

bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (id == it->m_Id)
			{
				return true;
			}
		}
	}
	else
	{
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (id == it->m_EmpId)
			{
				return true;
			}
		}
	}
	return false;
}
