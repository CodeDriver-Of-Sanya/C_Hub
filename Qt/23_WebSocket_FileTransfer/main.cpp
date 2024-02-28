#include<QApplication>
#include"RemoteFileDlg.h"

//去掉黑窗口
//#pragma comment(linker,"/subSystem:windows /entry:mainCRTStartup")

int main(int argc, char* argv[]) {

	QApplication a(argc, argv);

	RemoteFileDlg w;
	w.show();

	return a.exec();
}

#include "main.moc"