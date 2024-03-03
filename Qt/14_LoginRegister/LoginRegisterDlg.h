#ifndef _LOGINREGISTERDLG_H_
#define _LOGINREGISTERDLG_H_

#include<qdialog.h>
#include<qstackedwidget.h>
#include<qlabel.h>
#include<qlineedit.h>
#include<qcheckbox.h>
#include<qradiobutton.h>

class LoginRegisterDlg :public QDialog
{
public:
	LoginRegisterDlg(QWidget* parent = nullptr);

private:
	void initUi();
	QWidget* createLoginWidget();
	QWidget* createRegisterWidget();
	void saveInfo(const QString& account, const QString& password, const bool& isRemember);	
	void readInfo();
public://slots
	void onLogin();
	void onRegister();
protected:
	void paintEvent(QPaintEvent* pe)override;

private:
	QRect m_leftRect;
	QRect m_midRect;
	QRect m_rightRect;
	QWidget* m_loginWgt;
	QWidget* m_registerWgt;
	QStackedWidget* m_stkWidget;
	QLabel* m_tipBox{};
	QLineEdit* m_account{};
	QLineEdit* m_password{};
	QCheckBox* m_isRememberPwd{};
	void setTipBox(const QString& tip);

};

#endif // !_LOGINREGISTERDLG_H_
