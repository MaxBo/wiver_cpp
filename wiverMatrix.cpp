// wiverMatrix.cpp: Implementierung der Klasse CwiverMatrix.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"

#include "fstream.h"
#include <iomanip.h>
#include "locale.h"
#include "Math.h"

#include "wiverMatrix.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CwiverMatrix::CwiverMatrix()
{

}

CwiverMatrix::~CwiverMatrix()
{

}


// *****************************************************************************************


void CwiverMatrix::LoadStruktDat(CString PathInput)
{
	ifstream InFile;

	InFile.open(PathInput,ios::nocreate);

	char line[500];
	CString Help = "";

	while (!InFile.eof())
	{
		InFile.getline(line,500,'\t');
		Help = line;
		if (Help!="")
		{
			if (Help[0]!='*')
			{
				//Bezirk übernehmen und interne Bezirksnummer ermitteln
				int ExtVZ = atoi(Help);
				int IntVZ = Zellen.IntCellNumber(ExtVZ);

				if (IntVZ==-1)
				{
					AfxMessageBox("Nicht definierte Verkehrszelle");
				}

				//Jetzt nacheinander die Spalten einlesen
				for (short i1=1;i1<6;i1++)
				{
					InFile.getline(line,500,'\t');
					Help = line;
					operator() (IntVZ,i1) = atoi(Help);
				}

				//noch die letzte Spalte einlesen
				InFile.getline(line,500,'\n');
				Help = line;
				operator() (IntVZ,6) = atoi(Help);
			}
			else
			{
				//Rest der Zeile einlesen und vergessen
				InFile.getline(line,500);
			}
		}

	}

	InFile.close();
}


// *****************************************************************************************


void CwiverMatrix::LoadCellDef(CString PathInput)
{

	LoadCellDef2(PathInput);
/*	
	ifstream InFile;

	InFile.open(PathInput,ios::nocreate);

	char line[500];
	CString Help = "";

	while (!InFile.eof())
	{
		InFile.getline(line,500,' ');
		Help = line;
		if (Help!="")
		{
			if (Help[0]!='*')
			{
				//Nummer übernehmen
				CbaseCellDef::sCellDef NewCell;
				NewCell.extNumber = atoi(Help);

				InFile.getline(line,500,' ');
				InFile.getline(line,500,' ');
				InFile.getline(line,500,' ');

				Help = line;
				NewCell.extName = Help;

				Zellen.AddCell(NewCell);
			}

			//Rest der Zeile einlesen und vergessen
			InFile.getline(line,500);
		}

	}

	InFile.close();
	*/
}


// *****************************************************************************************


void CwiverMatrix::SavePrn(CString PathOutput, short Nachkomma)
{
	ofstream OutFile;

	OutFile.open(PathOutput,ios::out);

	setlocale(LC_ALL, "German");

	int Zeilen=0;
	int Spalten=0;

	GetSize(Zeilen,Spalten);

	for (int i1=1;i1<=Zeilen;i1++)
	{
		OutFile << setiosflags(ios::fixed) << setprecision(Nachkomma)
			<< Zellen.ExtCellNumber(i1);

		for (int i2=1;i2<=Spalten;i2++)
		{
			OutFile << ";" << operator() (i1,i2);
		}

		OutFile << endl;
	}

	OutFile.close();

	setlocale(LC_ALL, "English");
}


// *****************************************************************************************


void CwiverMatrix::LoadPara(CString PathInput, short InSpalte)
{
	setlocale(LC_NUMERIC,"usa");
	ifstream InFile;

	InFile.open(PathInput,ios::nocreate);

	char line[500];
	char Muell[500];
	CString Help = "";

	while (!InFile.eof())
	{
		streampos here = InFile.tellg();

		InFile.getline(line,500);
		Help = line;
		if (Help!="")
		{
			if (Help[0]!='*')
			{
				InFile.seekg(here);

				InFile.getline(line,500,'\t');
				Help=line;

				//Fahrzeugtyp übernehmen
				int FzgTyp = atoi(Help);

				//Quellbranche einlesen und übernehmen
				InFile.getline(line,500,'\t');
				Help=line;
				int QuellB = atoi(Help);

				if (InSpalte==1)
				{
					InFile.getline(line,500,'\t');
					InFile.getline(Muell,500,'\n');
				}

				if (InSpalte==2)
				{
					InFile.getline(Muell,500,'\t');
					InFile.getline(line,500,'\t');
					InFile.getline(Muell,500,'\n');
				}

				Help=line;

				operator() (FzgTyp,QuellB) = atof(Help);
			}
		}

	}

	InFile.close();
	setlocale(LC_NUMERIC,"deu");
}


