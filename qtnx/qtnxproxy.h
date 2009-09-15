#ifndef _QTNXPROXY_H
#define _QTNXPROXY_H

#include <QDialog>

#include "ui_proxydialog.h"
#include "nxdata.h"

using namespace nxcl;

class QtNXProxy : public QDialog
{
    Q_OBJECT
    public:
        QtNXProxy(NXConfigData *);
        ~QtNXProxy();
        public slots:
            void okPressed();
            void cancelPressed();
    private:
        Ui::ProxyDialog ui_pd;
        NXConfigData *configData;
};

#endif
