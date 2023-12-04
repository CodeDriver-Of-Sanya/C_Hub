#include<QApplication>
#include<QWidget>
#include<qpushbutton.h>

int main(int argc, char* argv[]) {

	QApplication a(argc, argv);

	QWidget w;
	//设置exe图标
	w.setWindowIcon(QIcon(":/Resource/logo.ico"));
	
	w.show();

	return a.exec();

}

#include "main.moc"