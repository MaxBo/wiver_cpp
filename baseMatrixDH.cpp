// baseMatrixDH.cpp: Implementierung der Klasse CbaseMatrixDH.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "baseMatrixDH.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CbaseMatrixDH::CbaseMatrixDH()
{

}

CbaseMatrixDH::~CbaseMatrixDH()
{

}


// *****************************************************************************************


double& CbaseMatrixDH::operator() (int Idx1, int Idx2)
{
	double *Zeiger;
	Zeiger = &Data.ElementAt(Idx1-1).operator () (Idx2);
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


bool CbaseMatrixDH::SetSize(int NewSize1, int NewSize2)
{
	if ((NewSize1>0)&&(NewSize2>0))
	{
		TRY
		{
			Data.SetSize(NewSize1);
			for (int i1=0;i1<NewSize1;i1++)
	 		{
	 			Data.ElementAt(i1).SetSize(NewSize2);
	 		}
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
		AfxMessageBox("Matrixgröße <= 0");
		return false;
	}
}


// *****************************************************************************************


void CbaseMatrixDH::GetSize(int &CurSize1, int &CurSize2)
{
	CurSize1 = Data.GetSize();
	if (CurSize1>0)
	{
		CurSize2 = Data[0].GetSize();
	}
	else
	{
		CurSize2=0;
	}
}


// *****************************************************************************************


void CbaseMatrixDH::Copy(CbaseMatrixDH &srcMat)
{
	int NewSize1=0; int NewSize2=0;
	srcMat.GetSize(NewSize1,NewSize2);

	Data.SetSize(NewSize2);

	for (int i1=0;i1<NewSize2;i1++)
	{
		Data[i1].Copy(srcMat.Data.ElementAt(i1));
	}
}


// *****************************************************************************************


