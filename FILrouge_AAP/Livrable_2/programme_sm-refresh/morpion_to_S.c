#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../fonctions_aux/posGraph.h"
#include "../fonctions_aux/morpion.h"
#include "../fonctions_aux/gestionGraph.h"
#include "../fonctions_aux/minimax.h"
#include "assert.h"

#include "posGraphUtimate.h"
#include "morpion_to_S.h"
#include "gestionGraphUltimate.h"

#define INFINI 1000

extern int DEBUG;

extern int profondeur;

int COUP_DEJA_JOUE = 0;

void GameUltimate(posGraphUltimate position){
    for(int i=0; i<9;i++){
        printf("///*****%d*******///\n",i+1);
        showTable(position.morpion[i]);
    }
    char* dernier_coup = calloc(10,sizeof(char));
    if(DEBUG == 1){
        printf("/********** Entrée dans le mode DEBUG **********/\n");
        printf("/*********** Profondeur choisie : %d ***********/\n", profondeur );
    }
    while(isNodeTerminal(position.morpion[9]) !=1){
        writeMorpionUltimate(position);
        do{
        	position = TourUltimate(position,&dernier_coup);
        }while(COUP_DEJA_JOUE ==1);	//On teste le cas où le position est déjà jouée
        writeMorpionUltimate(position);
        position.joueur = (position.joueur == 'o' ? 'x' : 'o');
        position = TourUltimateBot(position,&dernier_coup);
        position.joueur = (position.joueur == 'o' ? 'x' : 'o');
        printf("Voici le morpion principal : \n");
        showTable(position.morpion[9]);
    }
    writeMorpionUltimate(position);
    printf("Bravo, la partie est finie\n");
}

posGraphUltimate TourUltimateBot(posGraphUltimate position, char* pointeur_last_coup[]) {
    printf("Au tour du bot : \n");
    int maximum = -INFINI;
    int grille = coupToInt(*pointeur_last_coup);
    if(isNodeTerminal(position.morpion[9]) != 0){
        return position;
    }
    if (isNodeTerminal(position.morpion[grille-1]) != 0) {
        int coupSave[9];
        int evaluationSave[9];
        CoupOpti(position.morpion[9], -1, 0, 0, coupSave, evaluationSave,0.9);
        for(int i = 0;i<9;i++){
            if(evaluationSave[i]>maximum){
                grille = coupSave[i]+1;
                maximum = evaluationSave[i];
            }
        }
    }
    maximum = -INFINI;
    int coup_a_jouer[3];
    char joueur_temp = position.joueur;
    evaluation(position, grille, profondeur, 1, coup_a_jouer,1);
    position.joueur = joueur_temp;
    if(DEBUG == 1) printf("\nCoup joué par le bot: %d\n", coup_a_jouer[0] + 1 );
    strcpy(position.morpion[grille - 1].pos, TourAuto(position.morpion[grille - 1].pos, intToCoup(coup_a_jouer[0] + 1), position.joueur));

    strcpy(*pointeur_last_coup, intToCoup(coup_a_jouer[0] + 1));

    if (isNodeTerminal(position.morpion[grille - 1]) == 1) { 
        char* positionConvert = toTab(position.morpion[9].pos);
        if (position.joueur == 'o') positionConvert[grille - 1] = 'o';
        else positionConvert[grille - 1] = 'x';  
        strcpy(position.morpion[9].pos, toPosGraph(positionConvert));
        free(positionConvert);
    }

    for (int i = 0; i < 9; i++) {
        printf("///------%d-------///\n", i + 1);
        showTable(position.morpion[i]);
    }
    return position;
}

int evaluation(posGraphUltimate position, int coup_precedent, int horizon, int iterator, int coup_a_jouer[], int Joueurautrait) {
    int temp = -INFINI;
    int coupSave[9]={0};
    int evaluationSave[9]= {0};
    int maxi = -INFINI;
    if(iterator !=1){
        position.joueur = (position.joueur == 'x') ? 'o' : 'x';
    }
    
    if (iterator == horizon ) {
        CoupOpti(position.morpion[coup_precedent - 1], -1, 0, Joueurautrait, coupSave, evaluationSave,0.9);
        int aux = -INFINI;
        for (int k = 0; k < 9; k++) {
            if(DEBUG == 1) printf("eval : %d   | coup : %d\n",evaluationSave[k],coupSave[k]);
            if (evaluationSave[k] > aux && coupSave[k] != -100) { // == -100 signifie que le coup est deja pri
                coup_a_jouer[iterator - 1] = coupSave[k];
                aux = evaluationSave[k];
            }
        }
        if(DEBUG == 1) printf("Meilleur coup fils : %d  | evaluation : %d\n", coup_a_jouer[iterator - 1], aux);
        return aux;
    }
    else {
        int m = -INFINI;
        int i_max = -INFINI;
        char grille_saved_temp[9];
        
        strcpy(grille_saved_temp, position.morpion[coup_precedent - 1].pos);
        if(DEBUG == 1) showTable(position.morpion[coup_precedent - 1]);
        CoupOpti(position.morpion[coup_precedent - 1], -1, 0, Joueurautrait, coupSave, evaluationSave,0.9);
        for (int j = 0; j < 9; j++) {
            if(DEBUG == 1) printf("Avant\n");
            if(DEBUG == 1) showTable(position.morpion[coup_precedent-1]);
            strcpy(position.morpion[coup_precedent-1].pos, TourAuto(position.morpion[coup_precedent-1].pos, intToCoup(j + 1), position.joueur));
            if(DEBUG == 1) printf("Après\n");
            if(DEBUG == 1) showTable(position.morpion[coup_precedent-1]);
            m = evaluation(position, j + 1, horizon, iterator+1, coup_a_jouer,1-Joueurautrait);
            if(DEBUG == 1) printf("\n j: %d, eval: %d, m: %d, maxi: %d ", j,  evaluationSave[j], m, maxi);
            int old_maxi = maxi;
            maxi = max(maxi, m + evaluationSave[j]);
            if (maxi > old_maxi && coupSave[j] != -100) {
                i_max = j;
                old_maxi = maxi;
            }
            if(DEBUG == 1) printf("\n i_max: %d, maxi: %d", i_max,  maxi);
            strcpy(position.morpion[coup_precedent - 1].pos, grille_saved_temp);
        }
        if(DEBUG == 1) printf("\nFIN  : Grille n° : %d Joueur : %c, Coup à jouer: %d, iterator:%d _______\n", coup_precedent,position.joueur,i_max,iterator);
            //printf("\n__________________________________________\n");
        if (iterator == 1) coup_a_jouer[0] = i_max;            
        return maxi;
    }
}

