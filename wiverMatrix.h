// wiverMatrix.h: Schnittstelle für die Klasse CwiverMatrix.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WIVERMATRIX_H__A1BC2329_6B6C_41EB_A4BF_A727CA824895__INCLUDED_)
#define AFX_WIVERMATRIX_H__A1BC2329_6B6C_41EB_A4BF_A727CA824895__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "baseMatrix.h"
#include "baseCellDef.h"	// Hinzugefügt von der Klassenansicht

class CwiverMatrix : public CbaseMatrix  
{
public:
	void Import_PTV_VFormat(CString,short,short);
	double LeistungAuswerten(CwiverMatrix*);
	void LeistungAuswerten(CwiverMatrix*, CString);
	void Import_Visum_fzt2(CString);
	void StadtUmlandAuswerten(CString);
	void Import_Visum_fzt(CString);
	void LoadCellDef2(CString);
	void LoadMatrix_prn(CString);
	void Export_Visum_fzt(CString);
	void LoadRZMatrix(CString);
	void LoadPara3(CString, short);
	void SavePrnOhneCell(CString,short);
	void LoadPara2(CString,short);
	void LoadPara(CString,short);
	void SavePrn(CString,short);
	void LoadCellDef(CString);
	CbaseCellDef Zellen;
	void LoadStruktDat(CString);
	CwiverMatrix();
	virtual ~CwiverMatrix();

};

#endif // !defined(AFX_WIVERMATRIX_H__A1BC2329_6B6C_41EB_A4BF_A727CA824895__INCLUDED_)
