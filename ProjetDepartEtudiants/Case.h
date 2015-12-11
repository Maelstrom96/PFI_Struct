#pragma once
using namespace std;

class Case
{
   int _x;
   int _y;
   int PriorityIndex;

   void SetPrioriteIndex();

public:
   Case(int x, int y);
   Case(const Case & original);
   bool operator < (const Case& original) const;
   ~Case();
   int GetX() const { return _x; }
   int GetY() const { return _y; }
   void SetX(int x) { _x = x; }
   void SetY(int y) { _y = y; };
};