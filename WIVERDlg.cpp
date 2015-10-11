// WIVERDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "math.h"


#include "WIVER.h"
#include "WIVERDlg.h"

#include "wiverMatrix.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWIVERDlg Dialogfeld

CWIVERDlg::CWIVERDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWIVERDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWIVERDlg)
		// HINWEIS: Der Klassenassistent fügt hier Member-Initialisierung ein
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf benötigt
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWIVERDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWIVERDlg)
		// HINWEIS: Der Klassenassistent fügt an dieser Stelle DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWIVERDlg, CDialog)
	//{{AFX_MSG_MAP(CWIVERDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWIVERDlg Nachrichten-Handler

BOOL CWIVERDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Symbol für dieses Dialogfeld festlegen. Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden
	
	// ZU ERLEDIGEN: Hier zusätzliche Initialisierung einfügen
	
	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

// Wollen Sie Ihrem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie 
//  den nachstehenden Code, um das Symbol zu zeichnen. Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch für Sie erledigt.

void CWIVERDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext für Zeichnen

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Symbol in Client-Rechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Die Systemaufrufe fragen den Cursorform ab, die angezeigt werden soll, während der Benutzer
//  das zum Symbol verkleinerte Fenster mit der Maus zieht.
HCURSOR CWIVERDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


// *****************************************************************************************


