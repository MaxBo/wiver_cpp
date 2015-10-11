// CalcPVMatrix.cpp: Implementierung der Klasse CCalcPVMatrix.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "CalcPVMatrix.h"
#include "CalcPVTeilmatrix.h"
#include "CalcPVAggregatListe.h"

#include "fstream.h"
#include <iomanip.h>
#include "locale.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CCalcPVMatrix::CCalcPVMatrix()
{

}

CCalcPVMatrix::~CCalcPVMatrix()
{

}


// *****************************************************************************************


void CCalcPVMatrix::SpiegelnAddieren()
{
	double (*HelpMatrix)[co_MaxVZ][co_MaxVerkMPV];
	HelpMatrix = new double[co_MaxVZ][co_MaxVZ][co_MaxVerkMPV];

	for (short i1=0;i1<co_MaxVZ;i1++)
		for (short i2=0;i2<co_MaxVZ;i2++)
			for (short i3=0;i3<co_MaxVerkMPV;i3++)
				HelpMatrix[i1][i2][i3]=0;

	for (i1=0;i1<VZListe.AnzahlVZ;i1++)
		for (short i2=0;i2<VZListe.AnzahlVZ;i2++)
			for (short i3=0;i3<co_MaxVerkMPV;i3++)
			{
				HelpMatrix[i1][i2][i3]=HelpMatrix[i1][i2][i3]+Wert[i1][i2][i3];
				HelpMatrix[i2][i1][i3]=HelpMatrix[i2][i1][i3]+Wert[i1][i2][i3];
			}

	for (i1=0;i1<VZListe.AnzahlVZ;i1++)
		for (short i2=0;i2<VZListe.AnzahlVZ;i2++)
			for (short i3=0;i3<co_MaxVerkMPV;i3++)
				Wert[i1][i2][i3]=HelpMatrix[i1][i2][i3];

	//Speicherfreigabe nicht vergessen
	delete [] HelpMatrix;
}


// *****************************************************************************************


//Hier werden die internen, fortlaufenden VZ-Nr verwendet
bool CCalcPVMatrix::Export_VerkMod(CString PathOutput)
{
	ofstream OutFile;

	OutFile.open(PathOutput,ios::out);

	for (short i1=0;i1<VZListe.AnzahlVZ;i1++)
		for (short i2=0;i2<VZListe.AnzahlVZ;i2++)
		{
			bool Leer=true;
			for (short i3=0;i3<co_MaxVerkMPV;i3++)
			{
				if (Wert[i1][i2][i3]!=0)
					Leer=false;
			}
			if (!Leer)
			{
				OutFile << setiosflags(ios::fixed) << setprecision(0)
					<< VZListe.VZStDat[i1].Nr << " " << VZListe.VZStDat[i2].Nr;
				for (short i3=0;i3<co_MaxVerkMPV;i3++)
					OutFile << " " << Wert[i1][i2][i3];
				OutFile << endl;
			}
		}

	OutFile.close();

	if (OutFile.bad()==0)
		return true;
	else
		return false;	
}


// *****************************************************************************************


//Hier werden die internen, fortlaufenden VZ-Nr verwendet
bool CCalcPVMatrix::Load_prn(CString PathInput)
{
	WertInit();
	
	ifstream InFile;

	InFile.open(PathInput,ios::nocreate);

	while (!InFile.eof())
	{
		short AktQ=0; short AktZ=0;
		int AktWert[co_MaxVerkMPV];
		for (short VerkM=0;VerkM<co_MaxVerkMPV;VerkM++)
			AktWert[VerkM]=0;

		InFile >> AktQ >> AktZ;
		bool WerteOK=true;
		for (VerkM=0;VerkM<co_MaxVerkMPV;VerkM++)
		{
			InFile >> AktWert[VerkM];
			if (AktWert[VerkM]<0)
			{
				WerteOK=false;
			}
		}

		if ((AktQ>0)&&(AktQ<=co_MaxVZ)&&(AktZ>0)&&(AktZ<=co_MaxVZ)&&(WerteOK))
		{
			for (VerkM=0;VerkM<co_MaxVerkMPV;VerkM++)
				Wert[AktQ-1][AktZ-1][VerkM]=AktWert[VerkM];
		}
	}

	InFile.close();

	if (InFile.bad()==0)
		return true;
	else
		return false;
}


// *****************************************************************************************


void CCalcPVMatrix::WertInit()
{
	for (short i1=0;i1<co_MaxVZ;i1++)
		for (short i2=0;i2<co_MaxVZ;i2++)
			for (short i3=0;i3<co_MaxVerkMPV;i3++)
				Wert[i1][i2][i3]=0;
}


// *****************************************************************************************


bool CCalcPVMatrix::Export_Tranplan(CString PathOutput, short VerkM)
{
	ofstream OutFile;

	OutFile.open(PathOutput,ios::out);

	for (short i1=0;i1<VZListe.AnzahlVZ;i1++)
		for (short i2=0;i2<VZListe.AnzahlVZ;i2++)
			if (Wert[i1][i2][VerkM]>0)
			{
				OutFile << setw(5) << VZListe.VZStDat[i1].Nr << setw(5) 
					<< VZListe.VZStDat[i2].Nr << "  1" << setiosflags(ios::fixed) 
					<< setprecision(2) << setw(7) << Wert[i1][i2][VerkM] 
					<< endl;
			}

	OutFile.close();

	if (OutFile.bad()==0)
		return true;
	else
		return false;
}


// *****************************************************************************************


bool CCalcPVMatrix::Export_Visum(CString PathOutput, short VerkM)
{
	ofstream OutFile;

	OutFile.open(PathOutput,ios::out);

	//Zunächst den Dateikopf schreiben
	OutFile<<"$ON"<<endl;
	OutFile<<"*  Quell  Ziel  Anzahl  "<<endl;
	OutFile<<"*   Bez    Bez  Fahrten "<<endl;

	//Dann die besetzten Zellen herausschreiben
	for (short k1=0;k1<VZListe.AnzahlVZ;k1++)
		for (short k2=0;k2<VZListe.AnzahlVZ;k2++)
		{
			if (Wert[k1][k2][VerkM]!=0)
			{
				OutFile << setw(8) << VZListe.VZStDat[k1].Nr
					<< setw(8) << VZListe.VZStDat[k2].Nr
					<< setiosflags(ios::fixed) << setprecision(0)
					<< setw(10) << Wert[k1][k2][VerkM] << endl;
			}
		}

	OutFile.close();

	if (OutFile.bad()==0)
		return true;
	else
		return false;
}


// *****************************************************************************************


void CCalcPVMatrix::Kalibrieren_VZ(CCalcVektor* ZielVekSoll, CCalcPVMatrix* Faktor)
{
	//Gesamtmatrix über alle Verkehrsmittel auf VZ-Ebene berechnen
	double (*GesMat)[co_MaxVZ];
	GesMat = new double[co_MaxVZ][co_MaxVZ];
	for (short i1=0;i1<co_MaxVZ;i1++)
		for (short i2=0;i2<co_MaxVZ;i2++)
			GesMat[i1][i2]=0;

	for (i1=0;i1<VZListe.AnzahlVZ;i1++)
		for (short i2=0;i2<VZListe.AnzahlVZ;i2++)
			for (short i3=0;i3<co_MaxVerkMPV;i3++)
				GesMat[i1][i2] = GesMat[i1][i2] + Wert[i1][i2][i3];

	//Quellverkehr-Vektor(soll) berechnen
	CCalcVektor* QuellVekSoll = new CCalcVektor;
	QuellVekSoll->Init();
	for (i1=0;i1<VZListe.AnzahlVZ;i1++)
		for (short i2=0;i2<VZListe.AnzahlVZ;i2++)
			QuellVekSoll->Wert[i1] = QuellVekSoll->Wert[i1] + GesMat[i1][i2];

	//Feld zum separaten Speichern der Kalibrationsfaktoren einrichten
	Faktor->WertInit();
	for (i1=0;i1<VZListe.AnzahlVZ;i1++)
		for (short i2=0;i2<VZListe.AnzahlVZ;i2++)
			Faktor->Wert[i1][i2][0]=1;

	//3 Kalibrationsläufe
	for (short Durchlauf=0;Durchlauf<3;Durchlauf++)
	{
		//Aktuellen Zielverkehrs-Vektor berechnen
		CCalcVektor* ZielVek = new CCalcVektor;
		ZielVek->Init();
		for (i1=0;i1<VZListe.AnzahlVZ;i1++)
			for (short i2=0;i2<VZListe.AnzahlVZ;i2++)
				ZielVek->Wert[i2] = ZielVek->Wert[i2] + GesMat[i1][i2] * Faktor->Wert[i1][i2][0];

		//Faktoren für die Anpassung an den Zielvektor bestimmen
		for (i1=0;i1<VZListe.AnzahlVZ;i1++)
		{
			if (ZielVek->Wert[i1]>0)
				ZielVek->Wert[i1] = ZielVekSoll->Wert[i1] / ZielVek->Wert[i1];
			else
				ZielVek->Wert[i1] = 0;
		}

		//Faktoren auf den Faktoren-Vektor anwenden
		for (i1=0;i1<VZListe.AnzahlVZ;i1++)
			for (short i2=0;i2<VZListe.AnzahlVZ;i2++)
				Faktor->Wert[i1][i2][0] = Faktor->Wert[i1][i2][0] * ZielVek->Wert[i2];

		//Aktuellen Quellverkehrs-Vektor mit angewandten Faktoren bestimmen
		CCalcVektor* QuellVek = new CCalcVektor;
		QuellVek->Init();
		for (i1=0;i1<VZListe.AnzahlVZ;i1++)
			for (short i2=0;i2<VZListe.AnzahlVZ;i2++)
				QuellVek->Wert[i1] = QuellVek->Wert[i1] + GesMat[i1][i2] * Faktor->Wert[i1][i2][0];

		//Faktoren für die Anpassung an den Quellvektor bestimmen
		for (i1=0;i1<VZListe.AnzahlVZ;i1++)
		{
			if (QuellVek->Wert[i1]>0)
				QuellVek->Wert[i1] = QuellVekSoll->Wert[i1] / QuellVek->Wert[i1];
			else
				QuellVek->Wert[i1] = 0;
		}

		//Faktoren auf den Faktoren-Vektor anwenden
		for (i1=0;i1<VZListe.AnzahlVZ;i1++)
			for (short i2=0;i2<VZListe.AnzahlVZ;i2++)
				Faktor->Wert[i1][i2][0] = Faktor->Wert[i1][i2][0] * QuellVek->Wert[i1];

		delete ZielVek;
		delete QuellVek;
	}
	delete [] GesMat;


	CCalcPVTeilmatrix (*RestMat) = new CCalcPVTeilmatrix;
	RestMat->Init();

	//Faktoren auf die einzelnen Verkehrsmittelmatrizen anwenden
	for (i1=0;i1<VZListe.AnzahlVZ;i1++)
	{
		for (short i2=0;i2<VZListe.AnzahlVZ;i2++)
		{
			for (short i3=0;i3<co_MaxVerkMPV;i3++)
			{
				RestMat->Wert[i2][i3] = Wert [i1][i2][i3] * Faktor->Wert[i1][i2][0];
				Wert[i1][i2][i3] = int(Wert [i1][i2][i3] * Faktor->Wert[i1][i2][0]);
				RestMat->Wert[i2][i3] = RestMat->Wert[i2][i3] - Wert[i1][i2][i3];
			}
		}

		//Rundungsfehler beseitigen
		RundungsfehlerBeseitigenVer2(i1,QuellVekSoll->Wert[i1],RestMat);
	}
	
	delete RestMat;
	delete QuellVekSoll;
}


