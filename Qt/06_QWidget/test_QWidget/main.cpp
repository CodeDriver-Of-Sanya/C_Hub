#include<QApplication>
#include<QWidget>
#include<qpushbutton.h>

//去掉黑窗口
//#pragma comment(linker,"/subSystem:windows /entry:mainCRTStartup")

class Widget :public QWidget {
	Q_OBJECT
public:
	Widget(QWidget* parent = nullptr)
		:QWidget(parent) 
		, m_btn(new QPushButton("获取窗口QRect",this))
		, m_closeBtn(new QPushButton("X", this))
		, m_maxBtn(new QPushButton("口", this))
		, m_minBtn(new QPushButton("-", this))
		, m_fullScreenBtn(new QPushButton("大", this))
	{
		resize(640, 480);
		//窗口全屏、正常、最大化、最小化
		//设置按钮大小
		m_closeBtn->setFixedSize(32, 32);
		m_maxBtn->setFixedSize(32, 32);
		m_minBtn->setFixedSize(32, 32);
		m_fullScreenBtn->setFixedSize(32, 32);
		//将按钮放到右上角
		m_closeBtn->move(width() - m_closeBtn->width(),0);
		m_maxBtn->move(width() - m_closeBtn->width()*2,0);
		m_minBtn->move(width() - m_closeBtn->width()*3,0);
		m_fullScreenBtn->move(width() - m_fullScreenBtn->width()*4,0);
		//关联事件
		connect(m_closeBtn, &QPushButton::clicked, [=] {
			close();
			});
		connect(m_maxBtn, &QPushButton::clicked, [=] {
			//如果点击按钮时，窗口就是最大化，那就恢复正常窗口大小
			if (isMaximized()) {
				showNormal();
			}
			else {
				//如果不是，那就最大化
				showMaximized();
			}
			
			});
		connect(m_minBtn, &QPushButton::clicked, [=] {
			showMinimized();
			});
		connect(m_fullScreenBtn, &QPushButton::clicked, [=] {
			showFullScreen();
			});
		connect(&subWindow, &QWidget::destroyed, [] {
			qDebug() << "subWindow destoryed";
			});

		//隐藏、显示、可见、关闭
		subWindow.show();
		connect(m_btn, &QPushButton::clicked, [=] {
			//隐藏和显示
			/*if (subWindow.isHidden()) {
				subWindow.show();
			}
			else {
				subWindow.hide();
			}*/
			//可见和关闭(常用show和hide)
			/*if (subWindow.isVisible()) {
				subWindow.setVisible(false);
			}
			else {
				subWindow.setVisible(true);
			}*/
			
			//这样关了但是不会销毁
			//因为如果你的程序有多个窗口，那么当你关闭某一个窗口时，不会关闭，而是隐藏
			//subWindow.close();
			//但是可以通过设置实现让窗口调用close时销毁
			//subWindow.setAttribute(Qt::WA_DeleteOnClose);
			//subWindow.close();
			//但是为了安全，应该使用QPointer

			});

	}
	void test1(){
		//设置窗口标题（默认为项目名称）
		this->setWindowTitle("我的第一个窗口");
		//设置窗口图标
		//绝对路径
		//this->setWindowIcon(QIcon("C:\\Users\\zmq\\coding\\Qt\\06_QWidget\\Resource\\icon.jpg"));
		//资源文件路径
		this->setWindowIcon(QIcon(":/Resource/icon.jpg"));

		//窗口大小、位置
		//设置窗口大小
		this->resize(640, 480);
		//获取
		qDebug() << width() << this->height() << size();
		//注意，在窗口没有创建完成之前，获取到的坐标总是0
		qDebug() << "窗口没创建完成之前：" << geometry() << frameGeometry() << rect();

		connect(m_btn, &QPushButton::clicked, [=] {
			qDebug() << "窗口创建完成之后：" << geometry() << frameGeometry() << rect();
			});

		//移动窗口位置
		//move(0, 0);//可以得知是包括标题栏移动的
		//设置固定大小（用户不能用鼠标拖动改变大小）
		setFixedSize(300, 300);
		//设置 最小和最大 大小
		setMinimumSize(200, 200);//最小
		setMaximumSize(800, 800);//最大
		//设置几何(以客户区左上角为变换点)
		setGeometry(50, 50, 150, 150);
	}
private:
	QPushButton* m_btn{};
	QPushButton* m_closeBtn{};
	QPushButton* m_maxBtn{};
	QPushButton* m_minBtn{};
	QPushButton* m_fullScreenBtn{};
	QWidget subWindow;
};

int main(int argc, char* argv[]) {

	QApplication a(argc, argv);

	Widget w;
	w.show();

	return a.exec();
}

#include "main.moc"