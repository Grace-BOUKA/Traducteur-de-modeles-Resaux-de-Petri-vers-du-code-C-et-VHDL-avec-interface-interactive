#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "fonctions.h"


int main(void)
{
    Transition *TransitionsRdP = NULL;
    Place *PlacesRdP = NULL;

    char LeFichierTINA[MAX_NOM] = "etiquette.ndr";
    char LeFichierLog[MAX_NOM] = "etiquette.log";
    char LeFichier[MAX_NOM] = "evolution_modele.txt";
    

    printf("nom du fichier a Mouliner :");
    scanf("%s", LeFichierTINA);
    strcpy(LeFichierLog, LeFichierTINA);
    strcat(LeFichierTINA, ".ndr");
    strcat(LeFichierLog, ".log");

    int choix;
    printf("---- Veuillez choisir le langage cible svp ----\n");
    printf("===========================================\n");
    printf("1. Génération en VHDL\n2. Génération en C\n");
    printf("===========================================\n");
    scanf("%d",&choix);

    // Construction propre du chemin complet avec le repertoire des modèles "./models/"
    char cheminComplet[MAX_NOM + 15];
    snprintf(cheminComplet, sizeof(cheminComplet), "./models/%s", LeFichierTINA);

    // Ouverture du fichier issu de tina avec le chemin complet
    CreerStructure(cheminComplet, &TransitionsRdP, &PlacesRdP);

    // description de la struction complete du réseau de Pétri
    GenererLog(PlacesRdP, TransitionsRdP, LeFichierLog);


    // Choix utilisateur pour le langage cible
    switch(choix)
    {
    	 // GenererBlocs(TransitionsRdP, PlacesRdP, LeFichier)
        case 1: GenererBlocs_VHDL(TransitionsRdP, PlacesRdP, LeFichier);break;
        case 2: GenererBlocs_C(TransitionsRdP, PlacesRdP, LeFichier); break;
        default: GenererBlocs_C(TransitionsRdP, PlacesRdP, LeFichier); break;
    
    }
        
   
    NettoyerMemoire(&TransitionsRdP, &PlacesRdP);

    return EXIT_SUCCESS;
}
