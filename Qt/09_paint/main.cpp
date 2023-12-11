#include<QApplication>
#include<QWidget>
#include<qpainter.h>
#include<qtimer.h>

//去掉黑窗口
#pragma comment(linker,"/subSystem:windows /entry:mainCRTStartup")

class Widget :public QWidget
{
	Q_OBJECT
public:
	Widget(QWidget* parent = nullptr)
		:QWidget(parent)
	{
		resize(800, 600);

		auto jiaoduTimer = new QTimer(this);
		jiaoduTimer->callOnTimeout([=] {
			//如果更新绘图，不能手动调用paintEvent
			//必须调用update函数
			this->update();
			});
		jiaoduTimer->start(1000 / 60);
	}
protected:
	//所有在Widget上面的绘制，必须放到paintEvent函数里面，paintEvent会在需要绘图时自动调用
	void paintEvent(QPaintEvent* pe)override
	{
		qInfo() << __FUNCTION__;
		//1.创建一个画家
		QPainter painter;
		//设置绘制设备（让画家知道画在哪）
		painter.begin(this);

		//绘制直线
		//painter.drawLine(0, 0, width(), height());

		//绘制折线
		QList<QPointF> points = {//将下面的点一对一对连起来
			{width() / 2.0,height() / 2.0},
			{width() * 3 / 4.0,height() * 3 / 4.0},
			{width() * 3 / 4.0,height() * 3 / 4.0},
			{width() * 1 / 4.0,height() * 3 / 4.0},
			{width() * 1 / 4.0,height() * 3 / 4.0},
			{width() / 2.0,height() / 2.0},
		};
		painter.drawLines(points);

		//画完之后让画家离开绘图设备
		painter.end();

		//也可以直接这样
		QPainter p(this);//这么写，就不用再设置begin和end了

		//penStyle();
		//capStyle();
		//joinSytle();
		//brushStyle();
		//linearGradient();
		//radialGradient();
		//transform(p);
		pixmap(&p);
	}

	//输出图片一般用这个
	void pixmap(QPainter* painter)
	{
		//加载图片
		QPixmap pix(":/images/zay.png");
		//在位置为（0，0）大小是 50x50（图片全部缩放进来） 的矩形中填充图片pix
		painter->drawPixmap(QRect(0, 0, 50, 50), pix);
		//在位置为（0，50）大小是 100x100（图片按原比例切割） 的矩形中填充图片pix
		painter->drawPixmap(0, 50, pix, 0, 0, 100, 100);
		//在位置为（0，150）大小是 100x100 的矩形中 填充 图片pix的 （100，100）到（300，300）的部分内容
		painter->drawPixmap(QRect(0, 150, 100, 100), pix, QRect(100, 100, 300, 300));
	}

	//这个是pixmap的父级，功能更多,主要用于绘图
	void image(QPainter* painter)
	{
		//painter->drawImage(0, 0, m_image);

	}


	qreal jiaodu = 0;
	//坐标系变换
	void transform(QPainter& p) {

		//平移
		p.translate(50, 50);
		//缩放
		p.scale(0.5, 0.5);
		//旋转
		//p.rotate(jiaodu++);
		//旋转等也可以这么写（功能更强大）
		QTransform t;
		t.rotate(jiaodu++, Qt::XAxis);
		//扭曲
		t.shear(0.5, 0);

		p.setTransform(t);
		
		
		QPixmap pic(":/images/zay.png");
		p.drawPixmap(0, 0, pic);

	}

	//设置绘画时的线条样式
	void penStyle()
	{
		QPainter painter(this);
		//设置渲染提示，Antialiasing高质量渲染(反锯齿)
		painter.setRenderHint(QPainter::RenderHint::Antialiasing);

		for (int i = 0; i < 6; i++)
		{
			painter.setPen(QPen(Qt::red, 5, Qt::PenStyle(i)));
			painter.drawLine(i * 50, 0, i * 50 + 100, 200);
		}
	}

	//设置笔尖样式
	void capStyle()
	{
		QPainter painter(this);
		painter.setRenderHint(QPainter::RenderHint::Antialiasing);

		painter.setPen(QPen(QBrush(Qt::red), 5, Qt::PenStyle::DotLine, Qt::PenCapStyle::FlatCap));
		painter.drawLine(0, 0, 100, 200);

		painter.setPen(QPen(QBrush(Qt::red), 5, Qt::PenStyle::DotLine, Qt::PenCapStyle::MPenCapStyle));
		painter.drawLine(100, 0, 100 + 100, 200);

		painter.setPen(QPen(QBrush(Qt::red), 5, Qt::PenStyle::DotLine, Qt::PenCapStyle::RoundCap));
		painter.drawLine(200, 0, 100 + 200, 200);

		painter.setPen(QPen(QBrush(Qt::red), 5, Qt::PenStyle::DotLine, Qt::PenCapStyle::SquareCap));
		painter.drawLine(300, 0, 100 + 300, 200);
	}

