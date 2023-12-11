#ifndef SPRITE_H_
#define SPRITE_H_

#include"Entity.h"
#include<QVector2D>

class Sprite : public Entity
{
public:
	Sprite() = default;
	Sprite(const QString& filename, const QSize& size = QSize());

	QVector2D pos()const { return m_pos; }
	void setPos(float x, float y) { m_pos = { x,y }; }
	void setPos(const QPointF& pos) { m_pos = { (float)pos.x(),(float)pos.y() }; }
	void setPos(const QVector2D& pos) { m_pos = pos; }
	void moveBy(float dx, float dy) { m_pos += {dx, dy}; }

	void setPixmap(const QString& filename, const QSize& size = QSize());
	QPixmap pixmap()const { return m_pixmap; }
	QSize size()const;

	void setVelocity(float vx, float vy) { m_velocity = { vx,vy }; }
	QVector2D& velocity() { return m_velocity; }

	void setSpeed(int n) { m_speed = n; }

	int gap()const { return m_gap; }
	void setGap(int g) { m_gap = g; }

	QRect collider()const { return m_collider; }

public:
	// 通过 Entity 继承
	void update() override;
	void render(QPainter* p) override;
private:
	QPixmap m_pixmap;
	QVector2D m_pos;
	float m_speed{ 1.5 };//子弹移动速度
	int m_gap{ 50 };//子弹发射间隙
	QVector2D m_velocity; //分量

	QRect m_collider{};//碰撞器
};



#endif // SPRITE_H_
