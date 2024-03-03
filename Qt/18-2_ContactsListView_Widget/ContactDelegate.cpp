#include "ContactDelegate.h"
#include"Contact.h"
#include<QStyleOptionViewItem>
#include<QPainter>

ContactDelegate::ContactDelegate(QObject* parent)
	:QStyledItemDelegate(parent)
{

}

void ContactDelegate::paint(QPainter* p, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	auto c = index.data(Qt::userRole).value<Contact*>();
	if (!c)
	{
		QStyledItemDelegate::paint(p, option, index);
		return;
	}
	p->drawPixmap()
}

QSize ContactDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	return QSize(option.rect.width(), 60);
}
