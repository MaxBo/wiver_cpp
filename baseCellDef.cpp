// baseCellDef.cpp: Implementierung der Klasse CbaseCellDef.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "baseCellDef.h"

#include "fstream.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CbaseCellDef::CbaseCellDef()
{

}

CbaseCellDef::~CbaseCellDef()
{

}


// *****************************************************************************************


int CbaseCellDef::IntCellNumber(int SearchExtNumber)
{
	int FoundIntNr = -1;

	POSITION pos = Data.GetHeadPosition();
	if (pos!=NULL)
	{
		sCellDef AktCell;
		int Zeile=-1;

		do 
		{
			Zeile++;
			AktCell = Data.GetNext(pos);
		}
		while ((pos!=NULL)&&(AktCell.extNumber!=SearchExtNumber));

		if (AktCell.extNumber==SearchExtNumber)
		{
			FoundIntNr = Zeile+1;
		}
	}

/*
	short Zelle=-1;

	while ((Zelle<Data.GetUpperBound())&&(FoundIntNr==-1))
	{
		Zelle++;
		if (Data[Zelle].extNumber == SearchExtNumber)
		{
			FoundIntNr=Zelle+1;
		}
	}
*/
	return FoundIntNr;
}


// *****************************************************************************************


void CbaseCellDef::Init()
{
	Data.RemoveAll();
}


// *****************************************************************************************


void CbaseCellDef::AddCell(int NewExtCellNr)
{
	sCellDef NewCell;
	NewCell.extNumber = NewExtCellNr;
	NewCell.extName = "";
	NewCell.xCoordinate = 0;
	NewCell.yCoordinate = 0;

	if (NewExtCellNr>416)
	{
		int a=0;
		a=a;
	}

	//Nun auch gleich an der richtigen Stellen einsortieren
	POSITION pos = Data.GetHeadPosition();
	if (pos!=NULL)
	{
		sCellDef AktCell;

		do
		{
			AktCell = Data.GetNext(pos);
		}
		while ((pos!=NULL)&&(AktCell.extNumber<NewExtCellNr));

		if (pos!=NULL)
		{
			Data.GetPrev(pos);
			Data.InsertBefore(pos, NewCell);
		}
		else
		{
			if (NewExtCellNr<AktCell.extNumber)
			{
				pos = Data.GetTailPosition();
				Data.InsertBefore(pos, NewCell);
			}
			else
			{
				Data.AddTail(NewCell);
			}
		}
	}
	else
	{
		Data.AddTail(NewCell);
	}
}


// *****************************************************************************************


void CbaseCellDef::AddCell(sCellDef NewCell)
{
//	AfxMessageBox("Abgeschaltet");
	Data.AddTail(NewCell);
}


// *****************************************************************************************


int CbaseCellDef::GetNrCells()
{
	return Data.GetCount();

}


// *****************************************************************************************


void CbaseCellDef::Save(CString Path)
{
	ofstream OutFile;
	OutFile.open(Path,ios::out);

	POSITION pos = Data.GetHeadPosition();
	int Zeile=0;

	while (pos!=NULL)
	{
		Zeile++;
		sCellDef AktCell = Data.GetNext(pos);

		OutFile << Zeile << "," << AktCell.extNumber << "," << AktCell.extName << endl;
	}

/*
	for (int Zelle=0;Zelle<Data.GetSize();Zelle++)
	{
		sCellDef AktCell = Data.GetAt(Zelle);

		OutFile << Zelle << "," << AktCell.extNumber << "," << AktCell.extName << endl;
	}
*/
	OutFile.close();
}


// *****************************************************************************************


int CbaseCellDef::ExtCellNumber(int SearchIntNumber)
{
	POSITION pos = Data.FindIndex(SearchIntNumber-1);
	if (pos!=NULL)
	{
		sCellDef AktCell = Data.GetNext(pos);
		return AktCell.extNumber;
	}
	else
	{
		return -1;
	}
}


// *****************************************************************************************


