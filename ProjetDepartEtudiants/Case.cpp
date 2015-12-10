#include "Case.h"

Case::Case()
{
   NbCaseDispo = 0; // Initialisation à 0
   NumPas = -1; // Pas est null
}

bool Case::EstLibre()
{
   return NumPas == -1;
}

int Case::Pas()
{
   return NumPas;
}