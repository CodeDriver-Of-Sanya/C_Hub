#include<QApplication>
#include<QWidget>
#include<qpushbutton.h>
#include<QMouseEvent>

//去掉黑窗口
//#pragma comment(linker,"/subSystem:windows /entry:mainCRTStartup")

class Button :public QPushButton {
	Q_OBJECT
public:
	Button(const QString& text,QWidget* parent = nullptr)
		:QPushButton(text,parent)
	{
		 
	}
protected:
	void mousePressEvent(QMouseEvent* e)override
	{
		qInfo() << __FUNCSIG__;

		//e->accept();//默认调用的
		e->ignore();//忽略事件处理，事件将传播到父组件
	}
};

class Widget :public QWidget {
	Q_OBJECT
public:
	Widget(QWidget* parent = nullptr)
		:QWidget(parent)
	{
		resize(640, 480);
		auto* btn = new Button("Button",this);

		//安装事件过滤器,不会自动获取 事件过滤器 对象的所有权，因为一个 事件过滤器 对象可以安装给很多个对象
		installEventFilter(this);

		//取消安装
		//installEventFilter(nullptr);
	}
protected:
	void mousePressEvent(QMouseEvent* e)override
	{
		qInfo() << __FUNCSIG__;
	}
	bool eventFilter(QObject* watched, QEvent* e)override {

	}
};

int main(int argc, char* argv[]) {

	QApplication a(argc, argv);

	Widget w;
	w.show();

	return a.exec();
}

#include "main.moc"