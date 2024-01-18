#include "WindeployQtUI.h"
#include <qformlayout.h>
#include<qpushbutton.h>
#include<qboxlayout.h>
#include<qfile.h>
#include<qfiledialog.h>
#include<qstandardpaths.h>
#include<qlabel.h>

WindeployQtUI::WindeployQtUI(QWidget* parent)
	:QWidget(parent)
{
	init();
}

void WindeployQtUI::init()
{
	setFixedSize(640, 510);

	m_QtVersomListCbx = new QComboBox;
	m_QtKidsListCbx = new QComboBox;
	//选择需要打包的exe
	auto destExe = new QPushButton("选择exe文件");
	destExe->setObjectName("destExe");
	//生成按钮
	auto generateBtn = new QPushButton("生成");
	//测试按钮
	auto testBtn = new QPushButton("测试");
	//关于按钮
	auto aboutBtn = new QPushButton("关于");

	//最上面的两行两列的表格布局
	auto flayout = new QFormLayout;
	flayout->addRow("选择Qt版本", m_QtVersomListCbx);
	flayout->addRow("选择编译套件", m_QtKidsListCbx);

	//最下面的测试按钮和关于按钮的水平布局
	auto hlayout = new QHBoxLayout;
	hlayout->addWidget(testBtn);
	hlayout->addWidget(aboutBtn);

	//整体的垂直布局
	auto vlayout = new QVBoxLayout;
	vlayout->addLayout(flayout);
	vlayout->addWidget(destExe);
	vlayout->addWidget(generateBtn);
	vlayout->addLayout(hlayout);
	this->setLayout(vlayout);

	auto aboutDia = new QDialog(this);
	aboutDia->resize(200, 100);
	aboutDia->setWindowTitle("关于");
	auto flayout2 = new QFormLayout();
	flayout2->addRow("关于作者：", new QLabel("Winter"));
	flayout2->addRow("关于软件：", new QLabel("随堂完成的小软件，如有bug，那就别用了:)"));
	flayout2->addRow("已知bug：", new QLabel("用MinGW生成的exe无法打开"));
	aboutDia->setLayout(flayout2);

	//添加数据
	m_QtVersomListCbx->addItems(m_qtEnv.qtVersionList());
	m_QtKidsListCbx->addItems(m_qtEnv.qtKidsList());

	//调整样式
	destExe->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
	//添加样式表
	QFile file(":/Resource/style.css");
	if (file.open(QIODevice::ReadOnly))
	{
		setStyleSheet(file.readAll());
	}

	//添加事件
	//更新当前所选中的版本和套件
	m_qtEnv.setCurQtVer(m_QtVersomListCbx->currentText());
	m_qtEnv.setCurKid(m_QtKidsListCbx->currentText());

	//点击关于按钮，打开关于窗口
	connect(aboutBtn, &QPushButton::clicked, [=] {
		aboutDia->show();
		});

	//当选中的Qt版本改变时，更新套件选择
	connect(m_QtVersomListCbx, &QComboBox::currentTextChanged, [=](const QString& ver)
		{
			m_qtEnv.setCurQtVer(ver);
			m_QtKidsListCbx->clear();
			m_QtKidsListCbx->addItems(m_qtEnv.qtKidsList());
		});
	//当选中的套件改变时，更新现有套件
	connect(m_QtKidsListCbx, &QComboBox::currentTextChanged, &m_qtEnv, &QtEnvSearch::setCurKid);
	//点击打开exe文件按钮
	connect(destExe, &QPushButton::clicked, this, [=]()
		{
			auto filePath = QFileDialog::getOpenFileName(this, "选择需要打包的exe文件", QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), "exe (*.exe);;all(*.*)");
			if (filePath.isEmpty())
			{
				qWarning() << "filePath is Empty";
				return;
			}
			m_qtEnv.setExePath(filePath);
			//在上面显示选中的exe名字
			destExe->setText(QFileInfo(filePath).fileName());
		});
	//点击生成按钮
	connect(generateBtn, &QPushButton::clicked, &m_qtEnv, &QtEnvSearch::generate);
	//点击测试按钮，打开exe
	connect(testBtn, &QPushButton::clicked, &m_qtEnv, &QtEnvSearch::testExe);

}
