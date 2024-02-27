#include "ContactItem.h"
#include<qgridlayout.h>

ContactItem::ContactItem(Contact* ct,QWidget* parent)
	:QWidget(parent)
	,m_contact(ct)
{
	this->setData(QVariant::fromValue(m_contact), Qt::UserRole);
	initUI();
	updateContactDisplay();
}

QSize ContactItem::sizeHint() const
{
	//先获取本身的原先的size
	auto size = QStandardItem::sizeHint();
	return QSize(size.width(),60);
}

void ContactItem::initUI()
{
	setSizeHint(QSize(width(), 60));
	m_profileLab=new QLabel;
	m_profileLab->setFixedSize(40, 40);
	m_profileLab->setScaledContents(true);

	m_noteNameLab = new QLabel;
	m_userNameLab = new QLabel;
	m_typeLab = new QLabel;
	m_signatureLab = new QLabel;

	auto hlayout = new QHBoxLayout;
	hlayout->addWidget(m_noteNameLab);
	hlayout->addWidget(m_userNameLab);
	hlayout->addWidget(m_typeLab);
	hlayout->addStretch();

	auto glayout = new QGridLayout(this);
	glayout->addWidget(m_profileLab, 0, 0, 2, 1);
	glayout->addLayout(hlayout, 0, 1);
	glayout->addWidget(m_signatureLab, 1, 1);

}

void ContactItem::updateContactDisplay()
{
	if (!m_contact)return;

	m_profileLab->setPixmap(QPixmap(m_contact->profilePath));
	m_userNameLab->setText(m_contact->userName);
	m_noteNameLab->setText(m_contact->noteName);
	m_signatureLab->setText(m_contact->signature);

	switch (m_contact->type)
	{
	case Contact::NONE:
		break;
	case Contact::VIP:
		m_typeLab->setPixmap(QPixmap(":/Resource/images/vip.png"));
		break;
	case Contact::SVIP:
		m_typeLab->setPixmap(QPixmap(":/Resource/images/svip.png"));
		break;
	}
}
