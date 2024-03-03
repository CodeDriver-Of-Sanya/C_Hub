#include "MainWindow.h"
#include<qpushbutton.h>
#include<qpainter.h>

MainWindow::MainWindow(QWidget* parent)
	:QWidget(parent)
{
	resize(640, 480);
	auto btn = new QPushButton("绘图", this);
	//产生图片的工作类
	m_worker.moveToThread(&m_thr);
	connect(btn, &QPushButton::clicked, &m_worker, &MyWorker::drawImage);
	m_thr.start();
	
	connect(&m_worker, &MyWorker::newImage, [=](const QImage& img)
		{
			m_img = img;
			update();
		});
	connect(&m_thr, &QThread::finished, [=]()
		{
			qDebug() << "m_thr finished";
		});
}

void MainWindow::paintEvent(QPaintEvent* pe)
{
	QPainter p(this);
	p.drawImage(0, 0, m_img);
}

void MainWindow::closeEvent(QCloseEvent* ce)
{
	m_thr.quit();
}
