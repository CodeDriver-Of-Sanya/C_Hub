#include<QApplication>
#include<QWidget>
#include<qpushbutton.h>
#include<qdialog.h>

//去掉黑窗口
//#pragma comment(linker,"/subSystem:windows /entry:mainCRTStartup")

class Dialog :public QDialog {
	Q_OBJECT
public:
	Dialog(QDialog* parent = nullptr)
		:QDialog(parent)
		,m_yesBtn(new QPushButton("YES",this))
		,m_noBtn(new QPushButton("NO", this)) {

		m_noBtn->move(160, 0);
		m_noBtn->setDefault(true);//将no按钮设置为默认按钮

		connect(m_yesBtn, &QPushButton::clicked, [=] {
			//accept();
			//如果不想只能接收-1或者拒绝-0（多个选项），可以这样
			done(1);//这里可以传任意int整数
			m_dataStr = "左边";
			});
		connect(m_noBtn, &QPushButton::clicked, [=] {
			//reject();
			done(0);
			m_dataStr = "右边";
			});
	}
	//想要在窗口点下按钮消失时取出里面存的数据，可以设置get函数
	QString getDataStr() { return m_dataStr; };
private:
	QPushButton* m_yesBtn{};
	QPushButton* m_noBtn{};
	QString m_dataStr;
};

class Widget :public QWidget {
	Q_OBJECT
public:
	Widget(QWidget* parent = nullptr)
		:QWidget(parent) 
		,m_btn(new QPushButton("显示模态对话框（应用程序级别）",this))
		,m_btn1(new QPushButton("显示非模态对话框",this))
		,m_btn2(new QPushButton("显示半模态对话框（窗口级别）",this))
	{
		resize(640, 480);
		m_btn1->move(0, 50);
		m_btn2->move(0, 100);
		connect(m_btn, &QPushButton::clicked, []() {
			//显示对话框
			Dialog loginDlg;
			//阻塞程序执行
			int ret = loginDlg.exec();
			if (ret == QDialog::Accepted) {
				qDebug() << "accept"<<loginDlg.getDataStr();
			}
			else {
				qDebug() << "reject" << loginDlg.getDataStr();
			}
			});
		connect(m_btn1, &QPushButton::clicked, [this]() {
			//不阻塞，同理需要将窗口定义到成员变量
			loginDlg.show();
			});
		connect(m_btn2, &QPushButton::clicked, []() {
			QDialog loginDlg;//不想直接消失（销毁），需要将其设置为成员变量
			loginDlg.open();//直接就消失了，因为它不会阻塞程序执行
			});


	}
private:
	QPushButton* m_btn;
	QPushButton* m_btn1;
	QPushButton* m_btn2;
	QDialog loginDlg;
};

int main(int argc, char* argv[]) {

	QApplication a(argc, argv);

	Widget w;
	w.show();

	return a.exec();
}

#include "main.moc"