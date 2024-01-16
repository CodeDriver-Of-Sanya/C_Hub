#ifndef _WINDEPLOYQTUI_H_
#define _WINDEPLOYQTUI_H_

#include<qwidget.h>
#include<qcombobox.h>

class WindeployQtUI :public QWidget
{
	Q_OBJECT
public:
	WindeployQtUI(QWidget* parent = nullptr);
	void init();

private:
	QComboBox* m_QtVersomListCbx{};
	QComboBox* m_QtKidsListCbx{};
};

#endif // !_WINDEPLOYQTUI_H_
