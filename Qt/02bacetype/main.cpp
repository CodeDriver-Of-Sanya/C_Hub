#include<QApplication>
#include<QWidget>
#include<qdebug.h>
#include<Qdate>
#include<qelapsedtimer.h>

//去掉黑窗口
#pragma comment(linker,"/subSystem:console /entry:mainCRTStartup")

void testTypeAndQByteArry();
void testQString();
void testQByteArrayAndQString();
void testQVariant();
void testQPoint();
void testQLine();
void testQSize();
void testQRect();
void testQDate();
void testQTime();
void testQDateTime();

class Maye {
public:
	QString sign;
	int age = 18;
	Maye() = default;
	Maye(const QString& sig) :sign(sig) {

	}
	//需要重载输出流
	friend QDebug operator<<(QDebug out, const Maye& maye) {
		out << maye.sign << maye.age;
		return out;
	}
};

int main(int argc, char* argv[]) {

	//QApplication a(argc, argv);
	
	//testTypeAndQByteArry();
	//testQString();
	//testQByteArrayAndQString();
	//testQVariant();
	//testQPoint();
	//testQLine();
	//testQSize();
	//testQRect();
	//testQDate();
	//testQTime();
	testQDateTime();

	//QWidget w;
	//w.show();

	//return a.exec();
}

void testTypeAndQByteArry() {
	//Qt中的基本数据类型
	qint8 age = 127;
	quint64 tel = 1261338615;
	//输出,输出后会自动插入换行（不能不换行），而且在c++风格下，在多个数据之间会自动插入空格（这个可以取消）
	//c风格
	qDebug("age:%d", age);//在release下不会输出
	qInfo("qInfo");
	qWarning("qWarning");
	qCritical("qCritical");
	//注意！这个不能使用流输出（C++风格）
	//qFatal("qFatal:file is not exists");
	//c++风格
	qDebug() << "tel:" << tel;
	qDebug().nospace() << "tel:" << tel;
	//去掉双引号
	qDebug() << QString("hello Qt");
	qDebug().noquote() << QString("hello Qt");

	qInfo("============================================");

	//定义一个字节数组
	QByteArray name = "maye";
	//输出
	qInfo() << name;
	//在尾部追加数据
	name.append(" is");
	name.push_back(" good");
	//在头部添加数据
	name.push_front("I'm ");
	name.prepend("Hello,");
	//指定位置添加
	name.insert(5, " zay");
	qInfo() << name;
	//指定位置删除
	name.remove(5, 4);//在第五个字符后面开始删，删四个
	//从尾部截断,丢掉尾部n个字符
	name.chop(5);
	//丢掉指定位置后面的所有字符
	name.truncate(name.indexOf('i'));
	//清空字节数组
	name.clear();
	qInfo() << name;

	name = "I'maye,very good!And you?";
	//判断name中是否包含字符串very
	if (name.contains("very")) {
		qInfo() << "包含 very";
	}
	//判断name是否以 I 开始，以 ？ 结束
	if (name.startsWith('I')) {
		qInfo("以 I 开始");
	}

	//查找字符串
	qsizetype pos = name.indexOf('y');
	qInfo() << pos;
	pos = name.lastIndexOf('y');
	qInfo() << pos;

	for (auto& c : name) {
		qInfo() << c;
	}

	//字节数组和其他的数据类型转换
	//其他数据类型 转成 字节数组
	QByteArray num;
	num.setNum(1314520, 16);
	qInfo() << num;

	qInfo() << QByteArray::number(520);

	//字节数组 转成 其他数据类型
	num = "1234567";
	qInfo() << num.toInt() << num.toLongLong() << num.toShort();
	//还可以判断是否转换成功
	bool ok;
	auto n = num.toUInt(&ok);
	if (ok) {
		qInfo() << n;
	}
}

