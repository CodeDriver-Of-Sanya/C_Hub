#include"speechManager.h"


int main(){
	
	speechManager sm;
	srand((unsigned int)time(NULL));

	//for (map<int, speaker>::iterator it = sm.m_speaker.begin(); it != sm.m_speaker.end(); it++)
	//{
	//	cout << "选手编号：" << it->first
	//		<< " 姓名： " << it->second.m_name
	//		<< "     成绩： " << it->second.m_score[0] << endl;
	//}

	while (true)
	{
		sm.showMenu();
		int select;
		cout << "请输入选项>";
		cin >> select;
		switch (select)
		{
		case 0:
			cout << "正在退出，欢迎下次使用" << endl;
			exit(0);
			break;
		case 1:
			sm.startSpeech();
			break;
		case 2:
			sm.showRecord();
			break;
		case 3:
			sm.clearRecord();
			break;
		default:
			cout << "无效选项，请重新选择！" << endl;
			break;
		}
		//system("pause");
		system("cls");
	}
	

	return 0;
}
