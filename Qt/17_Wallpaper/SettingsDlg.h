#ifndef SETTINGS_H_
#define SETTINGS_H_

#include<qdialog.h>

namespace Ui { class SettingsDlg; }

class SettingsDlg : public QDialog
{
	Q_OBJECT
public:
	SettingsDlg(QWidget* parent = nullptr);
	~SettingsDlg();
	void initUi();
public slots:
	void on_closeBtn_clicked();
	void on_settings_clicked();
	void on_model1_clicked();
	void on_model2_clicked();
	void on_model3_clicked();
signals:
	void modelChanged(int id);

private:
	Ui::SettingsDlg* ui{};
};

#endif // !_SETTINGS_H_
