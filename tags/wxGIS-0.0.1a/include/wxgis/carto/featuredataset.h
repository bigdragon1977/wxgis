/******************************************************************************
 * Project:  wxGIS (GIS Catalog)
 * Purpose:  FeatureDataset class.
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

#include "wxgis/datasource.h"

void GetGeometryBoundsFunc(const void* hFeature, CPLRectObj* pBounds);

//---------------------------------------
// wxGISFeatureDataset
//---------------------------------------

class WXDLLIMPEXP_GIS_CRT wxGISFeatureDataset :
	public wxGISDataset
{
public:
	wxGISFeatureDataset(wxString sPath, wxMBConv* pPathEncoding = wxConvCurrent, wxFontEncoding Encoding = wxFONTENCODING_DEFAULT);
	virtual ~wxGISFeatureDataset(void);
//wxGISDataset
	virtual wxGISEnumDatasetType GetType(void){return enumGISFeatureDataset;};
//wxGISFeatureDataset
	virtual bool Open(int iLayer = 0);
	virtual bool Delete(int iLayer = 0);
	virtual OGRSpatialReference* GetSpatialReference(void);
	virtual OGREnvelope* GetEnvelope(void);
	//virtual void SetSpatialFilter(double dfMinX, double dfMinY, double dfMaxX, double dfMaxY);
	virtual OGRFeature* GetAt(long nIndex);
	virtual OGRFeature* operator [](long nIndex);
	virtual wxString GetAsString(long row, int col);
	//virtual wxGISFeatureSet* GetFeatureSet(IQueryFilter* pQFilter = NULL, ITrackCancel* pTrackCancel = NULL);
	virtual wxGISGeometrySet* GetGeometrySet(IQueryFilter* pQFilter = NULL, ITrackCancel* pTrackCancel = NULL);
    virtual wxGISGeometrySet* GetGeometries(void);
	virtual size_t GetSize(void);
	virtual OGRLayer* GetLayerRef(int iLayer = 0);
    virtual OGRFeature* Next(void);
    virtual void Reset(void);
protected:
    virtual void CreateQuadTree(OGREnvelope* pEnv);
    virtual void DeleteQuadTree(void);
    virtual void LoadGeometry(void);
    virtual void UnloadGeometry(void);
protected:
	OGRDataSource *m_poDS;
	OGREnvelope* m_psExtent;
	OGRLayer* m_poLayer;
	bool m_bIsOpened;
    bool m_bOLCStringsAsUTF8;
    wxFontEncoding m_Encoding;
    //
    bool m_bIsGeometryLoaded;
    wxGISGeometrySet *m_pGeometrySet;
    CPLQuadTree* m_pQuadTree;
    wxCriticalSection m_CritSect;
};

////---------------------------------------
//// wxGISShapeFeatureDataset
////---------------------------------------
//
//class WXDLLIMPEXP_GIS_CRT wxGISShapeFeatureDataset :
//	public wxGISFeatureDataset
//{
//public:
//	wxGISShapeFeatureDataset(wxString sPath, wxMBConv* pPathEncoding = wxConvCurrent, wxFontEncoding Encoding = wxFONTENCODING_DEFAULT);
//	virtual ~wxGISShapeFeatureDataset(void);
////wxGISFeatureDataset
//	virtual bool Open(int iLayer = 0);
//    virtual OGRErr CreateSpatialIndex(void);
//};
//
////---------------------------------------
//// wxGISFeatureCursor
////---------------------------------------
//
//class WXDLLIMPEXP_GIS_CRT wxGISFeatureCursor :
//    public IFeatureCursor
//{
//public:
//    wxGISFeatureCursor(wxGISFeatureDataset* pSet){m_pSet = pSet;};
//    virtual ~wxGISFeatureCursor(void){};
//    virtual OGRFeature* NextFeature(void){return m_pSet->Next();};
//protected:
//    wxGISFeatureDataset* m_pSet;
//};