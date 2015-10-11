// baseCube.cpp: Implementierung der Klasse CbaseCube.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "baseCube.h"

#include "fstream.h"
#include <iomanip.h>
#include "locale.h"

#include "baseZufall.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CbaseCube::CbaseCube()
{

}

CbaseCube::~CbaseCube()
{

}


// *****************************************************************************************


double& CbaseCube::operator() (int Idx1, int Idx2, int Idx3)
{
	double *Zeiger;
	Zeiger = &Data(Idx1,Idx2,Idx3);
	return *Zeiger;
}


// *****************************************************************************************


void CbaseCube::GetSize(int &CurSize1, int &CurSize2, int &CurSize3)
{
	Data.GetSize(CurSize1,CurSize2,CurSize3);
}


// *****************************************************************************************


void CbaseCube::Init()
{
	int CurSize1=0;int CurSize2=0;int CurSize3=0;
	GetSize(CurSize1,CurSize2,CurSize3);

	for (int i1=1;i1<=CurSize1;i1++)
	{
		for (int i2=1;i2<=CurSize2;i2++)
		{
			for (int i3=1;i3<=CurSize3;i3++)
			{
				Data(i1,i2,i3) = 0;
			}
		}
	}
}


// *****************************************************************************************


bool CbaseCube::SetSize(int NewSize1, int NewSize2, int NewSize3)
{
	return Data.SetSize(NewSize1,NewSize2,NewSize3);
}


// *****************************************************************************************