// *****************************************************************************************


void CwiverMatrix::LoadPara2(CString PathInput, short InSpalte)
{
	setlocale(LC_NUMERIC,"usa");
	ifstream InFile;

	InFile.open(PathInput,ios::nocreate);

	char line[500];
	char Muell[500];
	CString Help = "";

	while (!InFile.eof())
	{
		streampos here = InFile.tellg();

		InFile.getline(line,500);
		Help = line;
		if (Help!="")
		{
			if (Help[0]!='*')
			{
				InFile.seekg(here);

				InFile.getline(line,500,'\t');
				Help=line;

				//Fahrzeugtyp übernehmen
				int FzgTyp = atoi(Help);

				//Quellbranche einlesen und übernehmen
				InFile.getline(line,500,'\t');
				Help=line;
				int QuellB = atoi(Help);

				//Kalibrierungsgruppe überspringen
				InFile.getline(line,500,'\t');

				if (InSpalte==1)
				{
					InFile.getline(line,500,'\t');
					InFile.getline(Muell,500,'\n');
				}

				if (InSpalte==2)
				{
					InFile.getline(Muell,500,'\t');
					InFile.getline(line,500,'\n');
				}

				Help=line;

				operator() (FzgTyp,QuellB) = atof(Help);
			}
		}

	}

	InFile.close();
	setlocale(LC_NUMERIC,"deu");
}


// *****************************************************************************************


void CwiverMatrix::SavePrnOhneCell(CString PathOutput, short Nachkomma)
{
	ofstream OutFile;

	OutFile.open(PathOutput,ios::out);

	setlocale(LC_ALL, "German");

	int Zeilen=0;
	int Spalten=0;

	GetSize(Zeilen,Spalten);


	for (int i0=1;i0<=Spalten;i0++)
	{
		OutFile << setiosflags(ios::fixed) << setprecision(Nachkomma)
			<< ";" << i0;

	}

	OutFile << endl;

	for (int i1=1;i1<=Zeilen;i1++)
	{
		OutFile << setiosflags(ios::fixed) << setprecision(Nachkomma)
			<< i1;

		for (int i2=1;i2<=Spalten;i2++)
		{
			OutFile << ";" << operator() (i1,i2);
		}

		OutFile << endl;
	}

	OutFile.close();

	setlocale(LC_ALL, "English");
}


// *****************************************************************************************


void CwiverMatrix::LoadPara3(CString PathInput, short AnzahlEmpfBranchen)
{
	setlocale(LC_NUMERIC,"usa");
	ifstream InFile;

	InFile.open(PathInput,ios::nocreate);

	char line[500];
	CString Help = "";

	while (!InFile.eof())
	{
		streampos here = InFile.tellg();

		InFile.getline(line,500);
		Help = line;
		if (Help!="")
		{
			if (Help[0]!='*')
			{
				InFile.seekg(here);

				//Fahrzeugtyp überspringen
				InFile.getline(line,500,'\t');

				//Quellbranche überspringen
				InFile.getline(line,500,'\t');

				//Kalibrierungsgruppe einlesen und übernehmen
				InFile.getline(line,500,'\t');
				Help = line;
				int KaliGr = atoi(Help);

				//Nun freie Anzahl Spalten AnzahlEmpfBranchen
				for (short AktBranche=1;AktBranche<AnzahlEmpfBranchen;AktBranche++)
				{
					InFile.getline(line,500,'\t');
					Help=line;
					operator() (KaliGr,AktBranche) = atof(Help);
				}

				//und noch die letzte Spalte einlesen
				InFile.getline(line,500,'\n');
				Help=line;
				operator() (KaliGr,AktBranche) = atof(Help);
			}
		}

	}

	InFile.close();
	setlocale(LC_NUMERIC,"deu");

}


