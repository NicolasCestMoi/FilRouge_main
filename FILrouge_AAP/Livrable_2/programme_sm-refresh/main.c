#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#include "../fonctions_aux/posGraph.h"
#include "../fonctions_aux/morpion.h"
#include "../fonctions_aux/gestionGraph.h"
#include "../fonctions_aux/minimax.h"

#include "posGraphUtimate.h"
#include "morpion_to_S.h"
#include "gestionGraphUltimate.h"

int DEBUG = 0;
int profondeur = 1;

int main(int argc, char* argv[]){
    DEBUG = 0;
    posGraphUltimate position;

    /******Gestion des variables d'environnements****/

    char* debugEnv = getenv("DEBUG");
    if(debugEnv != NULL && atoi(debugEnv) != 0){
        DEBUG = 1;
    }
    else {
        DEBUG = 0;
    }

    char* smpathEnv = getenv("SMPATH");
    if(smpathEnv != NULL && atoi(debugEnv) != 0){
        printf("Voici le chemin : <../programme_sm-refresh/>");
    }

    /***Gestion des paramètres d'entrées****/
    if(argc ==1){
        position = fenToPosGraphUltimate("999999999");         //Exemple de buffer : "6xoxOOOX2xo1ox1oXx2xo4oox4ox"
        position.joueur = 'o';
        profondeur = 2;
        printf("Si vous voulez lancer une position précise OU lancer un mode, format : \n");
        printf("[programme] [position FEN (position   joueur)] [profondeur] \n");
    }
    else if(argc >= 2){
        char buffer[100];
        int count = 0;
        while(argv[1][count] != ' '){
            buffer[count] = argv[1][count];
            count++;
        }
        buffer[++count] = '\0';
        position = fenToPosGraphUltimate(buffer);         //Exemple de buffer : "6xoxOOOX2xo1ox1oXx2xo4oox4ox"
        position.joueur = argv[1][count];
        if(argc==3){
            profondeur = atoi(argv[2]);
            if(profondeur > 4){
                fprintf(stderr,"Attention, la profondeur est peut-être trop importante : risque de CRASH");
            }
        }
    }

    for(int i = 0; i<10;i++){
        position.morpion[i] = newPosition(position.morpion[i].pos,'o');
    }
    
    GameUltimate(position);

}
