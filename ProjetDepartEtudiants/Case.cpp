// Case.cpp
// Object de case ayant une coordonné et un indice de priorité correspondant au nombre de case accessible
// a partir de celle-ci.
//
// par Alexandre St-Jacques et Mathieu Lussier, 10 Decembre 2015
///////////////////////////////////////////////////////////////////////////////////////

#include "Case.h"
#include "Board.h"

Case::~Case()
{
}

Case::Case(int x, int y, Board * board)
{
	SetX(x);
	SetY(y);
	SetPrioriteIndex(board);
}

////////////////////////////////////////////////////////
// Case(const Case & original)
// Constructeur de copie pour la case.
//
// intrant : Case
////////////////////////////////////////////////////////
Case::Case(const Case & original)
{
	_x = original.GetX();
	_y = original.GetY();
	PriorityIndex = original.PriorityIndex;
}

////////////////////////////////////////////////////////
// operator < (const Case& original) const
// Permet de comparer deux Case.
// L'operateur à été overide pour utiliser la fonction sort()
//
// intrant : Case
// extrant : bool
////////////////////////////////////////////////////////
bool Case::operator < (const Case& original) const
{
	return (PriorityIndex < original.PriorityIndex);
}

////////////////////////////////////////////////////////
// SetPrioriteIndex(Board * board)
// Obtient le nombre de deplacements disponibles et 
// l'assigne à la case.
//
// intrant : Pointeur vers le board utilisé.
////////////////////////////////////////////////////////
void Case::SetPrioriteIndex(Board * board)
{
   PriorityIndex = board->NbCaseDisponible(_x, _y);
}