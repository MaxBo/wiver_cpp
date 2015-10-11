// baseCellDef.h: Schnittstelle für die Klasse CbaseCellDef.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASECELLDEF_H__A601F4FB_7EAD_45A2_AA7C_71F481DE542F__INCLUDED_)
#define AFX_BASECELLDEF_H__A601F4FB_7EAD_45A2_AA7C_71F481DE542F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "afxtempl.h"

class CbaseCellDef  
{
public:
	int ExtCellNumber(int);
	void Save(CString);
	int GetNrCells();
	struct sCellDef
	{
		int extNumber;
		CString extName;
		double xCoordinate;
		double yCoordinate;

	};


	void AddCell(sCellDef);
	void AddCell(int);
	void Init();
	int IntCellNumber(int);



	CbaseCellDef();
	virtual ~CbaseCellDef();

private:
	CList<sCellDef,sCellDef> Data;
};

#endif // !defined(AFX_BASECELLDEF_H__A601F4FB_7EAD_45A2_AA7C_71F481DE542F__INCLUDED_)
