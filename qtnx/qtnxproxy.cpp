#include "ui_proxydialog.h"

#include "qtnxproxy.h"
#include "nxdata.h"

#include <QMessageBox>

using namespace nxcl;
#include <iostream>

QtNXProxy::QtNXProxy(NXConfigData *data) : QDialog()
{
    configData = data;
    ui_pd.setupUi(this);

    connect(ui_pd.okButton, SIGNAL(pressed()), this, SLOT(okPressed()));
    connect(ui_pd.cancelButton, SIGNAL(pressed()), this, SLOT(cancelPressed()));

    if (configData->isHttpProxyEnabled()) {
        ui_pd.host->setText(QString::fromStdString(configData->getHttpProxyHost()));
        ui_pd.port->setText(QString::number(configData->getHttpProxyPort()));
        ui_pd.username->setText(QString::fromStdString(configData->getHttpProxyUsername()));
        ui_pd.password->setText(QString::fromStdString(configData->getHttpProxyPassword()));
    }
}

QtNXProxy::~QtNXProxy()
{
    if (!configData->getHttpProxyHost().empty() && 
               configData->getHttpProxyPort() != 0) {
        configData->enableHttpProxy();
    } else {
        configData->disableHttpProxy();
    }
}

void QtNXProxy::okPressed()
{
    string host = ui_pd.host->text().toStdString();
    unsigned short port = ui_pd.port->text().toUShort();
    string username = ui_pd.username->text().toStdString();
    string password = ui_pd.password->text().toStdString();

    if (host.empty()) {
        QMessageBox::warning(this, tr("Warning"), tr("Host missing"));
    } else if (!port) {
        QMessageBox::warning(this, tr("Warning"), tr("Port missing"));
    } else {
        configData->setHttpProxyHost(host);
        configData->setHttpProxyPort(port);
        configData->setHttpProxyUsername(username);
        configData->setHttpProxyPassword(password);

        close();
    }
}

void QtNXProxy::cancelPressed()
{
    close();
}
