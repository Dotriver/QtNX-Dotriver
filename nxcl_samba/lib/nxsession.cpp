/***************************************************************************
                                nxsession.cpp
                             -------------------
    begin                : Wed 26th July 2006
    modifications        : July 2007
    copyright            : (C) 2006 by George Wright
    modifications        : (C) 2007 Embedded Software Foundry Ltd. (U.K.)
                         :     Author: Sebastian James
                         : (C) 2008 Defuturo Ltd
                         :     Author: George Wright
    email                : seb@esfnet.co.uk, gwright@kde.org
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

// Enumerated type defining the stages through which the client goes when
// connecting
enum { HELLO_NXCLIENT,
    ACKNOWLEDGE,
    SHELL_MODE,
    AUTH_MODE,
    LOGIN,
    LIST_SESSIONS,
    PARSESESSIONS,
    STARTSESSION,
    FINISHED };

#define CLIENT_VERSION "3.0.0"

#include <iostream>

#include "notQt.h"
#include "nxclientlib.h"
#include "nxsession.h"

using namespace std;
using namespace nxcl;

NXSession::NXSession() :
    sessionDataSet(false),
    stage(HELLO_NXCLIENT),
    devurand_fd(-1),
    nxUsername("nouser"),
    nxPassword("nopass")
{
    setCallbacks(callbacks);
    setSessionName("");
    setSessionType("");
    setMemCache(32);
    setImageCache(8);
    setLinkType("adsl");
    setRender(true);
    setBackingstore("when_requested");
    setImageCompressionMethod(-1);
    setImageCompressionLevel(0);
    setGeometry("800x600+0+0");
    setKeyboard("defkeymap");
    setKbType("pc102/defkeymap");
    disableMedia();
    setAgentServer("");
    setAgentUser("");
    setAgentPass("");
    setCupsPort(0);
    disableFullscreen();
    enableEncryption();
    disableVirtualDesktop();
    setTerminate(false);
}

NXSession::~NXSession()
{
}

void NXSession::resetSession()
{
    this->stage = 0;
    this->sessionDataSet = false;
}

string NXSession::parseSSH(string message)
{
    dbgln ("NXSession::parseSSH called for: " + message);

    int response = parseResponse (message);
    string returnMessage;

#ifdef NXCL_USE_NXSSH
    if (response == 211) {
        if (doSSH == true) {
            returnMessage = "yes";
            doSSH = false;
        } else
            returnMessage = "no";
    }

    if (response == 204) { // Authentication failed
        returnMessage = "204";
    }
#endif

    if (response == 147) { // Server capacity reached
        returnMessage = "147";
        this->stage = FINISHED;
    }

    switch (this->stage) {
        case HELLO_NXCLIENT:
            dbgln ("HELLO_NXCLIENT stage");

	    if (message.find("Are you sure you want to continue connecting (yes/no)?") != string::npos)
            	returnMessage = "yes"; // FF-FIXME: Or 211?

	    if (message.find("assword") != string::npos)
            	returnMessage = nxPassword; // FF-FIXME: -> What to do? What to do?
	    
	    if (message.find("Permission denied") != string::npos || 
	            message.find("su: Authentication failure") != string::npos || 
		    message.find("Unknown id:") != string::npos)
                returnMessage = "204"; // Authentication failed

            if (message.find("HELLO NXSERVER - Version") != string::npos) {
                this->callbacks->authenticatedSignal();
                returnMessage = "hello NXCLIENT - Version ";
                returnMessage.append(CLIENT_VERSION);
                this->stage++;
            }

            break;
        case ACKNOWLEDGE:
            dbgln ("ACKNOWLEDGE stage");

            if (response == 105)
                this->stage++;

            break;
        case SHELL_MODE:
            dbgln ("SHELL_MODE stage");

            if (response == 105) {
                returnMessage = "SET SHELL_MODE SHELL";
                this->stage++;
            }

            break;
        case AUTH_MODE:
            dbgln ("AUTH_MODE stage");

            if (response == 105) {
                returnMessage = "SET AUTH_MODE PASSWORD";
                this->stage++;
            }

            break;
        case LOGIN:
            dbgln ("LOGIN stage");

            switch (response) {
                case 105:
                    returnMessage = "login";
                    break;
                case 101:
                    returnMessage = nxUsername;
                    break;
                case 102:
                    returnMessage = nxPassword;
                    break;
                case 103:
                    this->stage++;
                    break;
                case 404:
                    this->callbacks->loginFailedSignal();
            }

            break;
        case LIST_SESSIONS:
            dbgln ("LIST_SESSIONS stage");

            if (this->isTerminate()) {
                // Wait for termination
                dbgln ("Waiting for termination");

                if (response == 900) {
                    stringstream termsession;

                    termsession << "NX> 900 Session id: "
                        << this->getId()
                        << " terminated.";

                    if (message.find (termsession.str().c_str(), 0) == 0) {
                        // Session terminated.
                        this->setTerminate(false);
                    } else {
                        usleep (10000);
                    }
                }

            } else if (response == 105) {
                // Get a list of the available sessions on the server, for
                // given user, with given status, and any type. Not sure if
                // geometry is ignored or not.
                stringstream ss;

                // We want to list suspended or running sessions, with this
                // command:
                dbgln ("this->resumeSessions.size() == "
                        << this->resumeSessions.size());

                if (this->getSessionType() == "shadow") {
                    // This is how to list shadow sessions. Run NoMachine's
                    // client and see ~/.nx/temp/(pid)/sshlog for connection
                    // details
                    ss << "listsession --type=\"shadow\"";

                } else {

                    ss << "listsession --user=\"" << nxUsername
                        << "\" --status=\"suspended,running\" --geometry=\""
                        << this->getXRes() << "x"
                        << this->getYRes() << "x"
                        << this->getDepth()
                        << (this->renderEnabled() ? "+render" : "")

                        // If you leave --type blank, you can re-connect to any
                        // sessions available.
                        << "\" --type=\"" << this->getSessionType()
                        << "\"";
                }

                returnMessage = ss.str();
                this->stage++;
            }
            break;
        case PARSESESSIONS:
            dbgln ("PARSESESSIONS stage");

            if ((this->getSessionType() == "shadow" &&
                        response != 105) ||
                    (this->getSessionType() != "shadow" &&
                        response != 148)  ) {

                dbgln ("Building resumeSessions:"
                        << " resumeSessions.push_back(message);");

                this->resumeSessions.push_back(message);

            } else if ((this->getSessionType() == "shadow" &&
                        response == 105)
                    || (this->getSessionType() != "shadow" &&
                        response == 148)) {

                dbgln ("Parsing resumeSessions:"
                        << " parseResumeSessions(resumeSessions);");

                parseResumeSessions (this->resumeSessions);

                dbgln ("parseResumeSessions(resumeSessions) returned");

                // Now, the problem we have here, is that when
                // we return from the last 105 response, we
                // don't then get another stdout message to
                // act upon. So, we want to recurse back into
                // parseSSH to get onto the STARTSESSION stage here:
                returnMessage = this->parseSSH (message);
            }
            break;

        case STARTSESSION:
            dbgln ("STARTSESSION stage");
            if (response == 105 && sessionDataSet) {

                dbgln ("response is 105 and sessionDataSet is true");;
                int media = 0;
                string fullscreen = "";
                if (this->mediaEnabled()) {
                    media = 1;
                }

                if (this->fullscreenEnabled()) {
                    this->setGeometry("fullscreen");
                    fullscreen = "+fullscreen";
                }

                if (this->getSessionType() == "shadow" &&
                        !this->isTerminate()) {

                    dbgln ("It's a shadow session!");
                    stringstream ss;

                    // These are the session parameters that NoMachine's client
                    // sends for resume

                    ss << "attachsession "
                        << "--link=\"" << this->getLinkType() << "\" "
                        << "--backingstore=\""
                            << this->getBackingstore() << "\" "
                        << "--encryption=\"" << this->encryptionEnabled()
                            << "\" "
                        << "--cache=\"" << this->getMemCache() << "M\" "
                        << "--images=\"" << this->getImageCache() << "M\" "
                        // probably has been autodetected from my display
                        << "--shmem=\"1\" "
                        // probably has been autodetected from my display
                        << "--shpix=\"1\" "
                        // probably has been autodetected from my display
                        << "--strict=\"0\" "
                        // probably has been autodetected from my display
                        << "--composite=\"1\" "
                        << "--media=\"" << media << "\" "
                        << "--session=\"" << this->getSessionName()
                            << "\" "
                        << "--type=\"" << this->getSessionType()
                            << "\" "
                        // FIXME: This may be some other OS if you compile it on
                        // Sun, Windows, etc.
                        << "--client=\"linux\" "
                        << "--keyboard=\"" << this->getKeyboard()
                            << "\" "
                        << "--id=\"" << this->getId() << "\" "
                        // This may be the key?
                        << "--display=\"0\" "
                        << "--geometry=\"" << this->getGeometry()
                            << "\" ";

                    returnMessage = ss.str();

                    dbgln ("session parameter command: " + ss.str());

                    this->stage++;

                } else if (this->isTerminate()) {

                    stringstream ss;

                    // These are the session parameters that NoMachine's client
                    // sends for resume
                    ss << "Terminate --sessionid=\"" << this->getId()
                        << "\"";

                    returnMessage = ss.str();

                    dbgln ("session parameter command: " + ss.str());

                    // Back to listsessions after terminating a session.
                    this->stage -= 2;

                    // Clear the list of sessions to resume
                    this->resumeSessions.clear();
                    this->runningSessions.clear();

                } else if (this->isSuspended()) {

                    dbgln ("this->->suspended is true");

                    stringstream ss;

                    // These are the session parameters that NoMachine's client
                    // sends for resume
                    ss << "restoresession --id=\"" << this->getId() <<
                        "\" --session=\"" << this->getSessionName() <<
                        "\" --type=\"" << this->getSessionType() <<
                        "\" --cache=\"" << this->getMemCache() <<
                        "M\" --images=\"" << this->getImageCache() <<
                        "M\" --cookie=\"" << generateCookie() <<
                        "\" --link=\"" << this->getLinkType() <<
                        "\" --kbtype=\"" << this->getKbType() <<
                        "\" --nodelay=\"1\" --encryption=\""
                            << this->getEncryption() <<
                        "\" --backingstore=\""
                            << this->getBackingstore() <<
                        "\" --geometry=\"" << this->getGeometry() <<
                        "\" --media=\"" << media <<
                        "\" --agent_server=\""
                            << this->getAgentServer() <<
                        "\" --agent_user=\"" << this->getAgentUser() <<
                        "\" --agent_password=\""
                            << this->getAgentPass() << "\"";

                    returnMessage = ss.str();

                    dbgln ("session parameter command: " + ss.str());

                    this->stage++;

                } else {

                    dbgln ("this->suspended is false, and it's" <<
                            " not a shadow session.");

                    stringstream ss;

                    ss << "startsession --session=\""
                            << this->getSessionName()

                        << "\" --type=\"" << this->getSessionType()
                        << "\" --cache=\"" << this->getMemCache()
                        << "M\" --images=\"" << this->getImageCache()
                        << "M\" --cookie=\"" << generateCookie()
                        << "\" --link=\"" << this->getLinkType()
                        << "\" --render=\""
                            << (this->renderEnabled() ? 1 : 0)

                        << "\" --encryption=\""
                            << this->encryptionEnabled()

                        << "\" --backingstore=\""
                            << this->getBackingstore()

                        << "\" --imagecompressionmethod=\""
                        << this->getImageCompressionMethod()
                        << "\" --geometry=\"" << this->getGeometry()
                        << "\" --screeninfo=\"" << this->getXRes()
                        << "x" << this->getYRes() << "x"
                        << this->getDepth()
                        << (this->renderEnabled() ? "+render" : "")
                        << fullscreen << "\" --keyboard=\""
                            << this->getKeyboard()

                        << "\" --kbtype=\"" << this->getKbType()
                        << "\" --media=\"" << media
                        << "\" --agent_server=\""
                            << this->getAgentServer()

                        << "\" --agent_user=\""
                            << this->getAgentUser()

                        << "\" --agent_password=\""
                            << this->getAgentPass()

                        << "\"";

                    ss << " --title=\"sebtest\""; // testing a window title

                    if (this->getSessionType() == "unix-application") {
                        ss << " --application=\"" 
                            << this->getCustomCommand() << "\"";

                        if (this->virtualDesktopEnabled()) {
                            ss << " --rootless=\"0\" --virtualdesktop=\"1\"";
                        } else {
                            ss << " --rootless=\"1\" --virtualdesktop=\"0\"";
                        }

                    } else if
                        (this->getSessionType() == "unix-console") {

                        if (this->virtualDesktopEnabled()) {
                            ss << " --rootless=\"0\" --virtualdesktop=\"1\"";
                        } else {
                            ss << " --rootless=\"1\" --virtualdesktop=\"0\"";
                        }

                    } else if
                        (this->getSessionType() == "unix-default") {
                        // ignore this - does anyone use it?
                    }

                    returnMessage = ss.str();

                    dbgln ("session parameter command: " + ss.str());

                    this->stage++;
                }
            } else {
                dbgln ("either response is not 105 or sessionDataSet is"
                        << " false.");
            }
            break;

        case FINISHED:
            dbgln ("FINISHED stage. Response is " << response
                    << ". That should mean that session set up is complete.");
            this->callbacks->readyForProxySignal();
    }

    dbgln ("NXSession::parseSSH, about to return a message: " + returnMessage);

    if (!returnMessage.empty()) {
        returnMessage.append("\n");
        return returnMessage;
    } else
        return "";
}

int NXSession::parseResponse(string message)
{
    string::size_type idx1, idx2;

    int response;

    dbgln ("NXSession::parseResponse called for message:" << message);

    if ((idx1 = message.find ("notQProcess error", 0)) != string::npos) {

        dbgln ("Found notQProcess error");

        // This means a process crashed, we're going to return a number >100000
        // to indicate this.
        if ( ((idx2 = message.find ("crashed", 0)) != string::npos) && 
                idx2 > idx1) {

            stringstream ss;
            ss << message.substr((idx1+19), idx2-1-(idx1+19));

            // This is the pid that crashed
            ss >> response;

            // Add 100000 and return this
            response += 100000;

            return response;
        } else {
            dbgln ("Uh oh, didn't find \"crashed\"");
        }
    }

    // Find out the server response number
    // This will only be present in strings which contain "NX>"
    if (message.find("NX>") != string::npos && message.find("NX>") == 0) {
        idx1 = message.find("NX>") + 4;

        if ((idx2 = message.find(" ", idx1)) == string::npos) {
            if ((idx2 = message.find("\n", idx1)) == string::npos) {
                idx2 = message.size();
            }
        }

        if (idx2>idx1) {
            stringstream ss;
            ss << message.substr(idx1, idx2-idx1);
            ss >> response;
        } else {
            response = 0;
        }

    } else {
        response = 0;
    }

    dbgln ("NXSession::parseResponse() returning " << response);
    return response;
}

void NXSession::parseResumeSessions(list<string> rawdata)
{
    // Was: QStringList sessions, and got rawdata appended to it?
    list<string> sessions;
    list<string>::iterator iter, at;

    dbgln ("NXSession::parseResumeSessions called.");

    for (iter = rawdata.begin(); iter != rawdata.end(); iter++) {
        if (((*iter).find("-------") != string::npos) && !(*iter).empty()) {
            at = iter;
        }
    }

    for (iter = ++at; iter != rawdata.end(); iter++) {
        if ((!(*iter).find("NX> 148") != string::npos) && !(*iter).empty()) {
            sessions.push_back(*iter);
        }
    }

    list < vector<string> > rawsessions;
    list < vector<string> >::iterator rsIter;

    // Clean up each string in sessions[i], then push back
    // sessions[i] onto rawsessions., except that means
    // rawsessions is then just a list<string>...
    vector<string> session;
    vector<string>::iterator seshIter;

    for (iter = sessions.begin(); iter != sessions.end(); iter++) {
        session.clear();

        // Simplify one line of list<string> sessions
        (*iter) = notQtUtilities::simplify (*iter); 

        // Split one line of list<string> sessions into a vector<string>
        notQtUtilities::splitString (*iter, ' ', session); 

        // Add that to rawsessions
        rawsessions.push_back(session);
    }

    NXResumeData resData;

    for (rsIter = rawsessions.begin(); rsIter != rawsessions.end(); rsIter++) {
        stringstream ss1, ss2;
        int tmp;

        dbgln ("*rsIter.size() == " << (*rsIter).size());
        ss1 << (*rsIter)[0];
        ss1 >> tmp;

        resData.setDisplay(tmp);

        dbgln ("resData.display = " << resData.getDisplay());
        resData.setSessionType((*rsIter)[1]);

        dbgln ("resData.sessionType = " << resData.getSessionType());
        resData.setSessionId((*rsIter)[2]);

        dbgln ("resData.sessionID = " << resData.getSessionId());
        resData.setOptions((*rsIter)[3]);

        dbgln ("resData.options = " << resData.getOptions());
        ss2 << (*rsIter)[4];
        ss2 >> tmp;

        resData.setDepth(tmp);

        dbgln ("resData.depth = " << resData.getDepth());
        resData.setScreen((*rsIter)[5]);

        dbgln ("resData.screen = " << resData.getScreen());
        resData.setAvailable((*rsIter)[6]);

        dbgln ("resData.available = " << resData.getAvailable());
        resData.setSessionName((*rsIter)[7]);

        dbgln ("resData.sessionName = " << resData.getSessionName());
        this->runningSessions.push_back(resData);
    }

    if (this->runningSessions.size() != 0) {
        this->suspendedSessions = true;

        dbgln ("NXSession::parseResumeSessions(): Calling sessionsSignal.");

        // runningSessions is a list of NXResumeData
        this->callbacks->sessionsSignal (this->runningSessions);
    } else {
        dbgln ("NXSession::parseResumeSessions(): Calling"
                << " this->callbacks->noSessionsSignal()");

        // In case we previously had one resumable session,
        // which the user terminated, then we listsessions and
        // got no resumable sessions, we need to make sure
        // startsession is called, not restoresession. hence
        // set sessionData->suspended to false.
        this->setSuspended(false);
        this->callbacks->noSessionsSignal();
    }

    dbgln ("Increment stage");
    this->stage++;
    dbgln ("NXSession::parseResumeSessions() returning.");
}

void NXSession::wipeSessions()
{
    while (!this->runningSessions.empty()) {
        this->runningSessions.pop_front();
    }
}

string NXSession::generateCookie()
{
    unsigned long long int int1, int2;
    stringstream cookie;

    devurand_fd = open("/dev/urandom", O_RDONLY);

    fillRand((unsigned char*)&int1, sizeof(int1));
    fillRand((unsigned char*)&int2, sizeof(int2));
    cookie << int1 << int2;
    return cookie.str();
}

void NXSession::fillRand(unsigned char *buf, size_t nbytes)
{
    ssize_t r;
    unsigned char *where = buf;

    while (nbytes) {
        while ((r = read(devurand_fd, where, nbytes)) == -1)
            where  += r;
        nbytes -= r;
    }
}

bool NXSession::chooseResumable (int n)
{
    dbgln ("NXSession::chooseResumable called.");
    if (this->runningSessions.size() <= static_cast<unsigned int>(n)) {

        // No nth session to resume.
        dbgln ("No nth session to resume, return false.");
        return false;
    }

    // Set to false while we change contents of sessionData
    this->sessionDataSet = false;

    list<NXResumeData>::iterator it = this->runningSessions.begin();
    for (int i = 0; i<n; i++) { it++; }

    // If it's a shadow session, we don't want to replace "shadow" with
    // X11-local
    if (this->getSessionType() != "shadow") {
        this->getSessionType() = (*it).getSessionType();
    }

    this->setDisplay((*it).getDisplay());
    this->setSessionName((*it).getSessionName());
    this->setId((*it).getSessionId());

    stringstream geom;	

    // Plus render, if necessary
    geom << (*it).getScreen() << "x" << (*it).getDisplay();

    // FIXME: This not yet quite complete.
    // With depth in there too?
    this->setGeometry(geom.str());
    this->setSuspended(true);

    this->sessionDataSet = true;

    dbgln ("NXSession::chooseResumable returning true.");
    return true;
}

bool NXSession::terminateSession (int n)
{
    dbgln ("NXSession::terminateSession called.");
    if (this->runningSessions.size() <= static_cast<unsigned int>(n)) {

        // No nth session to terminate
        dbgln ("No nth session to terminate, return false.");
        return false;
    }

    // Set to false while we change the contents of sessionData
    this->sessionDataSet = false;

    list<NXResumeData>::iterator it = this->runningSessions.begin();
    for (int i = 0; i<n; i++) { it++; }

    this->setTerminate(true);
    this->setDisplay((*it).getDisplay());
    this->setSessionName((*it).getSessionName());
    this->setId((*it).getSessionId());
    this->setSuspended(true);

    this->sessionDataSet = true;

    return true;
}