void CWIVERDlg::OnOK() 
{

const short Iterationen=5;
const short MaxVZ = 551;

for (short Szenario=1;Szenario<=1;Szenario++)
{
	char cSzen[10];
	itoa(Szenario,cSzen,10);

	CString InPfad="F:\\N 060705\\07 WIVER\\Szen";
	InPfad=InPfad+cSzen+"\\";
	CString InPfadZonen = InPfad + "VZ-Liste.txt";
	CString InPfadStrukDat = InPfad + "WIVERStrukDat-Szen" + cSzen + ".txt";
	CString OutPfad="F:\\N 060705\\07 WIVER\\Szen";
	OutPfad=OutPfad+cSzen+"\\Result\\";

	//Beschäftigtendaten einlesen
	CwiverMatrix BevDat;
	BevDat.SetSize(MaxVZ,6);
	BevDat.Init();
	BevDat.Zellen.Init();
	BevDat.LoadCellDef(InPfadZonen);
	BevDat.LoadStruktDat(InPfadStrukDat);


	CwiverMatrix ArbPl;
	ArbPl.SetSize(MaxVZ,6);
	ArbPl.Init();
	ArbPl.Zellen.Init();
	ArbPl.LoadCellDef(InPfadZonen);
	ArbPl.LoadStruktDat(InPfadStrukDat);


	CwiverMatrix ParaFahrten;
	ParaFahrten.SetSize(4,6);
	ParaFahrten.Init();
	ParaFahrten.LoadPara(InPfad+"Fahrkal.dat",1);


	CwiverMatrix ParaArbStaet;
	ParaArbStaet.SetSize(4,6);
	ParaArbStaet.Init();
	ParaArbStaet.LoadPara(InPfad+"Fahrkal.dat",2);

	//Tourhäufigkeiten einlesen
	CwiverMatrix ParaTourzahl;
	ParaTourzahl.SetSize(4,6);
	ParaTourzahl.Init();
	ParaTourzahl.LoadPara2(InPfad+"Tourziel.dat",1);

	ParaTourzahl.SavePrnOhneCell(OutPfad+"Tour.csv",12);

	//Zielhäufigkeiten einlesen
	CwiverMatrix ParaZielzahl;
	ParaZielzahl.SetSize(4,6);
	ParaZielzahl.Init();
	ParaZielzahl.LoadPara2(InPfad+"Tourziel.dat",2);

	ParaZielzahl.SavePrnOhneCell(OutPfad+"Ziel.csv",12);


	//Zielpotenziale einlesen
	CwiverMatrix ZielPot;
	ZielPot.SetSize(MaxVZ,6);
	ZielPot.Init();
	ZielPot.Zellen.Init();
	ZielPot.LoadCellDef(InPfadZonen);
	ZielPot.LoadStruktDat(InPfadStrukDat);

	ZielPot.SavePrn(OutPfad+"ZielPot-1.csv",1);

	//Zielpotenziale in den einzelnen Spalten normieren
	ZielPot.NormColumns(1);
	ZielPot.SavePrn(OutPfad+"ZielPot-2.csv",12);


	//Empfängerbranchen-Verteilung einlesen
	//1. Kalibrierungsgruppen für Zuordnung
	CwiverMatrix KaliGruppe;
	KaliGruppe.SetSize(4,6);
	KaliGruppe.Init();
	KaliGruppe.LoadPara(InPfad+"Verempbr.dat",1);

	KaliGruppe.SavePrnOhneCell(OutPfad+"KaliGr.csv",1);

	//2. Verteilung für Kaligruppen einlesen
	CwiverMatrix ZielBranchen;
	ZielBranchen.SetSize(24,6);
	ZielBranchen.Init();
	ZielBranchen.LoadPara3(InPfad+"Verempbr.dat",6);

	ZielBranchen.SavePrnOhneCell(OutPfad+"EmpfBranchen-1.csv",3);

	ZielBranchen.NormRows(1);
	ZielBranchen.SavePrnOhneCell(OutPfad+"EmpfBranchen-2.csv",12);


	//Entfernungsempfindlichkeiten einlesen
	CwiverMatrix DistQuotient;
	DistQuotient.SetSize(4,6);
	DistQuotient.Init();
	DistQuotient.LoadPara2(InPfad+"Distkal.dat",1);

	DistQuotient.SavePrnOhneCell(OutPfad+"Distkal-1.csv",12);
		

	CwiverMatrix DistExponent;
	DistExponent.SetSize(4,6);
	DistExponent.Init();
	DistExponent.LoadPara2(InPfad+"Distkal.dat",2);

	DistExponent.SavePrnOhneCell(OutPfad+"Distkal-2.csv",12);


	//Einlesen Reisezeitmatrix

	//Altes fma-Format	
/*	CwiverMatrix RZMatrix;
	RZMatrix.SetSize(MaxVZ,MaxVZ);
	RZMatrix.Init();
	RZMatrix.Zellen.Init();
	RZMatrix.LoadCellDef(InPfadZonen);

	RZMatrix.LoadRZMatrix(InPfad+"min.out");
*/

	//fzt-Format für neugenerierte Matrix
	CwiverMatrix RZMatrix;
	RZMatrix.SetSize(MaxVZ,MaxVZ);
	RZMatrix.Init();
	RZMatrix.Zellen.Init();
	RZMatrix.LoadCellDef(InPfadZonen);

	RZMatrix.LoadMatrix_prn(InPfad+"RZ.txt");



	//Einlesen Savings-Parameter
	CwiverMatrix ParaSav;
	ParaSav.SetSize(24,10);
	ParaSav.Init();
	ParaSav.LoadPara3(InPfad+"Savkali.dat",10);

	ParaSav.SavePrnOhneCell(OutPfad+"Savkali.csv",10);


	CwiverMatrix Ergebnis;
	Ergebnis.SetSize(4,6);
	Ergebnis.Init();

	//Matrizen für zusammengefasstes Ergebnis
	CwiverMatrix GesMatrixPkw;
	GesMatrixPkw.SetSize(MaxVZ,MaxVZ);
	GesMatrixPkw.Init();
	GesMatrixPkw.Zellen.Init();
	GesMatrixPkw.LoadCellDef(InPfadZonen);


	CwiverMatrix GesMatrixLkw;
	GesMatrixLkw.SetSize(MaxVZ,MaxVZ);
	GesMatrixLkw.Init();
	GesMatrixLkw.Zellen.Init();
	GesMatrixLkw.LoadCellDef(InPfadZonen);

	//und noch das zusammengefasste Ergebnis
	CwiverMatrix GesMatrizenSummen;
	GesMatrizenSummen.SetSize(2,1);
	GesMatrizenSummen.Init();
	


	//Schleife über alle Branchen und Fahrzeuggruppen
	for (short Branche=1;Branche<=6;Branche++)
//	for (short Branche=6;Branche<=6;Branche++)
	{
		for (short FzgTyp=1;FzgTyp<=4;FzgTyp++)
//		for (short FzgTyp=1;FzgTyp<=1;FzgTyp++)
		{
			//AktKali-Gruppe
			short AktKaliGr = int(KaliGruppe(FzgTyp,Branche));

			//QUELLVERKEHRSAUFKOMMEN

			//Fahrtaktive Beschäftigte ermitteln
			CwiverMatrix FahrtAktiv;
			FahrtAktiv.SetSize(MaxVZ,1);
			FahrtAktiv.Init();
			FahrtAktiv.Zellen.Init();
			FahrtAktiv.LoadCellDef(InPfadZonen);

			double FahrtAktivAnteil = ParaFahrten(FzgTyp,Branche);
			double ArbStaetAnteil = ParaArbStaet(FzgTyp,Branche);
			double GesamtFahrtAktiv = 0;
			double GesamtArbStaet = 0;

			for (short AktVZ=1;AktVZ<=MaxVZ;AktVZ++)
			{
				FahrtAktiv(AktVZ,1) = BevDat(AktVZ,Branche) * FahrtAktivAnteil;
				GesamtFahrtAktiv = GesamtFahrtAktiv + FahrtAktiv(AktVZ,1);
				GesamtArbStaet = GesamtArbStaet + ArbPl(AktVZ,Branche);
			}

			FahrtAktiv.SavePrn(OutPfad+"FahrtAktiv-1.csv",12);

			double AufteilGesFahrtAktiv = GesamtFahrtAktiv * ArbStaetAnteil;

			double NeuGesFahrtAktiv = 0;

			//weitere Abhängigkeitsparameter einbeziehen
			for (AktVZ=1;AktVZ<=MaxVZ;AktVZ++)
			{
				FahrtAktiv(AktVZ,1) = FahrtAktiv(AktVZ,1) * (1-ArbStaetAnteil);
				FahrtAktiv(AktVZ,1) = FahrtAktiv(AktVZ,1) + 
					(AufteilGesFahrtAktiv * ArbPl(AktVZ,Branche) / GesamtArbStaet);
				NeuGesFahrtAktiv = NeuGesFahrtAktiv + FahrtAktiv(AktVZ,1);
			}

			FahrtAktiv.SavePrn(OutPfad+"FahrtAktiv-2.csv",12);

			//Sicherheitsabfrage
/*			if (GesamtFahrtAktiv != NeuGesFahrtAktiv)
			{
				AfxMessageBox("Fehler1");
			}
*/
			//Tour- und Zielhäufigkeiten berechnen
			CwiverMatrix Touren;
			Touren.SetSize(MaxVZ,1);
			Touren.Init();
			Touren.Zellen.Init();
			Touren.LoadCellDef(InPfadZonen);

/*			CwiverMatrix Zielfahrten;
			Zielfahrten.SetSize(MaxVZ,1);
			Zielfahrten.Init();
			Zielfahrten.Zellen.Init();
			Zielfahrten.LoadCellDef(InPfadZonen);
*/
			CwiverMatrix Quellaufkommen;
			Quellaufkommen.SetSize(MaxVZ,1);
			Quellaufkommen.Init();
			Quellaufkommen.Zellen.Init();
			Quellaufkommen.LoadCellDef(InPfadZonen);

			double AktTourzahl = ParaTourzahl(FzgTyp,Branche);
			double AktZielzahl = ParaZielzahl(FzgTyp,Branche);

			double GesTouren = 0;
			double GesZiele = 0;
			double GesAufkommen = 0;

			for (AktVZ=1;AktVZ<=MaxVZ;AktVZ++)
			{
				Touren(AktVZ,1) = FahrtAktiv(AktVZ,1) * AktTourzahl;
				GesTouren = GesTouren + Touren(AktVZ,1);
//				Zielfahrten(AktVZ,1) = FahrtAktiv(AktVZ,1) * AktZielzahl;
//				GesZiele = GesZiele + Zielfahrten(AktVZ,1);
				Quellaufkommen(AktVZ,1) = FahrtAktiv(AktVZ,1) * AktTourzahl * AktZielzahl;
				GesAufkommen = GesAufkommen + Quellaufkommen(AktVZ,1);
			}

			//Quellaufkommen nach VZ speichern
			Touren.SavePrn(OutPfad+"Quell-Tourzahl.csv",12);
//			Zielfahrten.SavePrn(OutPfad+"Quell-Zielfahrten.csv",12);
			Quellaufkommen.SavePrn(OutPfad+"Quell-Aufkommen.csv",12);


			//ZIELVERKEHRSAUFKOMMEN
			CwiverMatrix AktZiele;
			AktZiele.SetSize(MaxVZ,6);
			AktZiele.Init();
			AktZiele.Zellen.Init();
			AktZiele.LoadCellDef(InPfadZonen);


			//Nun über alle Empfängerbranchen laufen
			for (short ZielBranche=1;ZielBranche<=6;ZielBranche++)
			{
				//Berechnen des Anteils der Empfängerbranche anhand der Parameter
				double GesAufkommenBranche = GesAufkommen * ZielBranchen(AktKaliGr,ZielBranche);

				//Verteilung auf die Zielzellen anhand der räumlichen Verteilung der
				//Empfängerbranche
				for (int ZielVZ=1;ZielVZ<=MaxVZ;ZielVZ++)
				{
					AktZiele(ZielVZ,ZielBranche) = GesAufkommenBranche * ZielPot(ZielVZ,ZielBranche);
				}
			}

			AktZiele.SavePrn(OutPfad+"Ziel-AufkommenBr.csv",12);

			//Alle branchenspezifischen Zielaufkommen addieren
			CwiverMatrix Zielaufkommen;
			Zielaufkommen.SetSize(MaxVZ,1);
			Zielaufkommen.Init();
			Zielaufkommen.Zellen.Init();
			Zielaufkommen.LoadCellDef(InPfadZonen);

			for (ZielBranche=1;ZielBranche<=6;ZielBranche++)
			{
				for (int ZielVZ=1;ZielVZ<=MaxVZ;ZielVZ++)
				{
					Zielaufkommen(ZielVZ,1)=Zielaufkommen(ZielVZ,1)+AktZiele(ZielVZ,ZielBranche);
				}
			}

			Zielaufkommen.SavePrn(OutPfad+"Ziel-Aufkommen.csv",12);


			//VERBINDUNG QUELLE-ZIEL

			//Matrix implementieren
			CwiverMatrix AktMatrix;
			AktMatrix.SetSize(MaxVZ,MaxVZ);
			AktMatrix.Init();
			AktMatrix.Zellen.Init();
			AktMatrix.LoadCellDef(InPfadZonen);

			//Faktor-ZielVek implementieren
			CwiverMatrix FakZiel;
			FakZiel.SetSize(MaxVZ,1);
			FakZiel.Init();
			FakZiel.Zellen.Init();
			FakZiel.LoadCellDef(InPfadZonen);
			{
				for (short ZielVZ=1;ZielVZ<=MaxVZ;ZielVZ++)
				{
					FakZiel(ZielVZ,1)=1;
				}
			}

			short Lauf=1;
			do
			{
				//1. über alle Quellzellen laufen und direkte Zuordnung zu Zielzellen
				{
					for (short QuellVZ=1;QuellVZ<=MaxVZ;QuellVZ++)
					{
						//Zielvektor implementieren
						CwiverMatrix ZielVek;
						ZielVek.SetSize(MaxVZ,1);
						ZielVek.Init();
						ZielVek.Zellen.Init();
						ZielVek.LoadCellDef(InPfadZonen);

						for (short ZielVZ=1;ZielVZ<=MaxVZ;ZielVZ++)
						{
							ZielVek(ZielVZ,1) = pow(DistQuotient(FzgTyp,Branche),RZMatrix(QuellVZ,ZielVZ))*Zielaufkommen(ZielVZ,1)*FakZiel(ZielVZ,1);
						}

						//Zielvektor normieren
						ZielVek.NormAll(1);

						for (ZielVZ=1;ZielVZ<=MaxVZ;ZielVZ++)
						{
							AktMatrix(QuellVZ,ZielVZ)=Quellaufkommen(QuellVZ,1)*ZielVek(ZielVZ,1);
						}
					}
				}

				//2. Randsummenabgleich
				CwiverMatrix IstZielaufkommen;
				IstZielaufkommen.SetSize(MaxVZ,1);
				IstZielaufkommen.Init();
				IstZielaufkommen.Zellen.Init();
				IstZielaufkommen.LoadCellDef(InPfadZonen);

				{
					//Ist-Zielverkehr betsimmen
					for (short QuellVZ=1;QuellVZ<=MaxVZ;QuellVZ++)
					{
						for (short ZielVZ=1;ZielVZ<=MaxVZ;ZielVZ++)
						{
							IstZielaufkommen(ZielVZ,1)=IstZielaufkommen(ZielVZ,1)+AktMatrix(QuellVZ,ZielVZ);
						}
					}

					//und Korrekturfaktoren anpassen
					for (short ZielVZ=1;ZielVZ<=MaxVZ;ZielVZ++)
					{
						if (IstZielaufkommen(ZielVZ,1)!=0)
						{	
							double Akt1=Zielaufkommen(ZielVZ,1);
							double Akt2=IstZielaufkommen(ZielVZ,1);
							double FakNeu=FakZiel(ZielVZ,1)*Zielaufkommen(ZielVZ,1)/IstZielaufkommen(ZielVZ,1);
							FakZiel(ZielVZ,1)=FakZiel(ZielVZ,1)*Zielaufkommen(ZielVZ,1)/IstZielaufkommen(ZielVZ,1);
						}
						else
						{
							FakZiel(ZielVZ,1)=1;
						}
					}

				}

				CString OutDat=OutPfad+"Ziel-AufkommenIst";
				char hline[10];
				itoa(Lauf,hline,10);
				OutDat = OutDat + hline +".csv";
				IstZielaufkommen.SavePrn(OutDat,12);

				Lauf++;
			} while (Lauf<Iterationen+1);

			//Quellaufkommen zur Sicherheit ausgeben
			{
				CwiverMatrix IstQuellaufkommen;
				IstQuellaufkommen.SetSize(MaxVZ,1);
				IstQuellaufkommen.Init();
				IstQuellaufkommen.Zellen.Init();
				IstQuellaufkommen.LoadCellDef(InPfadZonen);

				for (short QuellVZ=1;QuellVZ<=MaxVZ;QuellVZ++)
				{
					for (short ZielVZ=1;ZielVZ<=MaxVZ;ZielVZ++)
					{
						IstQuellaufkommen(QuellVZ,1)=IstQuellaufkommen(QuellVZ,1)+AktMatrix(QuellVZ,ZielVZ);
					}
				}

				IstQuellaufkommen.SavePrn(OutPfad+"Quell-AufkommenIst.csv",12);
			}


			//Tourenbildung
			//Ergebnis sind drei Matrizen
			//Hinweg, Zwischenweg und Rückweg
			
			//Matrizen implementieren
			CwiverMatrix HinMatrix;
			HinMatrix.SetSize(MaxVZ,MaxVZ);
			HinMatrix.Init();
			HinMatrix.Zellen.Init();
			HinMatrix.LoadCellDef(InPfadZonen);

			CwiverMatrix ZwiMatrix;
			ZwiMatrix.SetSize(MaxVZ,MaxVZ);
			ZwiMatrix.Init();
			ZwiMatrix.Zellen.Init();
			ZwiMatrix.LoadCellDef(InPfadZonen);

			CwiverMatrix RueckMatrix;
			RueckMatrix.SetSize(MaxVZ,MaxVZ);
			RueckMatrix.Init();
			RueckMatrix.Zellen.Init();
			RueckMatrix.LoadCellDef(InPfadZonen);

			double AllSavings1=0;
			double AllSavings2=0;
			double AllSavings3=0;
			double AllSavings4=0;
			double AllSavings5=0;

			{
				//Anzahl der Savings berechnen
				//Anzahl der angefahrenen Ziel minus Anzahl der Touren
				//über alle Heimatzellen/Quellzellen laufen
				for (short QuellVZ=1;QuellVZ<=MaxVZ;QuellVZ++)
				{
					double AktGesSaving = Quellaufkommen(QuellVZ,1)-Touren(QuellVZ,1);
					AllSavings1=AllSavings1+AktGesSaving;

					if (AktGesSaving>0)
					{
						CwiverMatrix  AktSaving;
						AktSaving.SetSize(MaxVZ,MaxVZ);
						AktSaving.Init();
						AktSaving.Zellen.Init();
						AktSaving.LoadCellDef(InPfadZonen);

						CwiverMatrix  SavProb;
						SavProb.SetSize(MaxVZ,MaxVZ);
						SavProb.Init();
						SavProb.Zellen.Init();
						SavProb.LoadCellDef(InPfadZonen);

						//Savingsfunktionen für alle Ziel-Ziel-Kombinationen berechnen
						//und Zuordnung zu Klassen

						//Anzahl aller moeglichen Verbindungskombinationen
						double MaxProb = (Quellaufkommen(QuellVZ,1)*(Quellaufkommen(QuellVZ,1)-1));
//						double GesProb=0;

						for (short Ziel1=1;Ziel1<=MaxVZ;Ziel1++)
						{
							for (short Ziel2=1;Ziel2<=MaxVZ;Ziel2++)
							{
								//Savingsfunktion für Verbindung bestimmen
								double SavFkt = (RZMatrix(QuellVZ,Ziel1)+RZMatrix(QuellVZ,Ziel2)-RZMatrix(Ziel1,Ziel2))/(RZMatrix(QuellVZ,Ziel1)+RZMatrix(QuellVZ,Ziel2));
								SavFkt=SavFkt*10;
								
								//Theoretische Wahrscheinlichkeit des Savings berechnen
								double Prob=0;
								if ((AktMatrix(QuellVZ,Ziel1)>0)&&(AktMatrix(QuellVZ,Ziel2)>0))
								{
									if (Ziel1!=Ziel2)
									{
										Prob = AktMatrix(QuellVZ,Ziel1)*AktMatrix(QuellVZ,Ziel2);
									}
									else
									{
										Prob = AktMatrix(QuellVZ,Ziel1)*(AktMatrix(QuellVZ,Ziel2)-1);
										if (Prob<0)
										{
											Prob=0;
										}
									}
								}
								else
								{
									Prob = 0;
								}
			
								SavProb(Ziel1,Ziel2)=Prob/MaxProb;
//								GesProb=GesProb+Prob;

								//Anhand der Distanz den Wahrscheinlichkeitsfaktor 
								//für das Saving ermitteln
								if ((SavFkt<=1)||(SavFkt>=9))
								{
									//Für die Randgruppen die Werte direkt aus der Tabelle übernehmen
									if (SavFkt<=0.1)
									{
										SavProb(Ziel1,Ziel2)=SavProb(Ziel1,Ziel2)*ParaSav(AktKaliGr,1);
									}
									else
									{
										SavProb(Ziel1,Ziel2)=SavProb(Ziel1,Ziel2)*ParaSav(AktKaliGr,9);
									}
								}
								else
								{
									//Alles dazwischen interpolieren
									double Faktor=0;
									for (short i1=1;i1<9;i1++)
									{
										if ((SavFkt>=i1)&&(SavFkt<=(i1+1)))
										{
											Faktor = (SavFkt-i1) * (ParaSav(AktKaliGr,(i1+1))-ParaSav(AktKaliGr,i1))+ParaSav(AktKaliGr,i1);
										}
									}
									SavProb(Ziel1,Ziel2)=SavProb(Ziel1,Ziel2)*Faktor;
								}
							}//Alle Ziel2
						}//Alle Ziel1
//						GesProb=GesProb;


						//Wahrscheinlichkeiten anhand der Zahl der zu erzeugenden
						//Savings normieren
						SavProb.NormAll(AktGesSaving);

						{
							for (short i1=1;i1<=MaxVZ;i1++)
							{
								for (short i2=1;i2<=MaxVZ;i2++)
								{
									AllSavings2=AllSavings2+SavProb(i1,i2);
								}
							}
						}

						//Über alle Kombinationen laufen
						//und die Einzelwege erzeugen
						for (Ziel1=1;Ziel1<=MaxVZ;Ziel1++)
						{
							//Zunächst Quellaufkommen komplett in Hin- und Rückwege schreiben
							HinMatrix(QuellVZ,Ziel1) = HinMatrix(QuellVZ,Ziel1) + AktMatrix(QuellVZ,Ziel1);
							AllSavings3=AllSavings3+AktMatrix(QuellVZ,Ziel1);
							RueckMatrix(Ziel1,QuellVZ) = RueckMatrix(Ziel1,QuellVZ) + AktMatrix(QuellVZ,Ziel1);
							AllSavings3=AllSavings3+AktMatrix(QuellVZ,Ziel1);

							for (short Ziel2=1;Ziel2<=MaxVZ;Ziel2++)
							{
								//Nun die Savings-Wahrscheinlichkeiten
								//von den entsprechenden Hin- und Rückwegen abziehen
								//und die Zwischenwege definieren
								if (SavProb(Ziel1,Ziel2)>0)
								{
									ZwiMatrix(Ziel1,Ziel2) = ZwiMatrix(Ziel1,Ziel2) + SavProb(Ziel1,Ziel2);
									AllSavings4=AllSavings4+SavProb(Ziel1,Ziel2);
									RueckMatrix(Ziel1,QuellVZ) = RueckMatrix(Ziel1,QuellVZ) - SavProb(Ziel1,Ziel2);
									AllSavings5=AllSavings5+SavProb(Ziel1,Ziel2);
									HinMatrix(QuellVZ,Ziel2) = HinMatrix(QuellVZ,Ziel2) - SavProb(Ziel1,Ziel2);
									AllSavings5=AllSavings5+SavProb(Ziel1,Ziel2);
								}
							}//Alle Ziel2
						}//Alle Ziel1
					}//Abfrage, ob überhaupt Savings
				}//Alle Quellen
			}//Ende Tourenbildung

			{
				CwiverMatrix Testausgabe;
				Testausgabe.SetSize(5,1);
				Testausgabe.Init();
				Testausgabe(1,1)=AllSavings1;
				Testausgabe(2,1)=AllSavings2;
				Testausgabe(3,1)=AllSavings3;
				Testausgabe(4,1)=AllSavings4;
				Testausgabe(5,1)=AllSavings5;
				Testausgabe.SavePrnOhneCell(OutPfad+"SavQuell-Test.csv",12);
			}



			//Zur Kontrolle: Quellverkehr und Zielverkehrsvektoren berechnen
			{
				CwiverMatrix IstQuellaufkommen2;
				IstQuellaufkommen2.SetSize(MaxVZ,1);
				IstQuellaufkommen2.Init();
				IstQuellaufkommen2.Zellen.Init();
				IstQuellaufkommen2.LoadCellDef(InPfadZonen);

				CwiverMatrix IstZielaufkommen2;
				IstZielaufkommen2.SetSize(MaxVZ,1);
				IstZielaufkommen2.Init();
				IstZielaufkommen2.Zellen.Init();
				IstZielaufkommen2.LoadCellDef(InPfadZonen);

				for (short QuellVZ=1;QuellVZ<=MaxVZ;QuellVZ++)
				{
					for (short ZielVZ=1;ZielVZ<=MaxVZ;ZielVZ++)
					{
						IstQuellaufkommen2(QuellVZ,1)=IstQuellaufkommen2(QuellVZ,1)+HinMatrix(QuellVZ,ZielVZ);
						IstQuellaufkommen2(QuellVZ,1)=IstQuellaufkommen2(QuellVZ,1)+ZwiMatrix(QuellVZ,ZielVZ);
						IstQuellaufkommen2(QuellVZ,1)=IstQuellaufkommen2(QuellVZ,1)+RueckMatrix(ZielVZ,QuellVZ);
						IstZielaufkommen2(ZielVZ,1)=IstZielaufkommen2(ZielVZ,1)+HinMatrix(QuellVZ,ZielVZ);
						IstZielaufkommen2(ZielVZ,1)=IstZielaufkommen2(ZielVZ,1)+ZwiMatrix(QuellVZ,ZielVZ);
//						IstZielaufkommen2(QuellVZ,1)=IstZielaufkommen2(QuellVZ,1)+RueckMatrix(QuellVZ,ZielVZ);
					}
				}

				IstQuellaufkommen2.SavePrn(OutPfad+"SavQuell-AufkommenIst.csv",12);
				IstZielaufkommen2.SavePrn(OutPfad+"SavZiel-AufkommenIst.csv",12);

				//Matrizen addieren und ausgeben
				{
					CwiverMatrix GesMatrix;
					GesMatrix.SetSize(MaxVZ,MaxVZ);
					GesMatrix.Init();
					GesMatrix.Zellen.Init();
					GesMatrix.LoadCellDef(InPfadZonen);

					CwiverMatrix GesVektor;
					GesVektor.SetSize(MaxVZ,1);
					GesVektor.Init();
					GesVektor.Zellen.Init();
					GesVektor.LoadCellDef(InPfadZonen);

					for (short QuellVZ=1;QuellVZ<=MaxVZ;QuellVZ++)
					{
						for (short ZielVZ=1;ZielVZ<=MaxVZ;ZielVZ++)
						{
							GesMatrix(QuellVZ,ZielVZ)=HinMatrix(QuellVZ,ZielVZ)
								+ZwiMatrix(QuellVZ,ZielVZ)+RueckMatrix(QuellVZ,ZielVZ);
							GesVektor(QuellVZ,1)=GesVektor(QuellVZ,1)+GesMatrix(QuellVZ,ZielVZ);
							
							if (FzgTyp<=2)
							{
								GesMatrixPkw(QuellVZ,ZielVZ)=GesMatrixPkw(QuellVZ,ZielVZ)+GesMatrix(QuellVZ,ZielVZ);
							}
							else
							{
								GesMatrixLkw(QuellVZ,ZielVZ)=GesMatrixLkw(QuellVZ,ZielVZ)+GesMatrix(QuellVZ,ZielVZ);
							}
						}
					}

					CString Ausgabe=OutPfad+"";
					char cFzgTyp[10];
					char cBranche[10];
					itoa(FzgTyp,cFzgTyp,10);
					itoa(Branche,cBranche,10);

					CString vAusgabe=Ausgabe+"GesVek"+cFzgTyp+"-"+cBranche+".csv";
					GesVektor.SavePrn(vAusgabe,10);

					Ausgabe=Ausgabe+"Mat"+cFzgTyp+"-"+cBranche+".fzt";
					GesMatrix.Export_Visum_fzt(Ausgabe);

					Ergebnis(FzgTyp,Branche) = GesMatrix.GetSumTotal();
				}
			}
		}//Schleife FzgTyp
	}//Schleife Branche

	GesMatrizenSummen(1,1)=GesMatrixPkw.GetSumTotal();
	GesMatrizenSummen(2,1)=GesMatrixLkw.GetSumTotal();

/*
	//Matrizen nach Fahrzeugtypen addieren
	CwiverMatrix GesMatrizenSummen;
	GesMatrizenSummen.SetSize(2,1);
	GesMatrizenSummen.Init();

	//Zunächst die Pkw
	{
		double AktSum=0;

		CwiverMatrix GesMatrixPkw;
		GesMatrixPkw.SetSize(MaxVZ,MaxVZ);
		GesMatrixPkw.Init();
		GesMatrixPkw.Zellen.Init();
		GesMatrixPkw.LoadCellDef(InPfadZonen);
		for (short Branche=1;Branche<=6;Branche++)
		{
			for (short FzgTyp=1;FzgTyp<=2;FzgTyp++)
			{
				CwiverMatrix TeilMatrix;
				TeilMatrix.SetSize(MaxVZ,MaxVZ);
				TeilMatrix.Init();
				TeilMatrix.Zellen.Init();
				TeilMatrix.LoadCellDef(InPfadZonen);

				CString Eingabe=OutPfad+"";
				char cFzgTyp[10];
				char cBranche[10];
				itoa(FzgTyp,cFzgTyp,10);
				itoa(Branche,cBranche,10);

				Eingabe=Eingabe+"Mat"+cFzgTyp+"-"+cBranche+".fzt";

				TeilMatrix.Import_Visum_fzt(Eingabe);

				for (short VZ1=1;VZ1<=MaxVZ;VZ1++)
				{
					for (short VZ2=1;VZ2<=MaxVZ;VZ2++)
					{
						GesMatrixPkw(VZ1,VZ2)=GesMatrixPkw(VZ1,VZ2)+TeilMatrix(VZ1,VZ2);
						AktSum=AktSum+TeilMatrix(VZ1,VZ2);
					}
				}
			}
		}

		//Ausgabe
		CString Ausgabe=OutPfad + "WIVERPkw-Szen" + cSzen + ".fzt";
		GesMatrixPkw.Export_Visum_fzt(Ausgabe);
		GesMatrizenSummen(1,1)=AktSum;
	}

	//dann die Lkw
	{
		double AktSum=0;

		CwiverMatrix GesMatrixLkw;
		GesMatrixLkw.SetSize(MaxVZ,MaxVZ);
		GesMatrixLkw.Init();
		GesMatrixLkw.Zellen.Init();
		GesMatrixLkw.LoadCellDef(InPfadZonen);

		for (short Branche=1;Branche<=6;Branche++)
		{
			for (short FzgTyp=3;FzgTyp<=4;FzgTyp++)
			{
				CwiverMatrix TeilMatrix;
				TeilMatrix.SetSize(MaxVZ,MaxVZ);
				TeilMatrix.Init();
				TeilMatrix.Zellen.Init();
				TeilMatrix.LoadCellDef(InPfadZonen);

				CString Eingabe=OutPfad+"";
				char cFzgTyp[10];
				char cBranche[10];
				itoa(FzgTyp,cFzgTyp,10);
				itoa(Branche,cBranche,10);

				Eingabe=Eingabe+"Mat"+cFzgTyp+"-"+cBranche+".fzt";

				TeilMatrix.Import_Visum_fzt(Eingabe);

				for (short VZ1=1;VZ1<=MaxVZ;VZ1++)
				{
					for (short VZ2=1;VZ2<=MaxVZ;VZ2++)
					{
						GesMatrixLkw(VZ1,VZ2)=GesMatrixLkw(VZ1,VZ2)+TeilMatrix(VZ1,VZ2);
						AktSum=AktSum+TeilMatrix(VZ1,VZ2);
					}
				}
			}
		}

		CString Ausgabe=OutPfad + "WIVERLkw-Szen" + cSzen + ".fzt";
		GesMatrixLkw.Export_Visum_fzt(Ausgabe);
		GesMatrizenSummen(2,1)=AktSum;
	}
*/
	{
		CString Ausgabe=OutPfad + "WIVERPkw-Szen" + cSzen + ".fzt";
		GesMatrixPkw.Export_Visum_fzt(Ausgabe);

		Ausgabe=OutPfad + "WIVERLkw-Szen" + cSzen + ".fzt";
		GesMatrixLkw.Export_Visum_fzt(Ausgabe);
	}

	Ergebnis.SavePrn(OutPfad+"Gesamtergebnis-1.csv",12);

	GesMatrizenSummen.SavePrn(OutPfad+"Gesamtergebnis-2.csv",12);


}//Ende Szenario

	AfxMessageBox("Fertig");

	
	CDialog::OnOK();
}


