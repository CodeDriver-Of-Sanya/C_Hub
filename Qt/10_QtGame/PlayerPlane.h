#ifndef PLAYERPLAN_H_
#define PLAYERPLAN_H_

#include "Sprite.h"
#include"Bullet.h"
#include<array>//存储子弹

class PlayerPlane :public Sprite
{
public:
	using Sprite::Sprite;
	PlayerPlane();
	
	bool emitBullet();
};

#endif

