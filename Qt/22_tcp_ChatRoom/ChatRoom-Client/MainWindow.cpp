#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Util/SEventfilterObject.h"
#include "Util/SChatBubble.h"
#include <qinputdialog.h>
#include<qjsondocument.h>
#include<qjsonobject.h>
#include<qjsonvalue.h>
#include<QDateTime>
#include<qjsonarray.h>

MainWindow::MainWindow(QWidget* parent)
	:QWidget(parent)
	,ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	initUi();

	setWindowFlag(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	installEventFilter(new SEventFilterObject(this));

	m_client.connectToHost(QHostAddress("127.0.0.1"), 8888);


	m_userId = QDateTime::currentDateTime().toMSecsSinceEpoch();
}

MainWindow::~MainWindow()
{
	m_client.close();
	delete ui;
}

void MainWindow::initUi()
{
	SChatBubble* b = new SChatBubble(QPixmap(), "hello wrold");
	ui->chatMsgListWidget->addItem(b);
	ui->chatMsgListWidget->setItemWidget(b, b);

	b = new SChatBubble(QPixmap(), "hello wroldsdfsfjsklfjkdjfklj", SChatBubble::BubbleRight);
	ui->chatMsgListWidget->addItem(b);
	ui->chatMsgListWidget->setItemWidget(b, b);

	//默认让输入框获得焦点
	ui->chatMsgSendEdit->setFocus();
	//不让发送按钮获得焦点
	ui->msgSendBtn->setFocusPolicy(Qt::FocusPolicy::NoFocus);

	connect(&m_client, &QTcpSocket::readyRead, this, &MainWindow::onReadyRead);
	connect(&m_client, &QTcpSocket::disconnected, this, &MainWindow::onDisconnected);
	connect(&m_client, &QTcpSocket::connected, this, &MainWindow::onConnected);
	connect(&m_client, &QTcpSocket::errorOccurred, this, &MainWindow::onErrorOccurred);
}

/* 发送消息 */
void MainWindow::on_msgSendBtn_clicked()
{
	//获取输入框中输入的消息
	auto message = ui->chatMsgSendEdit->toPlainText();

	//如果没输入信息，那么就不创建聊天气泡
	if (message.isEmpty())return;

	//清空输入框
	ui->chatMsgSendEdit->clear();

	//创建聊天气泡
	SChatBubble* b = new SChatBubble(QPixmap(), message,SChatBubble::BubbleRight);
	ui->chatMsgListWidget->addItem(b);
	ui->chatMsgListWidget->setItemWidget(b, b);

	//滚动到底部
	ui->chatMsgListWidget->scrollToBottom();

	//把消息发送给服务器
	QJsonObject obj;
	obj.insert("type", "message");
	obj.insert("mtype", static_cast<int>(m_mtype));
	obj.insert("content", message);

	if (m_mtype == MessageType::MType_Friend)
	{
		obj.insert("to_userid", m_chatUserID);
		obj.insert("to_username", m_chatUsername);
		obj.insert("from_userid", m_userId);
		obj.insert("from_username", m_username);
	}

	m_client.write(QJsonDocument(obj).toJson(QJsonDocument::Compact));

}

/* 联系人选择改变 */
void MainWindow::on_friendListWidget_itemClicked(QListWidgetItem *item)
{
	m_mtype = MessageType::MType_Friend;
	m_chatUserID = ui->friendListWidget->currentItem()->data(Qt::UserRole).toDouble();
	m_chatUsername = ui->friendListWidget->currentItem()->text();


}
 
void MainWindow::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
	ui->systemBroadCatListWidget->addItem("服务器连接失败...");
}

void MainWindow::onConnected()
{
	//让用户输入用户名
	m_username = QInputDialog::getText(this, "欢迎使用", "请输入用户名");

	//将用户名显示在聊天室左上角
	ui->curUserLab->setText(m_username + " 正在使用聊天室");

	//登录
	QJsonObject obj;
	//消息类型
	obj.insert("type", "login");
	obj.insert("username", m_username);
	//用时间的部分作为id保证不重复
	obj.insert("id", (qreal)m_userId);
	qDebug() << "消息发送" << m_username;
	m_client.write(QJsonDocument(obj).toJson(QJsonDocument::Compact));

}

void MainWindow::onDisconnected()
{
}

void MainWindow::onReadyRead()
{
	auto data = m_client.readAll();
	QJsonParseError err;
	auto jdom = QJsonDocument::fromJson(data, &err);
	if (err.error != QJsonParseError::NoError)
	{
		qWarning() << "解析json数据失败" << err.errorString() << QString(data);
		return;
	}
	//开始判断
	auto type = jdom["type"].toString();
	if (type == "sys_online")
	{
		ui->systemBroadCatListWidget->addItem(jdom["username"].toString() + " 上线了！");
		qDebug() << jdom["username"].toString() << " " << jdom["id"].toString() << " 上线了！";
		//将新上线的用户加入到好友列表
		auto item = new QListWidgetItem(jdom["username"].toString());
		item->setData(Qt::UserRole, jdom["id"].toDouble());
		ui->friendListWidget->addItem(item);
	}
	else if (type == "user_list")
	{
		auto user_list = jdom["user_list"].toArray();
		for (size_t i = 0; i < user_list.size(); i++)
		{
			auto juser = user_list[i].toObject();
			auto item = new QListWidgetItem(juser.value("username").toString());
			item->setData(Qt::UserRole, juser.value("id").toDouble());
			ui->friendListWidget->addItem(item);
		}
	}
	else if (type == "sys_offline")
	{
		//先用系统提示下线的用户
		ui->systemBroadCatListWidget->addItem(jdom["username"].toString() + " 下线了...");
		//移除下线用户的item
		auto item_list = ui->friendListWidget->findItems(jdom["username"].toString(), Qt::MatchFlag::MatchContains);
		for (auto item : item_list)
		{
			if (item->data(Qt::UserRole) == jdom["id"].toDouble())
			{
				auto index = ui->friendListWidget->indexFromItem(item);
				delete ui->friendListWidget->takeItem(index.row());
				break;
			}
		}

	}
	else if (type == "message")
	{
		SChatBubble* b = new SChatBubble(QPixmap(), jdom["content"].toString());
		ui->chatMsgListWidget->addItem(b);
		ui->chatMsgListWidget->setItemWidget(b, b);

		if(static_cast<MessageType>(jdom["mtype"].toInt()) == MessageType::MType_Friend)
		{
			m_mtype = MessageType::MType_Friend;
			m_chatUserID = jdom["from_userid"].toDouble();
			m_chatUsername = jdom["from_username"].toString();
		}

	}

}

