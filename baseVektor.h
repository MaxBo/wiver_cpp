// baseVektor.h: Schnittstelle für die Klasse CbaseVektor.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASEVEKTOR_H__49591E96_E6D4_4B08_A9E9_64F41FFE0C50__INCLUDED_)
#define AFX_BASEVEKTOR_H__49591E96_E6D4_4B08_A9E9_64F41FFE0C50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "afxtempl.h"


class CbaseVektor  
{
public:
	CbaseVektor();
	CbaseVektor(int);
	CbaseVektor(const CbaseVektor & Operand);

	void Init();
	double& myElementAt(int);
	int myGetSize();
	void myRemoveAll();
	void mySetSize(int);
	virtual ~CbaseVektor();
	double &operator() (int Idx);
	CbaseVektor &operator=(const CbaseVektor&);

private:
	CArray<double,double> Feld;

};

#endif // !defined(AFX_BASEVEKTOR_H__49591E96_E6D4_4B08_A9E9_64F41FFE0C50__INCLUDED_)
