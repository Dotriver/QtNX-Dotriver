/***************************************************************************
                                nxdata.h
                             -------------------
    begin                : Wednesday 9th August 2006
    modifications        : July 2007
    copyright            : (C) 2006 by George Wright
    modifications        : (C) 2007 Embedded Software Foundry Ltd. (U.K.)
                         :     Author: Sebastian James
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

#ifndef _NXDATA_H_
#define _NXDATA_H_

#include <string>

/*!
 * Some definitions of numbers that we can send over to the frontend
 * client to tell it how we're getting along with the connection...
 */
#define NXCL_PROCESS_STARTED        1000001
#define NXCL_PROCESS_EXITED         1000002
#define NXCL_AUTH_FAILED            1000003
#define NXCL_AUTHENTICATING         1000004
#define NXCL_LOGIN_FAILED           1000005
#define NXCL_HOST_KEY_VERIFAILED    1000006
#define NXCL_INVOKE_PROXY           1000007
#define NXCL_STARTING               1000008
#define NXCL_FINISHED               1000009
#define NXCL_ALIVE                  1000010
#define NXCL_PROCESS_ERROR          1000011

using namespace std;

namespace nxcl {

	class NXData //commentaire bidon pour voir si ça marche
	{
	    public:
		string getServerHost(void)
		{
		    return this->serverHost;
		}

		int getServerPort(void)
		{
		    return this->serverPort;
		}

		string getSessionName(void)
		{
		    return this->sessionName;
		}

		string getSessionType()
		{
		    return this->sessionType;
		}

		int getMemCache(void)
		{
		    return this->memCache;
		}

		int getImageCache(void)
		{
		    return this->imageCache;
		}

		string getLinkType(void)
		{
		    return this->linkType;
		}

		bool getRender(void)
		{
		    return this->render;
		}

		bool renderEnabled(void)
		{
		    return this->render;
		}

		string getBackingstore(void)
		{
		    return this->backingstore;
		}

		int getImageCompressionMethod(void)
		{
		    return this->imageCompressionMethod;
		}

		int getImageCompressionLevel(void)
		{
		    return this->imageCompressionLevel;
		}

		string getGeometry(void)
		{
		    return this->geometry;
		}

		string getKeyboard(void)
		{
		    return this->keyboard;
		}
		
		string getKbType(void)
		{
		    return this->kbtype;
		}

		bool getMedia(void)
		{
		    return this->media;
		}

		bool mediaEnabled(void)
		{
		    return this->media;
		}
		
		
		
		
		bool getMicrophone(void)
		{
			return this->microphone;
		}
		
		bool microphoneEnabled(void)
		{
			return this->microphone;
		}
		
		
		

		string getAgentServer(void)
		{
		    return this->agentServer;
		}

		string getAgentUser(void)
		{
		    return this->agentUser;
		}

		string getAgentPass(void)
		{
		    return this->agentPass;
		}

		int getCupsPort(void)
		{
		    return cups;
		}

		bool cupsEnabled(void)
		{
		    return this->cups > 0 && this->cups < 65536;
		}

		string getKey(void)
		{
		    return this->key;
		}

		bool getEncryption(void)
		{
		    return this->encryption;
		}

		bool encryptionEnabled(void)
		{
		    return this->encryption;
		}

		bool getFullscreen(void)
		{
		    return this->fullscreen;
		}
		
		bool fullscreenEnabled(void)
		{
		    return this->fullscreen;
		}

		bool getVirtualDesktop()
		{
		    return this->virtualDesktop;
		}

		bool virtualDesktopEnabled(void)
		{
		    return this->virtualDesktop;
		}

		string getCustomCommand(void)
		{
		    return this->customCommand;
		}

                bool isHttpProxyEnabled(void)
                {
                    return this->httpProxyEnabled;
                }

                string getHttpProxyHost(void)
                {
                    return this->httpProxyHost;
                }

