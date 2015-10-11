// baseMatrix.h: Schnittstelle für die Klasse CbaseMatrix.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASEMATRIX_H__C491B9CE_97EE_4353_913E_8126492F7A0D__INCLUDED_)
#define AFX_BASEMATRIX_H__C491B9CE_97EE_4353_913E_8126492F7A0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "baseMatrixDH.h"

class CbaseMatrix  
{
public:
	double GetSumTotal();
	void Add(CbaseMatrix*);
	double &operator() (int,int);
	void Multiplicate(double);
	bool NormAll(double);
	bool NormRows(double);
	bool NormColumns(double);
	void MonteCarlo(int&, int&);
	bool SetSize(int,int);
	void GetSize(int&,int&);
	void Init();
	CbaseMatrix();
	CbaseMatrix(CbaseMatrix&);
	virtual ~CbaseMatrix();


private:
	CbaseMatrixDH Data;

};

#endif // !defined(AFX_BASEMATRIX_H__C491B9CE_97EE_4353_913E_8126492F7A0D__INCLUDED_)
