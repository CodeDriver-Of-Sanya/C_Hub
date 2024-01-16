#include "WindeployQtUI.h"
#include <qformlayout.h>
#include<qpushbutton.h>
#include<qboxlayout.h>
#include<qfile.h>

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
	vlayout->addLayout(hlayout);
	this->setLayout(vlayout);

	//调整样式
	destExe->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
	//添加样式表
	QFile file(":/Resource/style.css");
	if (file.open(QIODevice::ReadOnly))
	{
		setStyleSheet(file.readAll());
	}

}
