#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include<deque>


//选手类
class Person
{
public:
	Person(string name, int score)
	{
		this->m_Name = name;
		this->m_Score = score;
	 }
	string m_Name;
	int m_Score;
};
void createPerson(vector<Person>&v)
{
	string nameSeed = "ABCDE";
	for (int i= 0; i < 5; i++)
	{
		string name = "选手";
			name += nameSeed[i];
			int score = 0;

			Person p(name, score);

			//将创建的person对象，放入到容器中
			v.push_back(p);



	}
}
//打分
void setScore(vector<Person>& v)
{
	for (vector<Person>::iterator it; it != v.end(); it++)
	{
		//将评委的分数 放入到deque容器中
		deque<int>d;
		for (int i = 0; i < 5; i++)
		{
			int score=rand()%41+60;//60~100
				
		}
	}
}

int main()
{
	//1.创建五名选手
	vector<Person>v;
	createPerson(v);
	//测试
	for (vector<Person>::iterator it; it != v.end(); it++)
	{
		cout << "姓名："<<(*it).m_Name << "分数：" << (*it).m_Score << endl;
	}
	//2.给五名选手打分
	//3.显示最后的得分
}