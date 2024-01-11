Ce dossier contient les fichiers suivants:

gestionGraphUltimate.c, gestionGraphUltimate.h :  permettent l’affichage graphique de l’arbre de possibilité du morpion simple (fichier dot).

morpion_to_S.c, morpion_to_S.h : permettent la gestion d’une partie de super-morpion en utilisant les fonctions de gestions des objets du morpion classique.

posGraphUltimate.c, posGraphUtimate.h: contient la fonction de transformation des fenêtres du super-morpion en chaîne directe et l’algorithme permettant de déterminer le coup optimal pour le super-morpion.

main.c: permet le lancement de la partie de super-morpion.

Pour compiler le programme, entrez <make>.

Pour lancer une partie, ./sm-refresh.exe [position FEN (position   joueur)] [profondeur] [mode DEBUG? DEBUG / noDEBUG] [mode SMPATH? SMPATH/ noSMPATH]
