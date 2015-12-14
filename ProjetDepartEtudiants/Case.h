// Case.h
// Object de case ayant une coordonn� et un indice de priorit� correspondant au nombre de case accessible
// a partir de celle-ci.
//
// par Alexandre St-Jacques et Mathieu Lussier, 10 Decembre 2015
///////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Board.h"
using namespace std;

class Board;
class Case
{
   // Membres priv�e
   int _x;
   int _y;
   int PriorityIndex;

   // N'a pas besoin d'�tre public
   void SetPrioriteIndex(Board * board);

public:
   // Services
   Case(int x, int y, Board * board);
   Case(const Case & original);
   bool operator < (const Case& original) const;
   ~Case();

   // Accesseurs
   int GetX() const { return _x; }
   int GetY() const { return _y; }
   void SetX(int x) { _x = x; }
   void SetY(int y) { _y = y; };
};