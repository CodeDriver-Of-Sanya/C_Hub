#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_
#include<qwidget.h>
#include<qthread.h>
#include"MyWorker.h"

class MainWindow : public QWidget
{
public:
	MainWindow(QWidget* parent = nullptr);
protected:
	void paintEvent(QPaintEvent* pe)override;
	void closeEvent(QCloseEvent* ce)override;
private:
	MyWorker m_worker;
	QThread m_thr;
	QImage m_img;
};

#endif // !_MAINWINDOW_H_
