#ifndef _REMOTEFILEDLG_H_
#define _REMOTEFILEDLG_H_
#include<qwidget.h>

namespace Ui {
	class RemoteFileDlg;
}

class RemoteFileDlg : public QWidget
{
public:
	RemoteFileDlg(QWidget* parent = nullptr);

	void init();
private:
	Ui::RemoteFileDlg* ui;
};

#endif // !_REMOTEFILEDLG_H_
