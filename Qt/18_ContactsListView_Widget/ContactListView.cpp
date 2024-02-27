#include "ContactListView.h"

ContactListView::ContactListView(QWidget* parent)
	:QListView(parent)
	,m_model(new QStandardItemModel(this))
{
	setModel(m_model);
	initUI();
	connect(this, &QListView::clicked, this, &ContactListView::onClicked);
}

void ContactListView::onClicked(const QModelIndex& index)
{
	Contact* c = index.data(Qt::UserRole).value<Contact*>();
	if (!c)
	{
		qWarning() << "联系人信息获取失败";
		return;
	}
	qDebug() << c->userName << c->noteName << c->signature;
}

void ContactListView::initUI()
{
	//准备联系人
	m_contacts.emplace_back(new Contact("maye", "顽石老师"));
	m_contacts.emplace_back(new Contact("winter", "zmq"));
	m_contacts.emplace_back(new Contact("AAA", "小白"));

	for (auto& c : m_contacts)
	{
		
		auto itemWidget = new ContactItem(c.get());
		m_model->appendRow(itemWidget);
		this->setIndexWidget(itemWidget->index(), itemWidget);
	}
}
