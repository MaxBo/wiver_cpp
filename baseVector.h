// baseVector.h: Schnittstelle für die Klasse CbaseVector.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASEVECTOR_H__9BCBEE5F_12D6_43BB_9764_412C93CAC11B__INCLUDED_)
#define AFX_BASEVECTOR_H__9BCBEE5F_12D6_43BB_9764_412C93CAC11B__INCLUDED_

#include "baseVectorDH.h"	// Hinzugefügt von der Klassenansicht
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CbaseVector  
{
public:
	void Multilplicate(double);
	void Add(CbaseVector*);
	void Init();
	bool Norm(double);
	int GetSize();
	bool SetSize(int);
	double &operator() (int Idx);
	int MonteCarlo();
	CbaseVector();
	CbaseVector(CbaseVector&);
	virtual ~CbaseVector();
	CbaseVector &operator=(CbaseVector&);

private:
	CbaseVectorDH Data;
};

#endif // !defined(AFX_BASEVECTOR_H__9BCBEE5F_12D6_43BB_9764_412C93CAC11B__INCLUDED_)
