/******************************************************************************
 * Project:  wxGIS (GIS Remote)
 * Purpose:  wxGxRemoteServerUI class.
 * Author:   Bishop (aka Barishnikov Dmitriy), polimax@mail.ru
 ******************************************************************************
*   Copyright (C) 2010 Bishop
*
*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/
#pragma once

#include "wxgis/remoteserverui/remoteserverui.h"
#include "wxgis/remoteserver/gxremoteserver.h"
#include "wxgis/catalogui/catalogui.h"

/** \class wxGxRemoteServerUI gxremoteserverui.h
    \brief A Remote Server UI GxObject.
*/
class WXDLLIMPEXP_GIS_RSU wxGxRemoteServerUI :
	public wxGxRemoteServer,
	public IGxObjectUI,
	public IGxObjectWizard
{
public:
	wxGxRemoteServerUI(INetClientConnection* pNetConn);
	virtual ~wxGxRemoteServerUI(void);
	//IGxObjectUI
	virtual wxIcon GetLargeImage(void);
	virtual wxIcon GetSmallImage(void);
	virtual wxString ContextMenu(void){return wxString(wxT("wxGxRemoteServerUI.ContextMenu"));};
	virtual wxString NewMenu(void){return wxEmptyString;};
    //IGxObjectWizard
    virtual bool Invoke(wxWindow* pParentWnd);
    //wxGxRemoteServer
    virtual bool Connect(void);
	virtual void EmptyChildren(void);
    virtual void ProcessMessage(WXGISMSG msg, wxXmlNode* pChildNode);
	virtual bool Attach(IGxObject* pParent, IGxCatalog* pCatalog);
protected:
    wxIcon m_SmallIcon, m_LargeIcon;
    wxIcon m_SmallDsblIcon, m_LargeDsblIcon;
    wxIcon m_SmallAuthIcon, m_LargeAuthIcon;
};
