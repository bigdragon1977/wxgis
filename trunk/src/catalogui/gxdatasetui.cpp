/******************************************************************************
 * Project:  wxGIS (GIS Catalog)
 * Purpose:  wxGxDatasetUI classes.
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

#include "wxgis/catalogui/gxdatasetui.h"
#include "wxgis/framework/application.h"

//propertypages
#include "wxgis/catalogui/spatrefpropertypage.h"
#include "wxgis/catalogui/rasterpropertypage.h"

#include "../../art/properties.xpm"

#include "wx/busyinfo.h"
#include "wx/utils.h"
#include "wx/propdlg.h"

//--------------------------------------------------------------
//class wxGxTableDatasetUI
//--------------------------------------------------------------

wxGxTableDatasetUI::wxGxTableDatasetUI(wxString Path, wxString Name, wxGISEnumTableDatasetType nType, wxIcon LargeIcon, wxIcon SmallIcon) : wxGxTableDataset(Path, Name, nType)
{
    m_LargeIcon = LargeIcon;
    m_SmallIcon = SmallIcon;
}

wxGxTableDatasetUI::~wxGxTableDatasetUI(void)
{
}

wxIcon wxGxTableDatasetUI::GetLargeImage(void)
{
	return m_LargeIcon;
}

wxIcon wxGxTableDatasetUI::GetSmallImage(void)
{
	return m_SmallIcon;
}

void wxGxTableDatasetUI::EditProperties(wxWindow *parent)
{
}

//--------------------------------------------------------------
//class wxGxFeatureDatasetUI
//--------------------------------------------------------------

wxGxFeatureDatasetUI::wxGxFeatureDatasetUI(wxString Path, wxString Name, wxGISEnumVectorDatasetType nType, wxIcon LargeIcon, wxIcon SmallIcon) : wxGxFeatureDataset(Path, Name, nType)
{
    m_LargeIcon = LargeIcon;
    m_SmallIcon = SmallIcon;
}

wxGxFeatureDatasetUI::~wxGxFeatureDatasetUI(void)
{
}

wxIcon wxGxFeatureDatasetUI::GetLargeImage(void)
{
    return m_LargeIcon;
}

wxIcon wxGxFeatureDatasetUI::GetSmallImage(void)
{
    return m_SmallIcon;
}

void wxGxFeatureDatasetUI::EditProperties(wxWindow *parent)
{
}

wxGISDataset* wxGxFeatureDatasetUI::GetDataset(void)
{
    wxGISDataset* pOut = wxGxFeatureDataset::GetDataset();
    if(!pOut)
    {
        const char* err = CPLGetLastErrorMsg();
        wxString sErr = wxString::Format(_("Open failed! GDAL error: %s"), wgMB2WX(err));
        wxMessageBox(sErr, _("Error"), wxOK | wxICON_ERROR);
    }
    return pOut;
}

//--------------------------------------------------------------
//class wxGxRasterDatasetUI
//--------------------------------------------------------------

wxGxRasterDatasetUI::wxGxRasterDatasetUI(wxString Path, wxString Name, wxGISEnumRasterDatasetType nType, wxIcon LargeIcon, wxIcon SmallIcon) : wxGxRasterDataset(Path, Name, nType)
{
    m_LargeIcon = LargeIcon;
    m_SmallIcon = SmallIcon;
}

wxGxRasterDatasetUI::~wxGxRasterDatasetUI(void)
{
}

wxIcon wxGxRasterDatasetUI::GetLargeImage(void)
{
	return m_LargeIcon;
}

wxIcon wxGxRasterDatasetUI::GetSmallImage(void)
{
	return m_SmallIcon;
}

void wxGxRasterDatasetUI::EditProperties(wxWindow *parent)
{
    wxPropertySheetDialog PropertySheetDialog;
    if (!PropertySheetDialog.Create(parent, wxID_ANY, _("Properties"), wxDefaultPosition, wxSize( 480,640 ), wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER))
        return;
    PropertySheetDialog.SetIcon(properties_xpm);
    PropertySheetDialog.CreateButtons(wxOK);
    wxWindow* pParentWnd = static_cast<wxWindow*>(PropertySheetDialog.GetBookCtrl());

    wxGISRasterPropertyPage* RasterPropertyPage = new wxGISRasterPropertyPage(GetDataset(), pParentWnd);
    PropertySheetDialog.GetBookCtrl()->AddPage(RasterPropertyPage, RasterPropertyPage->GetPageName());
    wxGISSpatialReferencePropertyPage* SpatialReferencePropertyPage = new wxGISSpatialReferencePropertyPage(GetDataset(), pParentWnd);
    PropertySheetDialog.GetBookCtrl()->AddPage(SpatialReferencePropertyPage, SpatialReferencePropertyPage->GetPageName());

    PropertySheetDialog.LayoutDialog();
    //center?
    PropertySheetDialog.SetSize(480,640);
    PropertySheetDialog.Center();

    PropertySheetDialog.ShowModal();
}

bool wxGxRasterDatasetUI::Invoke(wxWindow* pParentWnd)
{
    EditProperties(pParentWnd);
    return true;
}


wxGISDataset* wxGxRasterDatasetUI::GetDataset(void)
{
    wxGISDataset* pOut = wxGxRasterDataset::GetDataset();
    if(!pOut)
    {
        const char* err = CPLGetLastErrorMsg();
        wxString sErr = wxString::Format(_("Open failed! GDAL error: %s"), wgMB2WX(err));
        wxMessageBox(sErr, _("Error"), wxOK | wxICON_ERROR);
    }
    return pOut;
}