// *****************************************************************************************


void CWIVERDlg::OnButton1() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	//Einlesen Reisezeitmatrix
	CString InPfad="F:\\Projekte\\JR2006-01 Szenarien Kiel\\AP1 Szenarienberechnung\\98 WIVER-Ergebnisse\\Aufbereitung\\";
	CString InPfadZonen = InPfad + "VZ-Liste.txt";

	CwiverMatrix (*PkwMatrix) = new CwiverMatrix;
	PkwMatrix->SetSize(551,551);
	PkwMatrix->Init();
	PkwMatrix->Zellen.Init();
	PkwMatrix->LoadCellDef(InPfadZonen);

	CwiverMatrix (*LkwMatrix) = new CwiverMatrix;
	LkwMatrix->SetSize(551,551);
	LkwMatrix->Init();
	LkwMatrix->Zellen.Init();
	LkwMatrix->LoadCellDef(InPfadZonen);

	CwiverMatrix (*DistMat) = new CwiverMatrix;
	DistMat->SetSize(551,551);
	DistMat->Init();
	DistMat->Zellen.Init();
	DistMat->LoadCellDef(InPfadZonen);

	DistMat->Import_Visum_fzt2(InPfad+"Kiel_distanz.txt");



	for (short Szenario=0;Szenario<6;Szenario++)
	{
		CString HelpPfad;
		char cHelpPfad[10];

		itoa(Szenario,cHelpPfad,10);
		HelpPfad=cHelpPfad;
		PkwMatrix->Import_Visum_fzt(InPfad+"WIVERPkw-Szen"+HelpPfad+".fzt");
		LkwMatrix->Import_Visum_fzt(InPfad+"WIVERLkw-Szen"+HelpPfad+".fzt");

		CwiverMatrix GesMatrix;
		GesMatrix.SetSize(551,551);
		GesMatrix.Init();
		GesMatrix.Zellen.Init();
		GesMatrix.LoadCellDef(InPfadZonen);

		GesMatrix.Add(PkwMatrix);
		GesMatrix.Add(LkwMatrix);

		GesMatrix.Export_Visum_fzt(InPfad+"WIVERGes-Szen"+HelpPfad+".fzt");

		GesMatrix.StadtUmlandAuswerten(InPfad+"WIVERGes-Szen"+HelpPfad+"-1.csv");

		GesMatrix.LeistungAuswerten(DistMat, InPfad+"WIVERGes-Szen"+HelpPfad+"-2.csv");
	}

	delete PkwMatrix;
	delete LkwMatrix;

	AfxMessageBox("Fertig");
}