	//设置连接样式
	void joinSytle()
	{
		QPainter painter(this);
		painter.setRenderHint(QPainter::RenderHint::Antialiasing);

		int s[] = { Qt::MiterJoin, Qt::BevelJoin, Qt::RoundJoin , Qt::SvgMiterJoin, Qt::MPenJoinStyle };
		for (int i = 0; i < 5; i++)
		{
			painter.setPen(QPen(QBrush(Qt::red), 5, Qt::SolidLine, Qt::PenCapStyle::SquareCap, Qt::PenJoinStyle(s[i])));
			QPoint points[] = { {20 + i * 100,30},{50 + i * 100,60},{100 + i * 100,10} };
			painter.drawPolygon(points, 3);
		}
	}

	//设置画刷样式
	void brushStyle()
	{
		QPainter painter(this);

		painter.setPen(Qt::PenStyle::NoPen);
		painter.setBrush(QBrush(QPixmap(":/images/tiled.png")));

		int w = 150;
		int h = 150;
		for (int r = 0; r < 3; r++)
		{
			for (int c = 0; c < 5; c++)
			{
				//painter.setBrush(QBrush(Qt::GlobalColor::blue, Qt::BrushStyle(r * 5 + c)));
				painter.drawRect(c * w, r * h, w, h);
			}
		}
	}

	//设置线性渐变
	void linearGradient()
	{
		////指定在那两个点之间线性渐变(开始坐标和结束坐标)
		//QLinearGradient lgra(0, 0, 100, 100);
		////也可以在构造对象后通过函数，设置开始点和结束点
		////lgra.setStart(0, 0);
		////lgra.setFinalStop(100, 100);

		////用给定的位置(比例：0~1)和颜色设置过度点，在哪里切换颜色
		//lgra.setColorAt(0, qRgb(82, 113, 196));
		//lgra.setColorAt(0.48, qRgb(177, 159, 255));
		//lgra.setColorAt(1, qRgb(236, 161, 254));

		////指定如何填充渐变区域之外的区域。
		//lgra.setSpread(QGradient::RepeatSpread);

		int cx = width() / 2;
		int cy = height() / 2;
		//定义线性渐变
		QLinearGradient lgra(0, 0, 1, 0);
		lgra.setColorAt(0, Qt::blue);
		lgra.setColorAt(0.5, Qt::yellow);
		lgra.setColorAt(1, Qt::red);

		//指定如何填充渐变区域之外的区域。
		lgra.setSpread(QGradient::PadSpread);
		lgra.setCoordinateMode(QGradient::CoordinateMode::ObjectMode);

		QPainter painter(this);
		//把渐变色设置给画刷
		painter.setBrush(lgra);


		//绘制矩形，观察渐变区域之外的区域的填充
		//painter.drawRect(cx, cy, cx, cy);
		//painter.drawRect(0, 0, cx, cy);
		painter.drawRect(rect());
		//绘制圆形(这里一般和开始点和结束点的坐标对应)
		painter.drawEllipse(cx - 50, cy - 50, 100, 100);

		painter.drawRect(50, 50, 100, 100);
	}

	//设置径向渐变
	void radialGradient()
	{
		//指定以圆心和半径，以圆心为中心渐变
		QRadialGradient rgra(50, 50, 50);
		//也可以在构造对象后通过函数，设置开始点和结束点
		//rgra.setCenter(50, 50);
		//下面两个设置半径的功能一样 
		//rgra.setRadius(50);
		//rgra.setCenterRadius(50);

		rgra.setCenter(70, 70);
		//用给定的位置(比例：0~1)和颜色设置过度点，在哪里切换颜色
		rgra.setColorAt(0, qRgb(82, 113, 196));
		rgra.setColorAt(0.48, qRgb(177, 159, 255));
		rgra.setColorAt(1, qRgb(236, 161, 254));

		//指定如何填充渐变区域之外的区域。
		rgra.setSpread(QGradient::ReflectSpread);

		QPainter painter(this);
		//把渐变色设置给画刷
		painter.setBrush(rgra);
		//绘制矩形，观察渐变区域之外的区域的填充
		painter.drawRect(50, 50, 250, 250);
		//绘制圆形(这里一般和开始指定的渐变坐标一样)
		painter.drawEllipse(0, 0, 100, 100);
	}

};

int main(int argc, char* argv[]) {

	QApplication a(argc, argv);

	Widget w;
	w.show();

	return a.exec();
}

#include "main.moc"