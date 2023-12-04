#ifndef QGAME_H_
#define QGAME_H_
#include<qwidget.h>
#include<qtimer.h>

#define QGAME QGame::instance()

class QGame : public QWidget
{
	Q_OBJECT
public:

	static QGame* instance();

	QGame(QWidget* parent = nullptr);
	~QGame();

	//游戏初始化
	void init(const QSize& size, const QString& title);
	//游戏反初始化（清理）
	void clean();
	//更新游戏（界面）(int为占位参数，为了防止和QWidget的update函数重名)
	void update(int);
	//渲染（绘制）游戏
	void render(QPainter* painter);
	//判断游戏是否在运行
	bool isRunning()const;
	//退出游戏
	void quit();
	//运行游戏
	void run();
	
	//设置游戏帧率
	void setFPS(qreal fps) { m_fps = fps; };
	//获取游戏帧率
	qreal fps()const { return m_fps; };
protected:
	void paintEvent(QPaintEvent* e)override;
	void keyPressEvent(QKeyEvent* ke)override;
	void keyReleaseEvent(QKeyEvent* ke)override;
	void mouseMoveEvent(QMouseEvent* me)override;
private:
	bool m_isRunning = false;
	qreal m_fps{ 1000 / 60.0 };
	QTimer* m_mainLoopTimer{};
};
#endif
