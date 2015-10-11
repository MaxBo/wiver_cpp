// baseCubeDH.cpp: Implementierung der Klasse CbaseCubeDH.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "baseCubeDH.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CbaseCubeDH::CbaseCubeDH()
{

}

CbaseCubeDH::~CbaseCubeDH()
{

}


// *****************************************************************************************


double& CbaseCubeDH::operator() (int Idx1, int Idx2, int Idx3)
{
	double *Zeiger;
	Zeiger = &Data.ElementAt(Idx3-1).operator () (Idx1,Idx2);
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


bool CbaseCubeDH::SetSize(int NewSize1, int NewSize2, int NewSize3)
{
	if ((NewSize1>0)&&(NewSize2>0)&&(NewSize3>0))
	{
		TRY
		{
			Data.SetSize(NewSize3);
			for (int i1=0;i1<NewSize3;i1++)
	 		{
	 			Data.ElementAt(i1).SetSize(NewSize1,NewSize2);
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
		AfxMessageBox("Cubegröße <= 0");
		return false;
	}
}


// *****************************************************************************************


void CbaseCubeDH::GetSize(int &CurSize1, int &CurSize2, int &CurSize3)
{
	CurSize3 = Data.GetSize();
	if (CurSize3>0)
	{
		Data[0].GetSize(CurSize1,CurSize2);
	}
	else
	{
		CurSize1=0;
		CurSize2=0;
	}
}


// *****************************************************************************************


