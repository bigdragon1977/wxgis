/******************************************************************************
 * Project:  wxGIS (GIS Catalog)
 * Purpose:  wxGxFolder class.
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
#include "wxgis/catalog/gxfolder.h"
#include "../../art/folder_16.xpm"
#include "../../art/folder_48.xpm"

wxGxFolder::wxGxFolder(wxString Path, wxString Name, bool bShowHidden) : m_bShowHidden(bShowHidden), m_bIsChildrenLoaded(false)
{
	m_sName = Name;
	m_sPath = Path;
}

wxGxFolder::~wxGxFolder(void)
{
}

void wxGxFolder::Detach(void)
{
	EmptyChildren();
}

void wxGxFolder::Refresh(void)
{
	EmptyChildren();
	LoadChildren();
    m_pCatalog->ObjectRefreshed(this);
}

void wxGxFolder::EmptyChildren(void)
{
	for(size_t i = 0; i < m_Children.size(); i++)
	{
        if(m_pCatalog)
        {
            IGxSelection* pSel = m_pCatalog->GetSelection();
            if(pSel)
                m_pCatalog->GetSelection()->Unselect(m_Children[i], IGxSelection::INIT_ALL);
        }
		m_Children[i]->Detach();
		wxDELETE( m_Children[i] );
	}
    m_Children.clear();
	m_bIsChildrenLoaded = false;
}

void wxGxFolder::LoadChildren(void)
{
	if(m_bIsChildrenLoaded)
		return;
	wxDir dir(m_sPath);
	if(dir.IsOpened())
	{
		WXDWORD style = wxDIR_FILES | wxDIR_DIRS;
		if(m_bShowHidden)
			style |= wxDIR_HIDDEN;

		dir.Traverse(*this, wxEmptyString, style );
	}

	//load names
	GxObjectArray Array;	
	if(m_pCatalog->GetChildren(m_sPath, &m_FileNames, &Array))
	{
		for(size_t i = 0; i < Array.size(); i++)
		{
			bool ret_code = AddChild(Array[i]);
			if(!ret_code)
				wxDELETE(Array[i]);
		}
	}
	m_bIsChildrenLoaded = true;
}

wxIcon wxGxFolder::GetLargeImage(void)
{
	return wxIcon(folder_48_xpm);
}

wxIcon wxGxFolder::GetSmallImage(void)
{
	return wxIcon(folder_16_xpm);
}

bool wxGxFolder::Delete(void)
{
    LoadChildren();
    //delete all items that can be deleted
    while(m_Children.size() > 0)
    {
        IGxObjectEdit* pEditObj = dynamic_cast<IGxObjectEdit*>(m_Children[0]);
        if(pEditObj)
            pEditObj->Delete();
    }
    //delete all files
	wxDir* pDir = new wxDir(m_sPath);
	if(pDir->IsOpened())
	{
        m_FileNames.Clear();
	    WXDWORD style = wxDIR_FILES | wxDIR_HIDDEN;
        pDir->Traverse(*this, wxEmptyString, style );
        for(size_t i = 0; i < m_FileNames.size(); i++)
        {
            int nRetCode = VSIUnlink(wgWX2MB(m_FileNames[i]));
            if(nRetCode != 0)
            {
                const char* err = CPLGetLastErrorMsg();
                wxLogError(_("Delete failed! OGR error: %s, file '%s'"), wgMB2WX(err), m_sPath.c_str());
            }
        }
    }
    wxDELETE(pDir);
    //delete all dirs

    //delete    
    //int ret = VSIRmdir(wgWX2MB(m_sPath));//recursive!!!
    //if(ret == 0)
	if(wxFileName::Rmdir(m_sPath))//recursive del wil be in >= 2.9.0
	{
		IGxObjectContainer* pGxObjectContainer = dynamic_cast<IGxObjectContainer*>(m_pParent);
		if(pGxObjectContainer == NULL)
			return false;
		return pGxObjectContainer->DeleteChild(this);		
	}
	else
    {
        const char* err = CPLGetLastErrorMsg();
        wxLogError(_("Delete failed! OGR error: %s, file '%s'"), wgMB2WX(err), m_sPath.c_str());
		return false;	
    }
}

bool wxGxFolder::Rename(wxString NewName)
{
	//rename ?
	m_sName = NewName; 
	m_pCatalog->ObjectChanged(this);
	return true;
}

void wxGxFolder::EditProperties(wxWindow *parent)
{
}

wxDirTraverseResult wxGxFolder::OnFile(const wxString& filename)
{
	m_FileNames.Add(filename);
	return wxDIR_CONTINUE;
}

wxDirTraverseResult wxGxFolder::OnDir(const wxString& dirname)
{
	m_FileNames.Add(dirname);
	return wxDIR_IGNORE;
}

bool wxGxFolder::DeleteChild(IGxObject* pChild)
{
	bool bHasChildren = m_Children.size() > 0 ? true : false;
	if(!IGxObjectContainer::DeleteChild(pChild))
		return false;
    m_pCatalog->ObjectDeleted(pChild);
	if(bHasChildren != m_Children.size() > 0 ? true : false)
		m_pCatalog->ObjectChanged(this);
	return true;		
}