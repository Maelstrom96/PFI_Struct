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

Case::Case(const Case & original)
{
	_x = original.GetX();
	_y = original.GetY();
	PriorityIndex = original.PriorityIndex;
}

bool Case::operator < (const Case& original) const
{
	return (PriorityIndex < original.PriorityIndex);
}

//Definir la priorite des deplacements 
void Case::SetPrioriteIndex(Board * board)
{
   PriorityIndex = board->NbCaseDisponible(_x, _y);

   /*
	PriorityIndex = 3;
	// Walling
	if (_x == 0 || _y == 0) PriorityIndex = 2;
	if (_x == 7 || _y == 7) PriorityIndex = 2;
	
	for (int y = 0; y < 8; y += 7)
	{
		for (int x = 0; x < 8; x += 7)
		{
			if (x == _x && y == _y) PriorityIndex = 1;
		}
	}
   */
}