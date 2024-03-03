#include<QApplication>
#include<QWidget>
#include<qlabel.h>
#include<qlineedit.h>
#include<QBoxLayout>
#include<qpushbutton.h>
#include<QCheckBox>
#include<qgridlayout.h>
#include<qformlayout.h>
#include<qcombobox.h>
#include<qplaintextedit.h>
#include<qstackedlayout.h>
#include<qbuttongroup.h>
#include<qsplitter.h>

//去掉黑窗口
#pragma comment(linker,"/subSystem:windows /entry:mainCRTStartup")

class Widget :public QWidget
{
public:
	Widget(QWidget* parent = nullptr):QWidget(parent)
	{
		//resize(640, 480);
		//boxLayout();
		//boxLayout1();
		//gridLayout();
		//formLayout();
		//stackedLayout();
		splitter();
	}

	void boxLayout(QWidget* parent)
	{
		//创建控件(设置布局时会自动设置父对象，不需要自己设置)
		auto tipLab_username = new QLabel("用户名：");
		auto usernameEdit = new QLineEdit();

		//创建布局
		auto hLay = new QHBoxLayout;
		//把控件添加到布局里（注意先后顺序）
		hLay->addWidget(tipLab_username);
		hLay->addWidget(usernameEdit);
		//把布局应用在谁上面就交给谁
		//setLayout(hLay);

		auto tipLab_password = new QLabel("密码：");
		auto passwordEdit = new QLineEdit();
		auto hLay1 = new QHBoxLayout;
		hLay1->addWidget(tipLab_password);
		hLay1->addWidget(passwordEdit);

		//一般 setxxx 就只能设置一个，addxxx就能设置多个
		//所以现在可以弄个垂直布局包裹两个水平布局实现账号和密码的输入界面

		auto vLay = new QVBoxLayout(parent);
		vLay->addLayout(hLay);
		vLay->addLayout(hLay1);
		setLayout(vLay);
	}
	void boxLayout1()
	{
		QPushButton* btn1 = new QPushButton("One");
		QPushButton* btn2 = new QPushButton("Two");
		QPushButton* btn3 = new QPushButton("Three");
		QPushButton* btn4 = new QPushButton("Four");
		QPushButton* btn5 = new QPushButton("Five");
		
		btn3->setFixedHeight(50);

		//这么指定父元素就不用使用setLayout设置了
		auto hlayout = new QBoxLayout(QBoxLayout::Direction::LeftToRight, this);

		//设置内容边距（默认9）
		hlayout->setContentsMargins(0, 0, 0, 0);
		//设置控件间距（默认6）
		hlayout->setSpacing(0);

		//添加弹簧（拉伸空间）,参数就是弹力系数
		hlayout->addStretch();

		hlayout->addWidget(btn1);
		hlayout->addWidget(btn2, 1, Qt::AlignTop);
		hlayout->addWidget(btn3);
		hlayout->addWidget(btn4, 2, Qt::AlignBottom);
		hlayout->addWidget(btn5);

		//添加弹簧（拉伸空间）
		hlayout->addStretch();

	}
	void gridLayout(QWidget* parent) {
		auto profileLab = new QLabel;//登录图像
		auto accountEdit = new QLineEdit;//账号输入框
		auto passwordEdit = new QLineEdit;//密码输入框
		auto rememberPasswordChx = new QCheckBox("记住密码");
		auto autoLognChx = new QCheckBox("自动登录");
		auto loginBtn = new QPushButton("登录");
		auto registerAccountBtn = new QPushButton("注册账号");
		auto retrievePasswordBtn = new QPushButton("找回密码");

		profileLab->setPixmap(QPixmap(":/Resource/zay.png"));
		profileLab->setFixedSize(90, 90);
		profileLab->setScaledContents(true);//设置标签内内容根据标签大小自动缩放

		//输入框内的提示内容
		accountEdit->setPlaceholderText("QQ号码/手机号/邮箱");
		passwordEdit->setPlaceholderText("请输入密码");

		//复选框默认勾选
		rememberPasswordChx->setChecked(true);

		auto glayout = new QGridLayout(parent);

		//后面四个数字分辨是（第几行，第几列，占几行，占几列）
		glayout->addWidget(profileLab, 0, 0, 3, 1);
		glayout->addWidget(accountEdit, 0, 1, 1, 2);
		glayout->addWidget(passwordEdit, 1, 1, 1, 2);
		glayout->addWidget(rememberPasswordChx, 2, 1);
		glayout->addWidget(autoLognChx, 2, 2);
		glayout->addWidget(loginBtn, 3, 1, 1, 2);
		glayout->addWidget(registerAccountBtn, 0, 3);
		glayout->addWidget(retrievePasswordBtn, 1, 3);
	}
	void formLayout() {
		auto usernameEdit = new QLineEdit;
		auto passwrodEdit = new QLineEdit;
		auto mobileEdit = new QLineEdit;
		auto emailEdit = new QLineEdit;

		auto manChx = new QCheckBox("男");
		auto womanChx = new QCheckBox("女");

		auto provinceCmb = new QComboBox;
		provinceCmb->addItem("河北省");
		provinceCmb->addItem("海南省");

		auto flayout = new QFormLayout(this);
		//设置换行策略
		flayout->setRowWrapPolicy(QFormLayout::RowWrapPolicy::WrapAllRows);//总是换行

		flayout->addRow("<font color=red size=3>*</font>用户名", usernameEdit);
		flayout->addWidget(new QLabel("<font color=gray size=2>中文、英文、特殊字符</font>"));
		flayout->addRow("密  码", passwrodEdit);
		flayout->addRow("手机号码", mobileEdit);
		flayout->addRow("电子邮箱", emailEdit);

		auto hlayout = new QHBoxLayout;
		hlayout->addWidget(manChx);
		hlayout->addWidget(womanChx);
		hlayout->addStretch();
		flayout->addRow("性别", hlayout);

		flayout->addRow("住址", provinceCmb);
		flayout->addRow("详细地址", new QPlainTextEdit);
	}
	void stackedLayout() 
	{
		//用来管理多个按钮可以用 按钮组
		auto btnGroup = new QButtonGroup(this);
		btnGroup->addButton(new QPushButton("page1"),0);//默认下标从0开始排列，也可以手动调整
		btnGroup->addButton(new QPushButton("page2"),1);
		
		auto hLayout = new QHBoxLayout;
		hLayout->addWidget(btnGroup->button(0));
		hLayout->addWidget(btnGroup->button(1));
		
		//这个布局是用来管理多个页面的
		auto slayout = new QStackedLayout;
		slayout->addWidget(createWidget(0));//0
		slayout->addWidget(createWidget(1));//1
		
		auto vLayout = new QVBoxLayout;
		vLayout->addLayout(hLayout);
		vLayout->addLayout(slayout);
		
		setLayout(hLayout);
		
		//页面切换
		//slayout->setCurrentIndex(1);
		
		//将按钮与页面联系起来
		connect(btnGroup, &QButtonGroup::idClicked, [=](int id)
			{
				slayout->setCurrentIndex(id);
			});

	}
	QWidget* createWidget(int id)
	{
		if (0 == id)
		{
			QWidget* page = new QWidget;
			boxLayout(page);
			return page;
		}
		else if (1 == id)
		{
			QWidget* page = new QWidget;
			gridLayout(page);
			return page;
		}
		return nullptr;

	}
	
	void splitter()
	{
		//splitter本身就是一个窗口
		auto sp = new QSplitter;
		sp->addWidget(new QPlainTextEdit);//0
		sp->addWidget(createWidget(1));//1

		//设置不可折叠
		sp->setCollapsible(1, false);

		auto hlay = new QHBoxLayout;
		hlay->addWidget(sp);

		setLayout(hlay);
	}

private:
	
};

int main(int argc, char* argv[]) {

	QApplication a(argc, argv);

	Widget w;
	w.show();

	return a.exec();
}