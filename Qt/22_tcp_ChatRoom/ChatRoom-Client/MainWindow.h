#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include<QWidget>
#include<QListWidgetItem>
#include<qtcpsocket.h>
#include"../common/common.h"

namespace Ui { class MainWindow; }



class MainWindow : public QWidget
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();

	void initUi();

private slots:
	void on_msgSendBtn_clicked();

	void on_friendListWidget_itemClicked(QListWidgetItem* item);

	void onErrorOccurred(QAbstractSocket::SocketError socketError);
	void onConnected();
	void onDisconnected();
	void onReadyRead();

private:
	Ui::MainWindow* ui{};
	QTcpSocket m_client;
	QString m_username;
	qreal m_userId;
	MessageType m_mtype{ MessageType::MType_Group };
	QString m_chatUsername{};
	qreal m_chatUserID{};
};

#endif // !MAINWINDOW_H_
