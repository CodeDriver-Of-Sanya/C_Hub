#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_
#include<qwidget.h>
#include<qfilesystemmodel>

namespace Ui { class MainWindow; }

class MainWindow :public QWidget
{
public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

	void initUi();
public:
	void onNavTreeViewClicked(const QModelIndex& idx);
private:
	Ui::MainWindow* ui{};
	QFileSystemModel* m_treeModel{};
};

#endif // !MAINWINDOW_H
