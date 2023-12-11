#include "speechManager.h"
#include<algorithm>
#include<deque>
#include<numeric>
#include <fstream>

using namespace std;

speechManager::speechManager()
{
	//初始化数据
	this->initSpeech();
	//创建比赛开始时的选手
	this->createSpeaker();
	//获取往届记录
	this->loadSorce();
}

void speechManager::showMenu()
{
	cout << "********************************************" << endl;
	cout << "*************  欢迎参加演讲比赛 ************" << endl;
	cout << "*************  1.开始演讲比赛  *************" << endl;
	cout << "*************  2.查看往届记录  *************" << endl;
	cout << "*************  3.清空比赛记录  *************" << endl;
	cout << "*************  0.退出比赛程序  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

speechManager::~speechManager()
{
}

void speechManager::initSpeech()
{
	//将容器置空
	this->v1.clear();
	this->v2.clear();
	this->vDone.clear();
	this->m_speaker.clear();
	this->m_index = 1;
	this->m_Record.clear();
}

void speechManager::createSpeaker()
{
	//准备随机名称种子
	string nameSeed = "ABCDEFGHIJKL";
	//循环生成
	for (int i = 0; i < nameSeed.size(); i++) {
		//创建选手
		speaker s;
		//填入名字
		string name = "选手";
		name += nameSeed[i];
		s.m_name = name ;
		//cout << nameSeed[i];
		//初始化两轮分数（就俩数，不用循环了）
		s.m_score[0] = 0;
		s.m_score[1] = 0;
		//插入本次循环的成员编号
		this->v1.push_back(10001 + i);
		//插入 选手编号 和 选手 到map中
		m_speaker.insert(make_pair(10001 + i, s));



	}
}

void speechManager::startSpeech()
{

	//第一轮比赛
	//1、抽签
	speechDraw();
	//2、比赛
	speechContest();
	//3、显示晋级结果
	showScore();
	//4、轮次++
	m_index++;

	//第二轮比赛
	//1、抽签
	speechDraw();
	//2、比赛
	speechContest();
	//3、显示晋级结果(最终结果)
	showScore();
	//4、保存分数
	scoreRecord();

	//每次比赛完要重置比赛
	//初始化属性
	this->initSpeech();
	//创建选手
	this->createSpeaker();
	//重新获取文件中的历史参赛数据
	this->loadSorce();

	//结束
	cout << "本届比赛结束！" << endl;
	system("pause");
	system("cls");

}

void speechManager::speechDraw()
{
	cout << "第 << " << this->m_index << " >> 轮比赛选手正在抽签" << endl;
	cout << "---------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;
	//先判断是第一轮还是第二轮
	vector<int>& v=v1;
	if (this->m_index == 2) {
		v = v2;
	}
	//开始打乱容器里的编号
	random_shuffle(v.begin(), v.end());
	//将结果输出
	for (vector<int>::iterator iter = v.begin(); iter != v.end(); iter++) { 
		cout << *iter << " "; 
	}
	cout << endl;
	cout << "---------------------" << endl;
	system("pause");
}

void speechManager::speechContest() {
	cout << "------------- 第" << this->m_index << "轮正式比赛开始：------------- " << endl;

	//临时分数保存，key为分数，value为参赛成员编号，根据分数降序排列(主要是为了排列)
	//key为分数是因为排列根据key来的；用multimap不用map是因为它的key可以重复
	multimap<double, int, greater<double>> scoreTemp;

	//判断是第一轮还是第二轮
	vector<int>& v = v1;
	if (this->m_index == 2) {
		v = v2;
	}
	
	//创建一个计数器，用于统计已比赛的人数
	int cntPerosn = 0;

	//循环遍历参赛成员v
	for (vector<int>::iterator iter = v.begin(); iter != v.end(); iter++) {
		//给每位选手打分（10-1-1再取平均）
		//先创建一个双向队列用于记录分数
		deque<double> scores;
		//循环10次取随机数模拟打分
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f; // 600 ~ 1000
			//cout << score << " ";
			scores.push_back(score);
		}
		//排序，-1-1取平均数
		sort(scores.begin(), scores.end(), greater<double>());
		scores.pop_back();
		scores.pop_front();
		double average = (accumulate(scores.begin(), scores.end(), 0.0f) / 8.0);
		//将平均值存储到对应选手的对应轮次上
		this->m_speaker[*iter].m_score[m_index - 1] = average;
		//顺便将平均值和成员编号放到临时容器，方便排序
		scoreTemp.insert(make_pair(average, *iter));
		//一个成员的分数弄完了，计数器++
		cntPerosn++;

		//六个一组，判断是否满6人
		if (cntPerosn % 6 == 0) {
			//满6人了就输出一下6人的比赛情况
			if (this->m_index == 1) {
				cout << "第" << cntPerosn / 6 << "小组比赛名次：" << endl;
			}
			for (multimap<double, int, greater<int>>::iterator it = scoreTemp.begin(); it
				!= scoreTemp.end(); it++)
			{
				cout << "编号: " << it->second 
					<< " 姓名： " << this->m_speaker[it -> second].m_name 
					<< " 成绩： " << this->m_speaker[it->second].m_score[this->m_index - 1] 
					<<endl;
			}

			//循环遍历临时分数容器，将前三名放入v2（vDone）中
			int count = 0;
			for (multimap<double, int, greater<int>>::iterator it = scoreTemp.begin();
				it != scoreTemp.end() && count < 3; it++, count++) {
				//判断第一轮还是第二轮
				if (this->m_index == 1) {
					//6进3到v2
					v2.push_back((*it).second);

				}
				if (this->m_index == 2) {
					//6进3到vDone
					vDone.push_back((*it).second);
				}
			}

			//将临时容器清空，方便下一组6个人的分数记录
			scoreTemp.clear();
			cout << endl;
			
		}
	}
	cout << "------------- 第" << this->m_index << "轮比赛完毕 ------------- " << endl;
	system("pause");
}

