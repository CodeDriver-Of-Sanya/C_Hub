#include "MainWindow.h"
#include <qpainter.h>

MainWindow::MainWindow(QWidget* parent)
	:QWidget(parent)
{
}

void MainWindow::paintEvent(QPaintEvent* pe)
{
	QPainter painter(this);

	QString pixName = QString("%1.png").arg(m_frameIndex);

	painter.drawPixmap(0, 0, QPixmap(":/Resource/desktopRole/littleBoy/"+pixName));
}
