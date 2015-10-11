// baseVectorDH.cpp: Implementierung der Klasse CbaseVectorDH.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "baseVectorDH.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CbaseVectorDH::CbaseVectorDH()
{

}

CbaseVectorDH::~CbaseVectorDH()
{

}


// *****************************************************************************************


double& CbaseVectorDH::operator() (int Idx)
{
	double *Zeiger;
	Zeiger = &Data.ElementAt(Idx-1);
	return *Zeiger;

	//Zugriffsprüfung abgeschaltet
/*
	if ((Idx>0)&&(Idx<=Data.GetSize()))
	{
		Zeiger = &Data.ElementAt(Idx-1);
	}
	else
	{
		Zeiger = NULL;
	}
*/
	return *Zeiger;
}


// *****************************************************************************************


//DEL void CbaseVectorDH::Init()
//DEL {
//DEL 	for (int i1=1;i1<=Data.GetSize();i1++)
//DEL 	{
//DEL 		Data[i1]=0;
//DEL 	}
//DEL }


// *****************************************************************************************


bool CbaseVectorDH::SetSize(int NewSize)
{
	if (NewSize>0)
	{
		TRY
		{
			Data.SetSize(NewSize);
		}

		CATCH (CMemoryException, ex)
		{
			TCHAR Cause[255];
			CString str_cause;
			ex->GetErrorMessage(Cause,255);
			str_cause = Cause;

			AfxMessageBox(str_cause);

			return false;
		}
		END_CATCH

		return true;
	}
	else
	{
		AfxMessageBox("Vektorgröße = 0");
		return false;
	}
}


// *****************************************************************************************


int CbaseVectorDH::GetSize()
{
	return Data.GetSize();
}


// *****************************************************************************************


//DEL void CbaseVectorDH::Add(CbaseVectorDH *InVector)
//DEL {
//DEL 	//Prüfen, ob InVector und derzeitiger Vektor in der Größe übereinstimmen
//DEL 	if (Data.GetSize()==InVector->GetSize())
//DEL 	{
//DEL 		for (int i1=0;i1<Data.GetSize();i1++)
//DEL 		{
//DEL 			Data[i1] = Data[i1] + (*InVector)(i1+1);
//DEL 		}
//DEL 	}
//DEL 	else
//DEL 	{
//DEL 		AfxMessageBox("Vektoren sind unterschiedlich groß");
//DEL 	}
//DEL }


// *****************************************************************************************


//DEL void CbaseVectorDH::Multiplication(double &InOperand)
//DEL {
//DEL 	for (short i1=0;i1<Data.GetSize();i1++)
//DEL 	{
//DEL 		Data[i1] = Data[i1] * InOperand;
//DEL 	}
//DEL }


// *****************************************************************************************


//DEL bool CbaseVectorDH::Norm(double NormOperand)
//DEL {
//DEL 	double Gesamt=0;
//DEL 	for (int i1=0;i1<Data.GetSize();i1++)
//DEL 	{
//DEL 		Gesamt = Gesamt + Data[i1];
//DEL 	}
//DEL 
//DEL 	Gesamt = Gesamt * NormOperand;
//DEL 	
//DEL 	if (Gesamt!=0)
//DEL 	{
//DEL 		for (i1=0;i1<Data.GetSize();i1++)
//DEL 		{
//DEL 			Data[i1] = Data[i1] / Gesamt;
//DEL 		}
//DEL 		return true;
//DEL 	}
//DEL 	else
//DEL 	{
//DEL 		Init();
//DEL 		return false;
//DEL 	}
//DEL }


// *****************************************************************************************


void CbaseVectorDH::Copy(const CbaseVectorDH &srcVec)
{
	Data.Copy(srcVec.Data);
}


// *****************************************************************************************


