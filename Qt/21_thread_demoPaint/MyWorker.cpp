#include "MyWorker.h"
#include<qpainter.h>
#include<qrandom.h>
#include<qdebug.h>
#include<qthread.h>

#define mrand(min,max) QRandomGenerator::global()->bounded(min,max)

void MyWorker::drawImage()
{
	QImage img(640,480,QImage::Format_RGBA8888);

	QPainter p(&img);
	p.setPen(QPen(QColor(mrand(0, 256), mrand(0, 256), mrand(0, 256)), 3));
	p.setBrush(QBrush(QColor(mrand(0, 256), mrand(0, 256), mrand(0, 256)), Qt::BrushStyle::Dense2Pattern));

	//随机生成四个点
	QPoint pos[] =
	{
		QPoint(mrand(0,640),mrand(0,480)),
		QPoint(mrand(0,640),mrand(0,480)),
		QPoint(mrand(0,640),mrand(0,480)),
		QPoint(mrand(0,640),mrand(0,480)),
		QPoint(mrand(0,640),mrand(0,480)),
		QPoint(mrand(0,640),mrand(0,480)),
		QPoint(mrand(0,640),mrand(0,480)),
		QPoint(mrand(0,640),mrand(0,480)),
		QPoint(mrand(0,640),mrand(0,480)),
		QPoint(mrand(0,640),mrand(0,480)),
		QPoint(mrand(0,640),mrand(0,480)),
		QPoint(mrand(0,640),mrand(0,480)),
	};
	p.drawPolygon(pos, 12);

	QThread::sleep(2);
	qDebug() << "绘图函数结束";

	emit newImage(img);
}
