// CalcPVMatrix.h: Schnittstelle für die Klasse CCalcPVMatrix.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCPVMATRIX_H__8E1223A0_9D7B_11D6_BB2F_E02E5CC1C8CC__INCLUDED_)
#define AFX_CALCPVMATRIX_H__8E1223A0_9D7B_11D6_BB2F_E02E5CC1C8CC__INCLUDED_

#include "DatVZEinteil.h"	// Hinzugefügt von der Klassenansicht
#include "CalcVektor.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DatBasis.h"
#include "CalcPVTeilmatrix.h"
#include "DatWiderstandsmatrizen.h"
#include "AktPVSzen.h"

class CCalcPVMatrix : public CDatBasis
{
public:
	void Import_PTV(CString);
	void Auswerten_ZweckQZVerkehr(CString, short);
	double GibSummeVerkM(short);
	void WertInit_ohneBinnen();
	void MultipliziereMitFaktor(double);
	void RundungsfehlerBeseitigenVer3(short&, double&, CCalcPVTeilmatrix*);
	void RundungsfehlerBeseitigenVer2(short&, double&, CCalcPVTeilmatrix*);
	void RundungsfehlerBeseitigen(short&, double&);

	void AuswertungenZus(CString);
	void Auswertungen_zusammen(CString);
	void Analyse_Gesamtreisezeiten(CDatWiderstandsmatrizen&,CDatWiderstandsmatrizen&,CDatWiderstandsmatrizen&,CDatWiderstandsmatrizen&,CDatWiderstandsmatrizen&,CDatWiderstandsmatrizen&);
	void Import_xml(CString);
	void Ausgabe_Durchlauf(short, CString, CString);
	double GibSumme();
	CString LoadTemp(CString, CString, short, short);
	bool SaveTemp(CString, CString, short, short);
	void Leistung_Berechnen(CDatWiderstandsmatrizen*);
	void Subtrahiere(CCalcPVMatrix*);

	bool OutputGenerator(short, int, int, CString, CString, CString, CAktPVSzen);

	void Kalibrieren_VD(CCalcVektor*, CCalcPVMatrix*);
	void Aggregieren(short);
	void FaktorenAnwenden(CCalcPVMatrix*);
	bool Export_ArcGIS(CString);
	void Auswerten_QuellZielVerkehr(CString, CString);
	void Auswerten_ModalSplit(CString, CString);
	bool Export_csv(CString, short);
	void Addiere(CCalcPVMatrix*);
	bool SaveQuellZielVerkehr_prn(CString);
	void Teile1000();
	void Kalibrieren_VZ(CCalcVektor*, CCalcPVMatrix*);
	CDatVZEinteil VZListe;
	bool Export_Visum(CString, short);
	bool Export_Tranplan(CString, short);
	void WertInit();
	bool Export_VerkMod(CString);
	void SpiegelnAddieren();
	double Wert[co_MaxVZ][co_MaxVZ][co_MaxVerkMPV];
	CCalcPVMatrix();
	virtual ~CCalcPVMatrix();

	//Später in private übernehmen
	bool Load_prn(CString);
	bool Save_prn(CString);

private:
	bool Save_prn0(CString);

	struct sRundVektor
	{
		double Wert;
		short ZielVZ;
		short VerkM;
	};

};

#endif // !defined(AFX_CALCPVMATRIX_H__8E1223A0_9D7B_11D6_BB2F_E02E5CC1C8CC__INCLUDED_)
