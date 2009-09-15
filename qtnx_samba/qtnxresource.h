/***************************************************************************
 *   qtnxresource.h
 *     -------------------
 *     begin                : Saturday May 4th 2009
 *     copyright            : (C) 2009 by Maxime Poncet
 *     email                : mponcet@dotriver.eu
 ****************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ****************************************************************************/

#ifndef _QTNXRESOURCE_H
#define _QTNXRESOURCE_H

#include "ui_resourcedialog.h"
#include "nxservice.h"

#include <QDialog>

#include <list>

using namespace std;
using namespace nxcl;

class QtNXResource : public QDialog
{
    Q_OBJECT;
    public:
        QtNXResource(NXSambaMount *, int);
        ~QtNXResource();
        bool isSmbMountSet()
        {
            return this->smbMountSet;
        }

    public slots:
        void okPressed();
        void cancelPressed();
        void chooseResource(int);
    signals:
        void closing(QString);
    private:
        Ui::ResourceDialog ui_rd;
        vector<string> localResources;
        NXSambaMount *smbMount;
        bool smbMountSet;
};

#endif
