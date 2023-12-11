#pragma once
#include"speaker.h"
#include<vector>
#include<map>
#include<iostream>

using namespace std;

class speechManager
{
public:
	//构造
	speechManager();
	//菜单展示
	void showMenu();
	//析构
	~speechManager();

	//成员属性
	//保存第一轮比赛选手编号容器
	vector<int> v1;
	//第二轮比赛选手编号容器
	vector<int> v2;
	//比赛结束前三名容器
	vector<int> vDone;
	//存放编号 以及对应的 具体选手 容器
	map<int, speaker> m_speaker;
	//记录轮次的计数器
	int m_index;

	//文件为空的标志
	bool fileIsEmpty;
	//往届记录
	map<int, vector<string>> m_Record;
	
	//初始化属性
	void initSpeech();
	//创建最开始（第一轮）的12个参赛人员
	void createSpeaker();
	//开始比赛功能
	void startSpeech();
	//打乱参赛成员（抽签）并展示
	void speechDraw();
	//开始比赛流程
	void speechContest();
	//显示每轮的晋级选手
	void showScore();
	//保存前三名的分数到本地文件
	void scoreRecord();

	//读取文件中的分数记录
	void loadSorce();
	//显示往届得分
	void showRecord();
	////清空记录
	void clearRecord();
};

