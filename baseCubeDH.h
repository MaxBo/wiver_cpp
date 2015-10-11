// baseCubeDH.h: Schnittstelle für die Klasse CbaseCubeDH.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASECUBEDH_H__0ED79732_20F2_446F_AFE0_0D00BAACCB3A__INCLUDED_)
#define AFX_BASECUBEDH_H__0ED79732_20F2_446F_AFE0_0D00BAACCB3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "baseMatrixDH.h"

class CbaseCubeDH  
{
public:
	void GetSize(int&,int&,int&);
	bool SetSize(int,int,int);
	CbaseCubeDH();
	virtual ~CbaseCubeDH();
	double &operator() (int,int,int);

private:
	CArray<CbaseMatrixDH,CbaseMatrixDH> Data;


};

#endif // !defined(AFX_BASECUBEDH_H__0ED79732_20F2_446F_AFE0_0D00BAACCB3A__INCLUDED_)
