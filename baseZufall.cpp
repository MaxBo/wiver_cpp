// baseZufall.cpp: Implementierung der Klasse CbaseZufall.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "baseZufall.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CbaseZufall::CbaseZufall()
{

}

CbaseZufall::~CbaseZufall()
{

}


// *****************************************************************************************

int CbaseZufall::ZufallInt(int Unten, int Oben)
{
	int Zufall=0;

	do
	{
		double r = Oben-Unten+1;
		Zufall = Unten + int((r*rand())/(RAND_MAX+1));
	} while((Zufall<Unten)||(Zufall>Oben));

	return Zufall;
}


// *****************************************************************************************


double CbaseZufall::Zufall01()
{
	double Zufall=0;
	do
	{
		Zufall = double(rand())/double(RAND_MAX);
	} while ((Zufall<=0)||(Zufall>1));

	return Zufall;
}


// *****************************************************************************************


void CbaseZufall::Initialisieren()
{
	srand( (unsigned)time( NULL ) );
}


// *****************************************************************************************


