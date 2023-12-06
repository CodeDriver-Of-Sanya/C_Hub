#include "PlayerPlane.h"
#include "EntityManager.h"

PlayerPlane::PlayerPlane()
{
}

bool PlayerPlane::emitBullet()
{
    Bullet* b = new Bullet;
    b->setPixmap(":/Resource/images/bullet1.png");
    b->setPos(pos() + QVector2D{ size().width() / 2.0f,0.0f });
    b->velocity().setY(-1);
    b->setSpeed(2);
    b->setType(bullet);
    eMgr.addEntity(b);

    return false;
}
