#include<QApplication>
#include<qproperty.h>

//绑定属性
//1.在QObject子类中使用绑定属性
class Circle :public QObject {
	Q_OBJECT
public:
	Circle() {
		//添加绑定
		area.setBinding([=] {
			return M_PI * radius * radius;
			});
	}
	//绑定的与被绑定的数据都需要这样
	QProperty<int> radius{};
	QProperty<qreal> area{};

};
//2.如果类没有继承自QObject



int main(int argc, char* argv[]) {

	QApplication a(argc, argv);

	Circle c;
	c.radius = 23;
	qDebug() << c.area;

	return a.exec();
}

#include "main.moc"
