/***************************************************************************
 *  qtnxresource.cpp
 * -------------------
 *     begin                : Saturday May 4th 2009
 *     copyright            : (C) 2009 by Maxime Poncet
 *     email                : mponcet@dotriver.eu
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <QComboBox>
#include <QMessageBox>
#include <QLineEdit>
#include <QString>
#include <QDialog>

#include <string>
#include <list>

#include "qtnxresource.h"

#include "ui_resourcedialog.h"
#include <iostream>

using namespace nxcl;
using namespace std;

QtNXResource::QtNXResource(NXSambaMount *mnt, int modify)
{
    vector<string>::iterator it;
    NXSamba smb;

    this->smbMount = mnt;
    smbMountSet = false;

    ui_rd.setupUi(this);
    connect(ui_rd.okResource, SIGNAL(pressed()), this, SLOT(okPressed()));
    connect(ui_rd.cancelResource, SIGNAL(pressed()), this, SLOT(cancelPressed()));
    connect(ui_rd.resourceList, SIGNAL(activated(int)), this, SLOT(chooseResource(int)));

    localResources = smb.listLocalResource();
    it = localResources.begin();
    while (it != localResources.end()) {
        ui_rd.resourceList->addItem((*it).c_str());
        it++;
    }

    if (modify) {
        ui_rd.username->setText(smbMount->getUsername().c_str());
        ui_rd.password->setText(smbMount->getPassword().c_str());
        ui_rd.mountDir->setText(smbMount->getMountDir().c_str());
        ui_rd.resourceList->setCurrentIndex(ui_rd.resourceList->findText(smbMount->getResourceName().c_str()));
    } else {
        if (localResources.size()) {
            QString resource0 = localResources.begin()->c_str();
            ui_rd.mountDir->setText("$(SHARES)/" + resource0);
        }
    }
}

QtNXResource::~QtNXResource()
{
    ;
}

void QtNXResource::cancelPressed()
{
    smbMountSet = false;
    close();
}

void QtNXResource::okPressed()
{
    string username = ui_rd.username->text().toStdString();
    string password = ui_rd.password->text().toStdString();
    string mountDir = ui_rd.mountDir->text().toStdString();
    string resource = ui_rd.resourceList->currentText().toStdString();
    smbMountSet = true;

    if (mountDir.empty()) {
        QMessageBox::warning(this, "Warning", "No Mount dir selected");
        smbMountSet = false;
    } else if (username.empty()) {
        QMessageBox::warning(this, "Warning", "No username given");
        smbMountSet = false;
    } else if (password.empty()) {
        QMessageBox::warning(this, "Warning", "No password given");
    }

    if (smbMountSet == false)
        return;

    smbMount->setUsername(username);
    smbMount->setPassword(password);
    smbMount->setMountDir(mountDir);


    int currentIdx = ui_rd.resourceList->currentIndex();
    vector<string>::iterator it = localResources.begin() + currentIdx;
    smbMount->setResourceName(resource);

    close();
}

void QtNXResource::chooseResource(int n)
{
    QString resource0 = localResources.at(n).c_str();
    ui_rd.mountDir->setText("$(SHARES)/" + resource0);
}
