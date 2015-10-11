// baseVektor.cpp: Implementierung der Klasse CbaseVektor.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "baseVektor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CbaseVektor::CbaseVektor()
{
}

CbaseVektor::CbaseVektor(int NewSize)
{
	if (NewSize>=0)
	{
		Feld.SetSize(NewSize);
	}
}


// *****************************************************************************************


CbaseVektor::~CbaseVektor()
{

}


// *****************************************************************************************


void CbaseVektor::mySetSize(int NewSize)
{
	//To Do: Memory Exception abfangen !!!

	if (NewSize>=0)
	{
		Feld.SetSize(NewSize);
	}
}


// *****************************************************************************************


void CbaseVektor::myRemoveAll()
{
	Feld.RemoveAll();
}


// *****************************************************************************************


int CbaseVektor::myGetSize()
{
	return Feld.GetSize();
}


// *****************************************************************************************


double& CbaseVektor::operator() (int Idx)
{
	static double Muell = 0;
	double *Zeiger;
	

	if ((Idx>0)&&(Idx<=Feld.GetSize()))
	{
		Zeiger = &Feld.ElementAt(Idx-1);
	}
	else
	{
		Zeiger = &Muell;
	}
	return *Zeiger;
}


// *****************************************************************************************


double& CbaseVektor::myElementAt(int Idx)
{
	static double Muell = 0;
	double *Zeiger;
	
	Zeiger = &Feld.ElementAt(Idx-1);

/*	if ((Idx>0)&&(Idx<=Feld.GetSize()))
	{
		Zeiger = &Feld.ElementAt(Idx-1);
	}
	else
	{
		Zeiger = &Muell;
	}
*/	return *Zeiger;
}


// *****************************************************************************************


void CbaseVektor::Init()
{
	for (int Idx=0;Idx<Feld.GetSize();Idx++)
	{
		Feld.ElementAt(Idx)=0;
	}
}


// *****************************************************************************************


CbaseVektor& CbaseVektor::operator=(const CbaseVektor& InVek)
{
	int NewSize = InVek.Feld.GetSize();
	mySetSize(NewSize);

	Feld.Copy(InVek.Feld);

	return *this;
}


// *****************************************************************************************


CbaseVektor::CbaseVektor(const CbaseVektor & Operand)
{
	int NewSize = Operand.Feld.GetSize();

	mySetSize(NewSize);

	Feld.Copy(Operand.Feld);
}


// *****************************************************************************************


