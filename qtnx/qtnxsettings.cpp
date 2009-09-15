/***************************************************************************
  qtnxsettings.cpp
  -------------------
begin                : Saturday August 12th 2006
copyright            : (C) 2006 by George Wright
email                : gwright@kde.org
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <QFile>
#include <QDir>

#include "qtnxsettings.h"
#include "qtnxproxy.h"

#include "nxdata.h"
#include "nxparsexml.h"
#include "nxwritexml.h"

#include "stdlib.h" // pour pouvoir exécuter des commandes système

using namespace nxcl;

QtNXSettings::QtNXSettings(QString sessionName) : QDialog()
{
    
	
	filedesc = sessionName;
    keyDialog = 0;

    if (!sessionName.isEmpty())
        fileName = QDir::homePath() + "/.qtnx/" + sessionName + ".nxml";
    else
        fileName = "";

    ui_sd.setupUi(this);
    ui_sd.sessionName->setText(sessionName);

    parseFile();

    connect(ui_sd.resolution, SIGNAL(currentIndexChanged(QString)), this, SLOT(resolutionChanged(QString)));
    connect(ui_sd.imageCompressionType, SIGNAL(currentIndexChanged(QString)), this, SLOT(compressionChanged(QString)));
    connect(ui_sd.defaultKey, SIGNAL(stateChanged(int)), this, SLOT(keyChanged(int)));
    connect(ui_sd.applyButton, SIGNAL(pressed()), this, SLOT(applyPressed()));
    connect(ui_sd.okButton, SIGNAL(pressed()), this, SLOT(okPressed()));
    connect(ui_sd.cancelButton, SIGNAL(pressed()), this, SLOT(cancelPressed()));
    connect(ui_sd.setAuthKeyButton, SIGNAL(pressed()), this, SLOT(authKeyPressed()));
    connect(ui_sd.proxyButton, SIGNAL(pressed()), this, SLOT(proxyButtonPressed()));
    connect(ui_sd.proxy, SIGNAL(stateChanged(int)), this, SLOT(proxyChanged(int)));

    if (config.isHttpProxyEnabled()) {
        ui_sd.proxy->setCheckState(Qt::Checked);
        ui_sd.proxyButton->setEnabled(true);
    } else {
        ui_sd.proxy->setCheckState(Qt::Unchecked);
        ui_sd.proxyButton->setEnabled(false);
    }
}

QtNXSettings::~QtNXSettings()
{
}

void QtNXSettings::parseFile()
{
    if (!fileName.isEmpty()) {
        NXParseXML handler;
        handler.setData(&config);

        QFile file(fileName);
        QXmlInputSource inputSource(&file);

        QXmlSimpleReader reader;
        reader.setContentHandler(&handler);
        reader.setErrorHandler(&handler);
        reader.parse(inputSource);

        ui_sd.hostname->setText(QString::fromStdString(config.getServerHost()));
        ui_sd.port->setValue(config.getServerPort());

        if (config.getKey().empty())
            ui_sd.defaultKey->setChecked(true);
        else {
            ui_sd.defaultKey->setChecked(false);
            ui_sd.setAuthKeyButton->setEnabled(true);
        }

	string sessionType = config.getSessionType();
        if (sessionType == "unix-kde") {
            ui_sd.platform->setCurrentIndex(ui_sd.platform->findText(tr("UNIX")));
            ui_sd.type->setCurrentIndex(ui_sd.type->findText(tr("KDE")));
        } else if (sessionType == "unix-gnome") {
            ui_sd.platform->setCurrentIndex(ui_sd.platform->findText(tr("UNIX")));
            ui_sd.type->setCurrentIndex(ui_sd.type->findText(tr("GNOME")));
        } else if (sessionType == "unix-cde") {
            ui_sd.platform->setCurrentIndex(ui_sd.platform->findText(tr("UNIX")));
            ui_sd.type->setCurrentIndex(ui_sd.type->findText(tr("CDE")));
        } else if (sessionType == "unix-application") {
            ui_sd.platform->setCurrentIndex(ui_sd.platform->findText(tr("UNIX")));
            ui_sd.type->setCurrentIndex(ui_sd.type->findText(tr("Custom")));
            ui_sd.desktopSettingButton->setEnabled(true);
        }

        string linkType = config.getLinkType();
        if (linkType == "modem")
            ui_sd.link->setCurrentIndex(ui_sd.link->findText(tr("Modem")));
        else if (linkType == "isdn")
            ui_sd.link->setCurrentIndex(ui_sd.link->findText(tr("ISDN")));
        else if (linkType == "adsl")
            ui_sd.link->setCurrentIndex(ui_sd.link->findText(tr("ADSL")));
        else if (linkType == "wan")
            ui_sd.link->setCurrentIndex(ui_sd.link->findText(tr("WAN")));
        else if (linkType == "lan")
            ui_sd.link->setCurrentIndex(ui_sd.link->findText(tr("LAN")));

        int imgCompMethod = config.getImageCompressionMethod();
        if (imgCompMethod == -1) {
            ui_sd.imageCompressionType->setCurrentIndex(ui_sd.imageCompressionType->findText(tr("JPEG")));
            ui_sd.imageQualityLevel->setValue(config.getImageCompressionLevel());
            ui_sd.imageQualityLevel->setEnabled(true);
        } else if (imgCompMethod == 2)
            ui_sd.imageCompressionType->setCurrentIndex(ui_sd.imageCompressionType->findText(tr("PNG")));
        else if (imgCompMethod == 0)
            ui_sd.imageCompressionType->setCurrentIndex(ui_sd.imageCompressionType->findText(tr("Raw X11")));

        string geometry = config.getGeometry();
        if (geometry == "640x480+0+0")
            ui_sd.resolution->setCurrentIndex(ui_sd.resolution->findText("640x480"));
        else if (geometry == "800x600+0+0")
            ui_sd.resolution->setCurrentIndex(ui_sd.resolution->findText("800x600"));
        else if (geometry == "1024x768+0+0")
            ui_sd.resolution->setCurrentIndex(ui_sd.resolution->findText("1024x768"));
        else {
            if (config.fullscreenEnabled()) {
                ui_sd.resolution->setCurrentIndex(ui_sd.resolution->findText(tr("Fullscreen")));
            } else {
                ui_sd.resolution->setCurrentIndex(ui_sd.resolution->findText(tr("Custom")));

                QString res;
                res = QString::fromStdString(geometry).left(geometry.length() - 4);
                ui_sd.width->setValue(res.split('x').at(0).toInt());
                ui_sd.height->setValue(res.split('x').at(1).toInt());
                ui_sd.width->setEnabled(true);
                ui_sd.height->setEnabled(true);
            }
        }

        ui_sd.encryption->setChecked(config.encryptionEnabled());
        ui_sd.memoryCache->setValue(config.getMemCache());
        ui_sd.diskCache->setValue(config.getImageCache());

        ui_sd.render->setChecked(config.renderEnabled());
        ui_sd.proxy->setChecked(config.isHttpProxyEnabled());
        ui_sd.media->setChecked(config.mediaEnabled());
		
		//initialisation de la case à cocher "Enable Microphone" en fonction de son état
		ui_sd.microphone->setChecked(config.microphoneEnabled());
    }
}

void QtNXSettings::resolutionChanged(QString text)
{
    if (text == tr("Custom")) {
        ui_sd.width->setEnabled(true);
        ui_sd.height->setEnabled(true);
    } else {
        ui_sd.width->setEnabled(false);
        ui_sd.height->setEnabled(false);
    }
}

void QtNXSettings::compressionChanged(QString text)
{
    if (text == tr("JPEG")) {
        ui_sd.imageQualityLevel->setEnabled(true);
    } else {
        ui_sd.imageQualityLevel->setEnabled(false);
    }
}

void QtNXSettings::platformChanged(QString text)
{
}

void QtNXSettings::typeChanged(QString text)
{
}

void QtNXSettings::keyChanged(int state)
{
    if (state == Qt::Checked) {
        config.setKey("");
        ui_sd.setAuthKeyButton->setEnabled(false);
    } else
        ui_sd.setAuthKeyButton->setEnabled(true);
}

void QtNXSettings::cancelPressed()
{
    close();
}

void QtNXSettings::okPressed()
{
    applyPressed();
    emit closing(ui_sd.sessionName->text());
    close();
}

void QtNXSettings::authKeyPressed()
{
    keyDialog = 0;
    delete keyDialog;
    keyDialog = new QDialog(this);
    ui_kd.setupUi(keyDialog);
    keyDialog->show();
    QTextDocument *doc_key = new QTextDocument(QString::fromStdString(config.getKey()));
    ui_kd.key->setDocument(doc_key);

    connect(keyDialog, SIGNAL(accepted()), this, SLOT(keyDialogAccept()));
}

void QtNXSettings::keyDialogAccept()
{

    config.setKey(ui_kd.key->document()->toPlainText().toStdString());
}

void QtNXSettings::keyDialogReject()
{
}

void QtNXSettings::applyPressed()
{
    // File has been renamed, remove old one
    if (filedesc != ui_sd.sessionName->text()) {
        QFile temp(QDir::homePath() + "/.qtnx/" + filedesc + ".nxml");
        temp.remove();
    }

    QDir configDir(QDir::homePath() + "/.qtnx/");
    configDir.mkpath(QDir::homePath() + "/.qtnx/");

    config.setSessionName(ui_sd.sessionName->text().toStdString());
    config.setServerHost(ui_sd.hostname->text().toStdString());
    config.setServerPort(ui_sd.port->value());

    // TODO: Add keyboard selection support
    config.setKeyboard("defkeymap");
    config.setKbType("pc102/defkeymap");

    string sessionType;
    if (ui_sd.platform->currentText() == tr("UNIX")) {
        if (ui_sd.type->currentText() == tr("KDE"))
            sessionType = "unix-kde";
        else if (ui_sd.type->currentText() == tr("GNOME"))
            sessionType = "unix-gnome";
        else if (ui_sd.type->currentText() == tr("CDE"))
            sessionType = "unix-cde";
        else if (ui_sd.type->currentText() == tr("Custom"))
            sessionType = "unix-application";
        config.setSessionType(sessionType);
    }

    string linkType;
    if (ui_sd.link->currentText() == tr("Modem"))
        linkType = "modem";
    else if (ui_sd.link->currentText() == tr("ISDN"))
        linkType = "isdn";
    else if (ui_sd.link->currentText() == tr("ADSL"))
        linkType = "adsl";
    else if (ui_sd.link->currentText() == tr("WAN"))
        linkType = "wan";
    else if (ui_sd.link->currentText() == tr("LAN"))
        linkType = "lan";
    config.setLinkType(linkType);

    int imgCompMethod;
    if (ui_sd.imageCompressionType->currentText() == tr("JPEG")) {
        imgCompMethod = -1;
        config.setImageCompressionLevel(ui_sd.imageQualityLevel->value());
    } else if (ui_sd.imageCompressionType->currentText() == tr("PNG"))
        imgCompMethod = 2;
    else if (ui_sd.imageCompressionType->currentText() == tr("Raw X11"))
        imgCompMethod = 0;
    config.setImageCompressionMethod(imgCompMethod);

    if (ui_sd.resolution->currentText() == tr("Fullscreen"))
        config.enableFullscreen();
    else if (ui_sd.resolution->currentText() == tr("Custom")) {
        config.disableFullscreen();
        config.setGeometry((QString::number(ui_sd.width->value()) + "x" + QString::number(ui_sd.height->value()) + "+0+0").toStdString());
    } else {
        config.disableFullscreen();
        config.setGeometry((ui_sd.resolution->currentText() + "+0+0").toStdString());
    }

    if (ui_sd.encryption->checkState() == Qt::Checked)
        config.enableEncryption();
    else
        config.disableEncryption();

    config.setMemCache(ui_sd.memoryCache->value());
    config.setImageCache(ui_sd.diskCache->value());

    if (ui_sd.render->checkState() == Qt::Checked)
        config.enableRender();
    else
        config.disableRender();

    if (ui_sd.media->checkState() == Qt::Checked)
        config.enableMedia();
    else
        config.disableMedia();
	
	// ajouté pour le microphone
	if(ui_sd.microphone->checkState() == Qt::Checked) {
		config.enableMicrophone();
	}
	else {
		config.disableMicrophone();
	}

    NXWriteXML writeData;
    writeData.setSessionData(config);
    writeData.write(QDir::homePath() + "/.qtnx/" + ui_sd.sessionName->text() + ".nxml");
}

void QtNXSettings::proxyButtonPressed()
{
    QDialog *proxyDialog = new QtNXProxy(&this->config);
    proxyDialog->exec();
    delete proxyDialog;
}

void QtNXSettings::proxyChanged(int state)
{
    if (state == Qt::Checked) {
        ui_sd.proxyButton->setEnabled(true);
        config.enableHttpProxy();
    } else {
        ui_sd.proxyButton->setEnabled(false);
        config.disableHttpProxy();
    }
}
