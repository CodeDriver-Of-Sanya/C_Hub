#include "MainWindow.h"
#include "ui_MainWindow.h"
#include<qfilesystemmodel>
#include <qsplitter.h>
#include <qboxlayout.h>

MainWindow::MainWindow(QWidget* parent)
	:QWidget(parent)
	,ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	initUi();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::initUi()
{
	//窗口分裂器
	auto spliter = new QSplitter;
	spliter->addWidget(ui->navTreeView);
	spliter->addWidget(ui->stackedWidget);

	auto hlayout = new QHBoxLayout(this);
	hlayout->addWidget(spliter);

	//文件系统模型
	m_treeModel = new QFileSystemModel(this);
	m_treeModel->setRootPath("");
	m_treeModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);//只显示目录
	//树视图
	ui->navTreeView->setModel(m_treeModel);
	//ui->navTreeView->setRootIndex(m_treeModel->index("C:"));
	//手动实现列表展示样式
	//遍历所有列，只显示第一列的名称列
	for (size_t i = 1; i < m_treeModel->columnCount(); i++)
	{
		ui->navTreeView->setColumnHidden(i,true);
	}

	//再来一个文件模型，用于展示具体文件夹里的所有文件
	
	ui->tableView->setModel(m_treeModel);

	//根据左侧点击的具体文件夹，讲文件显示到右侧窗口
	connect(ui->navTreeView, &QTreeView::clicked, this, &MainWindow::onNavTreeViewClicked);
	//让右侧的表格也可以点击
	connect(ui->tableView, &QTreeView::clicked, [=](const QModelIndex& idx)
		{
			auto index = m_treeModel->index(idx.row(), 0, ui->tableView->rootIndex());
			ui->tableView->setRootIndex(index);
		});

}

void MainWindow::onNavTreeViewClicked(const QModelIndex& idx)
{
	ui->tableView->setRootIndex(idx);
}
