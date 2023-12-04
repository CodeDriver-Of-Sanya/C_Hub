#include "Sprite.h"

Sprite::Sprite(const QString& filename, const QSize& size)
{
	setPixmap(filename, size);
}

void Sprite::setPixmap(const QString& filename, const QSize& size)
{
	m_pixmap.load(filename);
	if (size.isValid()) {
		m_pixmap = m_pixmap.scaled(size);
	}
}

QSize Sprite::size() const
{
	if (m_pixmap.isNull()) {
		return QSize();
	}
	return m_pixmap.size();
}

void Sprite::update()
{
	float x = m_pos.x();
	float y = m_pos.y();
	x += m_velocity.x() * m_speed;
	y += m_velocity.y() * m_speed;
	m_pos = { x,y };
}

void Sprite::render(QPainter* p)
{
	p->drawPixmap(m_pos.toPoint(), m_pixmap);
}
