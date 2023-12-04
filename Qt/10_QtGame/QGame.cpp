#include "QGame.h"
#include"Sprite.h"

#include <qapplication.h>
#include<qpainter.h>
#include<QKeyEvent>

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

Sprite* player;

void QGame::init(const QSize& size, const QString& title)
{
	setFixedSize(size);
	setWindowTitle(title);
	m_isRunning = true;
	setMouseTracking(true);

	player = new Sprite(":/Resource/images/hero1.png");
}

void QGame::clean()
{
}

void QGame::update(int)
{
	player->update();
}

void QGame::render(QPainter* p)
{
	player->render(p);
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
