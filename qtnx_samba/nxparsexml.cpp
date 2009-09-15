/***************************************************************************
                              nxparsexml.cpp
                            -------------------
        begin                : Friday August 4th 2006
        copyright            : (C) 2006 by George Wright
                               (C) 2007 Defuturo Ltd
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

#include <iostream>
#include "nxparsexml.h"
#include "nxservice.h"

using namespace std;
using namespace nxcl;

NXSambaMount *smbMount;
string groupName;

NXParseXML::NXParseXML()
{
}

NXParseXML::~NXParseXML()
{
}

bool NXParseXML::startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &attributes)
{
    if (localName == "group") {
        if (attributes.value("name").contains("Share")) {
            groupName = "Share";
            smbMount = new NXSambaMount();
        }
    }

    if (attributes.value("key") == "Alias") {
        smbMount->setMountDir(attributes.value("value").toStdString());
    }

    if (attributes.value("key") == "Username") {
        smbMount->setUsername(attributes.value("value").toStdString());
    }

    if (attributes.value("key") == "Password") {
        smbMount->setPassword(attributes.value("value").toStdString());
    }

    if (attributes.value("key") == "Sharename") {
        smbMount->setResourceName(attributes.value("value").toStdString());
    }

    if (attributes.value("key") == "Connection Name") {
        sessionData->setSessionName(attributes.value("value").toStdString());
    }

    if (attributes.value("key") == "Server Hostname") {
        sessionData->setServerHost(attributes.value("value").toStdString());
    }

    if (attributes.value("key") == "Server Port") {
        sessionData->setServerPort(attributes.value("value").toInt());
    }

    if (attributes.value("key") == "Session Type") {
        sessionData->setSessionType(attributes.value("value").toStdString());
    }

    if (attributes.value("key") == "Custom Session Command") {
        sessionData->setCustomCommand(attributes.value("value").toStdString());
    }

    if (attributes.value("key") == "Disk Cache") {
        sessionData->setMemCache(attributes.value("value").toInt());
    }

    if (attributes.value("key") == "Image Cache") {
        sessionData->setImageCache(attributes.value("value").toInt());
    }

    if (attributes.value("key") == "Link Type") {
        sessionData->setLinkType(attributes.value("value").toStdString());
    }

    if (attributes.value("key") == "Use Render Extension") {
        if (attributes.value("value") == "True")
            sessionData->enableRender();
        else
            sessionData->disableRender();
    }

    int imgCompMethod;
    if (attributes.value("key") == "Image Compression Method") {
        if (attributes.value("value") == "JPEG")
            imgCompMethod = -1;
        else if (attributes.value("value") == "PNG")
            imgCompMethod = 2;
        else if (attributes.value("value") == "Raw X11")
            imgCompMethod = 0;
        sessionData->setImageCompressionMethod(imgCompMethod);
    }

    if (attributes.value("key") == "JPEG Compression Level") {
        sessionData->setImageCompressionLevel(attributes.value("value").toInt());
    }

    if (attributes.value("key") == "Desktop Geometry") {
        sessionData->setGeometry(attributes.value("value").toStdString());
    }

    if (attributes.value("key") == "Keyboard Layout") {
        sessionData->setKeyboard(attributes.value("value").toStdString());
    }

    if (attributes.value("key") == "Keyboard Type") {
        sessionData->setKbType(attributes.value("value").toStdString());
    }

    if (attributes.value("key") == "Media") {
        if (attributes.value("value") == "True")
            sessionData->enableMedia();
        else
            sessionData->disableMedia();
    }

    if (attributes.value("key") == "Agent Server") {
        sessionData->setAgentServer(attributes.value("value").toStdString());
    }

    if (attributes.value("key") == "Agent User") {
        sessionData->setAgentUser(attributes.value("value").toStdString());
    }

    if (attributes.value("key") == "CUPS Port") {
        sessionData->setCupsPort(attributes.value("value").toInt());
    }

    if (attributes.value("key") == "Authentication Key") {
        sessionData->setKey(attributes.value("value").toStdString());
    }

    if (attributes.value("key") == "Use SSL Tunnelling") {
        if (attributes.value("value") == "True")
            sessionData->enableEncryption();
        else
            sessionData->disableEncryption();
    }

    if (attributes.value("key") == "Enable Fullscreen Desktop") {
        if (attributes.value("value") == "True")
            sessionData->enableFullscreen();
        else
            sessionData->disableFullscreen();
    }

    return true;
}

bool NXParseXML::endElement(const QString &namespaceURI, const QString &localName, const QString &qName)
{
    if (localName == "group") {
        if (groupName == "Share") {
            list<NXSambaMount *> &list = sessionData->getSmbMountList();
            list.push_back(smbMount);
        }
    }

    return true;
}