// *****************************************************************************************


//Teilt alle Werte durch 1000 und ruft die Funktion zur Beseitigung von
//Rundungsfehlern auf
void CCalcPVMatrix::Teile1000()
{
	for (short i1=0;i1<VZListe.AnzahlVZ;i1++)
	{
		//Zu erhaltende Summe bestimmen
		double Summe=0;
		for (short i2=0;i2<VZListe.AnzahlVZ;i2++)
			for (short i3=0;i3<co_MaxVerkMPV;i3++)
				Summe = Summe + Wert[i1][i2][i3];
		//Dies muss natürlich auch durch 1000 geteilt werden
		Summe = Summe / 1000;

		CCalcPVTeilmatrix (*RestMat) = new CCalcPVTeilmatrix;
		RestMat->Init();

		//Jetzt die Werte durch 1000 teilen
		for (i2=0;i2<VZListe.AnzahlVZ;i2++)
		{
			for (short i3=0;i3<co_MaxVerkMPV;i3++)
			{
				RestMat->Wert[i2][i3] = Wert[i1][i2][i3]/1000 - int(Wert[i1][i2][i3]/1000);
				Wert[i1][i2][i3] = int(Wert[i1][i2][i3]/1000);
			}
		}

		RundungsfehlerBeseitigenVer2(i1,Summe,RestMat);

		delete RestMat;
/*
		//ALTER RUNDUNGSCODE
		//Jetzt die Werte durch 1000 teilen
		for (i2=0;i2<VZListe.AnzahlVZ;i2++)
			for (short i3=0;i3<co_MaxVerkMPV;i3++)
				Wert[i1][i2][i3] = Runden(Wert[i1][i2][i3]/1000);

		//Und schließlich die Rundungsfehler beseitigen
		RundungsfehlerBeseitigen(i1,Summe);
*/
	}
}


// *****************************************************************************************


bool CCalcPVMatrix::SaveQuellZielVerkehr_prn(CString Datei)
{
	//Zunächst Quell- und Zielverkehr bestimmen
	double (*QuellV);
	QuellV = new double[co_MaxVZ];
	double (*ZielV);
	ZielV = new double[co_MaxVZ];
	for (short i1=0;i1<co_MaxVZ;i1++)
	{
		QuellV[i1]=0;
		ZielV[i1]=0;
	}

	for (i1=0;i1<VZListe.AnzahlVZ;i1++)
		for (short i2=0;i2<VZListe.AnzahlVZ;i2++)
			for (short i3=0;i3<co_MaxVerkMPV;i3++)
			{
				QuellV[i1] = QuellV[i1] + Wert[i1][i2][i3];
				ZielV[i2] = ZielV[i2] + Wert[i1][i2][i3];
			}

	ofstream OutFile;
	OutFile.open(Datei,ios::out);
	OutFile << "VZ;QV;ZV" << endl;
	for (i1=0;i1<VZListe.AnzahlVZ;i1++)
	{
		OutFile << setiosflags(ios::fixed) << VZListe.VZStDat[i1].Nr << ";"
			<< setprecision(4) << QuellV[i1] << ";" << ZielV[i1] << endl;
	}
	OutFile.close();

	delete [] QuellV;
	delete [] ZielV;

	return true;
}


// *****************************************************************************************


void CCalcPVMatrix::Addiere(CCalcPVMatrix* InMatrix)
{
	for (short i1=0;i1<co_MaxVZ;i1++)
		for (short i2=0;i2<co_MaxVZ;i2++)
			for (short i3=0;i3<co_MaxVerkMPV;i3++)
			{
				Wert[i1][i2][i3] = Wert[i1][i2][i3] + InMatrix->Wert[i1][i2][i3];
			}
}


// *****************************************************************************************


bool CCalcPVMatrix::Save_prn0(CString PathOutput)
{
	ofstream OutFile;

	OutFile.open(PathOutput,ios::out);

	for (short i1=0;i1<VZListe.AnzahlVZ;i1++)
		for (short i2=0;i2<VZListe.AnzahlVZ;i2++)
			{
				OutFile << setiosflags(ios::fixed) << setprecision(0)
					<< i1+1 << " " << i2+1;
				for (short i3=0;i3<co_MaxVerkMPV;i3++)
					OutFile << " " << Wert[i1][i2][i3];
				OutFile << endl;
			}

	OutFile.close();

	if (OutFile.bad()==0)
		return true;
	else
		return false;	
}


// *****************************************************************************************


bool CCalcPVMatrix::Export_csv(CString PathOutput, short VerkM)
{
	ofstream OutFile;

	OutFile.open(PathOutput,ios::out);

	for (short i1=0;i1<VZListe.AnzahlVZ;i1++)
		for (short i2=0;i2<VZListe.AnzahlVZ;i2++)
			{
				OutFile << VZListe.VZStDat[i1].Nr << "," 
					<< VZListe.VZStDat[i2].Nr << ","
					<< setiosflags(ios::fixed) 
					<< setprecision(0) << Wert[i1][i2][VerkM] 
					<< endl;
			}

	OutFile.close();

	if (OutFile.bad()==0)
		return true;
	else
		return false;
}


// *****************************************************************************************


void CCalcPVMatrix::Auswerten_ModalSplit(CString Datei, CString Format)
{
	short Durchlauf = 0;
	if ((Format.GetAt(1)=='1')&&(Format.GetAt(4)=='1'))
		Durchlauf = 2;
	else
		Durchlauf = 1;

	for (short AktDurch=0;AktDurch<Durchlauf;AktDurch++)
	{
		double (*QuellV);
		QuellV = new double[co_MaxVerkMPV];
		double (*ZielV);
		ZielV = new double[co_MaxVerkMPV];
		for (short i1=0;i1<co_MaxVerkMPV;i1++)
		{
			QuellV[i1]=0;
			ZielV[i1]=0;
		}

		//Locale je nach Ausgabeformat setzen, so dass richtiges Dezimaltrennzeichen
		//verwendet wird
		CString Trenner = "";
		CString Kopfzeile = "";
		CString Dateiname = "";

		if ((AktDurch==0)&&(Format.GetAt(1)=='1'))
		{
			setlocale(LC_NUMERIC,"usa");
			Trenner = ",";
			Kopfzeile = "Nr,Q-Fuss,Q-Rad,Q-MIVF,Q-MIVB,Q-OEV,Q-SOEV,Z-Fuss,Z-Rad,Z-MIVF,Z-MIVB,Z-OEV,Z-SOEV";
			Dateiname = Datei + ".csv";
		}
		else
		{
			setlocale(LC_NUMERIC,"deu");
			Trenner = "\t";
			Kopfzeile = "Nr\tQ_Fuss\tQ_Rad\tQ_MIVF\tQ_MIVB\tQ_OEV\tQ_SOEV\tZ_Fuss\tZ_Rad\tZ_MIVF\tZ_MIVB\tZ_OEV\tZ_SOEV";
			Dateiname = Datei + ".tab";
		}
		
		//Header schreiben
		ofstream OutFile;
		OutFile.open(Dateiname,ios::out);
		OutFile << Kopfzeile << endl;
		OutFile << setiosflags(ios::fixed) << setprecision(3);

		//Zunächst globalen Modal-Split bestimmen
		for (i1=0;i1<VZListe.AnzahlVZ;i1++)
			for (short i2=0;i2<VZListe.AnzahlVZ;i2++)
				for (short i3=0;i3<co_MaxVerkMPV;i3++)
				{
					QuellV[i3] = QuellV[i3] + Wert[i1][i2][i3];
					ZielV[i3] = ZielV[i3] + Wert[i2][i1][i3];
				}

		//Summen bestimmen und Anteile berechnen
		double SummeQ = 0; double SummeZ = 0;
		for (i1=0;i1<co_MaxVerkMPV;i1++)
		{
			SummeQ = SummeQ + QuellV[i1];
			SummeZ = SummeZ + ZielV[i1];
		}
		for (i1=0;i1<co_MaxVerkMPV;i1++)
		{
			if (SummeQ!=0)
				QuellV[i1] = QuellV[i1]/SummeQ;
			else
				QuellV[i1] = 0;
			if (SummeZ!=0)
				ZielV[i1] = ZielV[i1]/SummeZ;
			else
				ZielV[i1] = 0;
		}

		//Anteile ausgeben
		OutFile << "GESAMT";
		for (i1=0;i1<co_MaxVerkMPV;i1++)
			OutFile << Trenner << QuellV[i1];
		for (i1=0;i1<co_MaxVerkMPV;i1++)
			OutFile << Trenner << ZielV[i1];
		OutFile << endl;


		//Nun die Modal-Split-Werte für die einzelnen Zellen berechnen
		for (i1=0;i1<VZListe.AnzahlVZ;i1++)
		{
			for (short i2=0;i2<co_MaxVerkMPV;i2++)
			{
				QuellV[i2]=0;
				ZielV[i2]=0;
			}
			for (i2=0;i2<VZListe.AnzahlVZ;i2++)
				for (short i3=0;i3<co_MaxVerkMPV;i3++)
				{
					QuellV[i3] = QuellV[i3] + Wert[i1][i2][i3];
					ZielV[i3] = ZielV[i3] + Wert[i2][i1][i3];
				}
			//Summen bestimmen und Anteile berechnen
			SummeQ = 0; SummeZ = 0;
			for (i2=0;i2<co_MaxVerkMPV;i2++)
			{
				SummeQ = SummeQ + QuellV[i2];
				SummeZ = SummeZ + ZielV[i2];
			}
			for (i2=0;i2<co_MaxVerkMPV;i2++)
			{
				if (SummeQ!=0)
					QuellV[i2] = QuellV[i2]/SummeQ;
				else
					QuellV[i2] = 0;
				if (SummeZ!=0)
					ZielV[i2] = ZielV[i2]/SummeZ;
				else
					ZielV[i2] = 0;
			}

			//Anteile ausgeben
			OutFile << VZListe.VZStDat[i1].Nr;
			for (i2=0;i2<co_MaxVerkMPV;i2++)
				OutFile << Trenner << QuellV[i2];
			for (i2=0;i2<co_MaxVerkMPV;i2++)
				OutFile << Trenner << ZielV[i2];
			OutFile << endl;
		}

		OutFile.close();

		//Locale zurücksetzen, damit ansonsten Punkte als Trennzeichen verwendet werden
		setlocale(LC_NUMERIC,"usa");		
		
		delete [] QuellV;
		delete [] ZielV;
	}//Ende Schleife über notwendige Durchläufe
}


