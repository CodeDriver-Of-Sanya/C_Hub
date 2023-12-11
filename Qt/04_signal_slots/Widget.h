#ifndef WIDGET_H_
#define WIDGET_H_
#include<qwidget.h>
#include<qpushbutton.h>
#include"SubWidget.h"

class Widget : public QWidget {
	Q_OBJECT
public:
	Widget(QWidget* parent = nullptr);
private:
	SubWidget* m_subWidget{};
	QPushButton* m_cutBtn{};
};
#endif // !WIDGET_H_
