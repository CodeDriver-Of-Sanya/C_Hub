#include<QApplication>
#include<QWidget>
#include"ContactListView.h"

//去掉黑窗口
//#pragma comment(linker,"/subSystem:windows /entry:mainCRTStartup")

int main(int argc, char* argv[]) {

	QApplication a(argc, argv);
	
	ContactListView v;
	v.show();
	

	return a.exec();
}

#include "main.moc"