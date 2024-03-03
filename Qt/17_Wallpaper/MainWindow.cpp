#include "MainWindow.h"
#include"Util/EventFilterObject.h"
#include <qpainter.h>
#include<qtimer.h>
#include<QMouseEvent>
#include<qfile.h>

MainWindow::MainWindow(QWidget* parent)
	:QWidget(parent)
{
	m_modelId = 0;
	setFixedSize(350, 1300);
	//去掉边框+顶置窗口
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	//设置背景透明
	setAttribute(Qt::WA_TranslucentBackground);
	//安装过滤器（实现左键鼠标拖动）(可以不指定父对象：因为确实是要从软件的开始到软件的关闭，不指定父对象造成的内存泄露可以忽略不记)
	installEventFilter(new EventFilterObject);

	auto timer_frameIndex = new QTimer(this);
	//用qoverload才能调用无参版本的update函数
	timer_frameIndex->callOnTimeout(this, QOverload<>::of(&MainWindow::update));
	timer_frameIndex->start(500);

	initUI();
}

void MainWindow::initUI()
{
	m_closeBtn = new QPushButton(this);
	m_closeBtn->setObjectName("closeBtn");
	m_settingsBtn = new QPushButton(this);
	m_settingsBtn->setObjectName("settingsBtn");

	m_settingsBtn->move(35, 0);

	//初始化设置窗口
	m_settingsDlg = new SettingsDlg(this);

	QFile style_btn(":/Resource/button/style.css");
	if (!style_btn.open(QFile::ReadOnly))
	{
		qWarning() << "按钮样式表打开失败";
		return;
	}
	setStyleSheet(style_btn.readAll());

	//关联事件
	connect(m_closeBtn, &QPushButton::clicked, this, &QWidget::close);
	connect(m_settingsBtn, &QPushButton::clicked, m_settingsDlg, &QDialog::exec);
	//根据设置来更改展示模型的样式
	connect(m_settingsDlg, &SettingsDlg::modelChanged, [=](int id)
		{
			m_modelId = id;
		});
	

}

void MainWindow::paintEvent(QPaintEvent* pe)
{
	QPainter painter(this);

	QString pixName = QString("%1.png").arg(m_frameIndex);

	if (0 == m_modelId)
		painter.drawPixmap(0, 0, QPixmap(":/Resource/desktopRole/littleBoy/" + pixName));
	else if (1 == m_modelId)
		painter.drawPixmap(0, 0, QPixmap(":/Resource/desktopRole/summerGril/" + pixName));

	m_frameIndex = (m_frameIndex + 1) % 6;
	//qWarning() << m_frameIndex;
}

void MainWindow::mouseReleaseEvent(QMouseEvent* me)
{
	if (me->button() == Qt::RightButton)
	{
		m_closeBtn->setHidden(!m_closeBtn->isHidden());
		m_settingsBtn->setHidden(!m_settingsBtn->isHidden());
	}
}
