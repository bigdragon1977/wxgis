/******************************************************************************
 * Project:  wxGIS (GIS Toolbox)
 * Purpose:  wxGxToolboxView class.
 * Author:   Bishop (aka Barishnikov Dmitriy), polimax@mail.ru
 ******************************************************************************
*   Copyright (C) 2009-2010 Bishop
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

#include "wxgis/geoprocessingui/geoprocessingui.h"
#include "wxgis/catalogui/gxview.h"
//#include "wxgis/geoprocessingui/gptasksview.h"

#include "wx/aui/aui.h"

class WXDLLIMPEXP_GIS_GPU wxGxToolboxView :
	public wxAuiNotebook,
	public wxGxView
{
    DECLARE_DYNAMIC_CLASS(wxGxToolboxView)
public:
    wxGxToolboxView(void);
	wxGxToolboxView(wxWindow* parent, wxWindowID id = TOOLVIEWCTRLID, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
	virtual ~wxGxToolboxView(void);
	virtual wxWindow* GetCurrentWnd(void);
//IGxView
    virtual bool Create(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxAUI_NB_BOTTOM | wxNO_BORDER | wxAUI_NB_TAB_MOVE, const wxString& name = wxT("ToolboxView"));
	virtual bool Activate(IGxApplication* application, wxXmlNode* pConf);
	virtual void Deactivate(void);
//Events
	//void OnAUINotebookPageChanged(wxAuiNotebookEvent& event);
protected:
    IApplication* m_pApp;
    //wxGxTasksView* m_pGxTasksView;
	//std::vector<wxGxTab*> m_Tabs;
	//IConnectionPointContainer *m_pConnectionPointSelection;
	//long m_ConnectionPointSelectionCookie;
	//IGxSelection* m_pSelection;

//DECLARE_EVENT_TABLE()
};
