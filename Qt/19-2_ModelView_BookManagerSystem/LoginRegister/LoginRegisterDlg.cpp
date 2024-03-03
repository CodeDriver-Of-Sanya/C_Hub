#include "LoginRegisterDlg.h"
#include "EventFilterObject.h"
#include <qpainter.h>
#include<qstatictext.h>
#include<qfont.h>
#include<qpushbutton.h>
#include<qfile.h>
#include<qboxlayout.h>
#include<qcheckbox.h>
#include<qcombobox.h>
#include<qlineedit.h>
#include<qradiobutton.h>


LoginRegisterDlg::LoginRegisterDlg(QWidget* parent)
	:QDialog(parent)
{
	initUi();
}

void LoginRegisterDlg::initUi()
{
	//去掉标题栏
	setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	//实现鼠标拖动
	installEventFilter(new EventFilterObject(this));

	//调整整体的窗口大小
	resize(740, 470);
	//让窗口透明
	setAttribute(Qt::WA_TranslucentBackground);

	//设置右侧白色矩形的大小
	m_rightRect = { 10,40,width() - 5 * 2 - 5,height() - 40 * 2 };
	//设置最左侧的深色矩形
	m_leftRect = { 5,5,185,440 };
	//设置中间的不规则矩形的大小
	m_midRect = { 5, 5, 370, 440 };

	//输入有误提示框
	m_tipBox = new QLabel(this);
	m_tipBox->setGeometry(434, 370, 200, 30);
	m_tipBox->setAlignment(Qt::AlignCenter);

	//关闭按钮
	auto closeBtn = new QPushButton(this);
	closeBtn->setGeometry(width() - 45, 45, 32, 32);
	closeBtn->setObjectName("closeBtn");
	connect(closeBtn, &QPushButton::clicked, this, &QDialog::close);

	//创建堆栈窗口（登录页和注册页需要可以切换）
	m_stkWidget = new QStackedWidget(this);
	m_stkWidget->setGeometry(434, 150, 200, 240);
	m_stkWidget->setContentsMargins(0, 0, 0, 0);
	m_loginWgt = createLoginWidget();
	m_registerWgt = createRegisterWidget();

	m_stkWidget->addWidget(m_loginWgt);
	m_stkWidget->addWidget(m_registerWgt);


	//加载样式表(一般放在最后加载)
	QFile file(":/Resource/style.css");
	if (file.open(QIODevice::ReadOnly))
	{
		setStyleSheet(file.readAll());
	}

}

QWidget* LoginRegisterDlg::createLoginWidget()
{
	//不需要指定父对象，之后要加入到堆栈布局里，堆栈布局会自动管理
	auto w = new QWidget();

	//账号输入框
	auto accountEdit = new QLineEdit;
	accountEdit->setPlaceholderText("请输入账号");
	//密码输入框
	auto passwordEdit = new QLineEdit;
	passwordEdit->setPlaceholderText("请输入密码");
	//记住密码 复选框
	auto rememberPwd = new QCheckBox("记住密码");
	rememberPwd->setObjectName("rememberPwdChx");
	//跳转注册页面的按钮
	auto goRegisterBtn = new QPushButton("注册账号");
	goRegisterBtn->setObjectName("goRegisterBtn");
	connect(goRegisterBtn, &QPushButton::clicked, [=]()
		{
			m_stkWidget->setCurrentWidget(m_registerWgt);
		});
	//登录按钮
	auto loginBtn = new QPushButton("登录");
	loginBtn->setObjectName("loginBtn");
	connect(loginBtn, &QPushButton::clicked, [=]()
		{
			auto account = accountEdit->text();
			auto password = passwordEdit->text();
			auto isRememberPwd = rememberPwd->isChecked();
			if (account.isEmpty() && password.isEmpty())
			{
				setTipBox("请输入账号和密码！");
				
			}
			else if (password.isEmpty())
			{
				setTipBox("请输入密码！");
			}
			else if (account.isEmpty())
			{
				setTipBox("请输入账号！");
			}
			else
			{
				setTipBox("");
			}
		});

	//里面的小水平布局
	auto hlayout = new QHBoxLayout;
	hlayout->setContentsMargins(0, 0, 0, 0);
	hlayout->addWidget(rememberPwd);
	hlayout->addWidget(goRegisterBtn);

	//垂直布局
	auto vlayout = new QVBoxLayout();
	vlayout->setContentsMargins(0, 0, 0, 0);
	vlayout->addWidget(accountEdit);
	vlayout->addWidget(passwordEdit);
	vlayout->addLayout(hlayout);
	vlayout->addWidget(loginBtn);

	w->setLayout(vlayout);

	return w;
}

