#include "gestionTemps.h"

void initialiserTemps(Temps *temps) {
    temps->debut = clock();
    temps->fin = temps->debut;
}

double obtenirTempsEcoule(Temps *temps) {
    temps->fin = clock();
    return ((double) (temps->fin - temps->debut)) / CLOCKS_PER_SEC;
}