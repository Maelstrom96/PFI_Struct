// Classe Board à compléter par les étudiants pour solutionner
// le problème du cavalier
//
// par Pierre Prud'homme, novembre 2015
// modifié et complété par <votre nom> et <votre nom si vous êtes en équipe> le <date>
///////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Matrice.h"
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

class Board
{
public:
	//--- Constructeur et destructeur
	Board(int ligne, int colonne, ostream & = cout, bool veutTrace=false);

	//--- Méthode utilisée par le client pour lancer la recherche de solution
	void Solutionner();

private:
	static const int iMAXCASES;  // Nombre de cases de l'échiquier
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
