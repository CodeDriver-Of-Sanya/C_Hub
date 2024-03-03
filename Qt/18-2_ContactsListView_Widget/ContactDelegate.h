#ifndef CONTACTDELEGATE_H_
#define CONTACTDELEGATE_H_

#include<QStyledItemDelegate>

class ContactDelegate :public QStyledItemDelegate
{
public:
	ContactDelegate(QObject* parent = nullptr);
protected:
	void paint(QPainter* p, const QStyleOptionViewItem& option, const QModelIndex& index)const override;
	QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index)const override;
};

#endif // !CONTACTDELEGATE_H
