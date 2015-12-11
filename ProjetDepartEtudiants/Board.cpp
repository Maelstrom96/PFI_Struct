// Classe Board à compléter par les étudiants pour solutionner
// le problème du cavalier
//
// par Pierre Prud'homme, novembre 2015
// modifié et complété par Mathieu Lussier et Alexandre St-Jacques le 10 décembre 2015
///////////////////////////////////////////////////////////////////////////////////////
#include "Board.h"
#include "Case.h"
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

const int Board::iMAXCASES = 8;
const int Board::DEUX = 2;
const int Board::NEG_DEUX = -2;
const int Board::ZERO = 0;

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


	// si tout est visité, on doit afficher ce résultat possible ce qui va devrait comprendre les instructions suivantes : 
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
	// sinon on doit procéder à continuer de chercher le trajet du cavalier récursivement (backtracking)
	// 
	// 1 - faire une liste des cases qu'on peut aller visiter à partir de la case où on se trouve présentement
	// 2 - pour toutes ces cases, on doit aller y placer un cavalier; lorsqu'il revient à l'instruction qui suit
	//     celles-ci, ça veut dire que tous les trajets possibles ont été visités à partir de la position i,j
	//     et que nous devons ...
   else
   {
	   vector<Case> oCases = CaseDisponible(i, j);
	   TrierCases(oCases);
	   for each(Case oCase in oCases)
		   PlacerCavalier(oCase.GetX(), oCase.GetY());
   }

	// 'démarquer' cette classe puisqu'on va revenir un pas en arrière
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

	// pour ne pas avoir à faire des enter quand on écrit dans un fichier de sortie...
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

//Creation dun vecteur de case disponible pour le prochain deplacement
vector<Case> Board::CaseDisponible(int i, int j)
{
	vector<Case> oCases;
	for (int y = NEG_DEUX; y <= DEUX; y++)
   {
	   for (int x = NEG_DEUX; x <= DEUX; x++)
      {
		  if ((abs(x) + abs(y) == 3) && CaseAccesible(x + i, y + j) && caseVisitee_[x+i][y+j] == false)
		  {
			  Case oCase(x + i, y + j, this);
			  oCases.push_back(oCase);
		  }
      }
   }
   return oCases;
}

int Board::NbCaseDisponible(int i, int j)
{
   int Total = 0;
   for (int y = NEG_DEUX; y <= DEUX; y++)
   {
      for (int x = NEG_DEUX; x <= DEUX; x++)
      {
         if ((abs(x) + abs(y) == 3) && CaseAccesible(x + i, y + j) && caseVisitee_[x + i][y + j] == false)
         {
            Total++;
         }
      }
   }
   return Total;
}

//Verification si la case du deplacement est valide 
bool Board::CaseAccesible(int i, int j)
{
	if (i >= ZERO && j >= ZERO && i < iMAXCASES && j < iMAXCASES) return true;
	else return false;
}

//Triage du vecteur par priorite 
void Board::TrierCases(vector<Case> & oCases)
{
	sort(oCases.begin(), oCases.end());
}