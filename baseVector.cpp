// baseVector.cpp: Implementierung der Klasse CbaseVector.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "baseVector.h"

#include "baseZufall.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CbaseVector::CbaseVector()
{

}

CbaseVector::~CbaseVector()
{

}


// *****************************************************************************************


CbaseVector::CbaseVector(CbaseVector& Operand)
{
	int NewSize = Operand.GetSize();

	SetSize(NewSize);

	Data.Copy(Operand.Data);
}


// *****************************************************************************************


int CbaseVector::MonteCarlo()
{
	Norm(1);

	int RandomSel=0;
	int UpLimit=Data.GetSize();

	do
	{
		double Zuf = CbaseZufall::Zufall01();

		RandomSel=1;

		while ((Zuf>Data(RandomSel))&&(RandomSel<UpLimit))
		{
			Zuf=Zuf-Data(RandomSel);
			RandomSel++;
		}

	} while ((RandomSel<1)||(RandomSel>UpLimit)||(Data(RandomSel)==0));

	return RandomSel;
}


// *****************************************************************************************


double& CbaseVector::operator() (int Idx)
{
	double *Zeiger;
	Zeiger = &Data(Idx);
	return *Zeiger;
}


// *****************************************************************************************


bool CbaseVector::SetSize(int NewSize)
{
	return Data.SetSize(NewSize);
}


// *****************************************************************************************


CbaseVector& CbaseVector::operator=(CbaseVector &InVec)
{
	int NewSize = InVec.GetSize();

	(*this).SetSize(NewSize);

	Data.Copy(InVec.Data);

	return *this;
}


// *****************************************************************************************


int CbaseVector::GetSize()
{
	return Data.GetSize();
}


// *****************************************************************************************


bool CbaseVector::Norm(double NormOperand)
{
	double Gesamt=0;
	for (int i1=1;i1<=Data.GetSize();i1++)
	{
		Gesamt = Gesamt + Data(i1);
	}

	Gesamt = Gesamt * NormOperand;
	
	if (Gesamt!=0)
	{
		for (i1=1;i1<=Data.GetSize();i1++)
		{
			Data(i1) = Data(i1) / Gesamt;
		}
		return true;
	}
	else
	{
		Init();
		return false;
	}
}


// *****************************************************************************************


void CbaseVector::Init()
{
	for (int i1=1;i1<=Data.GetSize();i1++)
	{
		Data(i1) = 0;
	}
}


// *****************************************************************************************


void CbaseVector::Add(CbaseVector *InVector)
{
	//Prüfen, ob InVector und derzeitiger Vektor in der Größe übereinstimmen
	if (Data.GetSize()==InVector->GetSize())
	{
		for (int i1=1;i1<=Data.GetSize();i1++)
		{
			Data(i1) = Data(i1) + (*InVector)(i1);
		}
	}
	else
	{
		AfxMessageBox("Vektoren sind unterschiedlich groß");
	}
}


// *****************************************************************************************


void CbaseVector::Multilplicate(double InOperand)
{
	for (int i1=1;i1<=Data.GetSize();i1++)
	{
		Data(i1) = Data(i1) * InOperand;
	}
}


// *****************************************************************************************