// *****************************************************************************************


void CWIVERDlg::OnButton2() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	for (short Szenario=6;Szenario<=7;Szenario++)
	{
		char cSzen[10];
		itoa(Szenario,cSzen,10);

		CString InPfad="F:\\N 060705\\07 WIVER\\Szen";
		InPfad=InPfad+cSzen+"\\";
		CString InPfadZonen = InPfad + "VZ-Liste.txt";
		CString OutPfad="F:\\N 060705\\07 WIVER\\Szen";
		OutPfad=OutPfad+cSzen+"\\Result\\";
//		OutPfad=OutPfad+cSzen+"\\";

		//Distanz-Matrix einlesen
		CwiverMatrix (*DistMat) = new CwiverMatrix;
		DistMat->SetSize(551,551);
		DistMat->Init();
		DistMat->Zellen.Init();
		DistMat->LoadCellDef(InPfadZonen);

		DistMat->Import_Visum_fzt2(InPfad+"Kiel_distanz.txt");

		CwiverMatrix Ergebnis;
		Ergebnis.SetSize(4,6);
		Ergebnis.Init();

		

		//Schleife über alle Branchen und Fahrzeuggruppen
		for (short Branche=1;Branche<=6;Branche++)
		{
			for (short FzgTyp=1;FzgTyp<=4;FzgTyp++)
			{
				CString Ausgabe=OutPfad+"";
				char cFzgTyp[10];
				char cBranche[10];
				itoa(FzgTyp,cFzgTyp,10);
				itoa(Branche,cBranche,10);

				CString vAusgabe=Ausgabe+"GesVek"+cFzgTyp+"-"+cBranche+"-2.csv";

				Ausgabe=Ausgabe+"Mat"+cFzgTyp+"-"+cBranche+".fzt";


				//Fahrtenmatrix einlesen
				CwiverMatrix (*AktMat) = new CwiverMatrix;
				AktMat->SetSize(551,551);
				AktMat->Init();
				AktMat->Zellen.Init();
				AktMat->LoadCellDef(InPfadZonen);

				AktMat->Import_Visum_fzt(Ausgabe);

				//und auswerten
				Ergebnis(FzgTyp,Branche) = AktMat->LeistungAuswerten(DistMat);

				delete AktMat;
			}
		}

		Ergebnis.SavePrn(OutPfad+"Gesamtergebnis-km.csv",12);

		delete DistMat;
	}
}


