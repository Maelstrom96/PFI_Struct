#pragma once
#include "Board.h"
using namespace std;

class Board;
class Case
{
   int _x;
   int _y;
   int PriorityIndex;

   void SetPrioriteIndex(Board * board);

public:
   Case(int x, int y, Board * board);
   Case(const Case & original);
   bool operator < (const Case& original) const;
   ~Case();
   int GetX() const { return _x; }
   int GetY() const { return _y; }
   void SetX(int x) { _x = x; }
   void SetY(int y) { _y = y; };
};