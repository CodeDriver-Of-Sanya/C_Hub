#include<QApplication>
#include<QWidget>

//ȥ���ڴ���
#pragma comment(linker,"/subSystem:windows /entry:mainCRTStartup")

int main( int argc,char* argv[]) {

	QApplication a(argc, argv);

	QWidget w;
	w.show();

	return a.exec();
}
