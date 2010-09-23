/******************************************************************************
 * Project:  wxGIS (GIS Catalog)
 * Purpose:  Catalog main header.
 * Author:   Bishop (aka Barishnikov Dmitriy), polimax@mail.ru
 ******************************************************************************
*   Copyright (C) 2009  Bishop
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

#include "wxgis/datasource/datasource.h"
#include "wx/filename.h"

#define APP_NAME wxT("wxGISCatalog")
#define APP_VER wxT("0.2.1")

//#include <wx/dynload.h>
//#include <wx/dynlib.h>
//#include <algorithm>
//#include <map>

#define NOTFIRESELID    1010


enum wxGISEnumSaveObjectResults
{
	enumGISSaveObjectNone = 0x0000,
	enumGISSaveObjectAccept = 0x0001,
	enumGISSaveObjectExists = 0x0002,
	enumGISSaveObjectDeny = 0x0004
};

class IGxObject;
typedef std::vector<IGxObject*> GxObjectArray;

class IGxSelection
{
public:
	enum wxGISEnumInitiators
	{
		INIT_ALL = -2,
		INIT_NONE = -1
	} Initiator;
	virtual ~IGxSelection(void){};
	virtual void Select( IGxObject* pObject,  bool appendToExistingSelection, long nInitiator ) = 0;
	virtual void Select( IGxObject* pObject) = 0;
	virtual void Unselect(IGxObject* pObject, long nInitiator) = 0;
	virtual void Clear(long nInitiator) = 0;
	virtual size_t GetCount(void) = 0;
	virtual size_t GetCount(long nInitiator) = 0;
	virtual IGxObject* GetSelectedObjects(size_t nIndex) = 0;
	virtual IGxObject* GetSelectedObjects(long nInitiator, size_t nIndex) = 0;
	virtual IGxObject* GetLastSelectedObject(void) = 0;
	virtual void SetInitiator(long nInitiator) = 0;
    virtual void Do(IGxObject* pObject) = 0;
    virtual bool CanRedo() = 0;
	virtual bool CanUndo() = 0;
	virtual void RemoveDo(wxString sPath) = 0;
    virtual wxString Redo(int nPos = -1) = 0;
    virtual wxString Undo(int nPos = -1) = 0;
    virtual void Reset() = 0;
    virtual size_t GetDoSize() = 0;
    virtual int GetDoPos(void) = 0;
    virtual wxString GetDoPath(size_t nIndex) = 0;
};

class IGxSelectionEvents
{
public:
	virtual ~IGxSelectionEvents(void){};
	virtual void OnSelectionChanged(IGxSelection* Selection, long nInitiator) = 0;
};

class IGxCatalog
{
public:
	IGxCatalog(void) : m_bShowHidden(false), m_bShowExt(true), m_pSelection(NULL), m_pConf(NULL){};
	virtual ~IGxCatalog(void){};
	virtual wxString ConstructFullName(IGxObject* pObject) = 0;
	virtual bool GetChildren(wxString sParentDir, wxArrayString* pFileNames, GxObjectArray* pObjArray) = 0;
	virtual bool GetShowHidden(void){return m_bShowHidden;};
	virtual bool GetShowExt(void){return m_bShowExt;};
	virtual void SetShowHidden(bool bShowHidden){m_bShowHidden = bShowHidden;};
	virtual void SetShowExt(bool bShowExt){m_bShowExt = bShowExt;};
	virtual void ObjectAdded(IGxObject* pObject) = 0;
	virtual void ObjectChanged(IGxObject* pObject) = 0;
	virtual void ObjectDeleted(IGxObject* pObject) = 0;
	virtual void ObjectRefreshed(IGxObject* pObject) = 0;
	virtual IGxSelection* GetSelection(void){return m_pSelection;};
	virtual IGxObject* ConnectFolder(wxString sPath, bool bSelect = true) = 0;
	virtual void DisconnectFolder(wxString sPath, bool bSelect = true) = 0;
	virtual void SetLocation(wxString sPath) = 0;
    virtual IGISConfig* GetConfig(void){return m_pConf;};
    virtual void Undo(int nPos = -1) = 0;
    virtual void Redo(int nPos = -1) = 0;
protected:
	bool m_bShowHidden, m_bShowExt;
	IGxSelection* m_pSelection;
    IGISConfig* m_pConf;
};


class IGxObject
{
public:
	virtual ~IGxObject(void){};
	virtual bool Attach(IGxObject* pParent, IGxCatalog* pCatalog)
	{
		m_pParent = pParent;
		m_pCatalog = pCatalog;
		return true;
	};
	virtual void Detach(void)
	{
		m_pParent = NULL;
		m_pCatalog = NULL;
	};
	virtual wxString GetName(void) = 0;
	virtual wxString GetFullName(void)
	{
		if(m_pCatalog)
			return m_pCatalog->ConstructFullName(this);
		else
			return wxEmptyString;
	};
	virtual wxString GetCategory(void) = 0;
	virtual IGxObject* GetParent(void){return m_pParent;};
	virtual void Refresh(void){};
protected:
	IGxObject* m_pParent;
	IGxCatalog* m_pCatalog;
};

class IGxObjectUI
{
public:
	virtual ~IGxObjectUI(void){};
	virtual wxIcon GetLargeImage(void) = 0;
	virtual wxIcon GetSmallImage(void) = 0;
	virtual wxString ContextMenu(void) = 0;
	virtual wxString NewMenu(void) = 0;
};

class IGxObjectWizard
{
public:
	virtual ~IGxObjectWizard(void){};
	virtual bool Invoke(wxWindow* pParentWnd) = 0;
};

class IGxObjectEdit
{
public:
	virtual ~IGxObjectEdit(void){};
	virtual bool Delete(void){return false;};
	virtual bool CanDelete(void){return false;};
	virtual bool Rename(wxString NewName){return false;};
	virtual bool CanRename(void){return false;};
	virtual void EditProperties(wxWindow *parent){};
};

class IGxObjectContainer :
	public IGxObject
{
public:
	virtual ~IGxObjectContainer(void){};
	virtual bool AddChild(IGxObject* pChild)
	{
		if(pChild == NULL)
			return false;
		if(!pChild->Attach(this, m_pCatalog))
			return false;
		m_Children.push_back(pChild);
		return true;
	};
	virtual bool DeleteChild(IGxObject* pChild)
	{
		if(pChild == NULL)
			return false;
		GxObjectArray::iterator pos = std::find(m_Children.begin(), m_Children.end(), pChild);
		if(pos != m_Children.end())
		{
			pChild->Detach();
			delete pChild;
			m_Children.erase(pos);
		}
		return true;
	};
	virtual bool AreChildrenViewable(void) = 0;
	virtual bool HasChildren(void) = 0;
	virtual GxObjectArray* GetChildren(void){return &m_Children;};
	virtual IGxObject* SearchChild(wxString sPath)
	{
		wxString sTestPath = sPath;
		if(GetFullName().CmpNoCase(sPath) == 0)//GetName
			return this;
		for(size_t i = 0; i < m_Children.size(); i++)
		{
			wxString sTestedPath = m_Children[i]->GetFullName();
			if(sTestedPath.CmpNoCase(sPath) == 0)
				return m_Children[i];
			if(sPath.Find(sTestedPath) != wxNOT_FOUND)
			{
				IGxObjectContainer* pContainer = dynamic_cast<IGxObjectContainer*>(m_Children[i]);
				if(pContainer && pContainer->HasChildren())
				{
					IGxObject* pFoundChild = pContainer->SearchChild(sPath);
					if(pFoundChild)
						return pFoundChild;
				}
			}
		}
		return NULL;
	}
protected:
	GxObjectArray m_Children;
};

class IGxObjectFactory
{
public:
	IGxObjectFactory(void) : m_pCatalog(NULL), m_bIsEnabled(true){};
	virtual ~IGxObjectFactory(void){};
    //pure virtual
	virtual bool GetChildren(wxString sParentDir, wxArrayString* pFileNames, GxObjectArray* pObjArray) = 0;
    virtual void Serialize(wxXmlNode* pConfig, bool bStore) = 0;
    virtual wxString GetName(void) = 0;
    //
    virtual bool GetEnabled(void){return m_bIsEnabled;};
    virtual void SetEnabled(bool bIsEnabled){m_bIsEnabled = bIsEnabled;};
	virtual void PutCatalogRef(IGxCatalog* pCatalog){m_pCatalog = pCatalog;};
protected:
	IGxCatalog* m_pCatalog;
    bool m_bIsEnabled;
};

class IGxCatalogEvents
{
public:
	virtual ~IGxCatalogEvents(void){};
	virtual void OnObjectAdded(IGxObject* object) = 0;
	virtual void OnObjectChanged(IGxObject* object) = 0;
	virtual void OnObjectDeleted(IGxObject* object) = 0;
	virtual void OnObjectRefreshed(IGxObject* object) = 0;
	virtual void OnRefreshAll(void) = 0;
};


class IGxDataset
{
public:
	virtual ~IGxDataset(void){};
	virtual wxGISDataset* GetDataset(void) = 0;
	virtual wxGISEnumDatasetType GetType(void) = 0;
	virtual int GetSubType(void) = 0;
    virtual wxString GetPath(void) = 0;
};

class IGxFile
{
public:
	virtual ~IGxFile(void){};
	//virtual bool Open(void) = 0;
	//virtual bool Close(bool bSaveEdits) = 0;
	//virtual void Edit(void) = 0;
	//virtual void New(void) = 0;
	//virtual bool Save(void) = 0;
};

class IGxRootObjectProperties
{
public:
	virtual ~IGxRootObjectProperties(void){};
	virtual void Init(wxXmlNode* pConfigNode) = 0;
	virtual wxXmlNode* GetProperties(void) = 0;
};

class IGxObjectSort
{
public:
	virtual ~IGxObjectSort(void){};
	virtual bool IsAlwaysTop(void) = 0;
	virtual bool IsSortEnabled(void) = 0;
};

class IGxObjectFilter
{
public:
	virtual ~IGxObjectFilter(void){};
	virtual bool CanChooseObject( IGxObject* pObject ) = 0;//, esriDoubleClickResult* result
	virtual bool CanDisplayObject( IGxObject* pObject ) = 0;
	virtual wxGISEnumSaveObjectResults CanSaveObject( IGxObject* pLocation, wxString sName ) = 0;
	virtual wxString GetName(void) = 0;
    virtual wxString GetExt(void) = 0;
    virtual wxString GetDriver(void) = 0;
    virtual int GetSubType(void) = 0;
};

typedef std::vector<IGxObjectFilter*> OBJECTFILTERS, *LPOBJECTFILTERS;
//
//typedef std::vector<IGxObjectFactory*> GxObjectFactoryArray;
//
//class IGxObjectFactories
//{
//public:
//	virtual ~IGxObjectFactories(void){};
//	virtual GxObjectFactoryArray* GetEnabledGxObjectFactories() = 0;
//};