// *****************************************************************************************


void CWIVERDlg::OnButton3() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	short AktMaxVZ=551;

	CwiverMatrix Zw1;
	Zw1.SetSize(AktMaxVZ,6);
	CwiverMatrix Zw2;
	Zw2.SetSize(AktMaxVZ,6);
	CwiverMatrix Zw3;
	Zw3.SetSize(AktMaxVZ,6);
	CwiverMatrix Zw4;
	Zw4.SetSize(AktMaxVZ,6);
	CwiverMatrix Zw5;
	Zw5.SetSize(AktMaxVZ,6);

	//Über alle Szenarien laufen
	for (short Szen=0;Szen<6;Szen++)
	{
		CString InPfad1="F:\\Projekte\\JR2006-01 Szenarien Kiel\\AP1 Szenarienberechnung\\97 VISEM-Ergebnisse\\Sz";
		char buffPfad[10];
		itoa(Szen,buffPfad,10);
		InPfad1=InPfad1+buffPfad;

		CwiverMatrix Mat1;
		Mat1.Import_PTV_VFormat(InPfad1+"\\Ges_Eink_E.fma",10,9);
		CwiverMatrix Mat2;
		Mat2.Import_PTV_VFormat(InPfad1+"\\Ges_Eink_T.fma",10,9);
		CwiverMatrix Mat3;
		Mat3.Import_PTV_VFormat(InPfad1+"\\Ges_Freiz.fma",10,9);
		CwiverMatrix Mat4;
		Mat4.Import_PTV_VFormat(InPfad1+"\\Ges_GrundSch.fma",11,8);

		CwiverMatrix Mat5;
		if ((Szen==0)||(Szen==3))
			Mat5.Import_PTV_VFormat(InPfad1+"\\Ges_Schule.fma",10,9);
		else
			Mat5.Import_PTV_VFormat(InPfad1+"\\Ges_Schule.fma",11,8);

		{
			for (int ZVZ=1;ZVZ<=551;ZVZ++)
			{
				double ZielSum1=0;
				double ZielSum2=0;
				double ZielSum3=0;
				double ZielSum4=0;
				double ZielSum5=0;
				for (int QVZ=1;QVZ<=551;QVZ++)
				{
					ZielSum1=ZielSum1+Mat1(QVZ,ZVZ);
					ZielSum2=ZielSum2+Mat2(QVZ,ZVZ);
					ZielSum3=ZielSum3+Mat3(QVZ,ZVZ);
					ZielSum4=ZielSum4+Mat4(QVZ,ZVZ);
					ZielSum5=ZielSum5+Mat5(QVZ,ZVZ);
				}
				Zw1(ZVZ,Szen+1)=ZielSum1;
				Zw2(ZVZ,Szen+1)=ZielSum2;
				Zw3(ZVZ,Szen+1)=ZielSum3;
				Zw4(ZVZ,Szen+1)=ZielSum4;
				Zw5(ZVZ,Szen+1)=ZielSum5;
			}

/*			Zw1(552,Szen+1)=Mat1.GetSumTotal();
			Zw2(552,Szen+1)=Mat2.GetSumTotal();
			Zw3(552,Szen+1)=Mat3.GetSumTotal();
			Zw4(552,Szen+1)=Mat4.GetSumTotal();
			Zw5(552,Szen+1)=Mat5.GetSumTotal();
*/		}


	}//Schleife über Szenarien

	Zw1.SavePrnOhneCell("F:\\Projekte\\JR2006-01 Szenarien Kiel\\AP1 Szenarienberechnung\\97 VISEM-Ergebnisse\\Ges_Eink_E.csv",2);
	Zw2.SavePrnOhneCell("F:\\Projekte\\JR2006-01 Szenarien Kiel\\AP1 Szenarienberechnung\\97 VISEM-Ergebnisse\\Ges_Eink_T.csv",2);
	Zw3.SavePrnOhneCell("F:\\Projekte\\JR2006-01 Szenarien Kiel\\AP1 Szenarienberechnung\\97 VISEM-Ergebnisse\\Ges_Freiz.csv",2);
	Zw4.SavePrnOhneCell("F:\\Projekte\\JR2006-01 Szenarien Kiel\\AP1 Szenarienberechnung\\97 VISEM-Ergebnisse\\Ges_GrundSch.csv",2);
	Zw5.SavePrnOhneCell("F:\\Projekte\\JR2006-01 Szenarien Kiel\\AP1 Szenarienberechnung\\97 VISEM-Ergebnisse\\Ges_Schule.csv",2);

	AfxMessageBox("Fertig");
}


