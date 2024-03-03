#include "Student.h"
#include<fstream>
#include<algorithm>
#include<vector>
#include<string>
#include"globalFile.h"
#include"ComputerRooom.h"
#include"OrderFile.h"

using namespace std;

Student::Student()
{
}

Student::Student(int id, string name, string pwd)
{
	//初始化属性
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;
	//获取机房信息
	ifstream ifs;
	ComputerRoom c;

	ifs.open(COMPUTER_FILE, ios::in);
	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
	{
		vCom.push_back(c);
	}

	ifs.close();
}

void Student::operMenu()
{
	system("cls");
	cout << "~~欢迎学生：" << this->m_Name << " 登录！" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.申请预约              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.查看我的预约          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          3.查看所有预约          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          4.取消预约              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.注销登录              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请选择您的操作：" << endl;
}

void Student::applyOrder()
{
	//可能用到的数据
	int week, day, room;

	cout << "机房开放时间为周一至周五！" << endl;
	cout << "请输入申请预约的时间：" << endl;
	cout << "1、周一" << endl;
	cout << "2、周二" << endl;
	cout << "3、周三" << endl;
	cout << "4、周四" << endl;
	cout << "5、周五" << endl;
	while (true)
	{
		cin >> week;
		if (week >= 1 && week <= 5)break;
		cout << "输入有误，请重新输入" << endl;
	}

	cout << "请输入申请预约的时间段：" << endl;
	cout << "1、上午" << endl;
	cout << "2、下午" << endl;
	while (true)
	{
		cin >> day;
		if (day >= 1 && day <= 2)break;
		cout << "输入有误，请重新输入" << endl;
	}

	cout << "请选择机房：" << endl;
	int i = 1;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++,i++) {
		cout << "[" << i << "]" << " " << "机房名称：" << (*it).m_ComId << " " << "容量：" << (*it).m_MaxNum << endl;
	}
	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= vCom.size())break;
		cout << "输入有误，请重新输入" << endl;
	}

	cout << "预约成功！审核中" << endl;

	//开始写入文件
	ofstream ofs(ORDER_FILE, ios::app);
	ofs << "星期:" << week << " ";
	ofs << "时间:" << day << " ";
	ofs << "申请人学号:" << this->m_Id << " ";
	ofs << "申请人姓名:" << this->m_Name << " ";
	ofs << "房间号:" << vCom[room-1].m_ComId << " ";
	ofs << "预约状态:" << 1 << endl;
	ofs.close();

	system("pause");
}

void Student::showMyOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录！" << endl;
		system("pause");
		return;
	}
	//开始遍历输出
	for (int i = 0; i < of.m_Size; i++)
	{
		//atoi()函数将数字格式的字符串转换为整数类型。例如，将字符串“12345”转换成数字12345
		//c_str()函数是C++中 string 类中的函数，其头文件为：#include <string>
		//它是将C++的 string 转化为C的字符串数组，即 string 与 const char* 之间的转换
		if (atoi(of.m_orderData[i]["申请人学号"].c_str()) == this->m_Id)
		{
			cout << "预约日期： 周" << of.m_orderData[i]["星期"];
			cout << " 时段：" << (of.m_orderData[i]["时间"] == "1" ? "上午" : "下午");
			cout << " 机房：" << of.m_orderData[i]["房间号"];
			string status = " 状态："; 
			// 0 取消的预约   1 审核中   2 已预约 -1 预约失败
			if (of.m_orderData[i]["预约状态"] == "1")
			{
				status += "审核中";
			}
			else if (of.m_orderData[i]["预约状态"] == "2")
			{
				status += "成功";
			}
			else if (of.m_orderData[i]["预约状态"] == "-1")
			{
				status += "失败，审核未通过";
			}
			else
			{
				status += "已取消";
			}
			cout << status << endl;
		}
	}//end of for (int i = 0; i < of.m_Size; i++)
	system("pause");
}

void Student::showAllOrder()
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
		string status = " 状态：";
		// 0 取消的预约   1 审核中   2 已预约 -1 预约失败
		if (of.m_orderData[i]["预约状态"] == "1")
		{
			status += "审核中";
		}
		else if (of.m_orderData[i]["预约状态"] == "2")
		{
			status += "成功";
		}
		else if (of.m_orderData[i]["预约状态"] == "-1")
		{
			status += "失败，审核未通过";
		}
		else
		{
			status += "已取消";
		}
		cout << status << endl;
	}
	system("pause");
}

void Student::cancelOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		return;
	}
	cout << "审核中或预约成功的记录可以取消，请输入取消的记录" << endl;
	//用于存储审核中和成功的数据下标
	vector<int> idx;
	//用于输出到屏幕的可取消的申请的序号
	int index = 0;
	for (int i = 0; i < of.m_Size; i++) {
		if (atoi(of.m_orderData[i]["申请人学号"].c_str()) == this->m_Id) {
			if (of.m_orderData[i]["预约状态"] == "1" || of.m_orderData[i]["预约状态"] == "2") {
				//把这个符合要求的数据的下标存入idx容器
				idx.push_back(i);
				cout << ++index << "、 ";
				cout << "预约日期： 周" << of.m_orderData[i]["星期"];
				cout << " 时段：" << (of.m_orderData[i]["时间"] == "1" ? "上午" : "下午");
				cout << " 机房：" << of.m_orderData[i]["房间号"];
				string status = " 状态： "; 
				// 0 取消的预约   1 审核中   2 已预约  -1 预约失败
				if (of.m_orderData[i]["预约状态"] == "1")
				{
					status += "审核中";
				}
				else if (of.m_orderData[i]["预约状态"] == "2")
				{
					status += "预约成功";
				}
				cout << status << endl;
			}
		}
	}
	cout << "请输入取消的记录,0代表返回" << endl;
	int select = 0;
	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= idx.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				//	cout << "记录所在位置： " << v[select - 1] << endl;
				of.m_orderData[idx[select - 1]]["预约状态"] = "0";
				of.updateOrder();
				cout << "已取消预约" << endl;
				break;
			}

		}
		cout << "输入有误，请重新输入" << endl;
	}
	system("pause");
}
