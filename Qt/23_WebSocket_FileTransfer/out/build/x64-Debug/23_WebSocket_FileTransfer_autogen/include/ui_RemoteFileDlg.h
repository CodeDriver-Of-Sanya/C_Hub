/********************************************************************************
** Form generated from reading UI file 'RemoteFileDlg.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REMOTEFILEDLG_H
#define UI_REMOTEFILEDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RemoteFileDlg
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *titleBar_statusLab;
    QLabel *titleBar_titleLab;
    QSpacerItem *horizontalSpacer;
    QPushButton *titleBar_minBtn;
    QPushButton *titleBar_maxBtn;
    QPushButton *titleBar_closeBtn;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_3;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_4;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *local_backBtn;
    QPushButton *local_refreshBtn;
    QPushButton *local_newFolderBtn;
    QComboBox *local_curPathCmb;
    QPushButton *transferBtn;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *remote_backBtn;
    QPushButton *remote_refreshBtn;
    QPushButton *remote_newFolderBtn;
    QComboBox *remote_curPathCmb;
    QHBoxLayout *horizontalLayout_5;
    QTableView *local_tableView;
    QTableView *remote_tableView;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *allStartBtn;
    QPushButton *allStopBtn;
    QPushButton *allCancelBtn;
    QSpacerItem *horizontalSpacer_2;
    QTableView *transferDetail_tableView;

    void setupUi(QWidget *RemoteFileDlg)
    {
        if (RemoteFileDlg->objectName().isEmpty())
            RemoteFileDlg->setObjectName("RemoteFileDlg");
        RemoteFileDlg->resize(785, 583);
        verticalLayout = new QVBoxLayout(RemoteFileDlg);
        verticalLayout->setObjectName("verticalLayout");
        widget = new QWidget(RemoteFileDlg);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        titleBar_statusLab = new QLabel(widget);
        titleBar_statusLab->setObjectName("titleBar_statusLab");
        titleBar_statusLab->setMinimumSize(QSize(16, 16));
        titleBar_statusLab->setMaximumSize(QSize(16, 16));

        horizontalLayout->addWidget(titleBar_statusLab);

        titleBar_titleLab = new QLabel(widget);
        titleBar_titleLab->setObjectName("titleBar_titleLab");

        horizontalLayout->addWidget(titleBar_titleLab);

        horizontalSpacer = new QSpacerItem(532, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        titleBar_minBtn = new QPushButton(widget);
        titleBar_minBtn->setObjectName("titleBar_minBtn");
        titleBar_minBtn->setMinimumSize(QSize(48, 32));
        titleBar_minBtn->setMaximumSize(QSize(48, 32));

        horizontalLayout->addWidget(titleBar_minBtn);

        titleBar_maxBtn = new QPushButton(widget);
        titleBar_maxBtn->setObjectName("titleBar_maxBtn");
        titleBar_maxBtn->setMinimumSize(QSize(48, 32));
        titleBar_maxBtn->setMaximumSize(QSize(48, 32));

        horizontalLayout->addWidget(titleBar_maxBtn);

        titleBar_closeBtn = new QPushButton(widget);
        titleBar_closeBtn->setObjectName("titleBar_closeBtn");
        titleBar_closeBtn->setMinimumSize(QSize(48, 32));
        titleBar_closeBtn->setMaximumSize(QSize(48, 32));

        horizontalLayout->addWidget(titleBar_closeBtn);


        verticalLayout->addWidget(widget);

        widget_5 = new QWidget(RemoteFileDlg);
        widget_5->setObjectName("widget_5");
        horizontalLayout_7 = new QHBoxLayout(widget_5);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(21, -1, 21, -1);
        label_3 = new QLabel(widget_5);
        label_3->setObjectName("label_3");
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        label_3->setFont(font);

        horizontalLayout_7->addWidget(label_3);

        label_4 = new QLabel(widget_5);
        label_4->setObjectName("label_4");
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(label_4);


        verticalLayout->addWidget(widget_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(23);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, -1, -1, -1);
        widget_2 = new QWidget(RemoteFileDlg);
        widget_2->setObjectName("widget_2");
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(21, -1, 21, -1);
        local_backBtn = new QPushButton(widget_2);
        local_backBtn->setObjectName("local_backBtn");
        local_backBtn->setMinimumSize(QSize(36, 22));
        local_backBtn->setMaximumSize(QSize(36, 22));

        horizontalLayout_2->addWidget(local_backBtn);

        local_refreshBtn = new QPushButton(widget_2);
        local_refreshBtn->setObjectName("local_refreshBtn");
        local_refreshBtn->setMinimumSize(QSize(36, 22));
        local_refreshBtn->setMaximumSize(QSize(36, 22));

        horizontalLayout_2->addWidget(local_refreshBtn);

        local_newFolderBtn = new QPushButton(widget_2);
        local_newFolderBtn->setObjectName("local_newFolderBtn");
        local_newFolderBtn->setMinimumSize(QSize(36, 22));
        local_newFolderBtn->setMaximumSize(QSize(36, 22));

        horizontalLayout_2->addWidget(local_newFolderBtn);

        local_curPathCmb = new QComboBox(widget_2);
        local_curPathCmb->setObjectName("local_curPathCmb");
        local_curPathCmb->setEditable(true);

        horizontalLayout_2->addWidget(local_curPathCmb);


        horizontalLayout_4->addWidget(widget_2);

        transferBtn = new QPushButton(RemoteFileDlg);
        transferBtn->setObjectName("transferBtn");
        transferBtn->setMinimumSize(QSize(74, 23));
        transferBtn->setMaximumSize(QSize(74, 23));

        horizontalLayout_4->addWidget(transferBtn);

        widget_3 = new QWidget(RemoteFileDlg);
        widget_3->setObjectName("widget_3");
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(21, -1, 21, -1);
        remote_backBtn = new QPushButton(widget_3);
        remote_backBtn->setObjectName("remote_backBtn");
        remote_backBtn->setMinimumSize(QSize(36, 22));
        remote_backBtn->setMaximumSize(QSize(36, 22));

        horizontalLayout_3->addWidget(remote_backBtn);

        remote_refreshBtn = new QPushButton(widget_3);
        remote_refreshBtn->setObjectName("remote_refreshBtn");
        remote_refreshBtn->setMinimumSize(QSize(36, 22));
        remote_refreshBtn->setMaximumSize(QSize(36, 22));

        horizontalLayout_3->addWidget(remote_refreshBtn);

        remote_newFolderBtn = new QPushButton(widget_3);
        remote_newFolderBtn->setObjectName("remote_newFolderBtn");
        remote_newFolderBtn->setMinimumSize(QSize(36, 22));
        remote_newFolderBtn->setMaximumSize(QSize(36, 22));

        horizontalLayout_3->addWidget(remote_newFolderBtn);

        remote_curPathCmb = new QComboBox(widget_3);
        remote_curPathCmb->setObjectName("remote_curPathCmb");
        remote_curPathCmb->setEditable(true);

        horizontalLayout_3->addWidget(remote_curPathCmb);


        horizontalLayout_4->addWidget(widget_3);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(21);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        local_tableView = new QTableView(RemoteFileDlg);
        local_tableView->setObjectName("local_tableView");

        horizontalLayout_5->addWidget(local_tableView);

        remote_tableView = new QTableView(RemoteFileDlg);
        remote_tableView->setObjectName("remote_tableView");

        horizontalLayout_5->addWidget(remote_tableView);


        verticalLayout->addLayout(horizontalLayout_5);

        widget_4 = new QWidget(RemoteFileDlg);
        widget_4->setObjectName("widget_4");
        horizontalLayout_6 = new QHBoxLayout(widget_4);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        allStartBtn = new QPushButton(widget_4);
        allStartBtn->setObjectName("allStartBtn");
        allStartBtn->setMinimumSize(QSize(93, 23));
        allStartBtn->setMaximumSize(QSize(93, 23));

        horizontalLayout_6->addWidget(allStartBtn);

        allStopBtn = new QPushButton(widget_4);
        allStopBtn->setObjectName("allStopBtn");
        allStopBtn->setMinimumSize(QSize(93, 23));
        allStopBtn->setMaximumSize(QSize(93, 23));

        horizontalLayout_6->addWidget(allStopBtn);

        allCancelBtn = new QPushButton(widget_4);
        allCancelBtn->setObjectName("allCancelBtn");
        allCancelBtn->setMinimumSize(QSize(93, 23));
        allCancelBtn->setMaximumSize(QSize(93, 23));

        horizontalLayout_6->addWidget(allCancelBtn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(widget_4);

        transferDetail_tableView = new QTableView(RemoteFileDlg);
        transferDetail_tableView->setObjectName("transferDetail_tableView");

        verticalLayout->addWidget(transferDetail_tableView);


        retranslateUi(RemoteFileDlg);

        QMetaObject::connectSlotsByName(RemoteFileDlg);
    } // setupUi

    void retranslateUi(QWidget *RemoteFileDlg)
    {
        RemoteFileDlg->setWindowTitle(QCoreApplication::translate("RemoteFileDlg", "Form", nullptr));
        titleBar_statusLab->setText(QCoreApplication::translate("RemoteFileDlg", "TextLabel", nullptr));
        titleBar_titleLab->setText(QCoreApplication::translate("RemoteFileDlg", "\350\277\234\347\250\213\346\226\207\344\273\266", nullptr));
        titleBar_minBtn->setText(QCoreApplication::translate("RemoteFileDlg", "\342\200\224", nullptr));
        titleBar_maxBtn->setText(QCoreApplication::translate("RemoteFileDlg", "\345\217\243", nullptr));
        titleBar_closeBtn->setText(QCoreApplication::translate("RemoteFileDlg", "X", nullptr));
        label_3->setText(QCoreApplication::translate("RemoteFileDlg", "\346\234\254\345\234\260\350\256\276\345\244\207", nullptr));
        label_4->setText(QCoreApplication::translate("RemoteFileDlg", "\350\277\234\347\250\213\350\256\276\345\244\207", nullptr));
#if QT_CONFIG(tooltip)
        local_backBtn->setToolTip(QCoreApplication::translate("RemoteFileDlg", "\350\277\224\345\233\236\344\270\212\344\270\200\345\261\202", nullptr));
#endif // QT_CONFIG(tooltip)
        local_backBtn->setText(QCoreApplication::translate("RemoteFileDlg", "<", nullptr));
#if QT_CONFIG(tooltip)
        local_refreshBtn->setToolTip(QCoreApplication::translate("RemoteFileDlg", "\345\210\267\346\226\260\345\275\223\345\211\215\346\226\207\344\273\266\345\244\271", nullptr));
#endif // QT_CONFIG(tooltip)
        local_refreshBtn->setText(QCoreApplication::translate("RemoteFileDlg", "<", nullptr));
#if QT_CONFIG(tooltip)
        local_newFolderBtn->setToolTip(QCoreApplication::translate("RemoteFileDlg", "\346\226\260\345\273\272\346\226\207\344\273\266\345\244\271", nullptr));
#endif // QT_CONFIG(tooltip)
        local_newFolderBtn->setText(QCoreApplication::translate("RemoteFileDlg", "<", nullptr));
        transferBtn->setText(QCoreApplication::translate("RemoteFileDlg", "\344\274\240\350\276\223", nullptr));
#if QT_CONFIG(tooltip)
        remote_backBtn->setToolTip(QCoreApplication::translate("RemoteFileDlg", "\350\277\224\345\233\236\344\270\212\344\270\200\345\261\202", nullptr));
#endif // QT_CONFIG(tooltip)
        remote_backBtn->setText(QCoreApplication::translate("RemoteFileDlg", "<", nullptr));
#if QT_CONFIG(tooltip)
        remote_refreshBtn->setToolTip(QCoreApplication::translate("RemoteFileDlg", "\345\210\267\346\226\260\345\275\223\345\211\215\346\226\207\344\273\266\345\244\271", nullptr));
#endif // QT_CONFIG(tooltip)
        remote_refreshBtn->setText(QCoreApplication::translate("RemoteFileDlg", "<", nullptr));
#if QT_CONFIG(tooltip)
        remote_newFolderBtn->setToolTip(QCoreApplication::translate("RemoteFileDlg", "\346\226\260\345\273\272\346\226\207\344\273\266\345\244\271", nullptr));
#endif // QT_CONFIG(tooltip)
        remote_newFolderBtn->setText(QCoreApplication::translate("RemoteFileDlg", "<", nullptr));
        allStartBtn->setText(QCoreApplication::translate("RemoteFileDlg", "\345\274\200\345\247\213\345\205\250\351\203\250", nullptr));
        allStopBtn->setText(QCoreApplication::translate("RemoteFileDlg", "\346\232\202\345\201\234\345\205\250\351\203\250", nullptr));
        allCancelBtn->setText(QCoreApplication::translate("RemoteFileDlg", "\345\217\226\346\266\210\345\205\250\351\203\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RemoteFileDlg: public Ui_RemoteFileDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REMOTEFILEDLG_H
