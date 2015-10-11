// baseMatrixDH.h: Schnittstelle für die Klasse CbaseMatrixDH.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASEMATRIXDH_H__F8CCC31C_5E16_4684_8E2A_45D125824AD6__INCLUDED_)
#define AFX_BASEMATRIXDH_H__F8CCC31C_5E16_4684_8E2A_45D125824AD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "baseVectorDH.h"

class CbaseMatrixDH  
{
public:
	void Copy(CbaseMatrixDH&);
	void GetSize(int&,int&);
	bool SetSize(int,int);
	CbaseMatrixDH();
	virtual ~CbaseMatrixDH();
	double &operator() (int,int);

private:
	CArray<CbaseVectorDH,CbaseVectorDH> Data;


};

#endif // !defined(AFX_BASEMATRIXDH_H__F8CCC31C_5E16_4684_8E2A_45D125824AD6__INCLUDED_)
