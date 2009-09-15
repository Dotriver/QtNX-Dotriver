#include "nxservice.h"
#include "nxclientlib.h"
#include "nxclientlib_i18n.h"

extern "C" {
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
}

using namespace std;
using namespace nxcl;

NXSound::NXSound(NXClientLibCallbacks *callbacks) :
    nxesdProcess(new notQProcess())
{
    nxesdProcess->setCallbacks(callbacks);
}

NXMicrophone::NXMicrophone(NXClientLibCallbacks *callbacks) :
    microStreamerProcess(new notQProcess())
{
    microStreamerProcess->setCallbacks(callbacks);
}

int NXSound::startSoundServer(NXClientLib *NXLib)
{
    list<string> arguments;
    int port = NXUtility::findUnusedPort(6000, 6010);
    stringstream ss;
    string nxesdPath = NXUtility::getPath("nxesd");

    if (port < 0)
        return -1;
    ss << port;
    arguments.push_back("nxesd");
    arguments.push_back("-port");
    arguments.push_back(ss.str());
    arguments.push_back("-nobeeps");
    arguments.push_back("-tcp");
    arguments.push_back("-bind");
    arguments.push_back("127.0.0.1");

    this->nxesdProcess->start(nxesdPath, arguments);

    if (this->nxesdProcess->waitForStarted() == false) {
        NXLib->externalCallbacks->write
            (NXCL_PROCESS_ERROR, _("Error starting nxesd!"));
        NXLib->setIsFinished(true);
    }

    return port;
}

int NXMicrophone::startMicrophoneStreaming(NXClientLib *NXLib)
{
    list<string> arguments;
    int port = NXUtility::findUnusedPort(6000, 6010);
    stringstream ss;
    string microStreamerPath = "/usr/bin/";

    if (port < 0)
        return -1;
    ss << port;
    arguments.push_back("microStreamer");
    arguments.push_back(ss.str());

    this->microStreamerProcess->start(microStreamerPath, arguments);

    if (this->microStreamerProcess->waitForStarted() == false) {
        NXLib->externalCallbacks->write
            (NXCL_PROCESS_ERROR, _("Error starting Microphone Streaming!"));
        NXLib->setIsFinished(true);
    }

    return port;
}

int NXUtility::findUnusedPort(unsigned short start, unsigned short end)
{
    int i, sock, ret;
    struct sockaddr_in addr;

    if (end < start || end > 65535 || start <= 0)
        return -1;

    for (i = start; i <= end; i++) {
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(i);
        addr.sin_addr.s_addr = inet_addr("127.0.0.1");

        sock = socket(PF_INET, SOCK_STREAM, 0);
        if (sock < 0)
            continue;
        ret = bind(sock, (struct sockaddr *)&addr, sizeof(addr));
        close(sock);
        if (!ret)
            break;
    }

    if (i == (end + 1)) {
        return -1;
    }

    return i;
}

string NXUtility::getPath (string prog)
{
    string pathProg;
    string path = string(getenv("PATH")) + ":/usr/NX/bin";
    struct stat st;
    list<string> msglist;
    list<string>::iterator msgiter;

    notQtUtilities::splitString (path, ':', msglist);

    for (msgiter = msglist.begin(); msgiter != msglist.end(); msgiter++) {
        pathProg = *msgiter + "/" + prog;
	if(stat(pathProg.c_str(), &st))
	    continue;

        if (S_ISREG (st.st_mode) || S_ISLNK (st.st_mode))
            return pathProg; 
    }
    dbgln (prog + " not found in " + path);
    
    return prog;
}

