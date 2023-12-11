#include "SubWidget.h"

SubWidget::SubWidget(QWidget* parent)
	:QWidget(parent)
	,m_reBtn(new QPushButton("点击切换到主窗口",this))
{
	setWindowTitle("子窗口");
	resize(300, 300);
	//connect(m_reBtn, &QPushButton::clicked, [=]() {
	//	this->hide();
	//	//拿不到主窗口，
	//	//可以考虑发送信号给主窗口，主窗口接收并调用自身show出来
	//	emit showMainWidget();
	//
	//	});
	//上面的简单写：
	connect(m_reBtn, &QPushButton::clicked, this, &SubWidget::showMainWidget);
}
