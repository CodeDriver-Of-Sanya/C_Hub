/********************************************************************************
** Form generated from reading UI file 'SettingsDlg.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDLG_H
#define UI_SETTINGSDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsDlg
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *btns;
    QPushButton *settings;
    QPushButton *model1;
    QPushButton *model2;
    QPushButton *model3;
    QPushButton *closeBtn;
    QStackedWidget *stackedWidget;
    QWidget *model2Page3;
    QLabel *label_2;
    QCheckBox *cb_model2;
    QWidget *model3Page4;
    QLabel *label_3;
    QWidget *settingsPage1;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QWidget *model1Page2;
    QLabel *label;
    QCheckBox *cb_model1;

    void setupUi(QDialog *SettingsDlg)
    {
        if (SettingsDlg->objectName().isEmpty())
            SettingsDlg->setObjectName("SettingsDlg");
        SettingsDlg->resize(400, 300);
        SettingsDlg->setStyleSheet(QString::fromUtf8("*{\n"
"	margin:0px;\n"
"}\n"
"\n"
"QDialog#SettingsDlg\n"
"{\n"
"	background-color:skyblue;\n"
"}\n"
"QStackedWidget#stackedWidget\n"
"{\n"
"	background-color:qlineargradient(spread:reflect, x1:0.488, y1:0, x2:0.494, y2:1, stop:0 rgba(151, 211, 255, 255), stop:1 rgba(255, 255, 255, 255));\n"
"}\n"
"\n"
"#settings,#model1,#model2,#model3\n"
"{\n"
"	width:50px;\n"
"	height:30px;\n"
"	border:none;\n"
"	background-color:rgb(6,163,220);\n"
"	border-radius:10px;\n"
"	color:white;\n"
"}\n"
"#settings:hover\n"
"{\n"
"	background-color:darkblue;\n"
"}\n"
"#model1:hover\n"
"{\n"
"	background-color:darkblue;\n"
"}\n"
"#model2:hover\n"
"{\n"
"	background-color:darkblue;\n"
"}\n"
"#model3:hover\n"
"{\n"
"	background-color:darkblue;\n"
"}\n"
""));
        verticalLayoutWidget = new QWidget(SettingsDlg);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(310, 40, 91, 251));
        btns = new QVBoxLayout(verticalLayoutWidget);
        btns->setObjectName("btns");
        btns->setContentsMargins(0, 0, 0, 0);
        settings = new QPushButton(verticalLayoutWidget);
        settings->setObjectName("settings");

        btns->addWidget(settings);

        model1 = new QPushButton(verticalLayoutWidget);
        model1->setObjectName("model1");

        btns->addWidget(model1);

        model2 = new QPushButton(verticalLayoutWidget);
        model2->setObjectName("model2");

        btns->addWidget(model2);

        model3 = new QPushButton(verticalLayoutWidget);
        model3->setObjectName("model3");

        btns->addWidget(model3);

        closeBtn = new QPushButton(SettingsDlg);
        closeBtn->setObjectName("closeBtn");
        closeBtn->setGeometry(QRect(370, 0, 32, 32));
        closeBtn->setMinimumSize(QSize(32, 32));
        closeBtn->setMaximumSize(QSize(32, 32));
        stackedWidget = new QStackedWidget(SettingsDlg);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(10, 10, 291, 281));
        model2Page3 = new QWidget();
        model2Page3->setObjectName("model2Page3");
        label_2 = new QLabel(model2Page3);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 0, 201, 281));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/Resource/desktopRole/summerGril/0.png")));
        label_2->setScaledContents(true);
        label_2->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);
        label_2->setWordWrap(false);
        cb_model2 = new QCheckBox(model2Page3);
        cb_model2->setObjectName("cb_model2");
        cb_model2->setGeometry(QRect(0, 0, 79, 20));
        stackedWidget->addWidget(model2Page3);
        model3Page4 = new QWidget();
        model3Page4->setObjectName("model3Page4");
        label_3 = new QLabel(model3Page4);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(90, 100, 121, 31));
        stackedWidget->addWidget(model3Page4);
        settingsPage1 = new QWidget();
        settingsPage1->setObjectName("settingsPage1");
        widget = new QWidget(settingsPage1);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 10, 291, 271));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(widget);
        groupBox->setObjectName("groupBox");

        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(widget);
        groupBox_2->setObjectName("groupBox_2");

        verticalLayout->addWidget(groupBox_2);

        stackedWidget->addWidget(settingsPage1);
        model1Page2 = new QWidget();
        model1Page2->setObjectName("model1Page2");
        label = new QLabel(model1Page2);
        label->setObjectName("label");
        label->setGeometry(QRect(90, 0, 161, 291));
        label->setPixmap(QPixmap(QString::fromUtf8(":/Resource/desktopRole/littleBoy/0.png")));
        label->setScaledContents(false);
        label->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);
        cb_model1 = new QCheckBox(model1Page2);
        cb_model1->setObjectName("cb_model1");
        cb_model1->setGeometry(QRect(0, 0, 79, 20));
        stackedWidget->addWidget(model1Page2);

        retranslateUi(SettingsDlg);

        stackedWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(SettingsDlg);
    } // setupUi

    void retranslateUi(QDialog *SettingsDlg)
    {
        SettingsDlg->setWindowTitle(QCoreApplication::translate("SettingsDlg", "SettingsDlg", nullptr));
        settings->setText(QCoreApplication::translate("SettingsDlg", "\350\256\276\347\275\256", nullptr));
        model1->setText(QCoreApplication::translate("SettingsDlg", "\344\272\272\347\211\251\346\250\241\345\236\2131", nullptr));
        model2->setText(QCoreApplication::translate("SettingsDlg", "\344\272\272\347\211\251\346\250\241\345\236\2132", nullptr));
        model3->setText(QCoreApplication::translate("SettingsDlg", "\344\272\272\347\211\251\346\250\241\345\236\2133", nullptr));
        closeBtn->setText(QString());
        label_2->setText(QString());
        cb_model2->setText(QCoreApplication::translate("SettingsDlg", "\346\250\241\345\236\2132", nullptr));
        label_3->setText(QCoreApplication::translate("SettingsDlg", "\346\207\222\345\276\227\345\201\232\357\274\214\345\260\261\344\270\215\346\224\276\344\272\206", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SettingsDlg", "\347\250\213\345\272\217\350\256\276\347\275\256", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("SettingsDlg", "\350\207\252\345\256\232\344\271\211\346\241\214\351\235\242\345\243\201\347\272\270", nullptr));
        label->setText(QString());
        cb_model1->setText(QCoreApplication::translate("SettingsDlg", "\346\250\241\345\236\2131", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsDlg: public Ui_SettingsDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDLG_H
