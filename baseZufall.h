// baseZufall.h: Schnittstelle für die Klasse CbaseZufall.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASEZUFALL_H__4CACD013_C307_45B6_8254_B384065A05B4__INCLUDED_)
#define AFX_BASEZUFALL_H__4CACD013_C307_45B6_8254_B384065A05B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CbaseZufall  
{
public:
	void Initialisieren();
	static double Zufall01();
	CbaseZufall();
	virtual ~CbaseZufall();

	int ZufallInt(int,int);

};

#endif // !defined(AFX_BASEZUFALL_H__4CACD013_C307_45B6_8254_B384065A05B4__INCLUDED_)
