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
    posGraphUltimate position;
    if(argc ==1){
        position = fenToPosGraphUltimate("999999999");         //Exemple de buffer : "6xoxOOOX2xo1ox1oXx2xo4oox4ox"
        position.joueur = 'o';
        DEBUG = 0;
        profondeur = 1;
        printf("Si vous voulez lancer une position précise OU lancer un mode, format : \n");
        printf("[programme] [position FEN (position   joueur)] [profondeur] [mode DEBUG? DEBUG / noDEBUG] [mode SMPATH? SMPATH/ noSMPATH] \n");
    }
    else if(argc >= 2){
        DEBUG = 0;
        char buffer[100];
        int count = 0;
        while(argv[1][count] != ' '){
            buffer[count] = argv[1][count];
            count++;
        }
        buffer[++count] = '\0';
        position = fenToPosGraphUltimate(buffer);         //Exemple de buffer : "6xoxOOOX2xo1ox1oXx2xo4oox4ox"
        position.joueur = argv[1][count];
        if(argc>=3){
            profondeur = atoi(argv[2]);
            if(argc >= 4){                                          //6xox2xo4xO7xoX2xo1ox1oXx3o4oox4ox
                if(strcmp(argv[3],"DEBUG") == 0) DEBUG = 1;
                else if(strcmp(argv[3],"DEBUG") != 0) DEBUG =0;
                if(argc >= 5 && strcmp(argv[4],"SMPATH") ==0){
                    printf("\nRépertoire de création du .dot : ../super_morpion/ \n\n");
                }
            }
        }
    }

    for(int i = 0; i<10;i++){
        position.morpion[i] = newPosition(position.morpion[i].pos,'o');
    }
    
    GameUltimate(position);

    //int coup_a_jouer[2];
    //position.joueur = 'x';
    //evaluation(position,7, 2,1, coup_a_jouer);

    //printf("%d %d",coup_a_jouer[0],coup_a_jouer[1]);

}
