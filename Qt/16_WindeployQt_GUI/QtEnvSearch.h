#ifndef _QTENVSEARCH_H_
#define _QTENVSEARCH_H_
#include<qobject.h>
#include<qmap.h>

class QtEnvSearch : public QObject
{
	Q_OBJECT
public:
	QtEnvSearch(QObject* parent = nullptr);
	QStringList qtVersionList();
	QStringList qtKidsList();
	bool generate();
	bool testExe();

	void setCurQtVer(const QString& ver);
	QString getCurQtVer()const;

	void setCurKid(const QString& kid);
	QString getCurKid()const;

	void setExePath(const QString& path);
	QString getExePath()const;

private:
	QMap<QString, QString> m_qtVersionMap;
	QString m_curQtVer;
	QString m_curKid;
	QString m_exePath;
};

#endif // !_QTENVSEARCH_H_
