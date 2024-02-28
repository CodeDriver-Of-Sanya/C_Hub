#include "RemoteFileDlg.h"
#include "ui_RemoteFileDlg.h"
#include<qdiriterator.h>
#include<qstandardpaths.h>
#include<qfileiconprovider.h>

static QString FileTypeString(const QFileInfo& info);

RemoteFileDlg::RemoteFileDlg(QWidget* parent)
	:QWidget(parent),
	ui(new Ui::RemoteFileDlg)
{
	ui->setupUi(this);
	init();
}

RemoteFileDlg::~RemoteFileDlg()
{
	delete ui;
}

void RemoteFileDlg::init()
{
	//=================本地文件===============
	//找到桌面路径
	m_localFileDir.setPath(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
	//创建本地文件模型
	m_localFileModel = new QStandardItemModel(this);
	//将模型放入
	ui->local_tableView->setModel(m_localFileModel);
	//取消双击编辑
	ui->local_tableView->setEditTriggers(QTableView::NoEditTriggers);
	//让鼠标点中后直接选择一整行
	ui->local_tableView->setSelectionBehavior(QTableView::SelectionBehavior::SelectRows);
	//可以按住ctrl多选
	ui->local_tableView->setSelectionMode(QTableView::SelectionMode::ContiguousSelection);

	updateLocalFile();

	connect(ui->local_tableView, &QTableView::doubleClicked, this, &RemoteFileDlg::onLocalFileTableViewDoubleClicked);
	connect(ui->local_backBtn, &QPushButton::clicked, this, &RemoteFileDlg::localFileBack);
	connect(ui->local_refreshBtn, &QPushButton::clicked, this, &RemoteFileDlg::updateLocalFile);
	connect(ui->local_newFolderBtn, &QPushButton::clicked, this, [=]
		{
			m_localFileDir.mkdir("新建文件夹");
			updateLocalFile();
			//这样就可以更改新建文件夹的名字
			ui->local_tableView->edit(m_localFileModel->index(m_localFileModel->rowCount() - 1, 0));
			//但是只能改模型里的名字，在外面看还是没变
		});
	//更改新建文件夹的名字
	connect(m_localFileModel, &QStandardItemModel::itemChanged, [=](QStandardItem* item)
		{
			m_localFileDir.rename("新建文件夹", item->text());
		});
	connect(ui->local_curPathCmb, &QComboBox::currentTextChanged, [=](const QString& path)
		{
			m_localFileDir.setPath(path);
			updateLocalFile();
		});
	

	//=================远程文件===============
	m_remoteFileDir.setPath(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
	m_remoteFileModel = new QStandardItemModel(this);
	ui->remote_tableView->setModel(m_remoteFileModel);
	ui->remote_tableView->setEditTriggers(QTableView::NoEditTriggers);
	ui->remote_tableView->setSelectionBehavior(QTableView::SelectionBehavior::SelectRows);
	ui->remote_tableView->setSelectionMode(QTableView::SelectionMode::ContiguousSelection);
	
	updateRemoteFile();
	
	connect(ui->remote_tableView, &QTableView::doubleClicked, this, &RemoteFileDlg::onRemoteFileTableViewDoubleClicked);
	connect(ui->remote_backBtn, &QPushButton::clicked, this, &RemoteFileDlg::remoteFileBack);
	connect(ui->remote_refreshBtn, &QPushButton::clicked, this, &RemoteFileDlg::updateRemoteFile);
	connect(ui->remote_newFolderBtn, &QPushButton::clicked, this, [=]
		{
			m_remoteFileDir.mkdir("新建文件夹");
			updateRemoteFile();
			ui->remote_tableView->edit(m_remoteFileModel->index(m_remoteFileModel->rowCount() - 1, 0));
		});
	connect(m_remoteFileModel, &QStandardItemModel::itemChanged, [=](QStandardItem* item)
		{
			m_remoteFileDir.rename("新建文件夹", item->text());
		});
	connect(ui->remote_curPathCmb, &QComboBox::currentTextChanged, [=](const QString& path)
		{
			m_remoteFileDir.setPath(path);
			updateRemoteFile();
		});
}

void RemoteFileDlg::updateLocalFile()
{
	//更新前先清空就数据
	m_localFileModel->clear();
	//设置当先路径
	ui->local_curPathCmb->addItem(m_localFileDir.absolutePath());
	ui->local_curPathCmb->setCurrentText(m_localFileDir.absolutePath());

	QDirIterator iter(m_localFileDir.absolutePath(), QDir::NoDotAndDotDot | QDir::AllEntries);
	QFileIconProvider fip;
	while (iter.hasNext())
	{
		auto info = iter.nextFileInfo();
		QList<QStandardItem*> items;

		auto file_item = new QStandardItem(info.fileName());
		file_item->setIcon(fip.icon(info));
		items.append(file_item);

		items.append(new QStandardItem(QString::number(info.size()) + " 字节"));
		items.append(new QStandardItem(info.fileTime(QFile::FileTime::FileModificationTime).toString("yyyy/MM/dd hh:mm")));
		items.append(new QStandardItem(FileTypeString(info)));

		m_localFileModel->appendRow(items);
	}
}

void RemoteFileDlg::localFileBack()
{
	m_localFileDir.cdUp();
	updateLocalFile();
}

void RemoteFileDlg::updateRemoteFile()
{
	//更新前先清空就数据
	m_remoteFileModel->clear();
	//设置当先路径
	ui->remote_curPathCmb->addItem(m_remoteFileDir.absolutePath());
	ui->remote_curPathCmb->setCurrentText(m_remoteFileDir.absolutePath());

	QDirIterator iter(m_remoteFileDir.absolutePath(), QDir::NoDotAndDotDot | QDir::AllEntries);
	QFileIconProvider fip;
	while (iter.hasNext())
	{
		auto info = iter.nextFileInfo();
		QList<QStandardItem*> items;

		auto file_item = new QStandardItem(info.fileName());
		file_item->setIcon(fip.icon(info));
		items.append(file_item);

		items.append(new QStandardItem(QString::number(info.size()) + " 字节"));
		items.append(new QStandardItem(info.fileTime(QFile::FileTime::FileModificationTime).toString("yyyy/MM/dd hh:mm")));
		items.append(new QStandardItem(FileTypeString(info)));

		m_remoteFileModel->appendRow(items);
	}
}

void RemoteFileDlg::remoteFileBack()
{
	m_remoteFileDir.cdUp();
	updateRemoteFile();
}

void RemoteFileDlg::onLocalFileTableViewDoubleClicked(const QModelIndex& index)
{
	auto filename = m_localFileModel->data(m_localFileModel->index(index.row(), 0)).toString();
	qDebug() << filename;
	QFileInfo info(m_localFileDir.absolutePath() + "/" + filename);
	if (info.isDir())
	{
		m_localFileDir.cd(filename);
		updateLocalFile();
	}
}

void RemoteFileDlg::onRemoteFileTableViewDoubleClicked(const QModelIndex& index)
{
	auto filename = m_remoteFileModel->data(m_remoteFileModel->index(index.row(), 0)).toString();
	qDebug() << filename;
	QFileInfo info(m_remoteFileDir.absolutePath() + "/" + filename);
	if (info.isDir())
	{
		m_remoteFileDir.cd(filename);
		updateRemoteFile();
	}
}

static QString FileTypeString(const QFileInfo& info)
{
	if (info.isAlias()) { return "别名"; }      //mac
	if (info.isBundle()) { return "bundle"; }     //mac
	if (info.isDir()) { return "文件夹"; }
	if (info.isExecutable()) { return "exe"; }
	if (info.isFile()) { return "文件"; }
	if (info.isHidden()) { return "隐藏文件"; }
	if (info.isJunction()) { return "lnk"; }
	if (info.isShortcut()) { return "lnk"; }
	if (info.isSymLink()) { return "lnk"; }
	if (info.isSymbolicLink()) { return "lnk"; }
	return "unknown";
}
