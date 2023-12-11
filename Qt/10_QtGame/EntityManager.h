#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_

#include "Entity.h"
#include "Sprite.h"

#include<qlist.h>
#include <memory>

#define eMgr EntityManager::instance()

class EntityManager {
public:
	static EntityManager& instance() { static EntityManager em; return em; }
	void update() {
		for (auto& e :m_entities)
		{
			e->update();
		}
	}
	void render(QPainter* p) {
		for (auto& e : m_entities)
		{
			e->render(p);
		}
	}

	template<typename T = Entity>
	T* addEntity(T* e) {
		m_entities.emplaceBack(e);
		return e;
	}

	void refresh() {
		m_entities.removeIf([](Entity* e) {
			if (!e->active()) {
				delete e;
				return true;
			}
			return false;
			});
	}

	QList<Sprite*> getSpriteByType(int _type) {
		QList<Sprite*> sList;
		for (auto& e : m_entities) {
			if (e->type() == _type&&e->active()) {
				sList.append(dynamic_cast<Sprite*>(e));
			}
		}
		return sList;
	}

private:
	EntityManager() {};
	QList <Entity*> m_entities;
};

#endif // !ENTITYMANAGER_H_
