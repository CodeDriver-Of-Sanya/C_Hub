#include<QApplication>
#include<QWidget>
//系统属性
class Person :public QObject {
	Q_OBJECT
	//让成员变量暴露给属性
	Q_PROPERTY(int m_age MEMBER m_age)
	Q_PROPERTY(QString m_name MEMBER m_name)
	//可以不分开写，直接在这里定义属性
	Q_PROPERTY(quint64 m_tel READ getTel WRITE setTel)
public:
	Person() {

	}

	int age()const { return m_age; }
	void setAge(int age) { m_age = age; }

	QString name()const { return m_name; }
	void setName(QString name) { m_name = name; }

	quint64 getTel()const { return 114; }
	void setTel(quint64 tel) { qDebug() << __FUNCTION__ << tel; }

private:
	int m_age{};
	QString m_name;
};

int main(int argc, char* argv[]) {

	QApplication a(argc, argv);

	Person maye;
	//直接访问是访问不到的
	qDebug() << maye.property("m_age") << maye.property("m_name");
	//暴露出来之后就可以正常访问了
	maye.setAge(199);
	maye.setName("mmaayyee");
	qDebug() << maye.property("m_age") << maye.property("m_name");
	//直接定义(不常用)
	qDebug()  << maye.property("tel");
	maye.setProperty("tel", 123123);
	
	{
		qDebug() << "-------------------";
		//1.通过方法设置一些成员变量
		qDebug() << maye.objectName();
		maye.setObjectName("mayeName");
		qDebug() << maye.objectName();
		//2.通过属性设置
		maye.setProperty("objectName", "顽石");
		qDebug() << maye.property("objectName");//通过属性读取
		//3.如果设置类里面没有的属性，那么会添加临时的属性
		maye.setProperty("_age", 19);
		maye.setProperty("_name", "zc");
		qDebug() << maye.property("_age") << maye.property("_name");
	}

	return a.exec();
}

#include "main.moc"
