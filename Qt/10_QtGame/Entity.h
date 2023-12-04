#ifndef ENTITY_H_
#define ENTITY_H_
#include<qpainter.h>
class Entity
{
public:
	virtual ~Entity() {};
	//抽象函数（接口类）
	virtual void update() = 0;
	virtual void render(QPainter* p) = 0;

	bool active()const { return m_active; }
	void destory() { m_active = false; }

	int type()const { return m_type; }
	void setType(int type) { m_type = type; }

private:
	bool m_active{ true };//实体是否是活动的
	int m_type{};//实体类型
};

#endif // ENTITY_H_
