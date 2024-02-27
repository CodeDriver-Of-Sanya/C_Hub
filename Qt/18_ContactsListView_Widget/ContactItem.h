#ifndef CONTACTITEM_H_
#define CONTACTITEM_H_

#include"Contact.h"
#include <qwidget.h>
#include<qlabel.h>
#include<qpushbutton.h>
#include<qstandarditem>


class ContactItem :public QWidget,public QStandardItem
{
public:
	ContactItem(Contact* ct,QWidget* parent = nullptr);
protected:
	QSize sizeHint()const override;
private:
	void initUI();
	void updateContactDisplay();

	QLabel* m_profileLab{};
	QLabel* m_noteNameLab{};
	QLabel* m_userNameLab{};
	QLabel* m_typeLab{};
	QLabel* m_signatureLab{};
	Contact* m_contact{};

};

#endif // !CONTACTITEM_H_
