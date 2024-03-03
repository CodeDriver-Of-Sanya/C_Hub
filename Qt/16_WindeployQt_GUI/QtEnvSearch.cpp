#include "QtEnvSearch.h"
#include<qdir.h>
#include<qapplication.h>
#include<qstandardpaths.h>
#include<qdiriterator.h>
#include<qprocess.h>
#include<qtextstream.h>

//开始菜单路径
#define START_MENU_PATH QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation)

QtEnvSearch::QtEnvSearch(QObject* parent)
	:QObject(parent)
{
	
}

static QString getQtEnv(const QString& qtBin)
{
	if (qtBin.isEmpty())return QString();

	QFile file(qtBin + "/qtenv2.bat");
	if (!file.open(QIODevice::ReadOnly))return QString();

	QTextStream stream(&file);
	while (!stream.atEnd())
	{
		auto line = stream.readLine();
		if (line.startsWith("set PATH="))
		{
			return line.mid(9).remove("%PATH%").trimmed();
		}
	}
	return QString();
}

QStringList QtEnvSearch::qtVersionList()
{
	if (m_qtVersionMap.isEmpty())
	{
		QDir dir(START_MENU_PATH);
		if (!dir.exists())
		{
			qWarning() << START_MENU_PATH << "not exists!";
			return {};
		}

		QDirIterator di(START_MENU_PATH, { "MinGW*","MSVC*" }, QDir::Dirs, QDirIterator::Subdirectories);
		QSet<QString> paths;
		while (di.hasNext())
		{
			paths.insert(QFileInfo(di.next()).path());
		}
		for (auto& path : paths)
		{
			m_qtVersionMap.insert(QFileInfo(path).fileName(), path);
		}
	}

	return m_qtVersionMap.keys();
}

QStringList QtEnvSearch::qtKidsList()
{
	if (m_curQtVer.isEmpty())
	{
		m_curQtVer = m_qtVersionMap.firstKey();
	}

	auto curPath = m_qtVersionMap.value(m_curQtVer);
	QDir dir(curPath);
	if (!dir.exists())
	{
		return QStringList({"没有找到该目录下的套件"});
	}
	return dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
}

bool QtEnvSearch::generate()
{
	//进入套件目录
	QDir dir((m_qtVersionMap.value(m_curQtVer)));
	if (!dir.cd(m_curKid))
	{
		qWarning() << "curKid 进入失败";
		return false;
	}

	//找到一个快捷方式并进入指定的目录
	auto allEntry = dir.entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries);
	//qDebug() << allEntry;
	if (allEntry.isEmpty())
	{
		qWarning() << "allEntry 是空的";
		return false;
	}
	
	//获取Qt的bin目录
	auto qtBin = QFileInfo(allEntry.first().symLinkTarget()).path();
	//qDebug() << qtBin;

	//先设置环境（临时的）防止有的人没有设置系统变量导致bug
	auto env = getQtEnv(qtBin);
	auto oldPath = qgetenv("path");
	qputenv("path", oldPath + env.toLatin1());
	//qWarning() << qgetenv("path");
	//使用QProcess处理，调用打包工具
	//qWarning() << getExePath();
	//qWarning() << qtBin;
	return QProcess::startDetached(qtBin + "/windeployqt.exe", { getExePath()});
}

bool QtEnvSearch::testExe()
{
	return QProcess::startDetached(getExePath());
}

void QtEnvSearch::setCurQtVer(const QString& ver)
{
	m_curQtVer = ver;
}

QString QtEnvSearch::getCurQtVer() const
{
	return m_curQtVer;
}

void QtEnvSearch::setCurKid(const QString& kid)
{
	m_curKid = kid;
}

QString QtEnvSearch::getCurKid() const
{
	return m_curKid;
}

void QtEnvSearch::setExePath(const QString& path)
{
	m_exePath = path;
}

QString QtEnvSearch::getExePath() const
{
	return m_exePath;
}
