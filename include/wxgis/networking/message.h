/******************************************************************************
 * Project:  wxGIS (GIS Remote)
 * Purpose:  wxNetMessage class. Network message class.
 * Author:   Bishop (aka Barishnikov Dmitriy), polimax@mail.ru
 ******************************************************************************
*   Copyright (C) 2008-2010  Bishop
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

#include "wxgis/networking/networking.h"

#define WXNETVER 2

#define BUFF 1000

#define WXNETMESSAGE1 wxT("<?xml version=\"1.0\" encoding=\"UTF-8\"?><msg ver=\"%d\" st=\"%d\" prio=\"%u\">%s</msg>")
#define WXNETMESSAGE2 wxT("<?xml version=\"1.0\" encoding=\"UTF-8\"?><msg ver=\"%d\" st=\"%d\" prio=\"%u\"/>")

//#define WEMESSAGE wxT("<?xml version=\"1.0\" encoding=\"UTF-8\"?><msg ver=\"%d\" st=\"%d\" message=\"%s\" priority=\"%u\">%s</msg>")
//
//
//// ----------------------------------------------------------------------------
//// wxNetMessage
//// ----------------------------------------------------------------------------
//

/** \class wxNetMessage message.h
    \brief A network message class.

	Used in messaging between server and client
*/

class WXDLLIMPEXP_GIS_NET wxNetMessage : public INetMessage
{
public:
    /** \fn wxNetMessage(void)
     *  \brief A default constructor.
     */    
	wxNetMessage(void);
    /** \fn wxNetMessage(unsigned char* pBuff, size_t nSize)
     *  \brief A constructor.
	 *	\param pBuff input buffer
	 *	\param nSize input buffer size
     */    
    wxNetMessage(unsigned char* pBuff, size_t nSize);
    wxNetMessage(wxString sMsgData, long nID);
//    wxNetMessage(long nID, wxGISMessageState nState = enumGISMsgStUnk, short nPriority = enumGISPriorityNormal, wxString sMessage = wxEmptyString, wxString sModuleSrc = wxEmptyString, wxString sModuleDst = wxEmptyString);
    /** \fn virtual ~wxNetMessage(void)
     *  \brief A destructor.
     */
	virtual ~wxNetMessage(void);
    virtual short GetPriority(void);
    virtual void SetPriority(short nPriority);
////    //virtual bool operator< (const INetMessage& msg) const;
////    //virtual INetMessage& operator= (const INetMessage& oSource);
    virtual bool IsOk(void);
    virtual wxGISMessageDirection GetDirection(void);
    virtual void SetDirection(wxGISMessageDirection nDirection);
    virtual wxGISMessageState GetState(void);
    virtual void SetState(wxGISMessageState nState);
//    virtual wxXmlNode* GetRoot(void);
    virtual const unsigned char* GetData(void);
    virtual size_t GetDataLen(void);
protected:
	virtual wxString StrFromBuff(unsigned char* pBuff, size_t nBuffByteSize, size_t nValSize);
protected:
	wxXmlDocument *m_pXmlDocument;
	long m_nID;
	bool m_bIsOk;
	short m_nPriority;
	wxGISMessageDirection m_nDirection;
	wxGISMessageState m_nState;
	//wxString m_sMessage;
	wxString m_sData;
    unsigned char m_cData[BUFF];
};
//
////std::priority_queue<Message, std::deque<Message> > pq;


