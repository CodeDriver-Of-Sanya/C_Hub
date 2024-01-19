#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_
#include <qwidget.h>

class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);
	
private:
	void paintEvent(QPaintEvent* pe) override;

private:
	int m_frameIndex{};//动图帧索引
};

#endif // !_MAINWINDOW_H_
