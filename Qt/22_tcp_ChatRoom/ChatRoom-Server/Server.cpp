#include "Server.h"

#include<qjsondocument.h>
#include<qjsonobject.h>
#include<qjsonvalue.h>
#include<qjsonparseerror>
#include<qjsonarray.h>

ChatRoomServer::ChatRoomServer(QObject* parent)
	:QObject(parent)
{
	init();
}

ChatRoomServer::~ChatRoomServer()
{
	m_server.close();
}

void ChatRoomServer::init()
{
	//让服务器监视 任意IPV4地址 端口8888
	m_server.listen(QHostAddress::AnyIPv4, 8888);

	//有新连接时的事件
	connect(&m_server, &QTcpServer::newConnection, this, &ChatRoomServer::onNewConnected);


}

void ChatRoomServer::onNewConnected()
{
	while (m_server.hasPendingConnections())
	{
		QTcpSocket* clientSocket = m_server.nextPendingConnection();
		if (!clientSocket)
		{
			qDebug() << m_server.errorString();
			continue;
		}
		connect(clientSocket, &QTcpSocket::readyRead, this, &ChatRoomServer::onReadyRead);
		connect(clientSocket, &QTcpSocket::disconnected, this, &ChatRoomServer::onDisconnected);
	}
}

void ChatRoomServer::onReadyRead()
{
	auto socket = dynamic_cast<QTcpSocket*>(sender());
	//登录的时候保存用户信息
	QJsonParseError err;
	auto data = socket->readAll();
	auto jdoc = QJsonDocument::fromJson(data,&err);
	//检查是否转换成功
	if (err.error != QJsonParseError::NoError)
	{
		QJsonObject obj;
		obj.insert("type", "Error");
		obj.insert("message", err.errorString());
		socket->write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
		qDebug() << "ChatRoomServer::onReadyRead 转换失败";
		return;
	}

	if (jdoc["type"] == "login")
	{
		User::ptr user(new User);
		user->id = jdoc["id"].toDouble();
		user->username = jdoc["username"].toString();
		qDebug() << "登录成功" << user->id << user->username;

		if (!m_userHash.isEmpty())
		{
			//给其他的用户发送上线通知
			QJsonObject jobj;
			jobj.insert("type", "sys_online");
			jobj.insert("username", user->username);
			jobj.insert("id", user->id);

			auto data = QJsonDocument(jobj).toJson(QJsonDocument::Compact);

			for (auto it = m_userHash.begin(); it != m_userHash.end(); ++it)
			{
				it.key()->write(data);
			}

			//给当前用户发送所有的在线用户列表
			QJsonArray jarr;
			for (auto& user : m_userHash)
			{
				QJsonObject juser;
				juser.insert("username", user->username);
				juser.insert("id", user->id);
				jarr.append(juser);
			}
			QJsonObject jroot;
			jroot.insert("type", "user_list");
			jroot.insert("user_list", jarr);
			socket->write(QJsonDocument(jroot).toJson(QJsonDocument::Compact));

		}

		m_userHash.insert(socket, std::move(user));
	}
	else if (jdoc["type"] == "message")
	{
		auto mtype = static_cast<MessageType>(jdoc["mtype"].toInt());
		if (mtype == MessageType::MType_Group)
		{
			//群发消息
			for (auto it = m_userHash.cbegin(); it != m_userHash.cend(); ++it)
			{
				//除了当前发出消息的用户之外的所有用户
				if (it.key() != socket)
				{
					it.key()->write(data);

				}
			}
		}
		else
		{
			auto to_userID = jdoc["to_userid"].toDouble();
			auto to_userName = jdoc["to_username"].toString();
			for (auto it = m_userHash.cbegin(); it != m_userHash.cend(); ++it)
			{
				auto user = it.value();
				if (user->id == to_userID && user->username == to_userName)
				{
					it.key()->write(data);
				}
			}
		}
	}



}

void ChatRoomServer::onDisconnected()
{
	//如果有用户下线了，那么通知其他所有用户，将他从好友列表中移除
	auto socket = dynamic_cast<QTcpSocket*>(sender());
	QJsonObject jobj;
	jobj.insert("type", "sys_offline");
	jobj.insert("username", m_userHash.value(socket)->username);
	jobj.insert("id", m_userHash.value(socket)->id);
	//也从hash表中删除该用户
	m_userHash.remove(socket);
	//发给其他的用户
	for (auto it = m_userHash.begin(); it != m_userHash.end(); ++it)
	{
		it.key()->write(QJsonDocument(jobj).toJson(QJsonDocument::Compact));
	}
}