                unsigned short getHttpProxyPort(void)
                {
                    return this->httpProxyPort;
                }

                string getHttpProxyUsername(void)
                {
                    return this->httpProxyUsername;
                }

                string getHttpProxyPassword(void )
                {
                    return this->httpProxyPassword;
                }

		void setServerHost(string server)
		{
		    this->serverHost = server;
		}

		void setServerPort(int port)
		{
		    this->serverPort = port;
		}

		void setSessionName(string sessName)
		{
		    this->sessionName = sessName;
		}

		void setSessionType(string sessType)
		{
		    this->sessionType = sessType;
		}

		void setMemCache(int mem)
		{
		    this->memCache = mem;
		}

		void setImageCache(int image)
		{
		    this->imageCache = image;
		}

		void setLinkType(string linkType)
		{
		    this->linkType = linkType;
		}

		void setRender(bool render)
		{
		    this->render = render;
		}

		void enableRender(void)
		{
		    this->render = true;
		}

		void disableRender(void)
		{
		    this->render = false;
		}

		void setBackingstore(string bs)
		{
		    this->backingstore = bs;
		}

		void setImageCompressionMethod(int icm)
		{
		    this->imageCompressionMethod = icm;
		}

		void setImageCompressionLevel(int icl)
		{
		    this->imageCompressionLevel = icl;
		}

		void setGeometry(string geom)
		{
		    this->geometry = geom;
		}

		void setKeyboard(string kbd)
		{
		    this->keyboard = kbd;
		}

		void setKbType(string kbtype)
		{
		    this->kbtype = kbtype;
		}

		void setMedia(bool media)
		{
		    this->media = media;
		}

		void enableMedia(void)
		{
		    this->media = true;
		}

		void disableMedia(void)
		{
		    this->media = false;
		}
		
		
		

		void setMicrophone(bool microphone)
		{
		    this->microphone = microphone;
		}

		void enableMicrophone(void)
		{
		    this->microphone = true;
		}

		void disableMicrophone(void)
		{
		    this->microphone = false;
		}
		
		
		

		void setAgentServer(string agentServer)
		{
		    this->agentServer = agentServer;
		}

		void setAgentUser(string agentUser)
		{
		    this->agentUser = agentUser;
		}

		void setAgentPass(string agentPass)
		{
		    this->agentPass = agentPass;
		}

		void setCupsPort(int port)
		{
		    this->cups = port;
		}

		void setKey(string key)
		{
		    this->key = key;
		}

		void setEncryption(bool encryption)
		{
		    this->encryption = encryption;
		}

		void enableEncryption(void)
		{
		    this->encryption = true;
		}

		void disableEncryption(void)
		{
		    this->encryption = false;
		}

		void setFullscreen(bool fs)
		{
		    this->fullscreen = fs;
		}

		void enableFullscreen(void)
		{
		    this->fullscreen = true;
		}

		void disableFullscreen(void)
		{
		    this->fullscreen = false;
		}

		void setVirtualDesktop(bool vd)
		{
		    this->virtualDesktop = vd;
		}

		void enableVirtualDesktop(void)
		{
		    this->virtualDesktop = true;
		}

		void disableVirtualDesktop(void)
		{
		    this->virtualDesktop = false;
		}

		void setCustomCommand(string customCommand)
		{
		    this->customCommand = customCommand;
		}

                void enableHttpProxy(void)
                {
                    this->httpProxyEnabled = true;
                }

                void disableHttpProxy(void)
                {
                    this->httpProxyEnabled = false;
                }

                void setHttpProxyHost(string host)
                {
                    this->httpProxyHost = host;
                }

                void setHttpProxyPort(unsigned short port)
                {
                    this->httpProxyPort = port;
                }

                void setHttpProxyUsername(string username)
                {
                    this->httpProxyUsername = username;
                }

                void setHttpProxyPassword(string password)
                {
                    this->httpProxyPassword = password;
                }