void testQString() {
	QString name("wanshui is very good teacher!");
	qInfo() << name;
	name.replace("good", "bad");
	qInfo() << name;
	name.replace("GOOD", "bad");//对大小写有要求
	qInfo() << name;

	QString _name = "顽石";
	qint32 age = 18;
	QString job = "摸鱼";

	qInfo() << _name + QString::number(age) + job;
	//使用c风格的格式化
	qInfo() << QString::asprintf("我是%s,今年%d岁了，我的工作是%s", _name, age, job);
	qInfo() << QString::asprintf("我是%s,今年%d岁了，我的工作是%s",
		_name.toStdString().data(), age, job.toStdString().data());

	//使用Qt风格的格式化
	qInfo() << QString("%1是我，我是%1,今年%2岁了，我的工作是%3").arg(_name).arg(age).arg(job);

	//输出时间
	quint32 s = 360065;
	auto str = QString("%1天，%2时:%3分:%4秒")
		.arg(s / 60 / 60 / 24)
		.arg(s % 24)
		.arg(s % 60,2,10,QChar('0'))//显示两位数字
		.arg(s % 24 % 60);
	qInfo() << str;

	QString _s("顽石hello");
	//获取本地编码 gbk
	qInfo() << _s.toLocal8Bit();
	//获取utf8编码
	qInfo() << _s.toUtf8();

}

void testQByteArrayAndQString() {
	QByteArray array("go home!我");
	qInfo() << array.size();//8 11 字节个数
	qInfo() << array;

	qInfo("============================================");

	QString string("go home!我");
	qInfo() << string.size();//8 9 字符个数
	qInfo() << string;
}

void testQVariant() {
	//QVariant 变体类型，可以存储大量的不同类型的数据
	QVariant var(520);
	//直接输出
	qInfo() << var;
	//获取值
	qInfo() << var.value<int>();
	qInfo() << var.toInt();
	//获取类型
	qInfo() << var.type();
	//重新设置值
	var.setValue("hello 同学们");
	qInfo() << var;
	var.setValue(QString("hello 同学们"));
	qInfo() << var;
	qInfo() << var.value<QString>();
	qInfo() << var.toString();

	//判断能否转换到指定的类型
	if (var.canConvert<QString>()) {
		qInfo("可以");
	}

	Maye m("我是顽石老师，我想摸鱼，但是不能");
	QVariant maye;
	//自定义的类型必须通过setValue设置
	maye.setValue(m);
	qInfo() << maye;

	Maye ma = maye.value<Maye>();
	qInfo() << ma;
	
}

void testQPoint() {
	QPoint point(2, 5);
	qInfo() << point << point.x() << point.y();
	//修改
	point.rx() = 9;
	point.ry() = 6;
	qInfo() << point;
	point.setX(2);
	point.setY(8);
	qInfo() << point;
	//曼哈顿距离(x+y,默认从原点开始)
	qInfo() << point.manhattanLength();

	//指定两点间的曼哈顿距离
	QPoint p1(1, 1);
	QPoint p2(3, 3);
	qInfo() << QPoint(p1 - p2).manhattanLength();

	//交换x,y数据
	qInfo() << point.transposed();
}

void testQLine() {
	QLine line(0, 0, 6, 6);
	qInfo() << line;
	line.translate(1, 2);//直接改到自身
	qInfo() << line;
	qInfo() << line.translated(-1, -2);//会有一个返回值

}

void testQSize() {
	QSize size(640, 480);
	qInfo() << size;
	qInfo() << size.transposed();
	QSize size1(640, 480);
	QSize size2(960, 320);
	//把两个size的高度和宽度最小的拿出来，构造一个size
	qInfo() << size1.boundedTo(size2);
	//把两个size的高度和宽度最大的拿出来，构造一个size
	qInfo() << size1.expandedTo(size2);
	//缩放
	qInfo() << size.scaled(100, 100, Qt::AspectRatioMode::IgnoreAspectRatio);//自由缩放
	qInfo() << size.scaled(100, 100, Qt::AspectRatioMode::KeepAspectRatio);//不丢失部分图片缩放
	qInfo() << size.scaled(100, 100, Qt::AspectRatioMode::KeepAspectRatioByExpanding);//丢失部分图片缩放

}

