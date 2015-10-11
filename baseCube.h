// baseCube.h: Schnittstelle für die Klasse CbaseCube.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASECUBE_H__9411FB21_B6D8_4A6C_AA8C_25065595AC4E__INCLUDED_)
#define AFX_BASECUBE_H__9411FB21_B6D8_4A6C_AA8C_25065595AC4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "afxtempl.h"
#include "baseCubeDH.h"
#include "baseMatrix.h"	// Hinzugefügt von der Klassenansicht
#include "baseVector.h"	// Hinzugefügt von der Klassenansicht

class CbaseCube  
{
public:
	double GetSumTotal();
	CbaseVector GetSumVector(short, short);
	CbaseMatrix GetSumMatrix(short);
	bool Save_prn(CString);
	bool Load_prn(CString);
	void MonteCarlo(int&,int&,int&);
	void Multiplicate(double);
	void Add(CbaseCube*);
	void Init();
	bool Norm(double);
	bool SetSize(int,int,int);
	void GetSize(int&,int&,int&);
	CbaseCube();
	virtual ~CbaseCube();
	double &operator() (int,int,int);

private:
	CbaseCubeDH Data;

};

#endif // !defined(AFX_BASECUBE_H__9411FB21_B6D8_4A6C_AA8C_25065595AC4E__INCLUDED_)
