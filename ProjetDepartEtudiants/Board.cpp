// Classe Board � compl�ter par les �tudiants pour solutionner
// le probl�me du cavalier
//
// par Pierre Prud'homme, novembre 2015
// modifi� et compl�t� par <votre nom> et <votre nom si vous �tes en �quipe> le <date>
///////////////////////////////////////////////////////////////////////////////////////
#include "Board.h"
#include <string>
#include <cmath>
using namespace std;

const int Board::iMAXCASES = 8;

Board::Board(int ligne, int colonne, ostream & sortie, bool veutTrace)
:ligneDepart_(ligne), colonneDepart_(colonne), rOut(sortie), traceDemandee_(veutTrace),
 caseVisitee_(iMAXCASES, iMAXCASES), caseTrajet_(iMAXCASES, iMAXCASES)
{
	for (int i=0; i<iMAXCASES; i++)
		for (int j=0; j<iMAXCASES; j++)
		{
			caseVisitee_[i][j] = false;
			caseTrajet_[i][j] = -1;
			noPasDuTrajet_ = 0;
		}
	nombreDeSolutions_ = 0;
}

void Board::Solutionner()
{
	tempsCumulatif_ = tempsDeDepart_ = system_clock::now();
	PlacerCavalier (ligneDepart_, colonneDepart_);
}


void Board::PlacerCavalier(unsigned int i, unsigned int j)
{
	// Marquer cette case que l'on vient d'atteindre afin d'indiquer qu'elle
	// contient un cavalier
	caseVisitee_[i][j] = true;
	caseTrajet_[i][j] = noPasDuTrajet_;
	noPasDuTrajet_++;
	if (traceDemandee_) AfficherTrajetTrace();    


	// si tout est visit�, on doit afficher ce r�sultat possible ce qui va devrait comprendre les instructions suivantes : 
	//
   if (ToutEstVisite())
   {
      auto stop = system_clock::now();
      auto tempsEcoule = stop - tempsDeDepart_;
      auto tempsEcouleCumulatif = stop - tempsCumulatif_;
      system("cls");
      AfficherTrajet(++nombreDeSolutions_, tempsEcoule, tempsEcouleCumulatif);
      tempsDeDepart_ = system_clock::now();
   }
	// sinon on doit proc�der � continuer de chercher le trajet du cavalier r�cursivement (backtracking)
	// 
	// 1 - faire une liste des cases qu'on peut aller visiter � partir de la case o� on se trouve pr�sentement
	// 2 - pour toutes ces cases, on doit aller y placer un cavalier; lorsqu'il revient � l'instruction qui suit
	//     celles-ci, �a veut dire que tous les trajets possibles ont �t� visit�s � partir de la position i,j
	//     et que nous devons ...
   else
   {
      if (CaseDisponible(i,j))
         PlacerCavalier(i, j);
   }

	// 'd�marquer' cette classe puisqu'on va revenir un pas en arri�re
	// pour chercher un nouveau trajet (backtracking)
    caseVisitee_[i][j] = false;
    caseTrajet_[i][j] = -1;
    noPasDuTrajet_ --;	
}

void Board::AfficherNoSolution(int iNbSolution) const
{
	rOut << endl 
		<< "Solution #" << iNbSolution << endl;
}

void Board::AfficherTrajet(int iNoSolution, system_clock::duration tempsRequis, system_clock::duration tempsRequisCumulatif) const
{
	rOut << "Cavalier en (" << ligneDepart_ << ", " << colonneDepart_ << ")" << endl;
	rOut << string(7*iMAXCASES+1,'-') << endl;
	for (int i=0; i<iMAXCASES; i++)
	{
		rOut << "| ";
		for (int j = 0; j < iMAXCASES; j++)
		{
			if (caseTrajet_[i][j] != 0)
			{
				rOut.width(4);
				rOut << caseTrajet_[i][j] << " | ";
			}
			else
			{
				rOut << "   C | ";
			}
		}
		rOut << endl;
		rOut << string(7*iMAXCASES+1,'-') << endl;
	}
	AfficherNoSolution( iNoSolution );
	rOut << "en " << duration_cast<microseconds>(tempsRequis).count() << " microsecondes" << endl;
	rOut << "ou si vous preferez en " << duration_cast<nanoseconds>(tempsRequis).count() << " nanosecondes" << endl;
	rOut << endl << "temps requis cumulatif : " << duration_cast<microseconds>(tempsRequisCumulatif).count() << " microsecondes" << endl;

	// pour ne pas avoir � faire des enter quand on �crit dans un fichier de sortie...
	if (&rOut == &cout) system("pause");

}

void Board::AfficherTrajetTrace() const
{
	system("cls");
	rOut << string(41,'-') << endl;
	for (int i=0; i<iMAXCASES; i++)
	{
		rOut << "| ";
		for (int j=0; j<iMAXCASES; j++)
		{
			if (caseTrajet_[i][j] != 0 && caseTrajet_[i][j] != -1)
			{
				rOut.width(2);
				rOut << caseTrajet_[i][j] << " | ";
			}
			else if (caseTrajet_[i][j] == -1)
			{
				rOut << "   | ";
			}
			else
			{
				rOut << " C | ";
			}
		}
		rOut << endl;
		rOut << string(41,'-') << endl;
	}
	Wait(750);  // millisecondes dont 3/4 de seconde
}

void Board::Wait(int iNbMilliSec) const
{
	auto start = system_clock::now();
	auto stop = system_clock::now();
	auto tempsEcoule = stop - start;

	while (duration_cast<milliseconds>(tempsEcoule).count() < iNbMilliSec)
	{
		stop = system_clock::now();
		tempsEcoule = stop - start;
	}
}

bool Board::ToutEstVisite() const
{
	return (noPasDuTrajet_ >= ((iMAXCASES * iMAXCASES)));
}


bool Board::CaseDisponible(unsigned int i, unsigned int j)
{
   for (int x = i - 2; x < i + 2; ++x)
   {
      for (int y = j - 2; y < j + 2; ++y)
      {
         if (abs(x) + abs(y) == 3)
            if (caseVisitee_[abs(x)][abs(y)] == false)
               return true;
      }
   }
}