// *****************************************************************************************


void CwiverMatrix::LoadRZMatrix(CString PathInput)
{
	Init();

	ifstream InFile;
	InFile.open(PathInput, ios::nocreate);

	setlocale(LC_NUMERIC,"usa");

	//Die ersten Zeile überlesen
	char line[500];
	InFile.getline(line, 500);

	//dann die Anzahl der Zellen einlesen
	InFile.getline(line, 500);
	int AnzahlVZ = atoi(line);

	bool Header=false;
	short AktVZ=0;

	while (!InFile.eof())
	{
		//zunächst die Zellennummer einlesen
		if (!Header)
		{
			for (short Zeile=0;Zeile<70;Zeile++)
			{
				//8-mal jeweils 10 Zeichen einlesen
				for (short Spalte=0;Spalte<8;Spalte++)
				{
					InFile.get(line,11);
					AktVZ++;

					if (Zellen.ExtCellNumber(AktVZ) != atoi(line))
					{
						short a=1;
						a=a;
					}
					else
					{
					}
				}
				InFile.getline(line, 500);
			}
			//letzte Zeile mit 3 Einträgen einlesen
			for (short Spalte=0;Spalte<3;Spalte++)
			{
				InFile.get(line,11);
				AktVZ++;

				if (Zellen.ExtCellNumber(AktVZ) != atoi(line))
				{
					short a=1;
					a=a;
				}
				else
				{
				}
			}
			InFile.getline(line, 500);

			Header = true;

		}
		else
		{
			//Wenn die Zellennummer eingelesen sind, dann die einzelnen Matrixzeilen einlesen
			//zunächst die Nummer der Quellzelle geführt von einem * einlesen

			int extQuellVZ=0;
			int intQuellVZ=0;

			InFile.getline(line,500);
			CString STRline= line;
			if (STRline!="")
			{
				if (STRline[0]=='*')
				{
					//Quellverkehrszelle bestimmen
					STRline = STRline.Right(STRline.GetLength()-1);
					extQuellVZ = atoi(STRline);
					intQuellVZ=Zellen.IntCellNumber(extQuellVZ);
					if ((intQuellVZ<1)||(intQuellVZ>563))
					{
						AfxMessageBox("Falsche intQuellVZ");
					}
				}
				else
				{
					AfxMessageBox("Kein Sternchen");
				}

				int intZielVZ=1;

				//dann die einzelnen Matrixzeilen einlesen
				for (short Zeile=0;Zeile<70;Zeile++)
				{
					//8-mal jeweils 10 Zeichen einlesen
					for (short Spalte=0;Spalte<8;Spalte++)
					{
						InFile.get(line,11);
						CString STRline= line;

						operator() (intQuellVZ,intZielVZ) = atof(line);

						intZielVZ++;
					}
					InFile.getline(line, 500);
				}

				//letzte Zeile mit 3 Einträgen einlesen
				for (short Spalte=0;Spalte<3;Spalte++)
				{
					InFile.get(line,11);

					operator() (intQuellVZ,intZielVZ) = atof(line);

					intZielVZ++;
				}
			}
		}
	}

	setlocale(LC_NUMERIC,"deu");
}


// *****************************************************************************************


void CwiverMatrix::Export_Visum_fzt(CString PathOutput)
{
	setlocale(LC_NUMERIC,"usa");

	ofstream OutFile;

	OutFile.open(PathOutput,ios::out);

	//Zunächst den Dateikopf schreiben
	OutFile<<"$ON;D4"<<endl;
	OutFile<<"*  Quell  Ziel  Anzahl  "<<endl;
	OutFile<<"*   Bez    Bez  Fahrten "<<endl;

	int AnzQuellen=0;
	int AnzZiele=0;

	GetSize(AnzQuellen,AnzZiele);

	//Dann die besetzten Zellen herausschreiben
	for (short Quelle=1;Quelle<=AnzQuellen;Quelle++)
		for (short Ziel=1;Ziel<=AnzZiele;Ziel++)
		{
//			if (operator() (Quelle,Ziel)!=0)
			{
				OutFile << setw(8) << Zellen.ExtCellNumber(Quelle)
					<< setw(8) << Zellen.ExtCellNumber(Ziel)
					<< setiosflags(ios::fixed) << setprecision(4)
					<< setw(12) << operator() (Quelle,Ziel) << endl;
			}
		}

	OutFile.close();

	setlocale(LC_NUMERIC,"deu");
}


