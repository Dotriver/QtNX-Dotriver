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

using namespace std;
using namespace nxcl;

NXParseXML::NXParseXML()
{
}

NXParseXML::~NXParseXML()
{
}

bool NXParseXML::startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &attributes)
{
    if (attributes.value("key") == "User") {
        sessionData->setSessionUser(attributes.value("value").toStdString());
    }

    if (attributes.value("key") == "Password") {
        sessionData->setSessionPass(attributes.value("value").toStdString());
    }

    if (attributes.value("key") == "Remember password") {
        sessionData->setRememberPass((attributes.value("value") == "True") ? true : false);
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
	
	
	
	
	
	if (attributes.value("key") == "Microphone") {
        if (attributes.value("value") == "True")
            sessionData->enableMicrophone();
        else
            sessionData->disableMicrophone();
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

    if (attributes.value("key") == "Enable HTTP proxy") {
        if (attributes.value("value") == "True")
            sessionData->enableHttpProxy();
        else
            sessionData->disableHttpProxy();
    }

    if (attributes.value("key") == "HTTP proxy host") {
        sessionData->setHttpProxyHost(attributes.value("value").toStdString());
    }

    if (attributes.value("key") == "HTTP proxy port") {
        sessionData->setHttpProxyPort(attributes.value("value").toUShort());
    }

    if (attributes.value("key") == "HTTP proxy username") {
        sessionData->setHttpProxyUsername(attributes.value("value").toStdString());
    }

    if (attributes.value("key") == "HTTP proxy password") {
        sessionData->setHttpProxyPassword(attributes.value("value").toStdString());
    }

    return true;
}

bool NXParseXML::endElement(const QString &namespaceURI, const QString &localName, const QString &qName)
{
    return true;
}
