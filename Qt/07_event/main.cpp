#include<QApplication>
#include<QWidget>
#include<QMouseEvent>
#include<qpushbutton.h>
#include<QMessageBox>
#include<qtimer.h>

//去掉黑窗口
//#pragma comment(linker,"/subSystem:windows /entry:mainCRTStartup")

class Button:public QPushButton
{
	Q_OBJECT
public:
	Button(QWidget* parent = nullptr)
		:QPushButton(parent)
	{

	}
private:
	//常用的事件最好 记下来 并写在 private 里
	//重写了父类的虚函数，不再由父类实现
	//按钮点击信号，是在mousePressEvent函数里触发的
	//自己重写了，就代表着信号触发也要全部自己手写吗？
	//不用，先把自己想要自定义的干完，剩下的传到父类的函数里调用父类的就可以了
	void mousePressEvent(QMouseEvent* e) override
	{
		if (e->button() == Qt::MouseButton::LeftButton) {
			qInfo() << "cilcked-mpe";
		}
		//干完自己的，剩下的传给父类函数
		QPushButton::mousePressEvent(e);
	}
};

class Widget :public QWidget {
	Q_OBJECT
public:
	QPushButton* m_btn{};
	Widget(QWidget* parent = nullptr)
		:QWidget(parent)
		,m_btn(new QPushButton("X", this))
	{
		m_btn->resize(50, 50);
		m_btn->move(QPoint(width() - m_btn->width(), 0));
		resize(640, 480);
		auto btn = new Button(this);
		btn->setText("hello");
		connect(btn, &QPushButton::clicked, []
			{
				qInfo() << "cilcked-connect";
			});

		//设置鼠标追踪（用于监听鼠标移动事件）
		setMouseTracking(true);//默认是关闭
	}
	//处理一下鼠标点击事件
	//重写虚函数即可，函数原型必须与父类中的虚函数完全一致
	void mousePressEvent(QMouseEvent* e) {
		//判断下是哪个键按下了
		if (e->button() == Qt::MouseButton::LeftButton) {
			qDebug() << "左键被按下，相对于当前窗口的按下的位置：" << e->pos() << "相对于屏幕的按下位置：" << e->globalPos();
		}
	}

	//鼠标 抬起（按下之后的动作） 事件
	void mouseReleaseEvent(QMouseEvent* e)override
	{

	}

	//鼠标 移动 事件
	void mouseMoveEvent(QMouseEvent* e)override
	{
		//按下右键并且移动
		if (e->buttons() & Qt::RightButton) {
			qInfo() << "右键并且移动";
		}
		//按下左键并且移动
		if (e->buttons() & Qt::LeftButton) {
			qInfo() << "左键并且移动";
		}
		//直接移动
		qInfo() << "移动";
	}

	//鼠标 双击 事件
	void mouseDoubleClickEvent(QMouseEvent* e)override {

	}

	//中键滚轮
	void wheelEvent(QWheelEvent* e) override{
		//判断滚轮的方向
		qInfo() << e->angleDelta().x() << e->angleDelta().y();
	}

	//键盘按键事件
	//按下
	void keyPressEvent(QKeyEvent* e)override {
		qInfo() << e->key() << Qt::Key(e->key());
		if (e->modifiers()&Qt::KeyboardModifier::ControlModifier && e->key() == Qt::Key_A) {
			qInfo() << "全选";
		}
		if (e->matches(QKeySequence::StandardKey::Save)) {
			qInfo() << "保存";
		}
	}
	//抬起
	void keyReleaseEvent(QKeyEvent* e)override {

	}

	//窗口关闭事件
	void closeEvent(QCloseEvent* e)override
	{
		auto ret = QMessageBox::question(this, "确定要关闭窗口吗？","你真的确定要关闭窗口吗？");
		qInfo() << ret;
		if (ret == QMessageBox::StandardButton::Yes) {
			//接受事件
			e->accept();
			//执行操作。。。
		}
		else {
			//忽略事件,啥也不干
			e->ignore();
		}
	}

	//当窗口大小改变的时候调用
	void resizeEvent(QResizeEvent* e)override
	{
		m_btn->move(QPoint(e->size().width() - m_btn->width(), 0));
	}

};

class SWidget :public QWidget {
	Q_OBJECT
public:
	SWidget(QWidget* parent = nullptr)
		:QWidget(parent)
	{
		//两种定时器

		//1.QTimer
		auto timer = new QTimer(this);
		//开启定时器，500ms触发一次
		timer->start(500);
		//超时执行...
		timer->callOnTimeout([] 
			{
				qInfo() << "update";
			});
		//只触发一次的事件
		QTimer::singleShot(1000, [] {qInfo() << "once"; });

		//2.定时器事件
		//开启定时器,因为可以开启多个，所以要接收返回值，也就是定时器ID做区分
		timer_id1 = startTimer(1500);
		timer_id2 = startTimer(2000);
	}
	void timerEvent(QTimerEvent* e)override
	{
		static int i = 0;
		if (i == 5) {
			killTimer(e->timerId());
		}
		if (e->timerId() == timer_id1) {
			qInfo() << "id1";
		}
		if (e->timerId() == timer_id2) {
			qInfo() << "id2";
		}

		i++;
	}

	int timer_id1;
	int timer_id2;

};



class MWidget :public QWidget {
	Q_OBJECT
public:
	MWidget(QWidget* parent = nullptr)
		:QWidget(parent)
	{

	}
	//所有的事件处理函数都是从event()事件派发函数调用的

};

int main(int argc, char* argv[]) {

	QApplication a(argc, argv);

	MWidget w;
	w.show();

	return a.exec();
}

#include "main.moc"