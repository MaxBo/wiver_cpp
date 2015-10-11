// WIVERDlg.h : Header-Datei
//

#if !defined(AFX_WIVERDLG_H__149EC45D_F0C4_462F_B9EB_8451AA595E6A__INCLUDED_)
#define AFX_WIVERDLG_H__149EC45D_F0C4_462F_B9EB_8451AA595E6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWIVERDlg Dialogfeld

class CWIVERDlg : public CDialog
{
// Konstruktion
public:
	CWIVERDlg(CWnd* pParent = NULL);	// Standard-Konstruktor

// Dialogfelddaten
	//{{AFX_DATA(CWIVERDlg)
	enum { IDD = IDD_WIVER_DIALOG };
		// HINWEIS: der Klassenassistent fügt an dieser Stelle Datenelemente (Members) ein
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CWIVERDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CWIVERDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_WIVERDLG_H__149EC45D_F0C4_462F_B9EB_8451AA595E6A__INCLUDED_)