// *****************************************************************************************


void CWIVERDlg::OnButton4() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	for (short Szenario=0;Szenario<=1;Szenario++)
	{
		char cSzen[10];
		itoa(Szenario,cSzen,10);

		CString InPfad="F:\\N 060705\\07 WIVER\\Szen";
		InPfad=InPfad+cSzen+"\\";
		CString InPfadZonen = InPfad + "VZ-Liste.txt";
		CString OutPfad="F:\\N 060705\\07 WIVER\\Szen";
		OutPfad=OutPfad+cSzen+"\\Result\\";


		//Schleife über alle FzgTypen
		for (short FzgTyp=1;FzgTyp<=4;FzgTyp++)
		{
			CString AggPfad=OutPfad+"";
			char cFzgTyp[10];
			itoa(FzgTyp,cFzgTyp,10);
			AggPfad=AggPfad+"Mat"+cFzgTyp+".fzt";

			CwiverMatrix (*AggMat) = new CwiverMatrix;
			AggMat->SetSize(551,551);
			AggMat->Init();
			AggMat->Zellen.Init();
			AggMat->LoadCellDef(InPfadZonen);
			
			
			//Schleife über alle Branchen
			for (short Branche=1;Branche<=6;Branche++)
			{
				CString Ausgabe=OutPfad+"";
				char cBranche[10];
				itoa(Branche,cBranche,10);

				CString vAusgabe=Ausgabe+"GesVek"+cFzgTyp+"-"+cBranche+"-2.csv";

				Ausgabe=Ausgabe+"Mat"+cFzgTyp+"-"+cBranche+".fma";


				//Fahrtenmatrix einlesen
				CwiverMatrix (*AktMat) = new CwiverMatrix;
				AktMat->SetSize(551,551);
				AktMat->Init();
				AktMat->Zellen.Init();
				AktMat->LoadCellDef(InPfadZonen);

				AktMat->Import_Visum_fzt(Ausgabe);

				//und addieren
				AggMat->Add(AktMat);

				delete AktMat;
			}

			//Ergebnismatrix schreiben

			AggMat->Export_Visum_fzt(AggPfad);

			delete AggMat;
		}
	}
}


// *****************************************************************************************


void CWIVERDlg::OnButton5() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	CwiverMatrix (*Mat) = new CwiverMatrix;
	Mat->Import_PTV_VFormat("F:\\0Scan\\Pkw.fma",9,10);

	Mat->Export_Visum_fzt("F:\\0Scan\\Pkw.txt");
	
	
	delete Mat;
}


// *****************************************************************************************


void CWIVERDlg::OnButton6() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	CwiverMatrix (*Mat1) = new CwiverMatrix;
	Mat1->SetSize(581,581);
	Mat1->LoadCellDef2("F:\\0Scan\\VZListe.txt");
	Mat1->LoadMatrix_prn("F:\\0Scan\\PkwQ.txt");

	CwiverMatrix (*Mat2) = new CwiverMatrix;
	Mat2->SetSize(581,581);
	Mat2->LoadCellDef2("F:\\0Scan\\VZListe.txt");
	Mat2->LoadMatrix_prn("F:\\0Scan\\PkwZ.txt");
	
	Mat1->Add(Mat2);

	Mat1->Export_Visum_fzt("F:\\0Scan\\Pkw_FernQZ.fzt");
	
	delete Mat1;
	delete Mat2;
}


// *****************************************************************************************


