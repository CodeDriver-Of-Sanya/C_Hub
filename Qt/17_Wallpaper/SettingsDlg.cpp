#include "SettingsDlg.h"
#include "ui_SettingsDlg.h"
#include<qbuttongroup.h>

SettingsDlg::SettingsDlg(QWidget* parent)
	:QDialog(parent)
	,ui(new Ui::SettingsDlg)
{
	ui->setupUi(this);
	initUi();
}

SettingsDlg::~SettingsDlg()
{
	delete ui;
}

void SettingsDlg::initUi()
{
	setFixedSize(412, 312);
	//按钮组
	auto btnGroup = new QButtonGroup(this);
	btnGroup->setExclusive(true);//设置按钮互斥
	btnGroup->addButton(ui->cb_model1,0);
	btnGroup->addButton(ui->cb_model2,1);
	ui->cb_model1->setChecked(true);
	connect(btnGroup, &QButtonGroup::idToggled, [=](int id, bool ischecked)
		{
			if (ischecked)
			{
				emit modelChanged(id);
			}
			//qWarning() << id << ischecked;
		});
}

void SettingsDlg::on_closeBtn_clicked()
{
	close();
}

void SettingsDlg::on_settings_clicked()
{
	ui->stackedWidget->setCurrentWidget(ui->settingsPage1);
}

void SettingsDlg::on_model1_clicked()
{
	ui->stackedWidget->setCurrentWidget(ui->model1Page2);
}

void SettingsDlg::on_model2_clicked()
{
	ui->stackedWidget->setCurrentWidget(ui->model2Page3);
}

void SettingsDlg::on_model3_clicked()
{
	ui->stackedWidget->setCurrentWidget(ui->model3Page4);
}