// *****************************************************************************************


void CCalcPVMatrix::Auswerten_QuellZielVerkehr(CString Datei, CString Format)
{
	short Durchlauf = 0;
	if ((Format.GetAt(1)=='1')&&(Format.GetAt(4)=='1'))
		Durchlauf = 2;
	else
		Durchlauf = 1;

	for (short AktDurch=0;AktDurch<Durchlauf;AktDurch++)
	{
		//Zunächst Quell- und Zielverkehr bestimmen
		double (*QuellV)[co_MaxVerkMPV];
		QuellV = new double[co_MaxVZ][co_MaxVerkMPV];
		double (*ZielV)[co_MaxVerkMPV];
		ZielV = new double[co_MaxVZ][co_MaxVerkMPV];
		for (short i1=0;i1<co_MaxVZ;i1++)
			for (short i2=0;i2<co_MaxVerkMPV;i2++)
			{
				QuellV[i1][i2]=0;
				ZielV[i1][i2]=0;
			}

		for (i1=0;i1<VZListe.AnzahlVZ;i1++)
			for (short i2=0;i2<VZListe.AnzahlVZ;i2++)
				for (short i3=0;i3<co_MaxVerkMPV;i3++)
				{
					QuellV[i1][i3] = QuellV[i1][i3] + Wert[i1][i2][i3];
					ZielV[i2][i3] = ZielV[i2][i3] + Wert[i1][i2][i3];
				}


		//Locale je nach Ausgabeformat setzen, so dass richtiges Dezimaltrennzeichen
		//verwendet wird
		CString Trenner = "";
		CString Kopfzeile = "";
		CString Dateiname = "";

		if ((AktDurch==0)&&(Format.GetAt(1)=='1'))
		{
			setlocale(LC_NUMERIC,"usa");
			Trenner = ",";
			Kopfzeile = "Nr,Q-Fuss,Q-Rad,Q-MIVF,Q-MIVB,Q-OEV,Q-SOEV,Q-Ges,Z-Fuss,Z-Rad,Z-MIVF,Z-MIVB,Z-OEV,Z-SOEV,Z-Ges";
			Dateiname = Datei + ".csv";
		}
		else
		{
			setlocale(LC_NUMERIC,"deu");
			Trenner = "\t";
			Kopfzeile = "Nr\tQ_Fuss\tQ_Rad\tQ_MIVF\tQ_MIVB\tQ_OEV\tQ_SOEV\tQ_Ges\tZ_Fuss\tZ_Rad\tZ_MIVF\tZ_MIVB\tZ_OEV\tZ-SOEV\tZ_Ges";
			Dateiname = Datei + ".tab";
		}
				
		ofstream OutFile;
		OutFile.open(Dateiname,ios::out);
		OutFile << Kopfzeile << endl;
		for (i1=0;i1<VZListe.AnzahlVZ;i1++)
		{
			OutFile << VZListe.VZStDat[i1].Nr << setiosflags(ios::fixed) << setprecision(0);
			double Summe=0;
			for (short i2=0;i2<co_MaxVerkMPV;i2++)
			{
				Summe = Summe + QuellV[i1][i2];
				OutFile << Trenner << QuellV[i1][i2];
			}
			OutFile << Trenner << Summe;
			Summe=0;
			for (i2=0;i2<co_MaxVerkMPV;i2++)
			{
				Summe = Summe + ZielV[i1][i2];
				OutFile << Trenner << ZielV[i1][i2];
			}
			OutFile << Trenner << Summe << endl;
		}
		OutFile.close();

		//Locale zurücksetzen, damit ansonsten Punkte als Trennzeichen verwendet werden
		setlocale(LC_NUMERIC,"usa");
		
		delete [] QuellV;
		delete [] ZielV;
	}
}


// *****************************************************************************************


bool CCalcPVMatrix::Export_ArcGIS(CString Datei)
{
/*	ofstream OutFile;

	OutFile.open(Datei,ios::out);

	//Titelzeile schreiben
	OutFile << "QVZ\tZVZ\tQZVZ\tFuss\tRad\tMIVF\tMIVB\tOEV\tSOEV\tGES" << endl;

	for (short i1=0;i1<VZListe.AnzahlVZ;i1++)
		for (short i2=0;i2<VZListe.AnzahlVZ;i2++)
		{
			int QZvzID = (i1+1)*10000+(i2+1);
			OutFile << setiosflags(ios::fixed) << setprecision(0)
				<< i1+1 << "\t" << i2+1 << "\t" << QZvzID;
			double Summe=0;
			for (short i3=0;i3<co_MaxVerkMPV;i3++)
			{
				OutFile << "\t" << Wert[i1][i2][i3];
				Summe=Summe+Wert[i1][i2][i3];
			}
			OutFile << "\t" << Summe << endl;
		}

	OutFile.close();

	if (OutFile.bad()==0)
		return true;
	else
		return false;	
*/
	ofstream OutFile;

	OutFile.open(Datei,ios::out);

	//Titelzeile schreiben
	OutFile << "QVZ\tZVZ\tQZVZ\tFuss\tRad\tMIVF\tMIVB\tOEV\tSOEV" << endl;

	for (short i1=0;i1<VZListe.AnzahlVZ;i1++)
		for (short i2=0;i2<VZListe.AnzahlVZ;i2++)
		{
//			OutFile << setiosflags(ios::fixed) << setprecision(0)
//				<< i1+1 << "\t" << i2+1;
			if (i1!=i2)
			{
				OutFile << setiosflags(ios::fixed) << setprecision(0)
					<< VZListe.VZStDat[i1].Nr << "\t" << VZListe.VZStDat[i2].Nr
					<< "\t" << VZListe.VZStDat[i1].Nr*10000+VZListe.VZStDat[i2].Nr;


				double Summe=0;
				for (short i3=0;i3<co_MaxVerkMPV;i3++)
				{
					OutFile << "\t" << Wert[i1][i2][i3];
					Summe=Summe+Wert[i1][i2][i3];
				}
				OutFile << endl;
			}
		}

	OutFile.close();

	if (OutFile.bad()==0)
		return true;
	else
		return false;	

}


// *****************************************************************************************


void CCalcPVMatrix::FaktorenAnwenden(CCalcPVMatrix* Faktor)
{
	//Quellverkehr-Vektor(soll) berechnen
	CCalcVektor* QuellVekSoll = new CCalcVektor;
	QuellVekSoll->Init();
	for (short i1=0;i1<VZListe.AnzahlVZ;i1++)
		for (short i2=0;i2<VZListe.AnzahlVZ;i2++)
			for (short i3=0;i3<co_MaxVerkMPV;i3++)
				QuellVekSoll->Wert[i1] = QuellVekSoll->Wert[i1] + Wert[i1][i2][i3];

	CCalcPVTeilmatrix (*RestMat) = new CCalcPVTeilmatrix;
	RestMat->Init();

	//Faktoren auf die einzelnen Verkehrsmittelmatrizen anwenden
	for (i1=0;i1<VZListe.AnzahlVZ;i1++)
	{
		for (short i2=0;i2<VZListe.AnzahlVZ;i2++)
		{
			for (short i3=0;i3<co_MaxVerkMPV;i3++)
			{
				RestMat->Wert[i2][i3] = Wert[i1][i2][i3] * Faktor->Wert[i1][i2][0];
				Wert[i1][i2][i3] = int(Wert[i1][i2][i3] * Faktor->Wert[i1][i2][0]);
				RestMat->Wert[i2][i3] = RestMat->Wert[i2][i3] - Wert[i1][i2][i3];
			}
		}

		//Rundungsfehler beseitigen
		RundungsfehlerBeseitigenVer2(i1,QuellVekSoll->Wert[i1],RestMat);
	}
	
	delete RestMat;
	delete QuellVekSoll;
}


// *****************************************************************************************


void CCalcPVMatrix::Aggregieren(short AggregatTyp)
{
	//Interne Zuordnungsliste für das Aggregat erstellen
	CCalcPVAggregatListe* AggListe = new CCalcPVAggregatListe;
	AggListe->VZListe.KopiereVZListe(VZListe);
	AggListe->AggregatListeErzeugen(AggregatTyp);

	//Feld zur Aufnahme der aggregierten Werte implementieren
	double (*AggWerte)[co_MaxVZ][co_MaxVerkMPV];
	AggWerte = new double[co_MaxVZ][co_MaxVZ][co_MaxVerkMPV];
	for (short i1=0;i1<co_MaxVZ;i1++)
		for (short i2=0;i2<co_MaxVZ;i2++)
			for (short i3=0;i3<co_MaxVerkMPV;i3++)
				AggWerte[i1][i2][i3]=0;

	//Jetzt über alle Werte der Ursprungsmatrix laufen
	for (i1=0;i1<VZListe.AnzahlVZ;i1++)
	{
		//Interne Nummer für QuellVZ heraussuchen
		short IntAggNrQuelle = AggListe->GibInterneAggNr(AggregatTyp, i1);

		for (short i2=0;i2<VZListe.AnzahlVZ;i2++)
		{
			//Interne Nummer für ZielVZ heraussuchen
			short IntAggNrZiel = AggListe->GibInterneAggNr(AggregatTyp, i2);

			//Jetzt die konkreten Werte übernehmen
			for (short i3=0;i3<co_MaxVerkMPV;i3++)
			{
				AggWerte[IntAggNrQuelle][IntAggNrZiel][i3] 
					= AggWerte[IntAggNrQuelle][IntAggNrZiel][i3] + Wert[i1][i2][i3];
			}
		}
	}

	WertInit();
	
	//... und die aggregierten Werte wieder in die Matrix zurückspielen
	for (i1=0;i1<AggListe->AnzahlAgg;i1++)
		for (short i2=0;i2<AggListe->AnzahlAgg;i2++)
			for (short i3=0;i3<co_MaxVerkMPV;i3++)
				Wert[i1][i2][i3] = AggWerte[i1][i2][i3];

	delete [] AggWerte;

	//VZListe durch AggListe ersetzen
	VZListe.Init();
	for (i1=0;i1<AggListe->AnzahlAgg;i1++)
		VZListe.VZStDat[i1].Nr = AggListe->Nr[i1];

	VZListe.AnzahlVZ = AggListe->AnzahlAgg;
	
	delete AggListe;
}


