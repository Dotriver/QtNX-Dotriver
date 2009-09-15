/***************************************************************************
 *  *  qtnxresource.cpp
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
 ****************************************************************************/


#ifndef _NXSERVICE_H
#define _NXSERVICE_H

#include <string>
#include <vector>

using namespace std;

namespace nxcl {

    class Resource
    {
        private:
	    string resourceName;
            string resourcePath;
        public:
            string getResourceName(void)
            {
                return this->resourceName;
            }

            string getResourcePath(void)
            {
                return this->resourcePath;
            }

            void setResourceName(string resourceName)
            {
                this->resourceName = resourceName;
            }

            void setResourcePath(string resourcePath)
            {
                this->resourcePath = resourcePath;
            }
    };

    class NXSambaMount : public Resource
    {
        private:
            string mountDir;
            string username;
            string password;

        public:
            string getMountDir()
            {
                return this->mountDir;
            }

            string getUsername()
            {
                return this->username;
            }

            string getPassword()
            {
                return this->password;
            }

            void setMountDir(string mountDir)
            {
                this->mountDir = mountDir;
            }

            void setUsername(string username)
            {
                this->username = username;
            }

            void setPassword(string password)
            {
                this->password = password;
            }
     };

    class NXSamba
    {
        public:
            NXSamba();
            NXSamba(string);
            vector<string> listLocalResource();
            static bool smbServerRunning();

            void setSmbFile(string smbFile)
            {
                this->smbFile = smbFile;
            }

        private:
            string smbFile;
    };
}

#endif
