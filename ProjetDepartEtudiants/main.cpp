//--------------------------------------------------------
//
//  Programme principal en mode console permettant de 
//  mettre en marche la solution au trajet du cavalier
//
//  par Pierre Prud'homme, novembre 2008
//  révision P. Prud'homme, novembre 2015
//--------------------------------------------------------
#include "board.h"
#include <iostream>
#include <fstream>
using namespace std;

unsigned int Lecture_Bornee (const unsigned int Borne_Min, const unsigned int Borne_Max);
void LireCoordonneesDepart  (unsigned int &x, unsigned int &y);
bool EstTraceVoulue();

int main()
{
	system("Color f0");
	unsigned int x, y;

	LireCoordonneesDepart(x, y);
	Board oEchiquier(x, y, cout, EstTraceVoulue());
	oEchiquier.Solutionner();

	//// ou encore cette version qui écrit les solutions dans un fichier
	//LireCoordonneesDepart(x, y);
	//ofstream sortie("sortie.txt");
	//Board oEchiquier(x, y, sortie, EstTraceVoulue());
	//oEchiquier.Solutionner();
	//sortie.close();
}

void LireCoordonneesDepart(unsigned int &x, unsigned int &y)
{
	cout << "Coordonnee ligne; ";
	x = Lecture_Bornee(0, 7);
	cout << "Coordonnee colonne; ";
	y = Lecture_Bornee(0, 7);
}

unsigned int Lecture_Bornee (const unsigned int Borne_Min, const unsigned int Borne_Max)
{
   unsigned int Valeur_Lue;
   do
   {
      cout << "entrez un entier entre "
           << Borne_Min
           << " et "
           << Borne_Max
           << " inclusivement: ";
      cin >> Valeur_Lue;
   }
   while (Valeur_Lue < Borne_Min || Valeur_Lue > Borne_Max);
   return Valeur_Lue;
}

bool EstTraceVoulue()
{
	char cReponse;

	cout << "Voulez-vous voir la trace d'execution (O/N) : ";
	cin >> cReponse;
	while (toupper(cReponse) != 'N' &&
		   toupper(cReponse) != 'O')
	{
		cout << "Voulez-vous voir la trace d'execution (O/N) : ";
		cin >> cReponse;
	}
	return (toupper(cReponse) == 'O');
}