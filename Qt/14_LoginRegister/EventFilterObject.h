#ifndef _EVENTFILTEROBJECT_H_
#define _EVENTFILTEROBJECT_H_
#include <qobject.h>
#include<qpoint.h>

class EventFilterObject :public QObject
{
public:
	EventFilterObject(QObject* parent = nullptr);
	
private:
	bool eventFilter(QObject* watch, QEvent* e)override;

	QPoint m_mousePressPos;
};


#endif // !_EVENTFILTEROBJECT_H_
