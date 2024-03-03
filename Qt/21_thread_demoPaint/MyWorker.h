#ifndef _MYWORKER_H_
#define _MYWORKER_H_
#include<qobject.h>
#include<qimage.h>

class MyWorker : public QObject
{
	Q_OBJECT
public:
	void drawImage();
signals:
	void newImage(const QImage& img);

private:

};

#endif // !_MYWORKER_H_

