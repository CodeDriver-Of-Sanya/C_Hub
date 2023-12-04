#pragma once
#include<iostream>
#include <map>
#include "globalFile.h"

using namespace std;

class OrderFile
{

public:
	//构造函数
	OrderFile();

	//更新预约记录
	void updateOrder();

	//预约记录条数
	int m_Size;

	//记录的容器  key --- 记录条数(m_Size)  value --- 具体记录的键值对信息
	map<int, map<string, string>> m_orderData;

	
};

