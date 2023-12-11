#include "Widget.h"

Widget::Widget(QWidget* parent)
	:QWidget(parent)
	,m_subWidget(new SubWidget)
	,m_cutBtn(new QPushButton("点击切换到子窗口",this))
{
	setWindowTitle("主窗口");
	resize(640, 480);
	//
	connect(m_cutBtn, &QPushButton::clicked, [=]() {
		this->hide();
		m_subWidget->show();
		});

	//连接子窗口的信号
	connect(m_subWidget, &SubWidget::showMainWidget, [=]() {
		//显示主窗口
		this->show();
		m_subWidget->hide();//注意！既然已经发送信号了，所以操作应当都在这里！！！
		});
}