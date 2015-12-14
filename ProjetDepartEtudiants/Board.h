// Classe Board à compléter par les étudiants pour solutionner
// le problème du cavalier
//
// par Pierre Prud'homme, novembre 2015
// modifié et complété par Alexandre-Jacques et Mathieu Lussier le 10 Decembre 2015
///////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Matrice.h"
#include <iostream>
#include <chrono>
#include "Case.h"
using namespace std;
using namespace std::chrono;

class Case;
class Board
{
public:
	//--- Constructeur et destructeur
	Board(int ligne, int colonne, ostream & = cout, bool veutTrace=false);

	//--- Méthode utilisée par le client pour lancer la recherche de solution
	void Solutionner();

   int NbCaseDisponible(int i, int j);

private:
	static const int iMAXCASES;  // Nombre de cases de l'échiquier
	static const int DEUX;
	static const int NEG_DEUX;
	static const int ZERO;
	ostream & rOut;
	bool traceDemandee_;
	int  noPasDuTrajet_;
	int  nombreDeSolutions_;
	int  ligneDepart_;
	int  colonneDepart_;
	Matrice<bool> caseVisitee_;  
	Matrice<int>  caseTrajet_; 
	system_clock::time_point tempsDeDepart_;
	system_clock::time_point tempsCumulatif_;
    bool CaseAccesible(int i, int j);
	void TrierCases(vector<Case> & oCases);
   vector<Case> CaseDisponible(int i, int j);

private:
	//--- Méthode lancée par le PlacerCavalier public
	void PlacerCavalier(unsigned int i, unsigned int j);

	//--- Autres méthodes utiles
	void AfficherNoSolution(int) const;
	void AfficherTrajet(int iNoSolution, system_clock::duration tempsRequis, system_clock::duration tempsRequisCumulatif) const;
	void AfficherTrajetTrace() const;
	bool ToutEstVisite() const;
	void Wait(int iNbMillisec) const;
};
