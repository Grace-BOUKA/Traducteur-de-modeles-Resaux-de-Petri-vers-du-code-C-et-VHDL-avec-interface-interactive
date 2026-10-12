// 27-03-2023: T.Lasguignes: inclusions de .h au lieu de .c
#include "types.h"
#include <string.h>
#include <stdio.h>

void GenererLog(Place *PlacesRdP, Transition *TransitionsRdP, char LeFichierLog[MAX_NOM])
{

	printf("\n\n=================================================================================\n");
	
	printf("  DESCRIPTION DU MODELE A IMPLEMENTE SUR LA CIBLE (FPGA, API, MICROCONTROLLEUR)\n");
	
	printf("=================================================================================\n\n");
	
    Place *LaPlace = PlacesRdP;
    Transition *LaTrans = TransitionsRdP;
    Arc *ArcIN = NULL;
    Arc *ArcOUT = NULL; 
    Action *UneAction = NULL;

    printf("\nOn est dans '%s'\n",LeFichierLog);

    /* ====== Gestion des places du Reseau de Pétri ====== */
    printf("========== Gestion des places du Reseau de Pétri ==========\n");
    while(LaPlace != NULL) 
    {
        printf("\n%s a pour marquage %d\n", LaPlace->Nom, LaPlace->Mo);
        
        /* Gestion des actions d'une place */
        UneAction = LaPlace->Actions;
        while(UneAction != NULL)
        {
            printf("Action de %s: %s \t", LaPlace->Nom, UneAction->Actions);
            UneAction = UneAction->Suivant;
        }
        printf("\n");
        
        LaPlace = LaPlace->Suivant;
    }

    printf("\n\n");

    /* ======= Gestion des transitions ======== */
    printf("============= Gestion des Transitions du Reseau de Petri ==========\n");
    while(LaTrans != NULL)
    {
        printf("%s a %d places in et %d places out\n", LaTrans->Nom, LaTrans->NbPlacesEntree, LaTrans->NbPlacesSortie);
        
        /* Gestion des prédicats */
        printf("Predicat: %s\n", LaTrans->Predicat);

        /* Gestion des arcs entrants */
        printf("Arcs entrants\n");
        // Initialisation du pointeur local sur le début de la liste
        ArcIN = LaTrans->ArcsEntrants; 
        while(ArcIN != NULL)
        {
            // On utilise ArcIN pour parcourir, ainsi LaTrans->ArcsEntrants ne bouge pas
            printf("%s --> %d\n", ArcIN->Place, ArcIN->Poids);
            ArcIN = ArcIN->Suivant;
        }

        /* Gestion des arcs sortants */
        printf("Arcs sortants\n");
        // Initialisation du pointeur local sur le début de la liste
        ArcOUT = LaTrans->ArcsSortants;
        while(ArcOUT != NULL)
        {
            // On utilise ArcOUT pour parcourir
            printf("%d --> %s\n", ArcOUT->Poids, ArcOUT->Place);
            ArcOUT = ArcOUT->Suivant;
        }

        LaTrans = LaTrans->Suivant;
        printf("\n");
    }
    printf("\n");
}
