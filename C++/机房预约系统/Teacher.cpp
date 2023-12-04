#include "Teacher.h"
#include"OrderFile.h"

Teacher::Teacher()
{
}

Teacher::Teacher(int empId, string name, string pwd)
{
	//初始化属性
	this->m_EmpId = empId;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

void Teacher::operMenu()
{
	system("cls");
	cout << "欢迎教师：" << this->m_Name << "登录！" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.查看所有预约          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.审核预约              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.注销登录              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

void Teacher::showAllOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		return;
	}
	for (int i = 0; i < of.m_Size; i++)
	{
		cout << i + 1 << "、 ";

		cout << "预约日期： 周" << of.m_orderData[i]["星期"];
		cout << " 时段：" << (of.m_orderData[i]["时间"] == "1" ? "上午" : "下午");
		cout << " 学号：" << of.m_orderData[i]["申请人学号"];
		cout << " 姓名：" << of.m_orderData[i]["申请人姓名"];
		cout << " 机房：" << of.m_orderData[i]["房间号"];
		string status = " 状态： "; 
		// 0 取消的预约   1 审核中   2 已预约 -1 预约失败
		if (of.m_orderData[i]["预约状态"] == "1")
		{
			status += "审核中";
		}
		else if (of.m_orderData[i]["预约状态"] == "2")
		{
			status += "预约成功";
		}
		else if (of.m_orderData[i]["预约状态"] == "-1")
		{
			status += "审核未通过，预约失败";
		}
		else
		{
			status += "预约已取消";
		}
		cout << status << endl;
	}
	system("pause");
}

void Teacher::validOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		return;
	}
	cout << "待审核的预约记录如下：" << endl;
	//用于记录可操作数据的下标
	vector<int>v;
	int index = 0;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (of.m_orderData[i]["预约状态"] == "1")
		{
			v.push_back(i);
			cout << ++index << "、 ";
			cout << "预约日期： 周" << of.m_orderData[i]["星期"];
			cout << " 时段：" << (of.m_orderData[i]["时间"] == "1" ? "上午" : "下午");
			cout << " 机房：" << of.m_orderData[i]["房间号"];
			string status = " 状态： ";  // 0取消的预约   1 审核中   2 已预约  -1 预约失败
			if (of.m_orderData[i]["预约状态"] == "1")
			{
				status += "审核中";
			}
			cout << status << endl;
		}
	}
	cout << "请输入审核的预约记录,0代表返回" << endl;
	int select = 0;
	int ret = 0;
	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				cout << "请输入审核结果" << endl;
				cout << "1、通过" << endl;
				cout << "2、不通过" << endl;
				cin >> ret;

				if (ret == 1)
				{
					of.m_orderData[v[select - 1]]["预约状态"] = "2";
				}
				else
				{
					of.m_orderData[v[select - 1]]["预约状态"] = "-1";
				}
				of.updateOrder();
				cout << "审核完毕！" << endl;
				break;
			}
		}
		cout << "输入有误，请重新输入" << endl;
	}

	system("pause");
}
