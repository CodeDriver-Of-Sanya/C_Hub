/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QGridLayout *gridLayout;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QWidget *topWidget;
    QGridLayout *gridLayout_4;
    QLabel *curChatLab;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_3;
    QLabel *curUserLab;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *closeBtn;
    QWidget *chatWidget;
    QGridLayout *gridLayout_3;
    QListWidget *chatMsgListWidget;
    QTextEdit *chatMsgSendEdit;
    QWidget *rightWidget;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *_friendListWidget;
    QWidget *friendTab;
    QVBoxLayout *verticalLayout_3;
    QListWidget *friendListWidget;
    QTabWidget *_broadcastWidget;
    QWidget *systemBroadcastTab;
    QVBoxLayout *verticalLayout_4;
    QListWidget *systemBroadCatListWidget;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *copyrightLab;
    QSpacerItem *horizontalSpacer;
    QPushButton *msgSendBtn;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(829, 534);
        MainWindow->setStyleSheet(QString::fromUtf8("*{\n"
"	\n"
"	background-color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QListWidget\n"
"{\n"
"	border:none;\n"
"}\n"
"\n"
"QWidget#centralWidget\n"
"{\n"
"	border-top-right-radius:11px;\n"
"	border-top-left-radius:11px;\n"
"}\n"
"\n"
"QWidget#topWidget\n"
"{\n"
"	background-color: rgb(72,73,77);\n"
"	border-top-right-radius:10px;\n"
"	border-top-left-radius:10px;\n"
"}\n"
"\n"
"QWidget#topWidget QPushButton,QWidget#widget{\n"
"	border:none;\n"
"	background-color:none;\n"
"	border-radius:5px;\n"
"	color:white;\n"
"}\n"
"\n"
"QPushButton#closeBtn:hover\n"
"{\n"
"	background-color:red;\n"
"}\n"
"\n"
"QLabel\n"
"{\n"
"	background:transparent;\n"
"}\n"
"\n"
"QLabel#curUserLab,QLabel#curChatLab\n"
"{\n"
"	color:white;\n"
"	font:normal 15pt '\346\245\267\344\275\223';\n"
"}\n"
"\n"
"QTextEdit#chatMsgSendEdit\n"
"{\n"
"	border-top:1px solid rgb(212,210,212);\n"
"}\n"
"\n"
"QPushButton#msgSendBtn\n"
"{\n"
"	border:none;\n"
"	border-radius:5px;\n"
"	background-color: rgb(20,180,206);\n"
"	color:white;\n"
"	min-width:85px;\n"
""
                        "	min-height:45px;\n"
"}\n"
"QPushButton#msgSendBtn:hover\n"
"{\n"
"	background-color: rgb(63,195,217);\n"
"}\n"
"\n"
" QTabBar::tab {\n"
"	 border-bottom:1px solid red;\n"
"     border-bottom-color: red; /* same as the pane color */\n"
"     border-top-left-radius: 4px;\n"
"     border-top-right-radius: 4px;\n"
"     min-width: 20ex;\n"
"	 min-height:10ex;\n"
"     padding: 2px;\n"
" }\n"
"\n"
"\n"
""));
        gridLayout = new QGridLayout(MainWindow);
        gridLayout->setObjectName("gridLayout");
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        topWidget = new QWidget(centralWidget);
        topWidget->setObjectName("topWidget");
        topWidget->setMinimumSize(QSize(0, 90));
        topWidget->setMaximumSize(QSize(16777215, 90));
        gridLayout_4 = new QGridLayout(topWidget);
        gridLayout_4->setObjectName("gridLayout_4");
        curChatLab = new QLabel(topWidget);
        curChatLab->setObjectName("curChatLab");
        curChatLab->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(curChatLab, 1, 1, 2, 1);

        horizontalSpacer_4 = new QSpacerItem(258, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_4, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(257, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_3, 2, 0, 1, 1);

        curUserLab = new QLabel(topWidget);
        curUserLab->setObjectName("curUserLab");

        gridLayout_4->addWidget(curUserLab, 0, 0, 2, 1);

        horizontalSpacer_2 = new QSpacerItem(257, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 2, 2, 1, 1);

        widget = new QWidget(topWidget);
        widget->setObjectName("widget");
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_5 = new QSpacerItem(219, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        closeBtn = new QPushButton(widget);
        closeBtn->setObjectName("closeBtn");
        closeBtn->setMinimumSize(QSize(32, 32));
        closeBtn->setMaximumSize(QSize(32, 32));

        horizontalLayout_2->addWidget(closeBtn);


        gridLayout_4->addWidget(widget, 0, 2, 1, 1);


        gridLayout_2->addWidget(topWidget, 0, 0, 1, 2);

        chatWidget = new QWidget(centralWidget);
        chatWidget->setObjectName("chatWidget");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(chatWidget->sizePolicy().hasHeightForWidth());
        chatWidget->setSizePolicy(sizePolicy);
        gridLayout_3 = new QGridLayout(chatWidget);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(9, 0, 0, 0);
        chatMsgListWidget = new QListWidget(chatWidget);
        chatMsgListWidget->setObjectName("chatMsgListWidget");

        gridLayout_3->addWidget(chatMsgListWidget, 0, 0, 1, 1);

        chatMsgSendEdit = new QTextEdit(chatWidget);
        chatMsgSendEdit->setObjectName("chatMsgSendEdit");
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(chatMsgSendEdit->sizePolicy().hasHeightForWidth());
        chatMsgSendEdit->setSizePolicy(sizePolicy1);
        chatMsgSendEdit->setMaximumSize(QSize(16777215, 120));
        chatMsgSendEdit->setFrameShape(QFrame::NoFrame);

        gridLayout_3->addWidget(chatMsgSendEdit, 1, 0, 1, 1);

        gridLayout_3->setRowStretch(0, 2);

        gridLayout_2->addWidget(chatWidget, 1, 0, 1, 1);

        rightWidget = new QWidget(centralWidget);
        rightWidget->setObjectName("rightWidget");
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(rightWidget->sizePolicy().hasHeightForWidth());
        rightWidget->setSizePolicy(sizePolicy2);
        verticalLayout_2 = new QVBoxLayout(rightWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 9, 9);
        _friendListWidget = new QTabWidget(rightWidget);
        _friendListWidget->setObjectName("_friendListWidget");
        friendTab = new QWidget();
        friendTab->setObjectName("friendTab");
        verticalLayout_3 = new QVBoxLayout(friendTab);
        verticalLayout_3->setObjectName("verticalLayout_3");
        friendListWidget = new QListWidget(friendTab);
        friendListWidget->setObjectName("friendListWidget");
        friendListWidget->setFrameShape(QFrame::NoFrame);

        verticalLayout_3->addWidget(friendListWidget);

        _friendListWidget->addTab(friendTab, QString());

        verticalLayout_2->addWidget(_friendListWidget);

        _broadcastWidget = new QTabWidget(rightWidget);
        _broadcastWidget->setObjectName("_broadcastWidget");
        systemBroadcastTab = new QWidget();
        systemBroadcastTab->setObjectName("systemBroadcastTab");
        verticalLayout_4 = new QVBoxLayout(systemBroadcastTab);
        verticalLayout_4->setObjectName("verticalLayout_4");
        systemBroadCatListWidget = new QListWidget(systemBroadcastTab);
        systemBroadCatListWidget->setObjectName("systemBroadCatListWidget");
        systemBroadCatListWidget->setFrameShape(QFrame::NoFrame);

        verticalLayout_4->addWidget(systemBroadCatListWidget);

        _broadcastWidget->addTab(systemBroadcastTab, QString());

        verticalLayout_2->addWidget(_broadcastWidget);


        gridLayout_2->addWidget(rightWidget, 1, 1, 2, 1);

        widget_3 = new QWidget(centralWidget);
        widget_3->setObjectName("widget_3");
        verticalLayout = new QVBoxLayout(widget_3);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 9);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(9, -1, -1, -1);
        copyrightLab = new QLabel(widget_3);
        copyrightLab->setObjectName("copyrightLab");

        horizontalLayout->addWidget(copyrightLab);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        msgSendBtn = new QPushButton(widget_3);
        msgSendBtn->setObjectName("msgSendBtn");

        horizontalLayout->addWidget(msgSendBtn);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout_2->addWidget(widget_3, 2, 0, 1, 1);

        gridLayout_2->setColumnStretch(0, 5);
        gridLayout_2->setColumnStretch(1, 2);

        gridLayout->addWidget(centralWidget, 0, 0, 1, 1);


        retranslateUi(MainWindow);
        QObject::connect(closeBtn, &QPushButton::clicked, MainWindow, qOverload<>(&QWidget::close));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Form", nullptr));
        curChatLab->setText(QCoreApplication::translate("MainWindow", "\346\255\243\345\234\250\345\222\214\346\211\200\346\234\211\344\270\212\347\272\277\347\224\250\346\210\267\347\276\244\350\201\212\344\270\255", nullptr));
        curUserLab->setText(QCoreApplication::translate("MainWindow", "\346\234\252\347\237\245\347\224\250\346\210\267", nullptr));
        closeBtn->setText(QCoreApplication::translate("MainWindow", "\303\227", nullptr));
        chatMsgSendEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\345\234\250\346\255\244\350\276\223\345\205\245\346\226\207\345\255\227\344\277\241\346\201\257...", nullptr));
        _friendListWidget->setTabText(_friendListWidget->indexOf(friendTab), QCoreApplication::translate("MainWindow", "\345\245\275\345\217\213\345\210\227\350\241\250", nullptr));
        _broadcastWidget->setTabText(_broadcastWidget->indexOf(systemBroadcastTab), QCoreApplication::translate("MainWindow", "\347\263\273\347\273\237\345\271\277\346\222\255", nullptr));
        copyrightLab->setText(QCoreApplication::translate("MainWindow", "\351\241\277\345\274\200\346\225\231\350\202\262 \347\211\210\346\235\203\346\211\200\346\234\211", nullptr));
        msgSendBtn->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