void testQRect() {
	QRect rect(0, 0, 5, 6);
	qInfo() << rect;
	//获取属性
	qInfo() << rect.x() << rect.y() << rect.width() << rect.height();
	//设置属性
	rect.setRect(5, 5, 5, 5);
	rect.setX(0);
	rect.setY(0);//注意这里只改了一个角，另一个角没变，所以大小跟想的不太一样
	//其他的获取
	qInfo() << rect.topLeft() << rect.topRight() << rect.bottomLeft() << rect.bottomRight();

	//移动矩形，不会改变矩形的宽度和高度
	qInfo() << rect;
	rect.moveTo(2, 2);
	qInfo() << rect;

	//调整矩形
	qInfo() << QRect(0, 0, 640, 480).adjusted(5, 5, -5, -5);
}

void testQDate() {
	QDate date(2022, 12, 11);
	qInfo() << date;
	//获取年月日
	qInfo() << date.year() << date.month() << date.day();
	//添加日期
	qInfo() << date.addDays(10);
	//格式化
	qInfo() << date.toString();
	qInfo() << date.toString("d");
	qInfo() << date.toString("dd");
	qInfo() << date.toString("ddd");
	qInfo() << date.toString("dddd");
	qInfo() << date.toString("M");
	qInfo() << date.toString("MM");
	qInfo() << date.toString("MMM");
	qInfo() << date.toString("MMMM");
	qInfo() << date.toString("yy");
	qInfo() << date.toString("yyyy");
	qInfo() << date.toString("yyyy/MM/dd");
	qInfo() << date.toString("yyyy年MM月dd日");
	qInfo() << date.toString(Qt::DateFormat::ISODate);
	//获取系统当前日期
	auto curDate = QDate::currentDate();
	qInfo() << curDate;

}

void testQTime() {
	QTime time(5, 2, 0);

	qInfo() << time;

	//获取属性
	qInfo() << time.hour() << time.minute() << time.second() << time.msec();
	//让时间增加
	time = time.addSecs(2);
	time = time.addMSecs(60);
	qInfo() << time;
	//把时间格式化成想要的字符串
	qInfo() << time.toString();
	qInfo() << time.toString("h");
	qInfo() << time.toString("hh");
	qInfo() << time.toString("H");
	qInfo() << time.toString("HH");
	qInfo() << time.toString("m");
	qInfo() << time.toString("mm");
	qInfo() << time.toString("s");
	qInfo() << time.toString("ss");
	qInfo() << time.toString("zzz");
	qInfo() << time.toString("a");
	qInfo() << time.toString("hh:mm:ss");
	qInfo() << time.toString("hh时mm分ss秒");

	//获取系统当前时间
	qInfo() << QTime::currentTime();

	//从指定的字符串获取生成时间 必须按照有前导0的格式指定字符串
	qInfo() << QTime::fromString("05:30:01");

}

void testQDateTime() {
	QDateTime dt = QDateTime::currentDateTime();
	qInfo() << dt;
	//获取具体日期时间
	qInfo() << dt.date().year();
	qInfo() << dt.time().hour();
	//格式化字符串
	qInfo() << dt.toString("yyyy年MM月dd日 hh点mm分ss秒");

	QElapsedTimer eTimer;
	//eTimer.start();//开始计时
	//for (int i = 0; i < 10000000; i++);
	//qInfo() << eTimer.elapsed();//从开始到现在用时
	//eTimer.restart();//重新计时
#if 0
	eTimer.start();
	int n;
	unsigned long long int sum = 0;
	unsigned long long int temp = 1;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			temp = temp * j;
		}
		sum = sum + temp;
		temp = 1;
	}
	//printf("%d", sum);
	qInfo() << sum;
	qInfo() << eTimer.elapsed();
#else
	eTimer.start();
	int n;
	scanf("%d", &n);
	int num = n + 1;
	for (int i = n; i >= 2; i--)
	{
		num = num * i + 1;
	}
	//printf("%d", num);
	qInfo() << num;
	qInfo() << eTimer.elapsed();

#endif
}