bool CbaseCube::Norm(double NormOperand)
{
	int CurSize1=0;int CurSize2=0;int CurSize3=0;
	GetSize(CurSize1,CurSize2,CurSize3);

	double Gesamt=0;
	for (int i1=1;i1<=CurSize1;i1++)
	{
		for (int i2=1;i2<=CurSize2;i2++)
		{
			for (int i3=1;i3<=CurSize3;i3++)
			{
				Gesamt = Gesamt + Data(i1,i2,i3);
			}
		}
	}

	Gesamt = Gesamt * NormOperand;
	
	if (Gesamt!=0)
	{
		for (int i1=1;i1<=CurSize1;i1++)
		{
			for (int i2=1;i2<=CurSize2;i2++)
			{
				for (int i3=1;i3<=CurSize3;i3++)
				{
					Data(i1,i2,i3) = Data(i1,i2,i3) / Gesamt;
				}
			}
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


void CbaseCube::Add(CbaseCube *InCube)
{
	int CurSize1=0;int CurSize2=0;int CurSize3=0;
	GetSize(CurSize1,CurSize2,CurSize3);

	//Abgleich mit den Dimensionen der InMatrix
	int InSize1=0; int InSize2=0; int InSize3=0;
	InCube->GetSize(InSize1,InSize2,InSize3);

	if ((CurSize1==InSize1)&&(CurSize2==InSize2)&&(CurSize3==InSize3))
	{
		for (int i1=1;i1<=CurSize1;i1++)
		{
			for (int i2=1;i2<=CurSize2;i2++)
			{
				for (int i3=1;i3<=CurSize3;i3++)
				{
					Data(i1,i2,i3) = Data(i1,i2,i3) + (*InCube)(i1,i2,i3);
				}
			}
		}
	}
	else
	{
		AfxMessageBox("Cubes sind unterschiedlich groß");
	}
}


// *****************************************************************************************


void CbaseCube::Multiplicate(double InOperand)
{
	int CurSize1=0;int CurSize2=0;int CurSize3=0;
	GetSize(CurSize1,CurSize2,CurSize3);

	for (int i1=1;i1<=CurSize1;i1++)
	{
		for (int i2=1;i2<=CurSize2;i2++)
		{
			for (int i3=1;i3<=CurSize3;i3++)
			{
				Data(i1,i2,i3) = Data(i1,i2,i3) * InOperand;
			}
		}
	}
}


// *****************************************************************************************


void CbaseCube::MonteCarlo(int &RandomSel1, int &RandomSel2, int &RandomSel3)
{
	Norm(1);

	RandomSel1=0;
	RandomSel2=0;
	RandomSel3=0;

	int UpLimit1=0;int UpLimit2=0;int UpLimit3=0;
	GetSize(UpLimit1,UpLimit2,UpLimit3);

	do
	{
		double Zuf = CbaseZufall::Zufall01();

		RandomSel1=0;
		RandomSel2=0;
		RandomSel3=0;

		bool Fertig=false;

		do
		{
			RandomSel1++;

			do
			{
				RandomSel2++;

				do
				{
					RandomSel3++;

					if (Zuf>Data(RandomSel1,RandomSel2,RandomSel3))
					{
						Zuf=Zuf-Data(RandomSel1,RandomSel2,RandomSel3);
					}
					else
					{
						Fertig=true;
					}

				}while ((!Fertig)&&(RandomSel3<UpLimit3));

				if ((!Fertig)&&(RandomSel2<UpLimit2))
				{
					RandomSel3=0;
				}


			}while ((!Fertig)&&(RandomSel2<UpLimit2));

			if ((!Fertig)&&(RandomSel1<UpLimit1))
			{
				RandomSel2=0;
				RandomSel3=0;
			}

		}while ((!Fertig)&&(RandomSel1<UpLimit1));

	} while ((RandomSel1<1)||(RandomSel1>UpLimit1)||
		(RandomSel2<1)||(RandomSel2>UpLimit2)||
		(RandomSel3<1)||(RandomSel3>UpLimit3)||
		(Data(RandomSel1,RandomSel2,RandomSel3)==0));
}


// *****************************************************************************************


bool CbaseCube::Load_prn(CString PathInput)
{
	Init();
	
	ifstream InFile;

	InFile.open(PathInput,ios::nocreate);

	while (!InFile.eof())
	{
		short AktQ=0; short AktZ=0;
		int AktWert[6];
		for (short VerkM=0;VerkM<6;VerkM++)
			AktWert[VerkM]=0;

		InFile >> AktQ >> AktZ;
		bool WerteOK=true;
		for (VerkM=0;VerkM<6;VerkM++)
		{
			InFile >> AktWert[VerkM];
			if (AktWert[VerkM]<0)
			{
				WerteOK=false;
			}
		}

		if ((AktQ>0)&&(AktQ<=418)&&(AktZ>0)&&(AktZ<=418)&&(WerteOK))
		{
			for (VerkM=0;VerkM<6;VerkM++)
			{
				Data(AktQ,AktZ,VerkM+1)=AktWert[VerkM];
			}
		}
	}

	InFile.close();

	if (InFile.bad()==0)
		return true;
	else
		return false;
}


// *****************************************************************************************



bool CbaseCube::Save_prn(CString PathOutput)
{
	ofstream OutFile;

	OutFile.open(PathOutput,ios::out);

	for (short i1=0;i1<418;i1++)
		for (short i2=0;i2<418;i2++)
		{
			bool Leer=true;
			for (short i3=0;i3<6;i3++)
			{
				if (Data(i1+1,i2+1,i3+1)!=0)
					Leer=false;
			}
			if (!Leer)
			{
				OutFile << setiosflags(ios::fixed) << setprecision(0)
					<< i1+1 << " " << i2+1;
				for (short i3=0;i3<6;i3++)
					OutFile << " " << Data(i1+1,i2+1,i3+1);
				OutFile << endl;
			}
		}

	OutFile.close();

	if (OutFile.fail()==0)
		return true;
	else
		return false;	

}


// *****************************************************************************************















// *****************************************************************************************


// *****************************************************************************************




// *****************************************************************************************

//DEL CbaseCube::CbaseCube(const CbaseCube & Operand)
//DEL {
//DEL 	int NewSize1 = Operand.Data.GetSize();
//DEL 	int NewSize2=0; int NewSize3=0;
//DEL 	
//DEL 	Operand.Data[0].myGetSize(NewSize2,NewSize3); 
//DEL 
//DEL 	mySetSize(NewSize1,NewSize2,NewSize3);
//DEL 
//DEL 	Data.Copy(Operand.Data);
//DEL }


// *****************************************************************************************


//DEL CbaseCube& CbaseCube::operator=(CbaseCube& InCube)
//DEL {
//DEL 	int NewSize1 = InCube.Data.GetSize();
//DEL 	int NewSize2=0; int NewSize3=0;
//DEL 	InCube.myGetSize(NewSize1,NewSize2,NewSize3);
//DEL 	InCube.Data[0].myGetSize(NewSize2,NewSize3); 
//DEL 
//DEL 	mySetSize(NewSize1,NewSize2,NewSize3);
//DEL 
//DEL 	Data.Copy(InCube.Data);
//DEL 
//DEL 	return *this;
//DEL }


// *****************************************************************************************


//DEL BOOL CbaseCube::Load(CString Path, //Pfad
//DEL 					 CString Delimiter) //Trennzeichen
//DEL {
//DEL     CStdioFile InFile;
//DEL     CFileException ex;
//DEL 
//DEL     if (!InFile.Open(Path, CFile::modeRead | CFile::typeText))
//DEL     {
//DEL         ex.ReportError();
//DEL         return FALSE;
//DEL     }
//DEL 
//DEL 	TRY
//DEL 	{
//DEL 		CString Zeile="";
//DEL 
//DEL 		//Zunächst Anzahl der Verkehrsmittel bestimmen
//DEL 		//1. Zeile einlesen
//DEL 		InFile.ReadString(Zeile);
//DEL 		short NrModes=0;
//DEL 
//DEL 		for (short Zeichen=0;Zeichen<Zeile.GetLength();Zeichen++)
//DEL 		{
//DEL 			if (Zeile.GetAt(Zeichen)==Delimiter)
//DEL 			{
//DEL 				NrModes++;
//DEL 			}
//DEL 		}
//DEL 		//Letzte Spalte wird nicht gezählt, da Zeilenabschluss
//DEL 		//2 Spalten müssen für Quell- und Zielzelle abgezogen werden
//DEL 		NrModes--;
//DEL 
//DEL 		//Wieder auf den Dateianfang setzen
//DEL 		InFile.SeekToBegin();
//DEL 
//DEL 		//Zelldefinition initialisieren
//DEL 		Cells.Init();
//DEL 
//DEL 
//DEL 		//Bis zum Ende durchlaufen und die Quell- und Zielzellen jeweils herauslesen
//DEL 		while (InFile.ReadString(Zeile))
//DEL 		{
//DEL 			CString hlp1 = Zeile;
//DEL 			CString hlp2 = "";
//DEL 
//DEL 			hlp2 = hlp1.SpanExcluding(Delimiter);
//DEL 			hlp1.Delete(0,hlp2.GetLength()+1);
//DEL 			hlp1 = hlp1.SpanExcluding(Delimiter);
//DEL 
//DEL 			//Ist hlp1 in der CellDef
//DEL 			if (Cells.IntCellNumber(atoi(hlp1))==-1)
//DEL 			{
//DEL 				Cells.AddCell(atoi(hlp1));
//DEL 			}
//DEL 
//DEL 			if (hlp1!=hlp2)
//DEL 			{
//DEL 				if (Cells.IntCellNumber(atoi(hlp2))==-1)
//DEL 				{
//DEL 					Cells.AddCell(atoi(hlp2));
//DEL 				}
//DEL 			}
//DEL 		}
//DEL 
//DEL 		int NrCells = Cells.GetNrCells();
//DEL 
//DEL 		//Datenfeld aufspannen
//DEL 		mySetSize(NrModes,NrCells,NrCells);
//DEL 
//DEL 		//nun die Daten einlesen und in das Feld packen
//DEL 		InFile.SeekToBegin();
//DEL 		while (InFile.ReadString(Zeile))
//DEL 		{
//DEL 			if (Zeile!="")
//DEL 			{
//DEL 				CString hlp1 = Zeile;
//DEL 				CString hlp2 = "";
//DEL 
//DEL 				//Spalte 1: Quellzelle
//DEL 				hlp2 = hlp1.SpanExcluding(Delimiter);
//DEL 				int extQuellVZ = atoi(hlp2);
//DEL 				int intQuellVZ = Cells.IntCellNumber(extQuellVZ);
//DEL 				if (intQuellVZ==-1)
//DEL 				{
//DEL 					//Hier Fehlerabfangen
//DEL 				}
//DEL 
//DEL 				//Spalte 2: Zielzelle
//DEL 				hlp1.Delete(0,hlp2.GetLength()+1);
//DEL 				hlp2 = hlp1.SpanExcluding(Delimiter);
//DEL 				int extZielVZ = atoi(hlp2);
//DEL 				int intZielVZ = Cells.IntCellNumber(extZielVZ);
//DEL 				if (intZielVZ==-1)
//DEL 				{
//DEL 					//Hier Fehlerabfangen
//DEL 				}
//DEL 
//DEL 				
//DEL 				//nun bis Verkehrsmittel-1 durchlaufen
//DEL 				for (short CurMode=1;CurMode<=NrModes-1;CurMode++)
//DEL 				{
//DEL 					hlp1.Delete(0,hlp2.GetLength()+1);
//DEL 					hlp2 = hlp1.SpanExcluding(Delimiter);
//DEL 					(*this)(CurMode,intQuellVZ,intZielVZ)=atof(hlp2);
//DEL 				}
//DEL 
//DEL 				//und das letzte Verkehrsmittel
//DEL 				hlp1.Delete(0,hlp2.GetLength()+1);
//DEL 				(*this)(NrModes,intQuellVZ,intZielVZ)=atof(hlp1);
//DEL 			}
//DEL 		}
//DEL 
//DEL 	InFile.Close();
//DEL 
//DEL 	}
//DEL 
//DEL     CATCH (CFileException, e)
//DEL     {
//DEL         AfxMessageBox("Cube konnte nicht geladen werden");
//DEL         return FALSE;
//DEL     }
//DEL     END_CATCH
//DEL 
//DEL     return TRUE;
//DEL }


// *****************************************************************************************


//DEL CbaseCube& CbaseCube::operator+(const CbaseCube& InCube)
//DEL {
//DEL 	//Prüfen, ob Dimensionen übereinstimmen
//DEL 
//DEL 
//DEL 	//Prüfen, ob Zelleinteilung übereinstimmt
//DEL 
//DEL 
//DEL 	//Addition durchführen
//DEL 	int Size1=0; int Size2=0; int Size3=0;
//DEL 	myGetSize(Size1,Size2,Size3);
//DEL 
//DEL 	for (int Idx1=1;Idx1<=Size1;Idx1++)
//DEL 	{
//DEL 		for (int Idx2=1;Idx2<=Size2;Idx2++)
//DEL 		{
//DEL 			for (int Idx3=1;Idx3<=Size3;Idx3++)
//DEL 			{
//DEL 				operator()(Idx1,Idx2,Idx3) = operator()(Idx1,Idx2,Idx3) + InCube.Feld[Idx1-1].myElementAt(Idx2,Idx3);
//DEL 			}
//DEL 		}
//DEL 	}
//DEL 
//DEL 	return *this;
//DEL }


// *****************************************************************************************


//DEL BOOL CbaseCube::Save(CString Pfad)
//DEL {
//DEL 	ofstream OutFile;
//DEL 	OutFile.open(Pfad,ios::out);
//DEL 
//DEL 	int Size1=0; int Size2=0; int Size3=0;
//DEL 	myGetSize(Size1,Size2,Size3);
//DEL 
//DEL 	for (int Idx2=1;Idx2<=Size2;Idx2++)
//DEL 	{
//DEL 		for (int Idx3=1;Idx3<=Size3;Idx3++)
//DEL 		{
//DEL 			//Zunächst prüfen, ob überhaupt Werte vorhanden sind
//DEL 			double CurSum=0;
//DEL 			for (int Idx1=1;Idx1<=Size1;Idx1++)
//DEL 			{
//DEL 				CurSum = CurSum + (*this)(Idx1,Idx2,Idx3);
//DEL 			}
//DEL 			if (CurSum>0)
//DEL 			{
//DEL 				OutFile << Cells.ExtCellNumber(Idx2) << " " << Cells.ExtCellNumber(Idx3);
//DEL 				for (Idx1=1;Idx1<=Size1;Idx1++)
//DEL 				{
//DEL 					OutFile << " " << (*this)(Idx1,Idx2,Idx3);
//DEL 				}
//DEL 				OutFile << endl;
//DEL 			}
//DEL 		}
//DEL 	}
//DEL 
//DEL 	OutFile.close();
//DEL 
//DEL 	return TRUE;
//DEL }


// *****************************************************************************************


//DEL void CbaseCube::Addiere(CbaseCube *InMat)
//DEL {
//DEL 	for (short i1=1;i1<=6;i1++)
//DEL 		for (short i2=1;i2<=418;i2++)
//DEL 			for (short i3=2;i3<=418;i3++)
//DEL 			{
//DEL 				double a = (*this)(i1,i2,i3);
//DEL 				double b = (*InMat)(i1,i2,i3);
//DEL 				a = a + b;
//DEL 				(*this)(i1,i2,i3) = a;
//DEL 			}
//DEL }


// *****************************************************************************************



//DEL void CbaseCube::Load2(CString Path, //Pfad
//DEL 					  CString Delimiter) //Trennzeichen
//DEL {
//DEL     CStdioFile InFile;
//DEL     CFileException ex;
//DEL 
//DEL     if (!InFile.Open(Path, CFile::modeRead | CFile::typeText))
//DEL     {
//DEL         ex.ReportError();
//DEL     }
//DEL 
//DEL 	TRY
//DEL 	{
//DEL 		CString Zeile="";
//DEL 
//DEL 		//Datenfeld aufspannen
//DEL 		mySetSize(6,418,418);
//DEL 
//DEL 		//nun die Daten einlesen und in das Feld packen
//DEL 		InFile.SeekToBegin();
//DEL 		while (InFile.ReadString(Zeile))
//DEL 		{
//DEL 			if (Zeile!="")
//DEL 			{
//DEL 				CString hlp1 = Zeile;
//DEL 				CString hlp2 = "";
//DEL 
//DEL 				//Spalte 1: Quellzelle
//DEL 				int StartPos = 0;
//DEL 				int EndPos = Zeile.Find(Delimiter,StartPos);
//DEL 				hlp2=Zeile.Mid(StartPos,EndPos-StartPos);
//DEL 				int intQuellVZ = atoi(hlp2);
//DEL 
//DEL 				//Spalte 2: Zielzelle
//DEL 				StartPos = EndPos+1;
//DEL 				EndPos = Zeile.Find(Delimiter,StartPos);
//DEL 				hlp2=Zeile.Mid(StartPos,EndPos-StartPos);
//DEL 				int intZielVZ = atoi(hlp2);
//DEL 				
//DEL 				//nun bis Verkehrsmittel-1 durchlaufen
//DEL 				for (short CurMode=1;CurMode<=6-1;CurMode++)
//DEL 				{
//DEL 					StartPos = EndPos+1;
//DEL 					EndPos = Zeile.Find(Delimiter,StartPos);
//DEL 					hlp2=Zeile.Mid(StartPos,EndPos-StartPos);
//DEL 
//DEL 					(*this)(CurMode,intQuellVZ,intZielVZ)=atof(hlp2);
//DEL 				}
//DEL 
//DEL 				//und das letzte Verkehrsmittel
//DEL 				StartPos = EndPos+1;
//DEL 				hlp2=Zeile.Mid(StartPos);
//DEL 				(*this)(6,intQuellVZ,intZielVZ)=atof(hlp1);
//DEL 
//DEL 
//DEL 
//DEL 
//DEL 
//DEL /*
//DEL 				CString hlp1 = Zeile;
//DEL 				CString hlp2 = "";
//DEL 
//DEL 				//Spalte 1: Quellzelle
//DEL 				hlp2 = hlp1.SpanExcluding(Delimiter);
//DEL 				int intQuellVZ = atoi(hlp2);
//DEL 
//DEL 				//Spalte 2: Zielzelle
//DEL 				hlp1.Delete(0,hlp2.GetLength()+1);
//DEL 				hlp2 = hlp1.SpanExcluding(Delimiter);
//DEL 				int intZielVZ = atoi(hlp2);
//DEL 				
//DEL 				//nun bis Verkehrsmittel-1 durchlaufen
//DEL 				for (short CurMode=1;CurMode<=6-1;CurMode++)
//DEL 				{
//DEL 					hlp1.Delete(0,hlp2.GetLength()+1);
//DEL 					hlp2 = hlp1.SpanExcluding(Delimiter);
//DEL 					myElementAt(CurMode,intQuellVZ,intZielVZ)=atof(hlp2);
//DEL 				}
//DEL 
//DEL 				//und das letzte Verkehrsmittel
//DEL 				hlp1.Delete(0,hlp2.GetLength()+1);
//DEL 				myElementAt(6,intQuellVZ,intZielVZ)=atof(hlp1);
//DEL 			*/
//DEL 			}
//DEL 		}
//DEL 
//DEL 	InFile.Close();
//DEL 
//DEL 	}
//DEL 
//DEL     CATCH (CFileException, e)
//DEL     {
//DEL         AfxMessageBox("Cube konnte nicht geladen werden");
//DEL     }
//DEL     END_CATCH
//DEL 
//DEL }



// *****************************************************************************************


//Summiert den Cube über die Dimension Idx zu einer Matrix
CbaseMatrix CbaseCube::GetSumMatrix(short Idx)
{
 	int Size1=0; int Size2=0; int Size3=0;
 	GetSize(Size1,Size2,Size3);

	CbaseMatrix SumMat;

	int i1=0; int i2=0; int i3=0;
	
	switch (Idx)
	{
	case 1:
		SumMat.SetSize(Size2,Size3);
		SumMat.Init();
		for (i1=1;i1<=Size1;i1++)
		{
			for (i2=1;i2<=Size2;i2++)
			{
				for (i3=1;i3<=Size3;i3++)
				{
					SumMat(i2,i3) = SumMat(i2,i3) + Data(i1,i2,i3);
				}
			}
		}
		break;

	case 2:
		SumMat.SetSize(Size1,Size3);
		SumMat.Init();
		for (i1=1;i1<=Size1;i1++)
		{
			for (i2=1;i2<=Size2;i2++)
			{
				for (i3=1;i3<=Size3;i3++)
				{
					SumMat(i1,i3) = SumMat(i1,i3) + Data(i1,i2,i3);
				}
			}
		}
		break;

	case 3:
		SumMat.SetSize(Size1,Size2);
		SumMat.Init();
		for (i1=1;i1<=Size1;i1++)
		{
			for (i2=1;i2<=Size2;i2++)
			{
				for (i3=1;i3<=Size3;i3++)
				{
					SumMat(i1,i2) = SumMat(i1,i2) + Data(i1,i2,i3);
				}
			}
		}
		break;

	default:
		//Fehlerabfangen
		break;
	}


	return SumMat;
}


// *****************************************************************************************


CbaseVector CbaseCube::GetSumVector(short Idx1, short Idx2)
{
	CbaseVector SumVec;

	Idx1=Idx2;

	return SumVec;
}


// *****************************************************************************************



double CbaseCube::GetSumTotal()
{
 	double Sum=0;
 
 	int Size1=0; int Size2=0; int Size3=0;
 	GetSize(Size1,Size2,Size3);
 
 	for (int Idx1=1;Idx1<=Size1;Idx1++)
 	{
 		for (int Idx2=1;Idx2<=Size2;Idx2++)
 		{
 			for (int Idx3=1;Idx3<=Size3;Idx3++)
 			{
 				Sum = Sum + Data(Idx1,Idx2,Idx3);
 			}
 		}
 	}
 
 	return Sum;
}


// *****************************************************************************************


