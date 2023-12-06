#include "QGame.h"
#include"Sprite.h"
#include "EntityManager.h"]
#include "PlayerPlane.h"
#include "Map.h"

#include <qapplication.h>
#include<qpainter.h>
#include<QKeyEvent>
#include<qrandom.h>

#define qRandom(min,max) QRandomGenerator::global()->bounded(min, max)

static QGame* ins = nullptr;
QGame* QGame::instance()
{
	return ins;
}

QGame::QGame(QWidget* parent)
	:QWidget(parent)
	,m_mainLoopTimer(new QTimer(this))
{
	if (!ins) {
		ins = this;
	}
	else {
		qErrnoWarning("There is already an instance of QGame");
	}
}

QGame::~QGame()
{
	clean();
}

PlayerPlane* player;

void QGame::init(const QSize& size, const QString& title)
{
	setFixedSize(size);
	setWindowTitle(title);
	m_isRunning = true;
	setMouseTracking(true);

	eMgr.addEntity(new Map);
	player = eMgr.addEntity(new PlayerPlane(":/Resource/images/hero1.png"));
	player->setType(Player);
}

void QGame::clean()
{
}

void QGame::update(int)
{
	eMgr.refresh();
	eMgr.update();
	static int gapCnt = 0;
	//子弹生成时间间隔控制
	if (gapCnt % player->gap() == 0) {
		player->emitBullet();
	}
	gapCnt++;

	//敌机生成时间间隔控制
	if (gapCnt % 50 == 0) {
		QStringList efile = { ":/Resource/images/enemy1.png",":/Resource/images/enemy2.png" };
		auto enemy = new Sprite(efile[qRandom(0,2)]);
		enemy->velocity().setY(1);
		enemy->setPos(QVector2D(qRandom(0, width()- enemy->size().width()), 0 - enemy->size().height()));
		enemy->setType(Enemy);
		eMgr.addEntity(enemy);
	}

	//获取子弹列表
	auto bullet_list = eMgr.getSpriteByType(bullet);
	//获取敌机列表
	auto enemy_list = eMgr.getSpriteByType(Enemy);

	for (auto& e : enemy_list) {
		for (auto& b : bullet_list) {
			if (e->collider().intersects(b->collider())) {
				e->destory();
				b->destory();
				break;
			}
		}
	}

}

void QGame::render(QPainter* p)
{
	eMgr.render(p);
}

bool QGame::isRunning() const
{
	return m_isRunning;
}

void QGame::quit()
{
	m_isRunning = false;
}

void QGame::run()
{
	show();
	//在游戏中开始游戏就是进入游戏主循环
	//主循环不能直接用while(1)设置死循环
	//用定时器实现游戏主程序(先连接再启动)
	m_mainLoopTimer->callOnTimeout([=] 
		{
			//如果游戏没有在运行，那么就结束游戏
			if (!isRunning()) {
				m_mainLoopTimer->stop();
				qApp->quit();
			}
			//如果正常运行

			//先更新游戏
			update(0);
			//窗口重绘
			QWidget::update();
			//qDebug() << "running";
		});
	m_mainLoopTimer->start(m_fps);
}

void QGame::paintEvent(QPaintEvent* e)
{
	QPainter p(this);
	render(&p);
}

void QGame::keyPressEvent(QKeyEvent* ke)
{
	switch (ke->key())
	{
	case Qt::Key_W:
	case Qt::Key_Up:
		player->velocity().setY(-1);
		break;
	case Qt::Key_S:
	case Qt::Key_Down:
		player->velocity().setY(1);
		break;
	case Qt::Key_A:
	case Qt::Key_Left:
		player->velocity().setX(-1);
		break;
	case Qt::Key_D:
	case Qt::Key_Right:
		player->velocity().setX(1);
		break;
	default:
		break;
	}
}

void QGame::keyReleaseEvent(QKeyEvent* ke)
{
	switch (ke->key())
	{
	case Qt::Key_W:
	case Qt::Key_Up:
	case Qt::Key_S:
	case Qt::Key_Down:
		player->velocity().setY(0);
		break;
	case Qt::Key_A:
	case Qt::Key_Left:
	case Qt::Key_D:
	case Qt::Key_Right:
		player->velocity().setX(0);
		break;
	default:
		break;
	}
}

void QGame::mouseMoveEvent(QMouseEvent* me)
{
	auto s = player->size() / 2;
	player->setPos(me->pos() - QPoint{ s.width(),s.height() });
}
