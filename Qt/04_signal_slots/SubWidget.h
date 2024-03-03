#ifndef SUBWIDGET_H_
#define SUBWIDGET_H_
#include<qwidget.h>
#include<qpushbutton.h>
class SubWidget : public QWidget {
	Q_OBJECT
public:
	SubWidget(QWidget* parent = nullptr);
signals:
	void showMainWidget();
private:
	QPushButton* m_reBtn{};
};
#endif // !WIDGET_H_