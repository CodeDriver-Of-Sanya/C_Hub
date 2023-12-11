#include<QApplication>
#include<QWidget>
#include<qpushbutton.h>
#include<qlineedit.h>

//去掉黑窗口
#pragma comment(linker,"/subSystem:windows /entry:mainCRTStartup")

class Login :public QWidget {
	Q_OBJECT
public:
	Login(QWidget* parent = nullptr)
		:QWidget(parent)
		,m_usernameEdit(new QLineEdit(this))
		,m_passwordEdit(new QLineEdit(this))
		,m_loginBtn(new QPushButton("登录",this))
	{
		//调整窗口大小
		resize(640, 480);
		//调整组件位置
		m_usernameEdit->move((width() - m_usernameEdit->width()) / 2, 50);
		m_passwordEdit->move((width() - m_passwordEdit->width()) / 2, 100);
		m_loginBtn->move((width() - m_loginBtn->width()) / 2 + 20, 150);
		//建立事件连接
		connect(m_loginBtn, &QPushButton::clicked, [=]() {
			auto username = m_usernameEdit->text();
			auto password = m_passwordEdit->text();
			//验证登录是否成功
			if (username == password) {
				//发送信号
				emit sig_loginSucceed();
				emit sig_loginSucceed(username,password);
			}
			});

	}
signals://注意这个下面只能放信号！
	//信号也可以重载
	void sig_loginSucceed();
	void sig_loginSucceed(const QString& username, const QString& password);
	void login_OK();
private:
	QLineEdit* m_usernameEdit{};
	QLineEdit* m_passwordEdit{};
	QPushButton* m_loginBtn{};
};

//去掉黑窗口
#pragma comment(linker,"/subSystem:console /entry:mainCRTStartup")

int main(int argc, char* argv[]) {

	QApplication a(argc, argv);

	Login l;
	l.show();
	//在这里接收
	//信号重载的二义性问题，解决办法：
	//1.使用函数指针解决
	//2.使用QOverload类来进行重载
	QObject::connect(&l,QOverload<const QString&, const QString&>::of(&Login::sig_loginSucceed) , [](const QString& username, const QString& password) {
		qDebug() << "登录成功！"<<username<<password;
		});
	//注意：如果有多个槽函数关联同一个信号，那么当信号触发的时候，槽函数的执行顺序是不定的
	//信号的转发
	QObject::connect(&l, QOverload<>::of(&Login::sig_loginSucceed), &Login::login_OK);
	QObject::connect(&l, &Login::login_OK, []() {
		qDebug() << "login_OK";
		});
	

	return a.exec();
}

#include "main.moc"
