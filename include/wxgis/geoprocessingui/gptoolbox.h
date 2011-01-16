/******************************************************************************
 * Project:  wxGIS (GIS Toolbox)
 * Purpose:  toolbox classes.
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

#include "wxgis/catalogui/catalogui.h"
#include "wxgis/geoprocessingui/geoprocessingui.h"
#include "wxgis/geoprocessing/gptoolmngr.h"
#include "wxgis/core/config.h"

class WXDLLIMPEXP_GIS_GPU wxGxRootToolbox;
/////////////////////////////////////////////////////////////////////////
// wxGxToolbox
/////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_GIS_GPU wxGxToolbox :
	public IGxObjectUI,
	public IGxObjectContainer
{
public:
    wxGxToolbox(void);
	wxGxToolbox(wxGxRootToolbox* pRootToolbox, wxXmlNode* pDataNode = NULL, wxIcon LargeToolboxIcon = wxNullIcon, wxIcon SmallToolboxIcon = wxNullIcon, wxIcon LargeToolIcon = wxNullIcon, wxIcon SmallToolIcon = wxNullIcon);
	virtual ~wxGxToolbox(void);
	//IGxObject
	virtual void Detach(void);
	virtual wxString GetName(void);
    virtual wxString GetBaseName(void){return GetName();};
    virtual wxString GetInternalName(void){return wxEmptyString;};
	virtual wxString GetCategory(void){return wxString(_("Toolbox"));};
	virtual void Refresh(void);
	//IGxObjectUI
	virtual wxIcon GetLargeImage(void);
	virtual wxIcon GetSmallImage(void);
	virtual wxString ContextMenu(void){return wxString(wxT("wxGxToolBox.ContextMenu"));};
	virtual wxString NewMenu(void){return wxString(wxT("wxGxToolBox.NewMenu"));};
	//IGxObjectContainer
	virtual bool DeleteChild(IGxObject* pChild);
	virtual bool AreChildrenViewable(void){return true;};
	virtual bool HasChildren(void){LoadChildren(); return m_Children.size() > 0 ? true : false;};
	//wxGxToolbox
	virtual void LoadChildren(void);
	virtual void LoadChildrenFromXml(wxXmlNode* pNode);
	virtual void EmptyChildren(void);
protected:
	wxString m_sName;
	bool m_bIsChildrenLoaded;
    wxGxRootToolbox* m_pRootToolbox;
    wxXmlNode* m_pDataNode;
    wxIcon m_LargeToolboxIcon, m_SmallToolboxIcon;
    wxIcon m_LargeToolIcon, m_SmallToolIcon;
};

/////////////////////////////////////////////////////////////////////////
// wxGxRootToolbox
/////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_GIS_GPU wxGxRootToolbox :
	public wxGxToolbox,
    public IGxRootObjectProperties,
    public IToolManagerUI,
    public wxObject
{
   DECLARE_DYNAMIC_CLASS(wxGxRootToolbox)
public:
	wxGxRootToolbox(void);
	virtual ~wxGxRootToolbox(void);
	//IGxObject
	virtual void Detach(void);
	virtual wxString GetName(void){return wxString(_("Toolboxes"));};
    virtual wxString GetBaseName(void){return GetName();};
    //IGxRootObjectProperties
    virtual void Init(wxXmlNode* pConfigNode);
    virtual wxXmlNode* GetProperties(void);
	//wxGxRootToolbox
	virtual void LoadChildren(void);
	virtual wxGISGPToolManager* GetGPToolManager(void);
    //IToolManagerUI
	virtual IGPTool* GetGPTool(wxString sToolName);
	virtual void OnExecuteTool(wxWindow* pParentWnd, IGPTool* pTool, IGPCallBack* pCallBack, bool bSync);
    virtual bool OnPrepareTool(wxWindow* pParentWnd, IGPTool* pTool, IGPCallBack* pCallBack, bool bSync);
protected:
	wxString m_sPath;
	bool m_bIsChildrenLoaded;
    wxXmlNode* m_pPropNode;
    wxGISAppConfig* m_pConfig;
    wxGISGPToolManager* m_pToolMngr;
};

/** \class wxGxFavoritesToolbox gptoolbox.h
 *  \brief The most popular tools.
 */

