#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include<deque>


//ѡ����
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
		string name = "ѡ��";
			name += nameSeed[i];
			int score = 0;

			Person p(name, score);

			//��������person���󣬷��뵽������
			v.push_back(p);



	}
}
//���
void setScore(vector<Person>& v)
{
	for (vector<Person>::iterator it; it != v.end(); it++)
	{
		//����ί�ķ��� ���뵽deque������
		deque<int>d;
		for (int i = 0; i < 5; i++)
		{
			int score=rand()%41+60;//60~100
				
		}
	}
}

int main()
{
	//1.��������ѡ��
	vector<Person>v;
	createPerson(v);
	//����
	for (vector<Person>::iterator it; it != v.end(); it++)
	{
		cout << "������"<<(*it).m_Name << "������" << (*it).m_Score << endl;
	}
	//2.������ѡ�ִ��
	//3.��ʾ���ĵ÷�
}