void speechManager::showScore()
{
	if (this->m_index == 1) {
		cout << "---------第" << this->m_index << "轮晋级选手信息如下：-----------" << endl;
	}
	else {
		cout << "---------比赛结果如下-----------" << endl;
	}
	vector<int>& v = v2;
	if (this->m_index == 2) {
		v = vDone;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "选手编号：" << *it << " 姓名： " << m_speaker[*it].m_name 
			<< " 得分： " <<m_speaker[*it].m_score[this->m_index - 1] 
			<< endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->showMenu();
}

void speechManager::loadSorce()
{
	//读的方式打开记录文件
	ifstream ifs("speech.csv", ios::in); 
	//判断文件是否正常打开
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}
	//读取一个字符后，看看是不是空文件，防止文件中只有空格或者换行符的情况出现
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空!" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	//除去上述两种情况，文件不为空
	this->fileIsEmpty = false;
	//再将刚才读取的单个字符放回去
	ifs.putback(ch); 

	//用于接收从文件中读取的字符串
	string scoreData;
	//用于统计届数
	int index = 0;
	//每次读取一行数据
	while (ifs >> scoreData) {
		//开始对数据进行分割
		//用于存储分割完的每小段string类型数据
		vector<string> v;
		//记录截取的起始位置
		int start = 0;
		//记录分割点位置
		int pos = -1;

		//开始找
		while (true)
		{
			//从start开始查找 ',' 将其位置记录在pos中
			pos = scoreData.find(",", start); 
			//找不到break返回
			if (pos == -1)
			{
				break; 
			}
			//找到的话，开始切割(参数1 起始位置，参数2 截取长度)
			string temp = scoreData.substr(start, pos - start);
			//将切割片段放入容器
			v.push_back(temp);
			//更新起始位置到切割点下一位，方便下轮寻找
			start = pos + 1;
		}
		//这一轮的找完后，将容器v的数据存到全局容器中
		this->m_Record.insert(make_pair(index, v));
		//届数增加
		index++;
	}
	//都找完之后，关闭文件
	ifs.close();
}

void speechManager::showRecord()
{
	if (this->m_Record.empty()) {
		cout << "无往届参赛数据" << endl;
	}
	for (int i = 0; i < this->m_Record.size(); i++)
	{
		cout << "第" << i + 1 << "届 " <<
			"冠军编号：" << this->m_Record[i][0] << "  得分：" << this->m_Record[i][1] << endl;
		cout << "\t亚军编号：" << this->m_Record[i][2] << "  得分：" << this->m_Record[i][3] << endl;
		cout<<"\t  季军编号：" << this->m_Record[i][4] << "  得分：" << this->m_Record[i][5] << endl;
		cout << "--------------------" << endl;
	}
	system("pause");
	system("cls");
}

void speechManager::clearRecord()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//打开模式 ios::trunc 如果存在删除文件并重新创建
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		//初始化属性
		this->initSpeech();
		//创建选手
		this->createSpeaker();
		//获取往届记录
		this->loadSorce();
		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}

void speechManager::scoreRecord()
{
	fstream file;
	//用写和追加写的方式打开文件
	file.open("speech.csv", ios::out | ios::app);
	//将前三名的分数写入文件
	for (vector<int>::iterator it = vDone.begin(); it != vDone.end(); it++)
	{
		file << *it << ","<< m_speaker[*it].m_score[1] << ",";
	}
	file << endl;
	cout << "记录已经保存" << endl;
	file.close();
}

