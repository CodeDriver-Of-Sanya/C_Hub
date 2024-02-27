#include "RemoteFileDlg.h"
#include "ui_RemoteFileDlg.h"

RemoteFileDlg::RemoteFileDlg(QWidget* parent)
	:QWidget(parent),
	ui(new Ui::RemoteFileDlg)
{
	ui->setupUi(this);
	init();
}

void RemoteFileDlg::init()
{
}
