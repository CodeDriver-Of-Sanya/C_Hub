#include<QApplication>
#include<QWidget>
#include<qpushbutton.h>

//去掉黑窗口
#pragma comment(linker,"/subSystem:console /entry:mainCRTStartup")

void on_btn_clicked_global() {
	qDebug() << __FUNCTION__;
}

class Widget :public QWidget {
	Q_OBJECT
public:
	Widget(QWidget* parent = nullptr) 
	:QWidget(parent)
	,m_btn(new QPushButton(this)){
		//调整窗口大小
		resize(640, 480);

		//按钮
		//QPushButton* btn = new QPushButton(this);

		//设置按钮上的文本
		m_btn->setText("快点我");

		//移动按钮的位置
		m_btn->move({ 150,150 });

		//点击按钮时，输出一句话
		//把成员函数作为槽函数使用
		//用连接标识 m_con 保存这个连接
		m_con = connect(m_btn, &QPushButton::clicked, this, &Widget::on_btn_clicked);
		connect(m_btn, &QPushButton::pressed, this, &Widget::on_btn_pressed);
		connect(m_btn, &QPushButton::released, this, &Widget::on_btn_released);

		//把静态函数作为槽函数使用
		//connect(m_btn, &QPushButton::clicked, this, &Widget::on_btn_clicked_static);
		//this 可以省略（不推荐）
		connect(m_btn, &QPushButton::clicked, &Widget::on_btn_clicked_static);

		//全局函数作为槽函数
		connect(m_btn, &QPushButton::clicked, on_btn_clicked_global);

		//把lambda表达式作为槽函数
		connect(m_btn, &QPushButton::clicked, [this] (){
			qDebug() << "lambda" << m_btn->text();
			});

		//注意：
		//1.槽函数返回值类型必须是void
		//2.槽函数的参数个数不能多于信号的参数个数，不过可以少
		//3.信号也可以作为槽函数

	}
public slots://成员函数作为槽函数时，最好有这个
	void on_btn_clicked() {
		qInfo() << "clicked";
	}
	void on_btn_pressed() {
		//断开连接
		disconnect(m_btn, &QPushButton::released, this, &Widget::on_btn_released);
		disconnect(m_con);
		qInfo() << "pressed";
	}
	void on_btn_released() {
		qInfo() << "released";
	}

	static void on_btn_clicked_static() {
		qDebug() << __FUNCTION__;
	}

private:
	QPushButton* m_btn{};
	QMetaObject::Connection m_con{};
};

int main(int argc, char* argv[]) {

	QApplication a(argc, argv);

	Widget w;
	w.show();

	return a.exec();
}
//如果把类和main写在了同一个文件，那么你就必须在代码的最后加上 #include[空格]"文件名.moc"
//这行预处理指令，告诉moc这个文件需要进行元编译，以实现 Q_OBJECT 宏中声明的函数
#include "main.moc"
