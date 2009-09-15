/********************************************************************************
** Form generated from reading ui file 'proxydialog.ui'
**
** Created: Thu Jun 4 13:00:07 2009
**      by: Qt User Interface Compiler version 4.5.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_PROXYDIALOG_H
#define UI_PROXYDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProxyDialog
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *labelHost;
    QLineEdit *host;
    QLabel *labelPort;
    QLineEdit *port;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *labelUsername;
    QLabel *labelPassword;
    QLineEdit *username;
    QLineEdit *password;

    void setupUi(QDialog *ProxyDialog)
    {
        if (ProxyDialog->objectName().isEmpty())
            ProxyDialog->setObjectName(QString::fromUtf8("ProxyDialog"));
        ProxyDialog->resize(480, 252);
        horizontalLayoutWidget = new QWidget(ProxyDialog);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 20, 441, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        labelHost = new QLabel(horizontalLayoutWidget);
        labelHost->setObjectName(QString::fromUtf8("labelHost"));

        horizontalLayout->addWidget(labelHost);

        host = new QLineEdit(horizontalLayoutWidget);
        host->setObjectName(QString::fromUtf8("host"));

        horizontalLayout->addWidget(host);

        labelPort = new QLabel(horizontalLayoutWidget);
        labelPort->setObjectName(QString::fromUtf8("labelPort"));

        horizontalLayout->addWidget(labelPort);

        port = new QLineEdit(horizontalLayoutWidget);
        port->setObjectName(QString::fromUtf8("port"));

        horizontalLayout->addWidget(port);

        horizontalLayoutWidget_2 = new QWidget(ProxyDialog);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(90, 210, 286, 41));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        okButton = new QPushButton(horizontalLayoutWidget_2);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        horizontalLayout_2->addWidget(okButton);

        cancelButton = new QPushButton(horizontalLayoutWidget_2);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout_2->addWidget(cancelButton);

        gridLayoutWidget = new QWidget(ProxyDialog);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 70, 341, 131));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        labelUsername = new QLabel(gridLayoutWidget);
        labelUsername->setObjectName(QString::fromUtf8("labelUsername"));

        gridLayout->addWidget(labelUsername, 1, 0, 1, 1);

        labelPassword = new QLabel(gridLayoutWidget);
        labelPassword->setObjectName(QString::fromUtf8("labelPassword"));

        gridLayout->addWidget(labelPassword, 2, 0, 1, 1);

        username = new QLineEdit(gridLayoutWidget);
        username->setObjectName(QString::fromUtf8("username"));

        gridLayout->addWidget(username, 1, 1, 1, 1);

        password = new QLineEdit(gridLayoutWidget);
        password->setObjectName(QString::fromUtf8("password"));
        password->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(password, 2, 1, 1, 1);


        retranslateUi(ProxyDialog);

        QMetaObject::connectSlotsByName(ProxyDialog);
    } // setupUi

    void retranslateUi(QDialog *ProxyDialog)
    {
        ProxyDialog->setWindowTitle(QApplication::translate("ProxyDialog", "Proxy Configuration", 0, QApplication::UnicodeUTF8));
        labelHost->setText(QApplication::translate("ProxyDialog", "Host : ", 0, QApplication::UnicodeUTF8));
        labelPort->setText(QApplication::translate("ProxyDialog", "Port :", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("ProxyDialog", "Ok", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("ProxyDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        labelUsername->setText(QApplication::translate("ProxyDialog", "Username : ", 0, QApplication::UnicodeUTF8));
        labelPassword->setText(QApplication::translate("ProxyDialog", "Password :", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(ProxyDialog);
    } // retranslateUi

};

namespace Ui {
    class ProxyDialog: public Ui_ProxyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROXYDIALOG_H
