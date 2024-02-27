#include<QApplication>
#include"MainWindow.h"
#include<QFile>
#include<QLabel>
int main(int argc,char* argv[])
{
	QApplication a(argc, argv);
	/*
	QFile wfile("xxx.txt");
	QFile file(":/Resource/default_head.png");
	if (file.open(QIODevice::ReadOnly) && wfile.open(QIODevice::WriteOnly))
	{
		while (!file.atEnd())
		{
			 auto ch = file.read(1);
			 wfile.write("0x"+ch.toHex() + ',');
		}
	}
	file.close();
	wfile.close();
	*/

	MainWindow w;
	w.show();
	
	return a.exec();
}