// *****************************************************************************************


void CwiverMatrix::LoadMatrix_prn(CString PathInput)
{
	setlocale(LC_NUMERIC,"deu");

	ifstream InFile;

	InFile.open(PathInput,ios::nocreate);

	while (!InFile.eof())
	{
		int extQuellVZ=0; int extZielVZ=0;
		double AktWert=0;

		char line[100];
		CString Hline="";
		InFile.getline(line,100,'\t');
		Hline=line;
		extQuellVZ = int(atof(Hline));
		InFile.getline(line,100,'\t');
		Hline=line;
		extZielVZ = int(atof(Hline));
		InFile.getline(line,100,'\n');
		Hline=line;
		AktWert = atof(Hline);

		int intQuellVZ = Zellen.IntCellNumber(extQuellVZ);
		int intZielVZ = Zellen.IntCellNumber(extZielVZ);


		if ((intQuellVZ!=-1)&&(intZielVZ!=-1))
		{
			operator() (intQuellVZ,intZielVZ) = AktWert;
		}
		else
		{
			AfxMessageBox("Nicht definierte Zellennummer");
		}
	}

	InFile.close();
}


// *****************************************************************************************


void CwiverMatrix::LoadCellDef2(CString PathInput)
{
	ifstream InFile;

	InFile.open(PathInput,ios::nocreate);

	char line[500];
	CString Help = "";

	//Erste Zeile überlesen
	InFile.getline(line,500);


	while (!InFile.eof())
	{
		//Nun die VZ-Nummern nacheinander einfach per Stream einlesen
		
		InFile.getline(line,500);
		Help = line;
		if (Help!="")
		{
			//Nummer übernehmen
			CbaseCellDef::sCellDef NewCell;
			NewCell.extNumber = atoi(Help);

			Zellen.AddCell(NewCell);
		}
	}

	InFile.close();
}


// *****************************************************************************************


void CwiverMatrix::Import_Visum_fzt(CString PathInput)
{
	setlocale(LC_NUMERIC,"usa");

	ifstream InFile;

	InFile.open(PathInput,ios::nocreate);

	//Die ersten drei Zeilen überlesen
	char Muell[500];
	InFile.getline(Muell,500);
	InFile.getline(Muell,500);
	InFile.getline(Muell,500);

	while (!InFile.eof())
	{
		int extQuellVZ=0; int extZielVZ=0;
		double AktWert=0;

		char line[100];
		CString Hline="";
		InFile.get(line,9);
		Hline=line;

		if (Hline!="")
		{
			extQuellVZ = int(atof(Hline));
			InFile.get(line,9);
			Hline=line;
			extZielVZ = int(atof(Hline));
			InFile.getline(line,100,'\n');
			Hline=line;
			AktWert = atof(Hline);

			int intQuellVZ = Zellen.IntCellNumber(extQuellVZ);
			int intZielVZ = Zellen.IntCellNumber(extZielVZ);


			if ((intQuellVZ!=-1)&&(intZielVZ!=-1))
			{
				operator() (intQuellVZ,intZielVZ) = AktWert;
			}
			else
			{
				AfxMessageBox("Nicht definierte Zellennummer");
			}
		}
	}

	InFile.close();

	setlocale(LC_NUMERIC,"deu");

}


// *****************************************************************************************


void CwiverMatrix::StadtUmlandAuswerten(CString PathOutput)
{
	CwiverMatrix AggMat;
	AggMat.SetSize(2,2);
	AggMat.Init();

	for (short QVZ=1;QVZ<=551;QVZ++)
	{
		for (short ZVZ=1;ZVZ<=551;ZVZ++)
		{
			short Quelle=0; short Ziel=0;

			if ((Zellen.ExtCellNumber(QVZ)<399)||(Zellen.ExtCellNumber(QVZ)==2131))
			{
				Quelle=1;
			}
			else
			{
				Quelle=2;
			}
			if ((Zellen.ExtCellNumber(ZVZ)<399)||(Zellen.ExtCellNumber(ZVZ)==2131))
			{
				Ziel=1;
			}
			else
			{
				Ziel=2;
			}

			AggMat(Quelle,Ziel)=AggMat(Quelle,Ziel) + operator()(QVZ,ZVZ);

		}
	}

	AggMat.SavePrnOhneCell(PathOutput,10);
}