// *****************************************************************************************


void CCalcPVMatrix::Kalibrieren_VD(CCalcVektor* ZielVekSoll, CCalcPVMatrix* FaktorVZ)
{
	//Gesamtmatrix über alle Verkehrsmittel auf VD-Ebene berechnen

	//Zielvektor (SOLL) zusammenfassen
	//dafür Interne Zuordnungsliste für das Aggregat(VD) erstellen
	CCalcPVAggregatListe* AggListe = new CCalcPVAggregatListe;
	AggListe->VZListe.KopiereVZListe(VZListe);
	AggListe->AggregatListeErzeugen(0);

	//Feld zur Zwischenaufnahme des zusammengefassten Vektors erstellen
	CCalcVektor* AggZielVekSoll = new CCalcVektor;
	AggZielVekSoll->Init();

	//Jetzt über alle Werte des Ursprungsvektors laufen
	for (short i1=0;i1<VZListe.AnzahlVZ;i1++)
	{
		//Interne Nummer für VZ heraussuchen
		short IntAggNr = AggListe->GibInterneAggNr(0,i1);

		//Jetzt die konkreten Werte übernehmen
		AggZielVekSoll->Wert[IntAggNr]= AggZielVekSoll->Wert[IntAggNr] + ZielVekSoll->Wert[i1];
	}

	//Matrix zur Aufnahme der aggregierten Werte erstellen
	CCalcPVMatrix* AggMatrix = new CCalcPVMatrix;
	AggMatrix->WertInit();
	AggMatrix->VZListe.KopiereVZListe(VZListe);
	AggMatrix->Addiere(this);

	//Aggregieren der kopierten Matrix mit Aggregat 0 aufrufen
	AggMatrix->Aggregieren(0);

	//Aggregieren funktioniert einwandfrei - geprüft 06.11.2003

	//
	//Ab hier findet jetzt alles auf dem aggregierten VD-Niveau statt
	//

	//Feld für VD-Gesamtmatrix implementieren
	double (*GesMat)[co_MaxVZ];
	GesMat = new double[co_MaxVZ][co_MaxVZ];
	for (i1=0;i1<co_MaxVZ;i1++)
		for (short i2=0;i2<co_MaxVZ;i2++)
			GesMat[i1][i2]=0;

	//Werte in VD-Gesamtmatrix überführen
	if (AggListe->AnzahlAgg!=AggMatrix->VZListe.AnzahlVZ)
		AfxMessageBox("Programmierfehler");

	for (i1=0;i1<AggListe->AnzahlAgg;i1++)
		for (short i2=0;i2<AggListe->AnzahlAgg;i2++)
			for (short i3=0;i3<co_MaxVerkMPV;i3++)
				GesMat[i1][i2] = GesMat[i1][i2] + AggMatrix->Wert[i1][i2][i3];

	//VD-Quellverkehr-Vektor(soll) berechnen
	CCalcVektor* AggQuellVekSoll = new CCalcVektor;
	AggQuellVekSoll->Init();
	for (i1=0;i1<AggMatrix->VZListe.AnzahlVZ;i1++)
		for (short i2=0;i2<AggMatrix->VZListe.AnzahlVZ;i2++)
			AggQuellVekSoll->Wert[i1] = AggQuellVekSoll->Wert[i1] + GesMat[i1][i2];

	//Feld zum separaten Speichern der Kalibrationsfaktoren einrichten
	CCalcPVMatrix* Faktor = new CCalcPVMatrix;
	Faktor->WertInit();
	for (i1=0;i1<AggListe->AnzahlAgg;i1++)
		for (short i2=0;i2<AggListe->AnzahlAgg;i2++)
			Faktor->Wert[i1][i2][0]=1;

	//3 Kalibrationsläufe
	for (short Durchlauf=0;Durchlauf<3;Durchlauf++)
	{
		//Aktuellen Zielverkehrs-Vektor berechnen
		CCalcVektor* ZielVek = new CCalcVektor;
		ZielVek->Init();
		for (i1=0;i1<AggListe->AnzahlAgg;i1++)
			for (short i2=0;i2<AggListe->AnzahlAgg;i2++)
				ZielVek->Wert[i2] = ZielVek->Wert[i2] + GesMat[i1][i2] * Faktor->Wert[i1][i2][0];

		//Faktoren für die Anpassung an den Zielvektor bestimmen
		for (i1=0;i1<AggListe->AnzahlAgg;i1++)
		{
			if (ZielVek->Wert[i1]>0)
				ZielVek->Wert[i1] = AggZielVekSoll->Wert[i1] / ZielVek->Wert[i1];
			else
				ZielVek->Wert[i1] = 0;
		}

		//Faktoren auf den Faktoren-Vektor anwenden
		for (i1=0;i1<AggListe->AnzahlAgg;i1++)
			for (short i2=0;i2<AggListe->AnzahlAgg;i2++)
				Faktor->Wert[i1][i2][0] = Faktor->Wert[i1][i2][0] * ZielVek->Wert[i2];

		//Aktuellen Quellverkehrs-Vektor mit angewandten Faktoren bestimmen
		CCalcVektor* QuellVek = new CCalcVektor;
		QuellVek->Init();
		for (i1=0;i1<AggListe->AnzahlAgg;i1++)
			for (short i2=0;i2<AggListe->AnzahlAgg;i2++)
				QuellVek->Wert[i1] = QuellVek->Wert[i1] + GesMat[i1][i2] * Faktor->Wert[i1][i2][0];

		//Faktoren für die Anpassung an den Quellvektor bestimmen
		for (i1=0;i1<AggListe->AnzahlAgg;i1++)
		{
			if (QuellVek->Wert[i1]>0)
				QuellVek->Wert[i1] = AggQuellVekSoll->Wert[i1] / QuellVek->Wert[i1];
			else
				QuellVek->Wert[i1] = 0;
		}

		//Faktoren auf den Faktoren-Vektor anwenden
		for (i1=0;i1<AggListe->AnzahlAgg;i1++)
			for (short i2=0;i2<AggListe->AnzahlAgg;i2++)
				Faktor->Wert[i1][i2][0] = Faktor->Wert[i1][i2][0] * QuellVek->Wert[i1];

		delete ZielVek;
		delete QuellVek;
	}
	delete [] GesMat;

	//
	//Jetzt die ermittelten Faktoren wieder auf VZ-Niveau zurückspielen
	//und dann auf die ursprüngliche Matrix anwenden
	//
	FaktorVZ->WertInit();
	//Über alle Verkehrszellen laufen
	for (i1=0;i1<FaktorVZ->VZListe.AnzahlVZ;i1++)
	{
		//Interne Nummer für VZ heraussuchen
		short IntAggNrQuelle = AggListe->GibInterneAggNr(0,i1);

		for (short i2=0;i2<FaktorVZ->VZListe.AnzahlVZ;i2++)
		{
			//Interne Nummer für VZ heraussuchen
			short IntAggNrZiel = AggListe->GibInterneAggNr(0,i2);
			
			//Jetzt die konkreten Werte übernehmen
			for (short i3=0;i3<co_MaxVerkMPV;i3++)
				FaktorVZ->Wert[i1][i2][i3] = Faktor->Wert[IntAggNrQuelle][IntAggNrZiel][0];
		}
	}

	delete Faktor;
	delete AggListe;
	delete AggQuellVekSoll;

	//Quellverkehr-Vektor(soll) auf der Basis berechnen
	CCalcVektor* QuellVekSoll = new CCalcVektor;
	QuellVekSoll->Init();
	for (i1=0;i1<VZListe.AnzahlVZ;i1++)
		for (short i2=0;i2<VZListe.AnzahlVZ;i2++)
			for (short i3=0;i3<co_MaxVerkMPV;i3++)
				QuellVekSoll->Wert[i1] = QuellVekSoll->Wert[i1] + Wert[i1][i2][i3];


	CCalcPVTeilmatrix (*RestMat) = new CCalcPVTeilmatrix;
	RestMat->Init();

	//Faktoren auf die einzelnen Verkehrsmittelmatrizen anwenden
	for (i1=0;i1<VZListe.AnzahlVZ;i1++)
	{
		for (short i2=0;i2<VZListe.AnzahlVZ;i2++)
		{
			for (short i3=0;i3<co_MaxVerkMPV;i3++)
			{
				RestMat->Wert[i2][i3] = Wert [i1][i2][i3] * FaktorVZ->Wert[i1][i2][0];
				Wert[i1][i2][i3] = int(Wert [i1][i2][i3] * FaktorVZ->Wert[i1][i2][0]);
				RestMat->Wert[i2][i3] = RestMat->Wert[i2][i3] - Wert[i1][i2][i3];
			}
		}

		//Rundungsfehler beseitigen
		RundungsfehlerBeseitigenVer2(i1,QuellVekSoll->Wert[i1],RestMat);
	}
	
	delete RestMat;
	delete QuellVekSoll;
}


// *****************************************************************************************


