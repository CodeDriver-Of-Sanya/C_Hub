#ifndef _REMOTEFILEDLG_H_
#define _REMOTEFILEDLG_H_
#include<qwidget.h>
#include<qdir.h>
#include<qstandarditemmodel.h>

namespace Ui {
	class RemoteFileDlg;
}

class RemoteFileDlg : public QWidget
{
	Q_OBJECT
public:
	explicit RemoteFileDlg(QWidget* parent = nullptr);
	~RemoteFileDlg();

private:
	void init();
	void updateLocalFile();
	void localFileBack();

	void updateRemoteFile();
	void remoteFileBack();

private://slots
	void onLocalFileTableViewDoubleClicked(const QModelIndex& index);
	void onRemoteFileTableViewDoubleClicked(const QModelIndex& index);
	
private:
	Ui::RemoteFileDlg* ui;

	QDir m_localFileDir;
	QStandardItemModel* m_localFileModel{};

	QDir m_remoteFileDir;
	QStandardItemModel* m_remoteFileModel{};
};

#endif // !_REMOTEFILEDLG_H_
