/***************************************************************************
 *  qtnxresource.cpp
 * -------------------
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
 ***************************************************************************/


#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include "nxservice.h"

extern "C" {
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
}

using namespace std;
using namespace nxcl;

vector<string> NXSamba::listLocalResource()
{
    string s;
    ifstream configfile(this->smbFile.c_str());
    vector<string> listR;

    while (configfile)
    {
        getline(configfile, s);

        if (not s.size() || s[0] == '#' || s[0] == ';')
            continue;

        if (s[0] == '[' && s[s.size()-1] == ']') {
            string section(s.substr(1, s.size()-2));
            if (section != "global" && section != "homes")
                listR.push_back(section);
        }
    }

    return listR;
}

bool NXSamba::smbServerRunning(void)
{
    bool ret = true;
    int sock;
    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(445);

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        return false;
    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        ret = false;

    close(sock);

    return ret;
}

NXSamba::NXSamba()
{
    this->setSmbFile("/etc/samba/smb.conf");
}

NXSamba::NXSamba(string smbFile)
{
    this->setSmbFile(smbFile);
}
