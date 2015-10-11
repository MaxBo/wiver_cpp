// baseVectorDH.h: Schnittstelle für die Klasse CbaseVectorDH.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASEVECTORDH_H__6FCC9EDF_DF0E_4905_9365_58575182E479__INCLUDED_)
#define AFX_BASEVECTORDH_H__6FCC9EDF_DF0E_4905_9365_58575182E479__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "afxtempl.h"


class CbaseVectorDH  
{
public:
	void Copy(const CbaseVectorDH&);
	int GetSize();
	bool SetSize(int);
	CbaseVectorDH();
	virtual ~CbaseVectorDH();

	double &operator() (int Idx);


private:
	CArray<double,double> Data;

};

#endif // !defined(AFX_BASEVECTORDH_H__6FCC9EDF_DF0E_4905_9365_58575182E479__INCLUDED_)
