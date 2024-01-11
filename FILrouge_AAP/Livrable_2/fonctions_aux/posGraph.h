#ifndef POSGRAPH_H
#define POSGRAPH_H

#define MAXLEN 100

/********Structures*******/

typedef struct posGraph {
    char pos[MAXLEN];
    char joueur;
    char last[MAXLEN];
} posGraph;


// Créer trois compartiments pour signifier le dernier coup jouer
// et le joueur -> + créer 

/******Prototypages********/

posGraph newPosition(char* c,char sigleJoueur); // transofrme oooooxxxxx et le joueur au trait en Posgraph
char* toTab(char* position); // xo3 en xo...
char* toPosGraph(char* positionC); // inverse
posGraph fenToPosGraph(char* fen); // code en posGraph 

#endif // POSGRAPH_H

