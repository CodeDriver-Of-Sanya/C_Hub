#include<QApplication>
#include<QWidget>
#include<qpushbutton.h>
#include<qradiobutton.h>

//去掉黑窗口
//#pragma comment(linker,"/subSystem:windows /entry:mainCRTStartup")

int main(int argc, char* argv[]) {

	QApplication a(argc, argv);

	QWidget w;
	


	//如果直接这么写在这里，这个按钮是单独呈现出来的，不会在上面的w窗口里面
	QPushButton btn1("touch me1");
	//btn1.setParent(&w); ←可以这样单独设置父类
	btn1.show();
	//需要给他设置一个父类
	QPushButton btn2("touch me2",&w);
	btn2.show();
	{
		auto btn3 = new QPushButton("touch me3", &w);
		auto rbtn1 = new QRadioButton("rbtn1", &w);
		rbtn1->move({ 100,0 });
		btn3->move({ 100,100 });
		//如果指定了父对象，则不需要手动调用show
		//btn3->show();

		//btn3这样绑定之后会在父窗口关闭后自动释放，可以这样检测：
		QObject::connect(btn3, &QPushButton::destroyed, [] {
			qDebug() << "btn3 destoryed";
			});

		//获取btn3的父类
		auto parentw = dynamic_cast<QWidget*>(btn3->parent());
		//可能会失败，所以要判断
		if (parentw) {
			qDebug() << parentw;
		}
		//上面的也可以简化成用 btn3->parentWidget() 

		//获取子对象
		const QObjectList& list = w.children();//将w下的所有孩子以列表的形式返回出来
		for (auto s : list) {
			qDebug() << s;
		}

		//获取指定类型的子对象
		qDebug() << "sub children" << w.findChildren<QPushButton*>();
		
		//还可以给对象起名字
		rbtn1->setObjectName("rbtn1Name");
		btn3->setObjectName("btn3Name");
		//然后就可以根据对象的名字去获取对象←用于在多个同类型对象中寻找指定对象
		qDebug() <<"知道要找的对象类型：" << w.findChild<QPushButton*>("btn3Name");
		//当你不知道你要找的对象的类型时可以填QWidget*
		qDebug() << "不知道要找的对象类型：" << w.findChild<QWidget*>("btn3Name");
		
	}


	//把所有子对象添加到窗口之后，再显示
	w.show();

	return a.exec();
}

#include "main.moc"