//Diese allgemeine Ausgabe um die Externen Zweck- und Personengruppen-Nummern erweitern
bool CCalcPVMatrix::OutputGenerator(short MatTyp,
									int Zweck,
									int PersGr,
									CString Formate,
									CString Aggregat,
									CString Auswertungen,
									CAktPVSzen AktSzenDat)
{
	CCalcPVMatrix* OutMat = new CCalcPVMatrix;
	OutMat->WertInit();
	OutMat->VZListe.KopiereVZListe(this->VZListe);
	OutMat->Addiere(this);
	
	//In Abhängigkeit vom OutputTyp (Gesamt, Zweck, PersGr) Stamm-Dateinamen vergeben
	CString AktOutPfad = "";
	CString Stamm = "";
	CString Anhang = "(1000)";

	//1. Sollen 1000tel oder ganze Reisen/Wege ausgegeben werden
	if (Formate.GetAt(5)!='1')
	{
		OutMat->Teile1000();
		Anhang = "";
	}
	
	//Nun zunächst die Namensbestandteile zusammenstellen
	switch (MatTyp)
	{
		case 1:
			AktOutPfad = AktSzenDat.PfadOut_AlleErgebnisse + "Hauptaktivitäten\\";
			Stamm = "HAM ";
		break;
		case 2:
			AktOutPfad = AktSzenDat.PfadOut_AlleErgebnisse + "Wege\\";
			Stamm = "Wege ";
		break;
		case 3:
			AktOutPfad = AktSzenDat.PfadOut_AlleErgebnisse + "Wege nach Stunden\\";
			Stamm = "Wege ";
		break;
		case 4:
			AktOutPfad = AktSzenDat.PfadOut_AlleErgebnisse + "Hauptaktivitäten\\nach Personengruppen\\";
			Stamm = "HAM ";
		break;
	}

	char buff[5];
	
	//Gesamtmatrix
//	if ((Zweck==-1)&&(PersGr==-1))
	if (Zweck==-1)
	{
		Stamm = Stamm + "Ges";
	}
	//zweckspezifische Matrix
	if (Zweck!=-1)
	{
		Stamm = Stamm + "Zw";
		_itoa(Zweck,buff,10);
		if (Zweck<10)
			Stamm = Stamm + "0" + buff;
		else
			Stamm = Stamm + buff;
	}
	//personengruppenspezifische Matrix
	if ((Zweck!=-1)&&(PersGr!=-1)&&(MatTyp==4))
	{
		Stamm = Stamm + "-Pg";
		_itoa(PersGr,buff,10);
		if (PersGr>99)
			Stamm = Stamm + buff;
		if ((PersGr>9)&&(PersGr<100))
			Stamm = Stamm + "0" + buff;
		if (PersGr<10)
			Stamm = Stamm + "00" + buff;
	}
	//Stundenmatrizen
	if ((PersGr!=-1)&&(MatTyp==3))
	{
		if (Zweck==-1)
		{
			Stamm = Stamm + "Ges";
		}

		Stamm = Stamm + "-Std";
		_itoa(PersGr,buff,10);
		if (PersGr>9)
			Stamm = Stamm + buff;
		if (PersGr<10)
			Stamm = Stamm + "0" + buff;
	}

	//Ausgabe VerkMod-Format
	if (Formate.GetAt(1)=='1')
		OutMat->Export_VerkMod(AktOutPfad+Stamm+Anhang+".txt");

	//Ausgabe ArcGIS-Format
	if (Formate.GetAt(4)=='1')
		OutMat->Export_ArcGIS(AktOutPfad+Stamm+"-ARC"+Anhang+".tab");

	//Ausgabe verkehrsmittelspezifische Matrizen
	for (short VerkM=0;VerkM<co_MaxVerkMPV;VerkM++)
	{
		CString AktVerkMPfad = AktOutPfad+Stamm;
		switch (VerkM)
		{
		case 0:
			AktVerkMPfad = AktVerkMPfad + "-Fuss";
			break;
		case 1:
			AktVerkMPfad = AktVerkMPfad + "-Rad";
			break;
		case 2:
			AktVerkMPfad = AktVerkMPfad + "-MIVF";
			break;
		case 3:
			AktVerkMPfad = AktVerkMPfad + "-MIVB";
			break;
		case 4:
			AktVerkMPfad = AktVerkMPfad + "-OEV";
			break;
		case 5:
			AktVerkMPfad = AktVerkMPfad + "-SOEV";
			break;
		}

		if (Formate.GetAt(2)=='1')
			OutMat->Export_Visum(AktVerkMPfad + Anhang + ".fzt",VerkM);

		if (Formate.GetAt(3)=='1')
			OutMat->Export_Tranplan(AktVerkMPfad+Anhang+".tpl",VerkM);
	}//Ende Schleife über alle Verkehrsmittel

	//Zusammenfassung der Matrizen OEV und SOEV zu GOEV
	if ((Formate.GetAt(2)=='1')||(Formate.GetAt(3)=='1'))
	{
		CString AktVerkMPfad = AktOutPfad+Stamm+"-GOEV";

		CCalcPVMatrix (*GesOEV) = new CCalcPVMatrix;
		GesOEV->WertInit();
		GesOEV->VZListe.KopiereVZListe(OutMat->VZListe);
		GesOEV->Addiere(OutMat);
		for (short qvz=0;qvz<co_MaxVZ;qvz++)
			for (short zvz=0;zvz<co_MaxVZ;zvz++)
				GesOEV->Wert[qvz][zvz][4]=GesOEV->Wert[qvz][zvz][4]+GesOEV->Wert[qvz][zvz][5];
		
		if (Formate.GetAt(2)=='1')
			GesOEV->Export_Visum(AktVerkMPfad + Anhang + ".fzt",4);

		if (Formate.GetAt(3)=='1')
			GesOEV->Export_Tranplan(AktVerkMPfad+Anhang+".tpl",4);

		delete GesOEV;
	}

	//Nun die Auswertungen durchführen
	if (Auswertungen.GetAt(1)=='1')
		OutMat->Auswerten_QuellZielVerkehr(AktOutPfad + "Ausw QZV " + Stamm + Anhang, Formate);

	if (Auswertungen.GetAt(2)=='1')
		OutMat->Auswerten_ModalSplit(AktOutPfad + "Ausw ModSp " + Stamm, Formate);

	CCalcPVMatrix (*Leistung) = new CCalcPVMatrix;
	CDatWiderstandsmatrizen (*EntfMat) = new CDatWiderstandsmatrizen;

	if ((Auswertungen.GetAt(3)=='1')||(Auswertungen.GetAt(4)=='1'))
	{
		//Zunächst Verkehrsleistungsmatrix berechnen
		EntfMat->VZEinteil.KopiereVZListe(OutMat->VZListe);
		EntfMat->Load(AktSzenDat.PfadWidMat_Entfernung);
		Leistung->WertInit();
		Leistung->VZListe.KopiereVZListe(OutMat->VZListe);
		Leistung->Addiere(OutMat);
		Leistung->Leistung_Berechnen(EntfMat);

		//Dann die Ausgaben durchführen
		if (Auswertungen.GetAt(3)=='1')
		{
			Leistung->Auswerten_QuellZielVerkehr(AktOutPfad + "KMAusw QZV " + Stamm + Anhang, Formate);
		}

		if (Auswertungen.GetAt(4)=='1')
		{
			Leistung->Auswerten_ModalSplit(AktOutPfad + "KMAusw ModSp " + Stamm, Formate);
		}
	}
	delete EntfMat;

	//Reisezeiten-Auswertung vorerst abgeschaltet
/*
	CCalcPVMatrix (*GesamtRZ) = new CCalcPVMatrix;
	CDatWiderstandsmatrizen (*RZMat) = new CDatWiderstandsmatrizen[co_MaxVerkMPV];

	if ((Auswertungen.GetAt(3)=='1')||(Auswertungen.GetAt(4)=='1'))
	{
		for (short i1=0;i1<co_MaxVerkMPV;i1++)
		{
			RZMat[i1].Init();
			RZMat[i1].VZEinteil.KopiereVZListe(OutMat->VZListe);

		}

		RZMat[0].Load(AktSzenDat.PfadWidMat_RZFuss);
		RZMat[0].LoadBinnen(AktSzenDat.PfadWidMat_Binnen,0);
		RZMat[1].Load(AktSzenDat.PfadWidMat_RZRad);
		RZMat[1].LoadBinnen(AktSzenDat.PfadWidMat_Binnen,1);
		RZMat[2].Load(AktSzenDat.PfadWidMat_RZmotIV);
		RZMat[2].LoadBinnen(AktSzenDat.PfadWidMat_Binnen,2);
		RZMat[3].Load(AktSzenDat.PfadWidMat_RZmotIV);
		RZMat[3].LoadBinnen(AktSzenDat.PfadWidMat_Binnen,3);
		RZMat[4].Load(AktSzenDat.PfadWidMat_RZOEV);
		RZMat[4].LoadBinnen(AktSzenDat.PfadWidMat_Binnen,4);
		RZMat[5].Load(AktSzenDat.PfadWidMat_RZSOEV);
		RZMat[5].LoadBinnen(AktSzenDat.PfadWidMat_Binnen,5);

		GesamtRZ->WertInit();
		GesamtRZ->VZListe.KopiereVZListe(OutMat->VZListe);
		GesamtRZ->Addiere(OutMat);
		GesamtRZ->Analyse_Gesamtreisezeiten(RZMat[0],RZMat[1],RZMat[2],RZMat[3],RZMat[4],RZMat[5]);

		//Dann die Ausgaben durchführen
		if (Auswertungen.GetAt(3)=='1')
		{
			GesamtRZ->Auswerten_QuellZielVerkehr(AktOutPfad + "RZAusw QZV " + Stamm + Anhang, Formate);
		}

		if (Auswertungen.GetAt(4)=='1')
		{
			GesamtRZ->Auswerten_ModalSplit(AktOutPfad + "RZAusw ModSp " + Stamm, Formate);
		}

	}
	delete [] RZMat;
*/

	//Jetzt ggf. aggregieren und Aggregate ausgeben und auswerten
	for (short AktAgg=0;AktAgg<4;AktAgg++)
	{
	if (Aggregat.GetAt(AktAgg)=='1')
	{
		CString Anhang2 = "";
		if (AktAgg==0)
			Anhang2 = "(VD)";
		else
		{
			char hbuff[5];
			_itoa(AktAgg,hbuff,10);
			Anhang2 = "(Agg";
			Anhang2 = Anhang2 + hbuff;
			Anhang2 = Anhang2 + ")";
		}

		CCalcPVMatrix* AggMat = new CCalcPVMatrix;
		AggMat->WertInit();
		AggMat->VZListe.KopiereVZListe(OutMat->VZListe);
		AggMat->Addiere(OutMat);

		AggMat->Aggregieren(AktAgg);

		//und nun die Ausgabe
		if (Formate.GetAt(1)=='1')
			AggMat->Export_VerkMod(AktOutPfad+Stamm+Anhang2+Anhang+".txt");

		if (Formate.GetAt(4)=='1')
			AggMat->Export_ArcGIS(AktOutPfad+Stamm+"-ARC"+Anhang2+Anhang+".tab");

		for (short VerkM=0;VerkM<co_MaxVerkMPV;VerkM++)
		{
			CString AktVerkMPfad = AktOutPfad+Stamm;
			switch (VerkM)
			{
			case 0:
				AktVerkMPfad = AktVerkMPfad + "-Fuss";
				break;
			case 1:
				AktVerkMPfad = AktVerkMPfad + "-Rad";
				break;
			case 2:
				AktVerkMPfad = AktVerkMPfad + "-MIVF";
				break;
			case 3:
				AktVerkMPfad = AktVerkMPfad + "-MIVB";
				break;
			case 4:
				AktVerkMPfad = AktVerkMPfad + "-OEV";
				break;
			case 5:
				AktVerkMPfad = AktVerkMPfad + "-SOEV";
				break;
			}

			if (Formate.GetAt(2)=='1')
				AggMat->Export_Visum(AktVerkMPfad+Anhang2+Anhang+".fzt",VerkM);

			if (Formate.GetAt(3)=='1')
				AggMat->Export_Tranplan(AktVerkMPfad+Anhang2+Anhang+".tpl",VerkM);
		}

		//Zusammenfassung der Matrizen OEV und SOEV zu GOEV
		if ((Formate.GetAt(2)=='1')||(Formate.GetAt(3)=='1'))
		{
			CString AktVerkMPfad = AktOutPfad+Stamm+"-GOEV";

			CCalcPVMatrix (*GesOEV) = new CCalcPVMatrix;
			GesOEV->WertInit();
			GesOEV->VZListe.KopiereVZListe(AggMat->VZListe);
			GesOEV->Addiere(AggMat);
			for (short qvz=0;qvz<co_MaxVZ;qvz++)
				for (short zvz=0;zvz<co_MaxVZ;zvz++)
					GesOEV->Wert[qvz][zvz][4]=GesOEV->Wert[qvz][zvz][4]+GesOEV->Wert[qvz][zvz][5];
			
			if (Formate.GetAt(2)=='1')
				GesOEV->Export_Visum(AktVerkMPfad+Anhang2+Anhang+".fzt",4);

			if (Formate.GetAt(3)=='1')
				GesOEV->Export_Tranplan(AktVerkMPfad+Anhang2+Anhang+".tpl",4);

			delete GesOEV;
		}

		//Nun die Auswertungen durchführen
		if (Auswertungen.GetAt(1)=='1')
			AggMat->Auswerten_QuellZielVerkehr(AktOutPfad + "Ausw QZV " + Stamm + Anhang2 + Anhang, Formate);

		if (Auswertungen.GetAt(2)=='1')
			AggMat->Auswerten_ModalSplit(AktOutPfad + "Ausw ModSp " + Stamm + Anhang2, Formate);

		//und schließlich ggf. noch die Leistung berechnen
		if ((Auswertungen.GetAt(3)=='1')||(Auswertungen.GetAt(4)=='1'))
		{
			AggMat->WertInit();
			AggMat->VZListe.KopiereVZListe(OutMat->VZListe);
			AggMat->Addiere(Leistung);
			AggMat->Aggregieren(AktAgg);

			if (Auswertungen.GetAt(3)=='1')
			{
				AggMat->Auswerten_QuellZielVerkehr(AktOutPfad + "KMAusw QZV " + Stamm + Anhang2 + Anhang, Formate);
			}

			if (Auswertungen.GetAt(4)=='1')
			{
				AggMat->Auswerten_ModalSplit(AktOutPfad + "KMAusw ModSp " + Stamm + Anhang2, Formate);
			}
		}

		//und die Gesamtreisezeiten
/*		if ((Auswertungen.GetAt(3)=='1')||(Auswertungen.GetAt(4)=='1'))
		{
			AggMat->WertInit();
			AggMat->VZListe.KopiereVZListe(OutMat->VZListe);
			AggMat->Addiere(GesamtRZ);
			AggMat->Aggregieren(AktAgg);

			if (Auswertungen.GetAt(3)=='1')
			{
				AggMat->Auswerten_QuellZielVerkehr(AktOutPfad + "RZAusw QZV " + Stamm + Anhang2 + Anhang, Formate);
			}

			if (Auswertungen.GetAt(4)=='1')
			{
				AggMat->Auswerten_ModalSplit(AktOutPfad + "RZAusw ModSp " + Stamm + Anhang2, Formate);
			}
		}
*/
		delete AggMat;
	}//Ende Abfrage, ob Aggregat-Typ 1..4 gebildet werden soll
	}//Ende Schleife über alle Aggregat-Typen

	delete OutMat;
	delete Leistung;
//	delete GesamtRZ;

	return true;
}