	    protected:
		string serverHost;
		int serverPort;
		string sessionName;
		string sessionType;
		int memCache;
		int imageCache;
		string linkType;
		bool render;
		string backingstore;
		int imageCompressionMethod;
		int imageCompressionLevel;
		string geometry;
		string keyboard;
		string kbtype;
		bool media;
		
		// pour le microphone
		bool microphone;
		
		
		string agentServer;
		string agentUser;
		string agentPass;
		int cups;
		string key;
		bool encryption;
		bool fullscreen;
		bool virtualDesktop;
		string customCommand;
                bool httpProxyEnabled;
                string httpProxyHost;
                unsigned short httpProxyPort;
                string httpProxyUsername;
                string httpProxyPassword;
	};

	class NXConfigData : public NXData
	{
	    public:
		string getSessionUser(void)
		{
		    return this->sessionUser;
		}

		string getSessionPass(void)
		{
		    return this->sessionPass;
		}

                bool getRememberPass(void)
                {
                    return this->rememberPass;
                }

		void setSessionUser(string user)
		{
		    this->sessionUser = user;
		}

		void setSessionPass(string pass)
		{
		    this->sessionPass = pass;
		}

                void setRememberPass(bool rp)
                {
                    this->rememberPass = rp;
                }

	    protected:
		string sessionUser;
		string sessionPass;
                bool rememberPass;
	};

	class NXSessionData : public NXData
	{
	    public:
		string getId(void)
		{
		    return this->id;
		}

		bool isSuspended(void)
		{
		    return this->suspended;
		}

		int getXRes(void)
		{
		    return this->xRes;
		}

		int getYRes(void)
		{
		    return this->yRes;
		}

		int getDepth(void)
		{
		    return this->depth;
		}

		int getDisplay(void)
		{
		    return this->display;
		}

		bool isTerminate(void)
		{
		    return this->terminate;
		}

		void setId(string id)
		{
		    this->id = id;
		}

		void setSuspended(bool suspend)
		{
		    this->suspended = suspend;
		}

		void setXRes(int xRes)
		{
		    this->xRes = xRes;
		}

		void setYRes(int yRes)
		{
		    this->yRes = yRes;
		}

		void setDepth(int depth)
		{
		    this->depth = depth;
		}

		void setDisplay(int display)
		{
		    this->display = display;
		}

		void setTerminate(bool terminate)
		{
		    this->terminate = terminate;
		}

	    protected:
		string id;
		bool suspended;
		int xRes;
		int yRes;
		int depth;
		int display;
		bool terminate;
	};

	class NXResumeData
	{
	    public:
		int getDisplay(void)
		{
		    return this->display;
		}

		string getSessionType(void)
		{
		    return this->sessionType;
		}

		string getSessionId(void)
		{
		    return this->sessionID;
		}

		string getOptions(void)
		{
		    return this->options;
		}

		int getDepth(void)
		{
		    return this->depth;
		}

		string getScreen(void)
		{
		    return this->screen;
		}

		string getAvailable(void)
		{
		    return this->available;
		}

		string getSessionName(void)
		{
		    return this->sessionName;
		}

		void setDisplay(int display)
		{
		    this->display = display;
		}

		void setSessionType(string sessionType)
		{
		    this->sessionType = sessionType;
		}

		void setSessionId(string sessionID)
		{
		    this->sessionID = sessionID;
		}

		void setOptions(string options)
		{
		    this->options = options;
		}

		void setDepth(int depth)
		{
		    this->depth = depth;
		}

		void setScreen(string screen)
		{
		    this->screen = screen;
		}

		void setAvailable(string available)
		{
		    this->available = available;
		}

		void setSessionName(string sessionName)
		{
		    this->sessionName = sessionName;
		}
	    protected:
		int display;
		string sessionType;
		string sessionID;
		string options;
		int depth;
		string screen;
		string available;
		string sessionName;

	};

} // namespace
#endif