// *****************************************************************************************


void CwiverMatrix::Import_Visum_fzt2(CString PathInput)
{
	setlocale(LC_NUMERIC,"usa");

	ifstream InFile;

	InFile.open(PathInput,ios::nocreate);

	//Die ersten drei Zeilen überlesen
	char Muell[500];
	InFile.getline(Muell,500);
	InFile.getline(Muell,500);
	InFile.getline(Muell,500);
	InFile.getline(Muell,500);
	InFile.getline(Muell,500);
	InFile.getline(Muell,500);
	InFile.getline(Muell,500);
	InFile.getline(Muell,500);

	while (!InFile.eof())
	{
		int extQuellVZ=0; int extZielVZ=0;
		double AktWert=0;

		char line[100];
		CString Hline="";
		InFile.get(line,22);
		Hline=line;

		if (Hline!="")
		{
			extQuellVZ = int(atof(Hline));
			InFile.get(line,24);
			Hline=line;
			extZielVZ = int(atof(Hline));
			InFile.getline(line,100,'\n');
			Hline=line;
			AktWert = atof(Hline);

			int intQuellVZ = Zellen.IntCellNumber(extQuellVZ);
			int intZielVZ = Zellen.IntCellNumber(extZielVZ);


			if ((intQuellVZ!=-1)&&(intZielVZ!=-1))
			{
				operator() (intQuellVZ,intZielVZ) = AktWert;
			}
			else
			{
				AfxMessageBox("Nicht definierte Zellennummer");
			}
		}
	}

	InFile.close();

	setlocale(LC_NUMERIC,"deu");
}


// *****************************************************************************************


void CwiverMatrix::LeistungAuswerten(CwiverMatrix *DistMat, CString PathOutput)
{
	CwiverMatrix AggMat;
	AggMat.SetSize(2,2);
	AggMat.Init();

	for (short QVZ=1;QVZ<=551;QVZ++)
	{
		for (short ZVZ=1;ZVZ<=551;ZVZ++)
		{
			short Quelle=0; short Ziel=0;

			if ((Zellen.ExtCellNumber(QVZ)<399)||(Zellen.ExtCellNumber(QVZ)==2131))
			{
				Quelle=1;
			}
			else
			{
				Quelle=2;
			}
			if ((Zellen.ExtCellNumber(ZVZ)<399)||(Zellen.ExtCellNumber(ZVZ)==2131))
			{
				Ziel=1;
			}
			else
			{
				Ziel=2;
			}

			double AktDist = DistMat->operator () (QVZ,ZVZ);

			AggMat(Quelle,Ziel)=AggMat(Quelle,Ziel) + operator()(QVZ,ZVZ) * AktDist;
		}
	}

	AggMat.SavePrnOhneCell(PathOutput,10);
}


// *****************************************************************************************


double CwiverMatrix::LeistungAuswerten(CwiverMatrix *DistMat)
{
	CwiverMatrix AggMat;
	AggMat.SetSize(551,551);
	AggMat.Init();

	for (short QVZ=1;QVZ<=551;QVZ++)
	{
		for (short ZVZ=1;ZVZ<=551;ZVZ++)
		{
			double AktDist = DistMat->operator () (QVZ,ZVZ);

			AggMat(QVZ,ZVZ)=AggMat(QVZ,ZVZ) + operator()(QVZ,ZVZ) * AktDist;
		}
	}

	return AggMat.GetSumTotal();
}


// *****************************************************************************************


