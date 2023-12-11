#include<QApplication>
#include"QGame.h"

//去掉黑窗口
//#pragma comment(linker,"/subSystem:windows /entry:mainCRTStartup")

int main(int argc, char* argv[]) {

	QApplication a(argc, argv);

	QGame game;
	game.init({ 480,852 }, "第一个Qt小游戏");
	game.run();

	return a.exec();
}

#include "main.moc"