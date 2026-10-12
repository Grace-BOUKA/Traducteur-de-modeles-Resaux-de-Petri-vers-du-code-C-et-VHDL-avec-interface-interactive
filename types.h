#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>

// Taille des noms des fichers
#define MAX_NOM 200

// Taille maximale des lignes à lire dans les fichiers .ndr
#define MAX_LINE_LENGTH 200

typedef struct ACTION {
    char Actions[MAX_NOM];
    struct ACTION *Suivant;
} Action;

typedef struct ARC {
    char Place[MAX_NOM];
    int Poids;
    struct ARC *Suivant;
} Arc;

typedef struct TRANSITION {
    char Nom[MAX_NOM];
    int NbPlacesEntree;
    Arc *ArcsEntrants;
    int NbPlacesSortie;
    Arc *ArcsSortants;
    char Actions[MAX_NOM];
    char Predicat[MAX_NOM];
    struct TRANSITION *Suivant;
} Transition;

typedef struct PLACE {
    char Nom[MAX_NOM];
    int Mo;
    int NbActions;
    Action *Actions;
    struct PLACE *Suivant;
} Place;

#endif
