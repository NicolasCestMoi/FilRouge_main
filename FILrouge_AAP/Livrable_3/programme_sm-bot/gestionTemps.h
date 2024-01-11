
#ifndef TEMPS_H
#define TEMPS_H

#include <time.h>

typedef struct {
    clock_t debut;
    clock_t fin;
} Temps;

void initialiserTemps(Temps *temps);
double obtenirTempsEcoule(Temps *temps);

#endif 