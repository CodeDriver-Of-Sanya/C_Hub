#include "EventFilterObject.h"
#include<QMouseEvent>
#include<qwidget.h>
#include<QGraphicsDropShadowEffect>

EventFilterObject::EventFilterObject(QObject* parent)
	:QObject(parent)
{
	QWidget* w = dynamic_cast<QWidget*>(parent);
	if (w)
	{
		//实现窗口阴影特效
		auto effect = new QGraphicsDropShadowEffect(this);
		effect->setOffset(0);
		effect->setBlurRadius(10);
		w->setGraphicsEffect(effect);
	}
	
	
}

bool EventFilterObject::eventFilter(QObject* watch, QEvent* e)
{
	QMouseEvent* me = dynamic_cast<QMouseEvent*>(e);
	if (e->type() == QEvent::MouseButtonPress)
	{
		m_mousePressPos = me->pos();
	}
	else if (e->type() == QEvent::MouseMove && (me->buttons() & Qt::MouseButton::LeftButton))
	{
		QWidget* w = dynamic_cast<QWidget*>(watch);
		if (w)
		{
			w->move(me->globalPos() - m_mousePressPos);
		}
		return true;
		
	}

	return false;
}