QWidget* LoginRegisterDlg::createRegisterWidget()
{
	auto w = new QWidget();

	//昵称输入框
	auto accountEdit = new QLineEdit;
	accountEdit->setPlaceholderText("请输入账号");
	//密码输入框
	auto passwordEdit = new QLineEdit;
	passwordEdit->setPlaceholderText("请输入密码");
	auto rePasswordEdit = new QLineEdit;
	rePasswordEdit->setPlaceholderText("请再次输入密码");
	//选择性别
	auto manRBtn = new QRadioButton("男");
	auto womanRBtn = new QRadioButton("女");
	//注册按钮
	auto registerBtn = new QPushButton("注册");
	registerBtn->setObjectName("registerBtn");
	auto backLoginBtn = new QPushButton("返回登录");
	backLoginBtn->setObjectName("backLoginBtn");

	connect(backLoginBtn, &QPushButton::clicked, [=]()
		{
			m_stkWidget->setCurrentWidget(m_loginWgt);
		});
	connect(registerBtn, &QPushButton::clicked, this, &LoginRegisterDlg::onRegister);
	//第一个水平布局放男女单选
	auto hlayout1 = new QHBoxLayout;
	hlayout1->addWidget(manRBtn);
	hlayout1->addWidget(womanRBtn);
	//第二个水平布局放注册和返回登录按钮
	auto hlayout2 = new QHBoxLayout;
	hlayout2->addWidget(registerBtn);
	hlayout2->addWidget(backLoginBtn);

	//最后放整体的
	auto vlayout = new QVBoxLayout;
	vlayout->addWidget(accountEdit);
	vlayout->addWidget(passwordEdit);
	vlayout->addWidget(rePasswordEdit);
	vlayout->addLayout(hlayout1);
	vlayout->addLayout(hlayout2);
	w->setLayout(vlayout);


	return w;
}

void LoginRegisterDlg::onLogin()
{

}

void LoginRegisterDlg::onRegister()
{
}

void LoginRegisterDlg::paintEvent(QPaintEvent* pe)
{
	QPainter p(this);
	//设置高质量渲染（抗锯齿）
	p.setRenderHint(QPainter::Antialiasing);
	//先绘制右边的白色矩形
	p.setPen(Qt::NoPen);//无边框
	p.fillRect(m_rightRect, Qt::white);
	//绘制最左侧的规则矩形
	p.fillRect(m_leftRect, qRgb(27, 45, 67));
	//绘制中间的不规则矩形（弦）
	p.setBrush(QColor(27, 45, 67));
	p.drawChord(m_midRect, 90 * 16, -180 * 16);

	//绘制welcome
	p.setPen(Qt::white);
	p.setFont(QFont("微软雅黑", 30));
	p.drawStaticText(48, 60, QStaticText("Welcome!"));
	p.setFont(QFont("微软雅黑", 8));
	p.drawStaticText(50, 115, QStaticText("顿开—教学跟练"));
	//welcome下面的图片
	p.drawPixmap(QRect(40, 190, 240, 260), QPixmap(":/Resource/cai.png"));
	p.drawPixmap(QRect(40, 190, 240, 260), QPixmap(":/Resource/dream.png"));
	//右侧的logo
	p.drawPixmap(QPoint(423, 70), QPixmap(":/Resource/dunkai.png"));

}

void LoginRegisterDlg::setTipBox(const QString& tip)
{
	m_tipBox->setText("<font color=red>" + tip + "</font>");
	//m_tipBox->setText(tip);
}
