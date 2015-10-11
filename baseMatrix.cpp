// baseMatrix.cpp: Implementierung der Klasse CbaseMatrix.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "baseMatrix.h"

#include "baseZufall.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CbaseMatrix::CbaseMatrix()
{

}

CbaseMatrix::~CbaseMatrix()
{

}


// *****************************************************************************************


CbaseMatrix::CbaseMatrix(CbaseMatrix &Operand)
{
	int NewSize1 = 0; int NewSize2 = 0;
	
	Operand.GetSize(NewSize1,NewSize2);

	SetSize(NewSize1,NewSize2);

	Data.Copy(Operand.Data);
}


// *****************************************************************************************


void CbaseMatrix::Init()
{
	int CurSize1=0;int CurSize2=0;
	GetSize(CurSize1,CurSize2);

	for (int i1=1;i1<=CurSize1;i1++)
	{
		for (int i2=1;i2<CurSize2;i2++)
		{
			Data(i1,i2) = 0;
		}
	}
}


// *****************************************************************************************


void CbaseMatrix::GetSize(int &CurSize1, int &CurSize2)
{
	Data.GetSize(CurSize1,CurSize2);
}


// *****************************************************************************************


bool CbaseMatrix::SetSize(int NewSize1, int NewSize2)
{
	return Data.SetSize(NewSize1,NewSize2);
}


// *****************************************************************************************


void CbaseMatrix::MonteCarlo(int &RandomSel1, int &RandomSel2)
{
	NormAll(1);

	RandomSel1=0;
	RandomSel2=0;

	int UpLimit1=0;int UpLimit2=0;
	GetSize(UpLimit1,UpLimit2);

	do
	{
		double Zuf = CbaseZufall::Zufall01();

		RandomSel1=0;
		RandomSel2=0;

		bool Fertig=false;

		do
		{
			RandomSel1++;

			do
			{
				RandomSel2++;
				if (Zuf>Data(RandomSel1,RandomSel2))
				{
					Zuf=Zuf-Data(RandomSel1,RandomSel2);
				}
				else
				{
					Fertig=true;
				}


			}while ((!Fertig)&&(RandomSel2<UpLimit2));

			if ((!Fertig)&&(RandomSel1<UpLimit1))
			{
				RandomSel2=0;
			}

		}while ((!Fertig)&&(RandomSel1<UpLimit1));

	} while ((RandomSel1<1)||(RandomSel1>UpLimit1)||(RandomSel2<1)||(RandomSel2>UpLimit2)||(Data(RandomSel1,RandomSel2)==0));
}


// *****************************************************************************************


bool CbaseMatrix::NormAll(double NormOperand)
{
	int CurSize1=0;int CurSize2=0;
	GetSize(CurSize1,CurSize2);

	double Gesamt=0;
	for (int i1=1;i1<=CurSize1;i1++)
	{
		for (int i2=1;i2<=CurSize2;i2++)
		{
			Gesamt = Gesamt + Data(i1,i2);
		}
	}

	Gesamt = Gesamt / NormOperand;
	
	double ChkSumme=0;
	if (Gesamt!=0)
	{
		for (int i1=1;i1<=CurSize1;i1++)
		{
			for (int i2=1;i2<=CurSize2;i2++)
			{
				Data(i1,i2) = Data(i1,i2) / Gesamt;
				ChkSumme=ChkSumme+Data(i1,i2);
			}
		}
		ChkSumme=ChkSumme;

		return true;
	}
	else
	{
		Init();
		return false;
	}
}


// *****************************************************************************************


bool CbaseMatrix::NormColumns(double NormOperand)
{
	int CurSize1=0;int CurSize2=0;
	GetSize(CurSize1,CurSize2);

	bool Abbruch=false;

	for (int i1=1;i1<=CurSize2;i1++)
	{
		double Gesamt = 0;
		for (int i2=1;i2<=CurSize1;i2++)
		{
			Gesamt = Gesamt + Data(i2,i1);
		}

		Gesamt = Gesamt * NormOperand;

		if (Gesamt!=0)
		{
			for (i2=1;i2<=CurSize1;i2++)
			{
				Data(i2,i1) = Data(i2,i1) / Gesamt;
			}
		}
		else
		{
			Abbruch=true;
		}
	}

	if (Abbruch)
	{
		Init();
		return false;
	}
	else
	{
		return true;
	}
}


// *****************************************************************************************


bool CbaseMatrix::NormRows(double NormOperand)
{
	int CurSize1=0;int CurSize2=0;
	GetSize(CurSize1,CurSize2);

	bool Abbruch=false;

	for (int i1=1;i1<=CurSize1;i1++)
	{
		double Gesamt=0;

		for (int i2=1;i2<=CurSize2;i2++)
		{
			Gesamt = Gesamt + Data(i1,i2);
		}

		Gesamt = Gesamt * NormOperand;

		if (Gesamt!=0)
		{
			for (int i2=1;i2<=CurSize2;i2++)
			{
				Data(i1,i2) = Data(i1,i2) / Gesamt;
			}
		}
		else
		{
			Abbruch=true;
		}
	}

	if (Abbruch)
	{
		Init();
		return false;
	}
	else
	{
		return true;
	}
}


// *****************************************************************************************


void CbaseMatrix::Multiplicate(double InOperand)
{
	int CurSize1=0;int CurSize2=0;
	GetSize(CurSize1,CurSize2);

	for (int i1=1;i1<=CurSize1;i1++)
	{
		for (int i2=1;i2<=CurSize2;i2++)
		{
			Data(i1,i2) = Data(i1,i2) * InOperand;
		}
	}

}


// *****************************************************************************************


double& CbaseMatrix::operator() (int Idx1, int Idx2)
{
	double *Zeiger;
	Zeiger = &Data(Idx1,Idx2);
	return *Zeiger;
}


// *****************************************************************************************


void CbaseMatrix::Add(CbaseMatrix *InMatrix)
{
	int CurSize1=0;int CurSize2=0;
	GetSize(CurSize1,CurSize2);

	//Abgleich mit den Dimensionen der InMatrix
	int InSize1=0; int InSize2=0;
	InMatrix->GetSize(InSize1,InSize2);

	if ((CurSize1==InSize1)&&(CurSize2==InSize2))
	{
		for (int i1=1;i1<=CurSize1;i1++)
		{
			for (int i2=1;i2<=CurSize2;i2++)
			{
				Data(i1,i2) = Data(i1,i2) + (*InMatrix)(i1,i2);
			}
		}
	}
	else
	{
		AfxMessageBox("Matrizen sind unterschiedlich groß");
	}

}


// *****************************************************************************************


double CbaseMatrix::GetSumTotal()
{
 	double Sum=0;
 
 	int Size1=0; int Size2=0; int Size3=0;
 	GetSize(Size1,Size2);
 
 	for (int Idx1=1;Idx1<=Size1;Idx1++)
 	{
 		for (int Idx2=1;Idx2<=Size2;Idx2++)
 		{
 			{
 				Sum = Sum + Data(Idx1,Idx2);
 			}
 		}
 	}
 
 	return Sum;
}


// *****************************************************************************************


