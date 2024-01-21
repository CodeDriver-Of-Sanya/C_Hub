#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_
#include <qwidget.h>
#include<qpushbutton.h>

class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);
	void initUI();

protected:
	void paintEvent(QPaintEvent* pe) override;
	void mouseReleaseEvent(QMouseEvent* me)override;

private:
	int m_frameIndex{};//动图帧索引
	int m_modelId{};//模型ID

	QPushButton* m_closeBtn{};
	QPushButton* m_settingsBtn{};
};

#endif // !_MAINWINDOW_H_