posGraphUltimate TourUltimate(posGraphUltimate position,char* pointeur_last_coup[]){
    if(strlen(*pointeur_last_coup) == 0){   // C'est le début de la partie OU on veut jouer dans un morpion fini
        printf("%c où voulez vous jouer? format[grille colonne ligne]\n",position.joueur);
        int grille;
        char colonne;
        int ligne;                                  // On utilise la convention pour un coup de la forme 'c3'
        fscanf(stdin, "%d %c %d",&grille, &colonne, &ligne);
        char coup[3];
        sprintf(coup,"%c%d",colonne,ligne);      //On écrit le coup dans le buffer 'coup' 
        if(strcmp(TourAuto(position.morpion[grille-1].pos, coup, position.joueur), position.morpion[grille-1].pos) == 0){
            printf("La position est déjà prise.\n");
            COUP_DEJA_JOUE = 1;
            return position;
        }
        else{ 
            COUP_DEJA_JOUE = 0;
            strcpy(position.morpion[grille-1].pos,TourAuto(position.morpion[grille-1].pos, coup, position.joueur));

            // On réalise le coup automatiquement 
            // - ATTENTION : On décale le morpion de 1 (morpion-1)

            strcpy(*pointeur_last_coup,coup);

            if(isNodeTerminal(position.morpion[grille-1]) != 0){ // Le joueur qui vient de jouer gagne la grille?
                char* positionConvert = toTab(position.morpion[9].pos);
                positionConvert[grille-1] = position.morpion[grille-1].joueur; 
                strcpy(position.morpion[9].pos,toPosGraph(positionConvert));
                free(positionConvert);
            }

            for(int i=0; i<9;i++){
                printf("///*****%d*******///\n",i+1);
                showTable(position.morpion[i]);
            }
            return position;
        }
    }
    else{
        int grille = coupToInt(*pointeur_last_coup);
        if(isNodeTerminal(position.morpion[grille-1]) != 0) {
            printf("Vous pouvez jouer où vous voulez !\n"); // On retourne TourUltimate avec un coup joué de taille nul (cas initial)
            strcpy(*pointeur_last_coup,"\0");
            return TourUltimate(position,pointeur_last_coup);
        }
        printf("%c où voulez vous jouer dans la grille %d? format[grille colonne ligne]\n",position.joueur,grille);
        int buffer;     //On utilise un buffer pour stocker la grille mais on ne s'en sert pas
        char colonne;
        int ligne;          // On utilise la convention pour un coup de la forme 'c3'
        fscanf(stdin, "%d %c %d", &buffer, &colonne, &ligne);
        char coup[3];
        sprintf(coup,"%c%d",colonne,ligne);      //On écrit le coup dans le buffer 'coup' 
        if(strcmp(TourAuto(position.morpion[grille-1].pos, coup, position.joueur), position.morpion[grille-1].pos) == 0){
            COUP_DEJA_JOUE = 1;
            printf("La position est déjà prise.\n");
            return position;
        }
        else{ 
            COUP_DEJA_JOUE = 0;
            strcpy(*pointeur_last_coup,coup);
            strcpy(position.morpion[grille-1].pos,TourAuto(position.morpion[grille-1].pos, coup, position.joueur)); 

            // On réalise le coup automatiquement 
            // - ATTENTION : On décale le morpion de 1 (morpion-1)

            if(isNodeTerminal(position.morpion[grille-1]) != 0){ // Le joueur qui vient de jouer gagne la grille?
                char* positionConvert = toTab(position.morpion[9].pos);
                positionConvert[grille-1] = position.morpion[grille-1].joueur; 
                strcpy(position.morpion[9].pos,toPosGraph(positionConvert));
                free(positionConvert);
            }

            for(int i=0; i<9;i++){
                printf("///*****%d*******///\n",i+1);
                showTable(position.morpion[i]);
            }
            return position;
        }
    }
}
