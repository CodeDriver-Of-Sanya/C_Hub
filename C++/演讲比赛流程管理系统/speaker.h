#pragma once
#include<iostream>

using namespace std;

class speaker{
public:
	//选手姓名
	string m_name;
	//选手得分（最多两轮，所以是2）
	double m_score[2];
};
