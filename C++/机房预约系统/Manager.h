#pragma once
#include<iostream>
#include<vector>
#include"Identity.h"
#include"Manager.h"
#include"Student.h"
#include"Teacher.h"
#include"ComputerRooom.h"

using namespace std;

class Manager:public Identity
{
public:
	//无参构造
	Manager();

	//有参构造（管理员姓名，密码）
	Manager(string name, string pwd);

	//选择菜单
	virtual void operMenu();

	//添加账号  
	void addPerson();

	//查看账号
	void showPerson();

	//查看机房信息
	void showComputer();

	//清空预约记录
	void cleanFile();

	//初始化容器（下面这两个容器是为了实现添加账号时的去重操作）
	void initVector();

	//检测重复(id，学生=1或老师=其他;返回true 代表有重复，false代表没有重复)
	bool checkRepeat(int id, int type);

	//学生容器
	vector<Student> vStu;

	//教师容器
	vector<Teacher> vTea;

	//机房容器
	vector<ComputerRoom> vCom;

};

