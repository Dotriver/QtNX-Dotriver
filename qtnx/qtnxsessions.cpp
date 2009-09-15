/***************************************************************************
                             qtnxsessions.cpp
                            -------------------
        begin                : Wednesday August 16th 2006
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

#include "qtnxsessions.h"

using namespace nxcl;

QtNXSessions::QtNXSessions(QList<NXResumeData> sessions)
{
    ui_sd.setupUi(this);

    connect(ui_sd.newButton, SIGNAL(pressed()), this, SLOT(pressedNew()));
    connect(ui_sd.resumeButton, SIGNAL(pressed()), this, 
            SLOT(pressedResume()));

    for (int i = 0; i < sessions.size(); ++i) {
	NXResumeData session = sessions.at(i);
        sessionItems.append(new QTreeWidgetItem(ui_sd.sessionsList));
        sessionItems.last()->setText(0,
                QString::number(session.getDisplay()));
        sessionItems.last()->setText(1,
                QString::fromStdString(session.getSessionType()));
        sessionItems.last()->setText(2,
                QString::fromStdString(session.getSessionId()));
        sessionItems.last()->setText(3,
                QString::number(session.getDepth()));
        sessionItems.last()->setText(4,
                QString::fromStdString(session.getScreen()));
        sessionItems.last()->setText(5,
                QString::fromStdString(session.getSessionName()));
    }
}

QtNXSessions::~QtNXSessions()
{
}

void QtNXSessions::pressedNew()
{
    emit newPressed();
    close();
}

void QtNXSessions::pressedResume()
{
    emit resumePressed(ui_sd.sessionsList->currentItem()->text(2));
    close();
}
