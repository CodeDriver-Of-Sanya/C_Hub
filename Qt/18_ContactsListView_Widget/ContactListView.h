#ifndef CONTACTLISTVIEW_H
#define CONTACTLISTVIEW_H
#include"ContactItem.h"
#include<qlistview.h>
#include<memory>
#include<qstandarditemmodel.h>


class ContactListView :public QListView
{
public:
	ContactListView(QWidget* parent = nullptr);
public:
	void onClicked(const QModelIndex& index);
private:
	void initUI();
	std::vector<std::unique_ptr<Contact>> m_contacts;
	QStandardItemModel* m_model{};

};


#endif // !CONTACTLISTVIEW_H_
