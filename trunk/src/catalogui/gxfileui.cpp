/******************************************************************************
 * Project:  wxGIS (GIS Catalog)
 * Purpose:  wxGxFileUI classes.
 * Author:   Bishop (aka Barishnikov Dmitriy), polimax@mail.ru
 ******************************************************************************
*   Copyright (C) 2010  Bishop
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

#include "wxgis/catalogui/gxfileui.h"

//--------------------------------------------------------------
//class wxGxFileUI
//--------------------------------------------------------------

wxGxFileUI::wxGxFileUI(wxString Path, wxString Name) : wxGxFile(Path, Name)
{
}

wxGxFileUI::~wxGxFileUI(void)
{
}


//--------------------------------------------------------------
//class wxGxPrjFileUI
//--------------------------------------------------------------

wxGxPrjFileUI::wxGxPrjFileUI(wxString Path, wxString Name, wxGISEnumPrjFileType nType, wxIcon LargeIcon, wxIcon SmallIcon) : wxGxPrjFile(Path, Name, nType)
{
    m_oLargeIcon = LargeIcon;
    m_oSmallIcon = SmallIcon;
}

wxGxPrjFileUI::~wxGxPrjFileUI(void)
{
}

wxIcon wxGxPrjFileUI::GetLargeImage(void)
{
    return m_oLargeIcon;
}

wxIcon wxGxPrjFileUI::GetSmallImage(void)
{
    return m_oSmallIcon;
}

void wxGxPrjFileUI::EditProperties(wxWindow *parent)
{
}

//--------------------------------------------------------------
//class wxGxTextFileUI
//--------------------------------------------------------------

wxGxTextFileUI::wxGxTextFileUI(wxString Path, wxString Name, wxIcon LargeIcon, wxIcon SmallIcon) : wxGxFileUI(Path, Name)
{
    m_oLargeIcon = LargeIcon;
    m_oSmallIcon = SmallIcon;
}

wxGxTextFileUI::~wxGxTextFileUI(void)
{
}

wxIcon wxGxTextFileUI::GetLargeImage(void)
{
	return m_oLargeIcon;
}

wxIcon wxGxTextFileUI::GetSmallImage(void)
{
	return m_oSmallIcon;
}

void wxGxTextFileUI::EditProperties(wxWindow *parent)
{
}