class WXDLLIMPEXP_GIS_GPU wxGxFavoritesToolbox :
	public IGxObjectUI,
	public IGxObjectContainer,
    public IGxObjectSort
{
public:
	wxGxFavoritesToolbox(wxGxRootToolbox* pRootToolbox, short nMaxCount = 10, wxIcon LargeToolIcon = wxNullIcon, wxIcon SmallToolIcon = wxNullIcon);
	virtual ~wxGxFavoritesToolbox(void);
	//IGxObject
	virtual void Detach(void);
	virtual wxString GetName(void);
    virtual wxString GetBaseName(void){return GetName();};
    virtual wxString GetInternalName(void){return wxEmptyString;};
	virtual wxString GetCategory(void){return wxString(_("Toolbox"));};
	virtual void Refresh(void);
	//IGxObjectUI
	virtual wxIcon GetLargeImage(void);
	virtual wxIcon GetSmallImage(void);
	virtual wxString ContextMenu(void){return wxEmptyString;};
	virtual wxString NewMenu(void){return wxEmptyString;};
	//IGxObjectContainer
	virtual bool DeleteChild(IGxObject* pChild);
	virtual bool AreChildrenViewable(void){return true;};
	virtual bool HasChildren(void){LoadChildren(); return m_Children.size() > 0 ? true : false;};
	//IGxObjectSort
    virtual bool IsAlwaysTop(void){return true;};
	virtual bool IsSortEnabled(void){return false;};
	//wxGxToolbox
	virtual void LoadChildren(void);
	virtual void EmptyChildren(void);
protected:
	bool m_bIsChildrenLoaded;
    wxGxRootToolbox* m_pRootToolbox;
    short m_nMaxCount;
    wxIcon m_LargeToolIcon, m_SmallToolIcon;
};

/** \class wxGxToolExecute gptoolbox.h
 *  \brief The executed and pending tools.
 */

class WXDLLIMPEXP_GIS_GPU wxGxToolExecute :
	public IGxObjectUI,
    public IGxObjectSort,
	public IGxObjectContainer,
    public wxGISGPToolManager
{
public:
	wxGxToolExecute(wxGxRootToolbox* pRootToolbox, wxXmlNode* pToolsNode);
	virtual ~wxGxToolExecute(void);
	//IGxObject
	virtual void Detach(void);
	virtual wxString GetName(void);
    virtual wxString GetBaseName(void){return GetName();};
    virtual wxString GetInternalName(void){return wxEmptyString;};
	virtual wxString GetCategory(void){return wxString(_("Toolbox"));};
	virtual void Refresh(void);
	//IGxObjectUI
	virtual wxIcon GetLargeImage(void);
	virtual wxIcon GetSmallImage(void);
	virtual wxString ContextMenu(void){return wxEmptyString;};
	virtual wxString NewMenu(void){return wxEmptyString;};
	//IGxObjectSort
    virtual bool IsAlwaysTop(void){return true;};
	virtual bool IsSortEnabled(void){return false;};
	//IGxObjectContainer
	virtual bool DeleteChild(IGxObject* pChild);
	virtual bool AreChildrenViewable(void){return false;};
	virtual bool HasChildren(void){return m_Children.size() > 0 ? true : false;};
    // wxGISGPToolManager
    virtual int OnExecute(IGPTool* pTool, ITrackCancel* pTrackCancel = NULL, IGPCallBack* pCallBack = NULL);
    virtual void StartProcess(size_t nIndex);
    //virtual void CancelProcess(size_t nIndex);
    virtual void OnFinish(IProcess* pProcess, bool bHasErrors);
protected:
    wxGxRootToolbox* m_pRootToolbox;
    wxIcon m_LargeToolIcon, m_SmallToolIcon;
};


/////////////////////////////////////////////////////////////////////////
// wxGxTool
/////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_GIS_GPU wxGxTool :
    public IGxObject,
	public IGxObjectUI,
    public IGxObjectWizard
{
public:
	wxGxTool(wxGxRootToolbox* pRootToolbox, wxXmlNode* pDataNode = NULL, wxIcon LargeToolIcon = wxNullIcon, wxIcon SmallToolIcon = wxNullIcon);
    wxGxTool(wxGxRootToolbox* pRootToolbox, wxString sInternalName, wxIcon LargeToolIcon = wxNullIcon, wxIcon SmallToolIcon = wxNullIcon);
	virtual ~wxGxTool(void);
	//IGxObject
    virtual wxString GetName(void){return m_sName;};
    virtual wxString GetBaseName(void){return GetName();};
    virtual wxString GetInternalName(void){return wxEmptyString;};
	virtual wxString GetCategory(void){return wxString(_("Tool"));};
    virtual bool Attach(IGxObject* pParent, IGxCatalog* pCatalog);
	//IGxObjectUI
	virtual wxIcon GetLargeImage(void);
	virtual wxIcon GetSmallImage(void);
	virtual wxString ContextMenu(void){return wxString(wxT("wxGxTool.ContextMenu"));};
	virtual wxString NewMenu(void){return wxEmptyString;};
    //IGxObjectWizard
    virtual bool Invoke(wxWindow* pParentWnd);
protected:
	//wxString m_sPath;
	wxString m_sName, m_sInternalName;
    wxXmlNode* m_pDataNode;
    wxGxRootToolbox* m_pRootToolbox;
    wxIcon m_LargeToolIcon, m_SmallToolIcon;
};

