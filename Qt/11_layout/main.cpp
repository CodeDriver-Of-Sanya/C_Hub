#include<QApplication>
#include<QWidget>
#include<qlabel.h>
#include<qlineedit.h>
#include<QBoxLayout>
#include<qpushbutton.h>

//去掉黑窗口
#pragma comment(linker,"/subSystem:windows /entry:mainCRTStartup")

class Widget :public QWidget
{
public:
	Widget(QWidget* parent = nullptr):QWidget(parent)
	{
		resize(640, 480);
		//boxLayout();
		boxLayout1();
	}

	void boxLayout()
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

		auto vLay = new QVBoxLayout();
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

private:

};

int main(int argc, char* argv[]) {

	QApplication a(argc, argv);

	Widget w;
	w.show();

	return a.exec();
}