/***************************************************************************
                                nxwritexml.cpp
                            -------------------
        begin                : Wednesday August 9th 2006
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

#include "nxwritexml.h"

NXWriteXML::NXWriteXML()
{
}

NXWriteXML::~NXWriteXML()
{
}

void NXWriteXML::write(QString fileName)
{
    QFile file(fileName);
    file.open(QFile::WriteOnly);

    QTextStream xml(&file);
    xml.setCodec("UTF-8");

    xml << "<!DOCTYPE NXClientLibSettings>\n";
    xml << "<NXClientLibSettings>\n";

    xml << "<option key=\"User\" value=\"" <<
        escape(QString::fromStdString(sessionData.getSessionUser())) << 
        "\"></option>\n";


    if (sessionData.getRememberPass()) {
        xml << "<option key=\"Password\" value=\"" <<
            escape(QString::fromStdString(sessionData.getSessionPass())) << 
            "\"></option>\n";
        xml << "<option key=\"Remember password\" value=\"True\"></option>\n";
    } else {
        xml << "<option key=\"Remember password\" value=\"False\"></option>\n";
    }

    xml << "<option key=\"Connection Name\" value=\"" <<
        escape(QString::fromStdString(sessionData.getSessionName())) <<
        "\"></option>\n";

    xml << "<option key=\"Server Hostname\" value=\"" <<
        escape(QString::fromStdString(sessionData.getServerHost())) <<
        "\"></option>\n";

    xml << "<option key=\"Server Port\" value=\"" <<
        escape(QString::number(sessionData.getServerPort())) <<
        "\"></option>\n";

    xml << "<option key=\"Session Type\" value=\"" <<
        escape(QString::fromStdString(sessionData.getSessionType())) <<
        "\"></option>\n";

    xml << "<option key=\"Custom Session Command\" value=\"" <<
        escape(QString::fromStdString(sessionData.getCustomCommand())) <<
        "\"></option>\n";

    xml << "<option key=\"Disk Cache\" value=\"" <<
        escape(QString::number(sessionData.getMemCache())) <<
        "\"></option>\n";

    xml << "<option key=\"Image Cache\" value=\"" <<
        escape(QString::number(sessionData.getImageCache())) <<
        "\"></option>\n";

    xml << "<option key=\"Link Type\" value=\"" <<
        escape(QString::fromStdString(sessionData.getLinkType())) <<
        "\"></option>\n";

    if (sessionData.renderEnabled())
        xml << "<option key=\"Use Render Extension\" value=\"True\">" <<
            "</option>\n";
    else
        xml << "<option key=\"Use Render Extension\" value=\"False\">" <<
            "</option>\n";

    int imgCompMethod = sessionData.getImageCompressionMethod();
    if (imgCompMethod == -1)
        xml << "<option key=\"Image Compression Method\" value=\"JPEG\">" <<
            "</option>\n";
    else if (imgCompMethod == 2)
        xml << "<option key=\"Image Compression Method\" value=\"PNG\">" <<
            "</option>\n";
    else if (imgCompMethod == 0)
        xml << "<option key=\"Image Compression Method\" value=\"Raw X11\">" <<
            "</option>\n";

    xml << "<option key=\"JPEG Compression Level\" value=\"" <<
        escape(QString::number(sessionData.getImageCompressionLevel())) <<
        "\"></option>\n";

    xml << "<option key=\"Desktop Geometry\" value=\"" <<
        escape(QString::fromStdString(sessionData.getGeometry())) <<
        "\"></option>\n";

    xml << "<option key=\"Keyboard Layout\" value=\"" <<
        escape(QString::fromStdString(sessionData.getKeyboard())) <<
        "\"></option>\n";

    xml << "<option key=\"Keyboard Type\" value=\"" <<
        escape(QString::fromStdString(sessionData.getKbType())) <<
        "\"></option>\n";

    if (sessionData.mediaEnabled())
        xml << "<option key=\"Media\" value=\"True\"></option>\n";
    else
        xml << "<option key=\"Media\" value=\"False\"></option>\n";
		
		
		
		
		
		
	if (sessionData.microphoneEnabled())
        xml << "<option key=\"Microphone\" value=\"True\"></option>\n";
    else
        xml << "<option key=\"Microphone\" value=\"False\"></option>\n";
		
		
			
		
		

    xml << "<option key=\"Agent Server\" value=\"" <<
        escape(QString::fromStdString(sessionData.getAgentServer())) <<
        "\"></option>\n";

    xml << "<option key=\"Agent User\" value=\"" <<
        escape(QString::fromStdString(sessionData.getAgentUser())) <<
        "\"></option>\n";

    xml << "<option key=\"CUPS Port\" value=\"" <<
        escape(QString::number(sessionData.getCupsPort())) <<
        "\"></option>\n";

    xml << "<option key=\"Authentication Key\" value=\"" <<
        escape(QString::fromStdString(sessionData.getKey())) <<
        "\"></option>\n";

    if (sessionData.encryptionEnabled())
        xml << "<option key=\"Use SSL Tunnelling\" value=\"True\">" <<
            "</option>\n";
    else
        xml << "<option key=\"Use SSL Tunnelling\" value=\"False\">" <<
            "</option>\n";

    if (sessionData.fullscreenEnabled())
        xml << "<option key=\"Enable Fullscreen Desktop\" value=\"True\">" <<
            "</option>\n";
    else
        xml << "<option key=\"Enable Fullscreen Desktop\" value=\"False\">" <<
            "</option>\n";

    if (sessionData.isHttpProxyEnabled()) {
        xml << "<option key=\"Enable HTTP proxy\" value=\"True\">" <<
            "</option>\n";
    } else {
        xml << "<option key=\"Enable HTTP proxy\" value=\"False\">" <<
            "</option>\n";
    }

    xml << "<option key=\"HTTP proxy host\" value=\"" <<
            escape(QString::fromStdString(sessionData.getHttpProxyHost())) << "\">" <<
            "</option>\n";
    xml << "<option key=\"HTTP proxy port\" value=\"" <<
            sessionData.getHttpProxyPort() << "\">" <<
            "</option>\n";
    xml << "<option key=\"HTTP proxy username\" value=\"" <<
            escape(QString::fromStdString(sessionData.getHttpProxyUsername())) << "\">" <<
            "</option>\n";
    xml << "<option key=\"HTTP proxy password\" value=\"" <<
            escape(QString::fromStdString(sessionData.getHttpProxyPassword())) << "\">" <<
            "</option>\n";
    if (sessionData.mediaEnabled())
        xml << "<option key=\"Media\" value=\"True\"></option>\n";
    else
        xml << "<option key=\"Media\" value=\"False\"></option>\n";

    xml << "</NXClientLibSettings>\n";

    file.close();
}

QString NXWriteXML::escape(QString plain)
{
    QString formatted;
    formatted = plain.replace('<', "&lt;");
    formatted = plain.replace('>', "&rt;");
    formatted = plain.replace('&', "&amp;");
    return formatted;
}
