#pragma once
using namespace std;

class Case
{
   int NbCaseDispo;
   int NumPas;

public :
   Case();

   bool EstLibre();
   int Pas();
};