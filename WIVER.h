// WIVER.h : Haupt-Header-Datei für die Anwendung WIVER
//

#if !defined(AFX_WIVER_H__CDE5CFF0_F7D3_436A_A9ED_E18D321E4973__INCLUDED_)
#define AFX_WIVER_H__CDE5CFF0_F7D3_436A_A9ED_E18D321E4973__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CWIVERApp:
// Siehe WIVER.cpp für die Implementierung dieser Klasse
//

class CWIVERApp : public CWinApp
{
public:
	CWIVERApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CWIVERApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CWIVERApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_WIVER_H__CDE5CFF0_F7D3_436A_A9ED_E18D321E4973__INCLUDED_)
