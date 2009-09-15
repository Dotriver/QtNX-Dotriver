#ifndef _NXSERVICE_H
#define _NXSERVICE_H

#include <string>
#include "notQt.h"
#include "nxclientlib.h"

#include <string>

using namespace std;

namespace nxcl {

    class NXUtility {
        public:
            static int findUnusedPort(unsigned short, unsigned short);
            /*!
             * Try a number of different paths to try to find the
             * program prog's full path.
             *
             * \param prog The program to find, likely to be nxssh
             * or nxproxy.
             *
             * \return The full path; e.g. /usr/bin/nxssh
             */
            static string getPath (string);

    };

    class NXSound {
        private:
            string nxesdPath;
            notQProcess *nxesdProcess;
        public:
            NXSound(NXClientLibCallbacks *);
            int startSoundServer(NXClientLib *);
    };
	
    class NXMicrophone {
        private:
            string microStreamerPath;
            notQProcess *microStreamerProcess;
        public:
            NXMicrophone(NXClientLibCallbacks *);
            int startMicrophoneStreaming(NXClientLib *);
    };
}

#endif
