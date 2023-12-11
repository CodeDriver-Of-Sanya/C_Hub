#include "OrderFile.h"
#include<fstream>

OrderFile::OrderFile()
{
	//打开预约文件
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);

	string week;		//周几
	string day;			//时间
	string stuId;		//申请人学号
	string stuName;		//申请人姓名
	string roomId;		//机房名称
	string status;		//预约状态
	this->m_Size = 0;	//统计预约记录个数

	while (ifs >> week && ifs >> day && ifs >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status)
	{
		//片段切割时临时存放的变量
		string key;
		string value;
		map<string, string> m;
		//切割
		int pos = week.find(":");
		if (pos != -1)
		{
			key = week.substr(0, pos);
			value = week.substr(pos + 1, week.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = day.find(":");
		if (pos != -1)
		{
			key = day.substr(0, pos);
			value = day.substr(pos + 1, day.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = stuId.find(":");
		if (pos != -1)
		{
			key = stuId.substr(0, pos);
			value = stuId.substr(pos + 1, stuId.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = stuName.find(":");
		if (pos != -1)
		{
			key = stuName.substr(0, pos);
			value = stuName.substr(pos + 1, stuName.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = roomId.find(":");
		if (pos != -1)
		{
			key = roomId.substr(0, pos);
			value = roomId.substr(pos + 1, roomId.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = status.find(":");
		if (pos != -1)
		{
			key = status.substr(0, pos);
			value = status.substr(pos + 1, status.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		this->m_orderData.insert(make_pair(this->m_Size, m));
		this->m_Size++;//插入一条预约数据就让统计数量的变量++
	}// end of while (ifs >> week && ifs >> day && ifs >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status)
	//最后记得关闭文件
	ifs.close();
}

void OrderFile::updateOrder()
{
	//更新到文件
	//如果内存中没有就不用存了
	if (this->m_Size == 0)return;

	ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
	for (int i = 0; i < m_Size; i++)
	{
		ofs << "星期:" << this->m_orderData[i]["星期"] << " ";
		ofs << "时间:" << this->m_orderData[i]["时间"] << " ";
		ofs << "申请人学号:" << this->m_orderData[i]["申请人学号"] << " ";
		ofs << "申请人姓名:" << this->m_orderData[i]["申请人姓名"] << " ";
		ofs << "房间号:" << this->m_orderData[i]["房间号"] << " ";
		ofs << "预约状态:" << this->m_orderData[i]["预约状态"] << endl;
	}
	ofs.close();
}
