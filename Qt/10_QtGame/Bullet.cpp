#include "Bullet.h"
#include"QGame.h"

void Bullet::update()
{
	Sprite::update();

	//如果子弹超出边界，那么让子弹消失
	if (pos().x() > QGAME->width() || pos().x() < 0 - size().width()
		|| pos().y() > QGAME->height() || pos().y() < 0 - size().height()) {
		destory();
	}
}
