#ifndef _SERVER_H_
#define _SERVER_H_

#include"../common/common.h"
#include<qtcpserver.h>
#include<qtcpsocket.h>
#include<qhash.h>
#include<memory>

struct User
{
	using ptr = std::shared_ptr<User>;
	qreal id;
	QString username;
};

class ChatRoomServer : public QObject
{
public:
	ChatRoomServer(QObject* parent = nullptr);
	~ChatRoomServer();

	void init();

public://slots
	//有新的客户端连接上时
	void onNewConnected();

	//有客户端发送消息时
	void onReadyRead();

	//有客户端退出(断开连接)时
	void onDisconnected();

private:
	QTcpServer m_server;
	QHash<QTcpSocket*, User::ptr> m_userHash; //服务器端本地存储由客户端发来信息的用户信息

};

#endif // !_SERVER_H_