// *****************************************************************************************


void CCalcPVMatrix::Subtrahiere(CCalcPVMatrix *InMatrix)
{
	for (short i1=0;i1<co_MaxVZ;i1++)
		for (short i2=0;i2<co_MaxVZ;i2++)
			for (short i3=0;i3<co_MaxVerkMPV;i3++)
			{
				Wert[i1][i2][i3] = Wert[i1][i2][i3] - InMatrix->Wert[i1][i2][i3];
			}
}


// *****************************************************************************************


bool CCalcPVMatrix::Save_prn(CString PathOutput)
{
	ofstream OutFile;

	OutFile.open(PathOutput,ios::out);

	for (short i1=0;i1<VZListe.AnzahlVZ;i1++)
		for (short i2=0;i2<VZListe.AnzahlVZ;i2++)
		{
			bool Leer=true;
			for (short i3=0;i3<co_MaxVerkMPV;i3++)
			{
				if (Wert[i1][i2][i3]!=0)
					Leer=false;
			}
			if (!Leer)
			{
				OutFile << setiosflags(ios::fixed) << setprecision(0)
					<< i1+1 << " " << i2+1;
				for (short i3=0;i3<co_MaxVerkMPV;i3++)
					OutFile << " " << Wert[i1][i2][i3];
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


//Beseitigt Rundungsfehler für eine Quelle und einen vorgegebenen Zielwert
void CCalcPVMatrix::RundungsfehlerBeseitigen(short& AktQ, double& Zielwert)
{
	//Zunächst die aktuelle Summe bestimmen
	double AktSumme=0;
	for (short AktZ=0;AktZ<VZListe.AnzahlVZ;AktZ++)
		for (short AktVM=0;AktVM<co_MaxVerkMPV;AktVM++)
		{
			AktSumme = AktSumme + Wert[AktQ][AktZ][AktVM];
		}
	
	if ((Zielwert<0)||(AktSumme<0))
	{
		AfxMessageBox("Fehler in Rundungsfehler-Funktion");
	}

	//1. Runde: Verteilung anhand der erzeugten Anteile
	if (Runden(AktSumme)!=Runden(Zielwert))
	{
		//zu verteilende Differenz bestimmen
		double Diff=Zielwert-AktSumme;

		//Feld zum Speichern der Anteil implementieren
		CCalcPVTeilmatrix* Anteile = new CCalcPVTeilmatrix;
		Anteile->Init();

		//Nun die Differenzen entsprechend der vorherigen Anteile verteilen
		//Realisierte Verkehrsmittelanteile bestimmen
		for (short AktZ=0;AktZ<VZListe.AnzahlVZ;AktZ++)
			for (short AktVM=0;AktVM<co_MaxVerkMPV;AktVM++)
				Anteile->Wert[AktZ][AktVM] = 
					Wert[AktQ][AktZ][AktVM] / AktSumme;

		//Differenz mittels der ermittelten realisierten Anteile verteilen
		AktSumme=0;
		for (AktZ=0;AktZ<VZListe.AnzahlVZ;AktZ++)
		{
			for (short AktVM=0;AktVM<co_MaxVerkMPV;AktVM++)
			{
				double Result = Diff * Anteile->Wert[AktZ][AktVM];
				int iResult = Runden(Result);
				Wert[AktQ][AktZ][AktVM] = Wert[AktQ][AktZ][AktVM] + iResult;
				AktSumme = AktSumme + Wert[AktQ][AktZ][AktVM];
			}
		}
		delete Anteile;
	}


	//2. Runde: Verteilung der Reste auf den größten Haufen
	while (Runden(AktSumme)!=Runden(Zielwert))
	{
		double Diff=Zielwert-AktSumme;

		//Den höchsten Wert suchen und alles draufschlagen bzw. abziehen
		//Müsste mehr abgezogen werden als der höchste Wert groß ist,
		//dann vom höchsten nur 1 abziehen und Schleife erneut durchlaufen
		double Highest=0;
		short HighZiel=0;
		short HighVerkM=0;
		for (AktZ=0;AktZ<VZListe.AnzahlVZ;AktZ++)
		{
			for (short AktVM=0;AktVM<co_MaxVerkMPV;AktVM++)
			{
				if (Wert[AktQ][AktZ][AktVM]>Highest)
				{
					Highest = Wert[AktQ][AktZ][AktVM];
					HighZiel = AktZ;
					HighVerkM = AktVM;
				}
			}
		}

		if (Wert[AktQ][HighZiel][HighVerkM]+Diff>0)
		{
			Wert[AktQ][HighZiel][HighVerkM] = 
				Wert[AktQ][HighZiel][HighVerkM] + Runden(Diff);
			AktSumme = AktSumme + Runden(Diff);
		}
		else
		{
			Wert[AktQ][HighZiel][HighVerkM] = Wert[AktQ][HighZiel][HighVerkM] - 1;
			AktSumme = AktSumme - 1;
		}
	}
}


// *****************************************************************************************


void CCalcPVMatrix::RundungsfehlerBeseitigenVer2(short& AktQ,
												 double& Zielwert,
												 CCalcPVTeilmatrix* RestMat)
{
	//Zunächst die aktuelle Summe bestimmen
	double AktSumme=0;
	for (short AktZ=0;AktZ<VZListe.AnzahlVZ;AktZ++)
	{
		for (short AktVM=0;AktVM<co_MaxVerkMPV;AktVM++)
		{
			AktSumme = AktSumme + Wert[AktQ][AktZ][AktVM];
		}
	}

	//Bestehen Abweichungen zwischen aktueller Summe und dem Zielwert?
	if (Runden(AktSumme)!=Runden(Zielwert))
	{
		//Restmatrix normieren
		RestMat->Normieren();
		//Letzten besetzten Wert der RestMat hochsetzen
		RestMat->LetzterWertHoch();

		int Diff = Runden(Zielwert)-Runden(AktSumme);

		int Korrektur=0;

		if (Diff>0)
		{
			Korrektur=1;
		}
		else
		{
			Korrektur=-1;
			Diff=Diff*(-1);
		}

		//Nun per Zufall die zu verteilende Differenz in Einzelschritten aufteilen
		while (Diff>0)
		{
			RestMat->WaehleZufall();
			short AuswZ = RestMat->UebergabeVZ;
			short AuswVM = RestMat->UebergabeVM;

			if (Wert[AktQ][AuswZ][AuswVM]+Korrektur>=0)
			{
				Wert[AktQ][AuswZ][AuswVM]=Wert[AktQ][AuswZ][AuswVM]+Korrektur;
				Diff--;
			}
		}
	}
}


// *****************************************************************************************


void CCalcPVMatrix::Leistung_Berechnen(CDatWiderstandsmatrizen *EntfMat)
{
	if ((EntfMat->VZEinteil.AnzahlVZ==0)||(VZListe.AnzahlVZ==0))
	{
		AfxMessageBox("CCalcPVMatrix::Leistung_Berechnen\nVZEinteilungen od. Entfernungsmatrix fehlen");
	}

	for (short Quelle=0;Quelle<VZListe.AnzahlVZ;Quelle++)
	{
		for (short Ziel=0;Ziel<VZListe.AnzahlVZ;Ziel++)
		{
			for (short VerkM=0;VerkM<co_MaxVerkMPV;VerkM++)
			{
				Wert[Quelle][Ziel][VerkM]=Wert[Quelle][Ziel][VerkM]*double(EntfMat->Wert[Quelle][Ziel]);
			}
		}
	}
}


// *****************************************************************************************


//Speichert der Matrix im Temporärverzeichnis
bool CCalcPVMatrix::SaveTemp(CString Pfad, 
							 CString Typ,
							 short Zweck, 
							 short PersGr)
{
	CString Datei = Pfad + "\\" + Typ;
	char buff[10];

	if (Zweck==-1)
	{
		Datei=Datei+"x-";
	}
	else
	{
		_itoa(Zweck, buff, 10);
		Datei=Datei+buff+"-";
	}

	if (PersGr==-1)
	{
		Datei=Datei+"x.txt";
	}
	else
	{
		_itoa(PersGr, buff, 10);
		Datei=Datei+buff+".txt";
	}

	bool Status = Save_prn(Datei);

	return Status;
}


// *****************************************************************************************


CString CCalcPVMatrix::LoadTemp(CString Pfad, 
							 CString Typ,
							 short Zweck, 
							 short PersGr)
{
	CString Datei = Pfad + "\\" + Typ;
	char buff[10];

	if (Zweck==-1)
	{
		Datei=Datei+"x-";
	}
	else
	{
		_itoa(Zweck, buff, 10);
		Datei=Datei+buff+"-";
	}

	if (PersGr==-1)
	{
		Datei=Datei+"x.txt";
	}
	else
	{
		_itoa(PersGr, buff, 10);
		Datei=Datei+buff+".txt";
	}

	Load_prn(Datei);

	return Datei;
}


// *****************************************************************************************


double CCalcPVMatrix::GibSumme()
{
	double Summe=0;
	for (short i1=0;i1<VZListe.AnzahlVZ;i1++)
		for (short i2=0;i2<VZListe.AnzahlVZ;i2++)
			for (short i3=0;i3<co_MaxVerkMPV;i3++)
				Summe=Summe+Wert[i1][i2][i3];

	return Summe;
}


// *****************************************************************************************


void CCalcPVMatrix::Ausgabe_Durchlauf(short LaufVZ, CString Datei, CString EntfMatPfad)
{
	//Ausgabedatei für aktuellen Lauf öffnen (append-Mode)
	ofstream OutFile;
	OutFile.open(Datei, ios::app);

	//Zunächst die absolute Zahl der Akivitäten nach Verkehrsmitteln auswerten und ausgeben
	OutFile << LaufVZ+1;
	OutFile << setiosflags(ios::fixed) << setprecision(0);

	for (short VerkM=0;VerkM<6;VerkM++)
	{
		double Summe=0;
		for (short QVZ=0;QVZ<VZListe.AnzahlVZ;QVZ++)
		{
			for (short ZVZ=0;ZVZ<VZListe.AnzahlVZ;ZVZ++)
			{
				Summe=Summe+Wert[QVZ][ZVZ][VerkM];
			}
		}
		OutFile << "," << Summe;
	}
	OutFile << ",,";

	//Entfernungsmatrix laden
	CDatWiderstandsmatrizen (*EntfMat) = new CDatWiderstandsmatrizen;
	EntfMat->VZEinteil.KopiereVZListe(VZListe);
	EntfMat->Load(EntfMatPfad);

	for (VerkM=0;VerkM<6;VerkM++)
	{
		double Summe=0;
		for (short QVZ=0;QVZ<VZListe.AnzahlVZ;QVZ++)
		{
			for (short ZVZ=0;ZVZ<VZListe.AnzahlVZ;ZVZ++)
			{
				Summe=Summe+double(Wert[QVZ][ZVZ][VerkM]*EntfMat->Wert[QVZ][ZVZ]);
			}
		}
		OutFile << "," << Summe;
	}

	delete EntfMat;

	OutFile << endl;

	OutFile.close();
}


// *****************************************************************************************


//Importiert eine Matrix im XML-Format mit 1 VM; Parameter: Dateiname (inkl. Init)
void CCalcPVMatrix::Import_xml(CString InPfad)
{
	WertInit();

	ifstream InFile;
	InFile.open(InPfad, ios::nocreate);

	//Zunächst den Anfang des Matrizenbereichs suchen

	while (!InFile.eof())
	{
		char line[500];
		InFile.getline(line, 500);
		CString InLine1 = line;
		
		if (InLine1=="<fahrten_zwischen_vz>")
		{
			//Nun bis zum Ende des Bereichs durchlaufen
			CString InLine2="";
			while (InLine2!="</fahrten_zwischen_vz>")
			{
				//Nun kommt zunächst eine Quellzelle
				InFile.getline(line, 500);
				InLine2=line;
				if (InLine2=="<quellvz>")
				{
					//Als nächstes kommt die Nummer der QuellVZ
					InFile.getline(line, 500);
					CString InLineQVZ = line;
					//Nun die eigentliche Nummer herausziehen
					short LaengeQVZ=InLineQVZ.GetLength();
					InLineQVZ = InLineQVZ.Mid(4, LaengeQVZ-9);
					int Quelle = atoi(InLineQVZ);
					if ((Quelle<0)||(Quelle>417))
						AfxMessageBox("Quelle falsch!");

					CString InLine3="";
					while (InLine3!="</quellvz>")
					{
						InFile.getline(line, 500);
						InLine3 = line;
						if (InLine3=="<zielvz>")
						{
							//Jetzt kommt die Nummer der ZielVZ
							InFile.getline(line, 500);
							CString InLineZVZ = line;
							//Nun die eigentliche Nummer herausziehen
							short LaengeZVZ=InLineZVZ.GetLength();
							InLineZVZ = InLineZVZ.Mid(4, LaengeZVZ-9);
							int Ziel = atoi(InLineZVZ);
							if ((Ziel<0)||(Ziel>417))
							{
								AfxMessageBox("Ziel falsch!");
							}
							else
							{
								//Nun kommt die Spalte mit der Fahrtenanzahl
								InFile.getline(line, 500);
								CString InLineWert = line;
								//Nun die eigentliche Fahrtenzahl herausziehen
								short LaengeWert =InLineWert.GetLength();
								InLineWert = InLineWert.Mid(9, LaengeWert-19);
								int AktWert = atoi(InLineWert);

								//Nun in das Feld schreiben
								Wert[Quelle][Ziel][0]=double(AktWert);
							}
						}
					}
				}
			}
		}
	}


	InFile.close();
}


// *****************************************************************************************


void CCalcPVMatrix::Analyse_Gesamtreisezeiten(CDatWiderstandsmatrizen &RZMat1,
											  CDatWiderstandsmatrizen &RZMat2,
											  CDatWiderstandsmatrizen &RZMat3,
											  CDatWiderstandsmatrizen &RZMat4,
											  CDatWiderstandsmatrizen &RZMat5,
											  CDatWiderstandsmatrizen &RZMat6)
{
	if ((RZMat1.VZEinteil.AnzahlVZ==0)||
		(RZMat2.VZEinteil.AnzahlVZ==0)||
		(RZMat3.VZEinteil.AnzahlVZ==0)||
		(RZMat4.VZEinteil.AnzahlVZ==0)||
		(RZMat5.VZEinteil.AnzahlVZ==0)||
		(RZMat6.VZEinteil.AnzahlVZ==0)||
		(VZListe.AnzahlVZ==0))
	{
		AfxMessageBox("CCalcPVMatrix::Leistung_Berechnen\nVZEinteilungen od. RZ-Matrizen fehlen");
	}

	for (short Quelle=0;Quelle<VZListe.AnzahlVZ;Quelle++)
	{
		for (short Ziel=0;Ziel<VZListe.AnzahlVZ;Ziel++)
		{
			Wert[Quelle][Ziel][0]=Wert[Quelle][Ziel][0]*double(RZMat1.Wert[Quelle][Ziel]);
			Wert[Quelle][Ziel][1]=Wert[Quelle][Ziel][1]*double(RZMat2.Wert[Quelle][Ziel]);
			Wert[Quelle][Ziel][2]=Wert[Quelle][Ziel][2]*double(RZMat3.Wert[Quelle][Ziel]);
			Wert[Quelle][Ziel][3]=Wert[Quelle][Ziel][3]*double(RZMat4.Wert[Quelle][Ziel]);
			Wert[Quelle][Ziel][4]=Wert[Quelle][Ziel][4]*double(RZMat5.Wert[Quelle][Ziel]);
			Wert[Quelle][Ziel][5]=Wert[Quelle][Ziel][5]*double(RZMat6.Wert[Quelle][Ziel]);
		}
	}
}


// *****************************************************************************************


void Auswertungen_zusammen(CString PfadOut)
{
	CString PfadStamm = PfadOut + "Wege\\Ausw QZV Wege Zw";
	CString Anhang = "(Agg3)(1000).csv)";

	//Ausgabedatei erstellen
	ofstream OutFile;
	OutFile.open(PfadStamm+"-G"+Anhang,ios::out);

	//Laufe über alle Zwecke
	for (short Zweck=1;Zweck<=17;Zweck++)
	{
		CString sZahl="";
		char buff[10];
		_itoa(Zweck,buff,10);
		if (Zweck<10)
			sZahl = sZahl + "0" + buff;
		else
			sZahl = sZahl + buff;

		//Daten einlesen
		ifstream InFile;
		InFile.open(PfadStamm+sZahl+Anhang,ios::nocreate);
		char line1[1000];
		char line2[1000];
		InFile.getline(line1,1000);
		InFile.getline(line2,1000);

		if (Zweck==1)
		{
			OutFile << "Zweck," << line1 << endl;
		}
		OutFile << Zweck << "," << line2 << endl;

		InFile.close();
	}//Ende Schleife über alle Zwecke

	OutFile.close();
}


// *****************************************************************************************


void CCalcPVMatrix::AuswertungenZus(CString PfadOut)
{
	CString PfadStamm = PfadOut + "Wege\\RZAusw QZV Wege Zw";
	CString Anhang = "(Agg3)(1000).csv";

	//Ausgabedatei erstellen
	ofstream OutFile;
	OutFile.open(PfadStamm+"-G"+Anhang,ios::out);

	//Laufe über alle Zwecke
	for (short Zweck=1;Zweck<=17;Zweck++)
	{
		CString sZahl="";
		char buff[10];
		_itoa(Zweck,buff,10);
		if (Zweck<10)
			sZahl = sZahl + "0" + buff;
		else
			sZahl = sZahl + buff;

		//Daten einlesen
		ifstream InFile;
		InFile.open(PfadStamm+sZahl+Anhang,ios::nocreate);
		char line1[1000];
		char line2[1000];
		InFile.getline(line1,1000);
		InFile.getline(line2,1000);

		if (Zweck==1)
		{
			OutFile << "Zweck," << line1 << endl;
		}
		OutFile << Zweck << "," << line2 << endl;

		InFile.close();
	}//Ende Schleife über alle Zwecke

	OutFile.close();
}


// *****************************************************************************************


void CCalcPVMatrix::RundungsfehlerBeseitigenVer3(short& AktQ,
												 double& Zielwert,
												 CCalcPVTeilmatrix* RestMat)
{
	//Aktueller IstWert und Differenz zum Zielwert bestimmen
	//Zunächst die aktuelle Summe bestimmen
	double AktSumme=0;
	{
		for (short AktZ=0;AktZ<VZListe.AnzahlVZ;AktZ++)
		{
			for (short AktVM=0;AktVM<co_MaxVerkMPV;AktVM++)
			{
				AktSumme = AktSumme + Wert[AktQ][AktZ][AktVM];
			}
		}
	}

	//Bestehen Abweichungen zwischen aktueller Summe und dem Zielwert?
	int Diff = Runden(Zielwert) - Runden(AktSumme);
	if (Diff!=0)
	{
		sRundVektor (*RVek) = new sRundVektor[co_MaxVZ*co_MaxVerkMPV];
		for (short i1=0;i1<(co_MaxVZ*co_MaxVerkMPV);i1++)
		{
			RVek[i1].Wert=0;
			RVek[i1].ZielVZ=-1;
			RVek[i1].VerkM=-1;
		}

		//Daten aus RestMat übernehmen
		int Laeufer=0;
		for (short AktZ=0;AktZ<VZListe.AnzahlVZ;AktZ++)
		{
			for (short AktVM=0;AktVM<co_MaxVerkMPV;AktVM++)
			{
				RVek[Laeufer].Wert=RestMat->Wert[AktZ][AktVM];
				RVek[Laeufer].ZielVZ = AktZ;
				RVek[Laeufer].VerkM = AktVM;
				Laeufer++;
			}
		}

		//Bubble-Sort zum Sortieren
		bool Getauscht=false;
		do
		{
			Getauscht=false;

			for (int i2=0;i2<(co_MaxVZ*co_MaxVerkMPV)-1;i2++)
			{
				if (RVek[i2].Wert<RVek[i2+1].Wert)
				{
					Getauscht=true;
					sRundVektor (*Tauscher) = new sRundVektor;
					Tauscher->Wert = RVek[i2].Wert;
					Tauscher->ZielVZ = RVek[i2].ZielVZ;
					Tauscher->VerkM = RVek[i2].VerkM;
					RVek[i2].Wert = RVek[i2+1].Wert;
					RVek[i2].ZielVZ = RVek[i2+1].ZielVZ;
					RVek[i2].VerkM = RVek[i2+1].VerkM;
					RVek[i2+1].Wert = Tauscher->Wert;
					RVek[i2+1].ZielVZ = Tauscher->ZielVZ;
					RVek[i2+1].VerkM = Tauscher->VerkM;
					delete Tauscher;
				}
			}
		}
		while (Getauscht);

		
		delete [] RVek;
	}
}


// *****************************************************************************************


void CCalcPVMatrix::MultipliziereMitFaktor(double Faktor)
{
	for (short i1=0;i1<co_MaxVZ;i1++)
		for (short i2=0;i2<co_MaxVZ;i2++)
			for (short i3=0;i3<co_MaxVerkMPV;i3++)
			{
				Wert[i1][i2][i3]=Wert[i1][i2][i3]*Faktor;
			}
}


// *****************************************************************************************


void CCalcPVMatrix::WertInit_ohneBinnen()
{
	for (short i1=0;i1<co_MaxVZ;i1++)
	{
		for (short i2=0;i2<co_MaxVZ;i2++)
		{
			if (i1!=i2)
			{
				for (short i3=0;i3<co_MaxVerkMPV;i3++)
				{
					Wert[i1][i2][i3]=0;
				}
			}
		}
	}
}


// *****************************************************************************************


double CCalcPVMatrix::GibSummeVerkM(short AktVM)
{
	double Summe=0;
	for (short i1=0;i1<VZListe.AnzahlVZ;i1++)
	{
		for (short i2=0;i2<VZListe.AnzahlVZ;i2++)
		{
			Summe=Summe+Wert[i1][i2][AktVM];
		}
	}

	return Summe;
}


// *****************************************************************************************


void CCalcPVMatrix::Auswerten_ZweckQZVerkehr(CString Datei, short Zweck)
{
	//Zunächst Quell- und Zielverkehr bestimmen
	double (*QuellV);
	QuellV = new double[co_MaxVerkMPV];
	for (short i2=0;i2<co_MaxVerkMPV;i2++)
	{
		QuellV[i2]=0;
	}

	for (short i1=0;i1<VZListe.AnzahlVZ;i1++)
		for (short i2=0;i2<VZListe.AnzahlVZ;i2++)
			for (short i3=0;i3<co_MaxVerkMPV;i3++)
			{
				QuellV[i3] = QuellV[i3] + Wert[i1][i2][i3];
			}


	//Locale je nach Ausgabeformat setzen, so dass richtiges Dezimaltrennzeichen
	//verwendet wird
	CString Trenner = "";
	CString Kopfzeile = "";
	CString Dateiname = "";

	setlocale(LC_NUMERIC,"usa");
	Trenner = ",";
	Kopfzeile = "Zweck,Fuss,Rad,MIVF,MIVB,OEV,SOEV,Ges";
	Dateiname = Datei + ".csv";
	

	//Testen, ob Datei bereits vorhanden
	bool DateiExists=false;
	{
		CFileFind (*Sucher) = new CFileFind;

		if (Sucher->FindFile(Dateiname)!=0)
		{
			DateiExists=true;
		}
	}


	ofstream OutFile;
	OutFile.open(Dateiname,ios::app);

	if (!DateiExists)
	{
		OutFile << Kopfzeile << endl;
	}

	OutFile << Zweck << setiosflags(ios::fixed) << setprecision(0);
	double Summe=0;
	for (i2=0;i2<co_MaxVerkMPV;i2++)
	{
		Summe = Summe + QuellV[i2];
		OutFile << Trenner << QuellV[i2];
	}
	OutFile << Trenner << Summe << endl;

	OutFile.close();

	//Locale zurücksetzen, damit ansonsten Punkte als Trennzeichen verwendet werden
	setlocale(LC_NUMERIC,"usa");
	
	delete [] QuellV;
}


// *****************************************************************************************


void CCalcPVMatrix::Import_PTV(CString Dateiname)
{
	WertInit();

	VZListe.Init();

	ifstream InFile;
	InFile.open(Dateiname, ios::nocreate);

	setlocale(LC_NUMERIC,"usa");

	//Die ersten Zeile überlesen
	char line[500];
	InFile.getline(line, 500);

	//dann die Anzahl der Zellen einlesen
	InFile.getline(line, 500);
	VZListe.AnzahlVZ = atoi(line);

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

					VZListe.VZStDat[AktVZ].Nr = atoi(line);
					
					AktVZ++;
				}
				InFile.getline(line, 500);
			}
			//letzte Zeile mit 3 Einträgen einlesen
			for (short Spalte=0;Spalte<3;Spalte++)
			{
				InFile.get(line,11);

				VZListe.VZStDat[AktVZ].Nr = atoi(line);

				AktVZ++;
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
					intQuellVZ=VZListe.GibInterneVZID(extQuellVZ);
					if ((intQuellVZ<0)||(intQuellVZ>562))
					{
						AfxMessageBox("Falsche intQuellVZ");
					}
				}
				else
				{
					AfxMessageBox("Kein Sternchen");
				}

				int intZielVZ=0;

				//dann die einzelnen Matrixzeilen einlesen
				for (short Zeile=0;Zeile<70;Zeile++)
				{
					//8-mal jeweils 10 Zeichen einlesen
					for (short Spalte=0;Spalte<8;Spalte++)
					{
						InFile.get(line,11);
						CString STRline= line;

						Wert[intQuellVZ][intZielVZ][0] = atof(line);

						intZielVZ++;
					}
					InFile.getline(line, 500);
				}

				//letzte Zeile mit 3 Einträgen einlesen
				for (short Spalte=0;Spalte<3;Spalte++)
				{
					InFile.get(line,11);

					Wert[intQuellVZ][intZielVZ][0] = atof(line);

					intZielVZ++;
				}
			}
		}
	}

	setlocale(LC_NUMERIC,"deu");
}


// *****************************************************************************************