void CwiverMatrix::Import_PTV_VFormat(CString PathInput,short MaxSpalten, short SpalteZeichen)
{
	setlocale(LC_NUMERIC,"usa");

	ifstream InFile;

	InFile.open(PathInput,ios::nocreate);

	int Zeile=0;
	int AnzahlVZ=0;
	int Abschnitt=0;
	int QVZ=0;

	while (!InFile.eof())
	{
		char Line[500];
		CString sLine="";

		InFile.getline(Line,500,'\n');
		sLine=Line;

		if (sLine!="")
		{
			if (sLine.Left(1)!='*')
			{
				Zeile++;
				if (Zeile<=3)
				{
					//1. Zeile Format
					//aktuell überlesen

					//2. Zeile Zeitintervall
					//ersteinmal überlesen

					//3. Zeile Faktor
					//ersteinmal überlesen
				}
				else
				{
					if (Zeile==4)
					{
						//Anzahl Bezirke
						AnzahlVZ=atoi(sLine);
						SetSize(AnzahlVZ,AnzahlVZ);
						Init();
					}
					else
					{
						if (Abschnitt==0)
						{
							//jetzt kommen zunächst die Bezirksnummern
							//Anzahl der einzulesenden Zeilen ist
							//AUFRUNDEN(AnzahlVZ/10)

							short ZeileToRead=int(AnzahlVZ/MaxSpalten);

							if (AnzahlVZ>ZeileToRead*MaxSpalten)
							{
								ZeileToRead++;
							}

							for (int AktZeile=0;AktZeile<ZeileToRead-1;AktZeile++)
							{
								if (AktZeile!=0)
								{
									InFile.getline(Line,500,'\n');
									sLine=Line;
								}

								//Spalte auswerten
								for (int AktSpalte=0;AktSpalte<MaxSpalten;AktSpalte++)
								{
									int AktVZ = atoi(sLine.Mid(SpalteZeichen+AktSpalte*SpalteZeichen,SpalteZeichen));
//									int AktVZ = atoi(sLine.Mid(AktSpalte*SpalteZeichen,SpalteZeichen));
									Zellen.AddCell(AktVZ);
								}
							}
							//und noch die letzte Zeile
							{
								InFile.getline(Line,500,'\n');
								sLine=Line;
								for (int AktSpalte=0;AktSpalte<int(AnzahlVZ-(ZeileToRead-1)*MaxSpalten);AktSpalte++)
								{
									int AktVZ = atoi(sLine.Mid(SpalteZeichen+AktSpalte*SpalteZeichen,SpalteZeichen));
//									int AktVZ = atoi(sLine.Mid(AktSpalte*SpalteZeichen,SpalteZeichen));
									Zellen.AddCell(AktVZ);
								}
							}

							Abschnitt=1;
//							Zellen.Save("F:\\Test.csv");
						}
						else
						{
							//und nun die eigentlichen Werte
							if (QVZ<AnzahlVZ)
							{
								QVZ++;

								short ZeileToRead=int(AnzahlVZ/MaxSpalten);

								if (AnzahlVZ>ZeileToRead*MaxSpalten)
								{
									ZeileToRead++;
								}

								int ZVZ=0;

								for (int AktZeile=0;AktZeile<ZeileToRead-1;AktZeile++)
								{
									if (AktZeile!=0)
									{
										InFile.getline(Line,500,'\n');
										sLine=Line;
									}

									//Spalte auswerten
									for (int AktSpalte=0;AktSpalte<MaxSpalten;AktSpalte++)
									{
										ZVZ++;
										double AktWert = atof(sLine.Mid(SpalteZeichen+AktSpalte*SpalteZeichen,SpalteZeichen));
//										double AktWert = atof(sLine.Mid(AktSpalte*SpalteZeichen,SpalteZeichen));
										operator() (QVZ,ZVZ) = AktWert;
									}
								}
								//und noch die letzte Zeile
								{
									InFile.getline(Line,500,'\n');
									sLine=Line;
									for (int AktSpalte=0;AktSpalte<int(AnzahlVZ-(ZeileToRead-1)*MaxSpalten);AktSpalte++)
									{
										ZVZ++;
										double AktWert = atof(sLine.Mid(SpalteZeichen+AktSpalte*SpalteZeichen,SpalteZeichen));
//										double AktWert = atof(sLine.Mid(AktSpalte*SpalteZeichen,SpalteZeichen));
										operator() (QVZ,ZVZ) = AktWert;
									}
								}
							}
						}

					}
				}

			}//Abfrage Kommentarzeile
		}//Abfrage leere Zeile
	}//Schleife über Datei

	setlocale(LC_NUMERIC,"deu");
}


// *****************************************************************************************


