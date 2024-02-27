#include<QCoreApplication>
#include"Server.h"

int main(int argc,char* argv[])
{
	QCoreApplication a(argc, argv);

	ChatRoomServer server;
	
	return a.exec();
}