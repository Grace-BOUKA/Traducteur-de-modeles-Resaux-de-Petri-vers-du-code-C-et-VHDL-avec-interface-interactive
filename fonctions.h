// 27-03-2023: T.Lasguignes: Création de fonctions.h pour regrouper les déclarations de fonctions (pas optimal mais plus propre qu'avant)

#ifndef FONCTIONS_H
#define FONCTIONS_H

#include "types.h"

// Fonctions à développer

void GenererLog(Place *, Transition *, char[MAX_NOM]);
void GenererBlocs_VHDL(Transition *TransitionsRdP, Place *PlacesRdp, char[MAX_NOM]);
void GenererBlocs_C(Transition *TransitionsRdP, Place *PlacesRdp, char[MAX_NOM]);
// void GenererBlocs(Transition *TransitionsRdP, Place *PlacesRdp, char[MAX_NOM]);
int CreerStructure(char[MAX_NOM], Transition **, Place **);

// Utilisées pour CreerStructure
void CreerUneTransition(Transition **, int, char **);
void CreerUnePlace(Place **, int, char **);
void CreerUnArc(Transition *, int, char **);
void NettoyerLaChaine(char *);
char **str_split(const char *, const char *, size_t *);
char **ExtraireJetons(char *, const char *, size_t *);

void NettoyerMemoire(Transition **, Place **);


#endif
