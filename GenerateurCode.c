#include "types.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> // Pour l'usage de strlen()


// ================================================== CODE EN VHDL =============================================

void GenererBlocs_VHDL(Transition *PremiereTransition, Place *PremierePlace, char LeFichier[MAX_NOM]) 
{
    FILE *f = fopen(LeFichier, "w");
    if (f == NULL) return;


    // BIBLIOTHEQUE NECESSAIRES
    fprintf(f, "library IEEE;\nuse IEEE.STD_LOGIC_1164.ALL;\nuse IEEE.NUMERIC_STD.ALL;\n\n");
    /*Ces librairies sont indispensables car nous allons utliser des types int 
      et donc des opérateurs numériques, donc le NUMERIC est indispensable pour
      les operatuers rélationnels*/
    
    // Entete Entity et les ports (clk,reset)
    fprintf(f, "entity Automate_RdP is\n    Port (\n");
    fprintf(f, "        clk   : in  STD_LOGIC;\n");
    fprintf(f, "        reset : in  STD_LOGIC\n");

    Transition *currT = PremiereTransition;
    // Déclaration des entrées (les capteurs)
    char predicat_faites[100][MAX_NOM]; // Predicat deja traitées
    int nb_pred = 0; // Nbre de Predicats

    while (currT) 
    {
        int vu = 0;
        for(int i=0; i<nb_pred; i++) if(strcmp(predicat_faites[i], currT->Predicat)==0) vu=1;
        if(!vu)
        {
            fprintf(f, "        %s : in  STD_LOGIC\n",currT->Predicat);
            strcpy(predicat_faites[nb_pred], currT->Predicat);
            nb_pred++;
        }
        currT = currT->Suivant;
    }

   
    // Déclaration des sorties
    Place* currP;
    currP = PremierePlace;
    char Actions_faites[100][MAX_NOM]; // Actions deja traitées
    int nbr_act = 0; // Nbre d'actions
    
    while (currP) {
        Action *currA = currP->Actions;
        while (currA) {
            int vu = 0;
            for(int i=0; i<nbr_act; i++) if(strcmp(Actions_faites[i], currA->Actions)==0) vu=1;
            if(!vu)
            {
                fprintf(f, "        %s : out  STD_LOGIC\n",currP->Actions->Actions);
                strcpy(Actions_faites[nbr_act], currA->Actions);              
            }
            currA = currA->Suivant;
            nbr_act++;
        }
        currP = currP->Suivant;
    }


    fprintf(f,")\nend Automate_RdP;\n\n");

    fprintf(f, "architecture Behavioral of Automate_RdP is\n");

    // DÉCLARATION DES SIGNAUX (P et NEXT_P)
    fprintf(f, "    -- Signaux de marquage (M et M_futur)\n");
    Place *currp = PremierePlace;
    /* On parcours toutes les places pour initialiser les signaux internes (qui ici sont les places)*/
    while (currp) {
        fprintf(f, "    signal %s, next_%s : integer := %d;\n", currp->Nom, currp->Nom, currp->Mo);
        currp = currp->Suivant;
    }

    fprintf(f, "begin\n\n");

    // PROCESS M : HORLOGE (SYNCHRONE)
    fprintf(f, "    -- PROCESS M : Mise a jour du marquage sur front d'horloge\n");
    fprintf(f, "    process(clk, reset)\n    begin\n");
    fprintf(f, "        if reset = '1' then\n");
    currp = PremierePlace;
    while (currp!=NULL) {
        fprintf(f, "            %s <= %d;\n", currp->Nom, currp->Mo);
        currp = currp->Suivant;
    }
    fprintf(f, "        elsif rising_edge(clk) then\n");
    currp = PremierePlace;
    while (currp!=NULL) {
        fprintf(f, "            %s <= next_%s;\n", currp->Nom, currp->Nom);
        currp = currp->Suivant;
    }
    fprintf(f, "        end if;\n    end process;\n\n");

    
    // PROCESS FG : LOGIQUE ET ACTIONS 
    fprintf(f, "    -- PROCESS FG : Calcul du franchissement et des actions\n");
    fprintf(f, "    process(");
    // Liste de sensibilité (toutes les places)
    /* On parcourt toutes les places et on les stockes au niveau de la liste de sensiblité */
    currp = PremierePlace;
    int first_sens = 1; // 
    while (currp!=NULL) {
        if (!first_sens) fprintf(f, ", ");
        fprintf(f, "%s", currp->Nom);
        first_sens = 0;
        currp = currp->Suivant;
    }
    fprintf(f, ")\n    begin\n");

    // Initialisation par défaut
    currp = PremierePlace;
    while (currp) {
        fprintf(f, "        next_%s <= %s;\n", currp->Nom, currp->Nom);
        currp = currp->Suivant;
    }
    fprintf(f, "\n");

    // BLOC F 
    Transition *currt = PremiereTransition;
    /* Tant que la liste chainée de la trnasition ne pointe pas vers NULL */
    while (currt!=NULL) {
        fprintf(f, "        if (");
        Arc *pArc = currt->ArcsEntrants;
        int first_arc = 1;
        /* On parcours l'ensemble des arcs*/
         
        while (pArc) { // VérificAtion des Arcs Entrants (Places d'entrées)
            if (!first_arc) fprintf(f, " and "); 
            fprintf(f, "%s>=%d", pArc->Place, pArc->Poids);
            first_arc = 0;
            pArc = pArc->Suivant;
        }
        
        fprintf(f, " and %s ", strlen(currt->Predicat) > 0 ? currt->Predicat:"1");
        fprintf(f, ") then\n");

        // Modification du "Next" marquage
        pArc = currt->ArcsEntrants;
        while (pArc) {
            fprintf(f, "            next_%s <= %s - %d;\n", pArc->Place, pArc->Place, pArc->Poids);
            pArc = pArc->Suivant;
        }
        pArc = currt->ArcsSortants;
        while (pArc) {
            fprintf(f, "            next_%s <= %s + %d;\n", pArc->Place, pArc->Place, pArc->Poids);
            pArc = pArc->Suivant;
        }
        fprintf(f, "        end if;\n\n");
        currt = currt->Suivant;
    }

    // BLOC G (ACTIONS)
    fprintf(f, "        -- Ecriture des actions \n");
    char actions_faites[100][MAX_NOM]; // Actions deja traitées
    int nb_act = 0; // Nbre d'actions
    // Fin declaration Variables 

    currp = PremierePlace;
     // On parcourt les places pour trouver les actions à piloter
    while (currp) {
        Action *curra = currp->Actions;
        while (curra) { 
            int vu = 0;
            for(int i=0; i<nb_act; i++) if(strcmp(actions_faites[i], curra->Actions)==0) vu=1;
            if(!vu) { // On écrit le début de la sortie correspondante
                fprintf(f, "        %s <= '1' when (%s > 0", curra->Actions, currp->Nom);
                 // On cherche si d'autres PLACES possèdent la meme action pour faire le "||"
                Place *p2 = PremierePlace;
                while(p2) {
                    if(p2 != currp) {  // On ne compare pas la place actuelle avec elle-même
                        Action *a2 = p2->Actions;
                        while(a2) {
                            if(strcmp(a2->Actions, curra->Actions)==0) fprintf(f, " or %s > 0", p2->Nom);
                            a2 = a2->Suivant;
                        }
                    }
                    p2 = p2->Suivant; // Passe à l'action suivante
                }
                fprintf(f, ") else '0';\n");
                strcpy(actions_faites[nb_act++], curra->Actions); // Comparaison si action deja traitées ou pas
            }
            curra = curra->Suivant; // Passe à l'action suivvante
        }
        currp = currp->Suivant; // Passe à la place suivante
    }

    fprintf(f, "    end process;\n\nend Behavioral;\n");
    fclose(f);
    printf("\n\n Generation du code en VHDL dans %s\n", LeFichier);
}







// ================================================== CODE EN C =============================================


void GenererBlocs_C(Transition *PremiereTransition, Place *PremierePlace, char LeFichier[MAX_NOM]) 
{
    
    printf("\nOn est dans 'GenerateurCode.c'\n");

    FILE *f = fopen(LeFichier, "w");
    if (f == NULL) {
        perror("Erreur lors de la création du fichier");
        return;
    }

    fprintf(f, "/* ===================================================== */\n");
    fprintf(f, "/* CODE GÉNÉRÉ AUTOMATIQUEMENT (STRUCTURE FMG)         */\n");
    fprintf(f, "/* ===================================================== */\n\n");

    fprintf(f,"#include<stdio.h>\n");
    fprintf(f,"#include<stdlib.h>\n");

    //  DECLARATION DES PLACES (Marquage Initial) 
    fprintf(f, "// --- DÉCLARATIONS DES PLACES ---\n");
    Place *currP = PremierePlace;
    while (currP != NULL) {
        // On initialise les places avec le nombre de jetons initial
        fprintf(f, "int %s = %d;\n", currP->Nom, currP->Mo);
        currP = currP->Suivant;
    }
    fprintf(f,"\n");

    // DECLARATION ET INITIALISATION DES ACTIONS
    fprintf(f,"//---- DECLARATION DES ACTIONS ---\n");
    currP = PremierePlace;
    while (currP) {
        Action *currA = currP->Actions;
        while (currA) {
            fprintf(f,"int %s = 0;\n", currA->Actions);
            currA = currA->Suivant;
        }
        currP = currP->Suivant;
    }
    fprintf(f, "\nint main(int argc, char* argv[]) {\n");

    // BLOC F : EVOLUTION DES TRANSITIONS
    fprintf(f, " /* --- BLOC F && M : ÉVOLUTIONS (TRANSITIONS) ET MISE A JOUR PLACE---*/\n");
    Transition *currT = PremiereTransition;
    while (currT != NULL) {
        fprintf(f, "    // Transition: %s\n", currT->Nom);
        
        // Début du IF : Condition de franchissement
        // On combine le PrédicurrAt  et la présence de jetons en entrée
        fprintf(f, "    if ((%s)", (strlen(currT->Predicat) > 0) ? currT->Predicat : "1");

        // VérificAtion des Arcs Entrants (Places d'entrées)
        Arc *arcIn = currT->ArcsEntrants;
        while (arcIn != NULL) {
            fprintf(f, " && (%s >= %d)", arcIn->Place, arcIn->Poids);
            arcIn = arcIn->Suivant;
        }
        fprintf(f, ") {\n");

        // ACTIONS DU FRANCHISSEMENT
        // Retirer les jetons des entrées
        arcIn = currT->ArcsEntrants;
        while (arcIn != NULL) {
            fprintf(f, "        %s -= %d;\n", arcIn->Place, arcIn->Poids);
            arcIn = arcIn->Suivant;
        }

        // Ajouter les jetons aux sorties
        Arc *arcOut = currT->ArcsSortants;
        while (arcOut != NULL) {
            fprintf(f, "        %s += %d;\n", arcOut->Place, arcOut->Poids);
            arcOut = arcOut->Suivant;
        }
        fprintf(f, "    }\n\n");

        currT = currT->Suivant; // Transition suivante
    }


    // --- BLOC G (Actions optimisées sans Reset) ---
    fprintf(f, " /* --- BLOC G : Calcul des sorties --- */\n");
    
    // On parcourt les places pour trouver les actions à piloter
    currP = PremierePlace;
    while (currP) {
        Action *currA = currP->Actions;
        while (currA) {
            // On écrit le début de la sortie correspondante
            fprintf(f, "        %s = (%s > 0)", currA->Actions, currP->Nom);
            
            // On cherche si d'autres PLACES possèdent la meme action pour faire le "||"
            Place *p_check = PremierePlace;
            while (p_check) {
                // On ne compare pas la place actuelle avec elle-même
                if (p_check != currP) {
                    Action *a_check = p_check->Actions;
                    while (a_check) {
                        if (strcmp(a_check->Actions, currA->Actions) == 0) {
                            fprintf(f, " || (%s > 0)", p_check->Nom);
                        }
                        a_check = a_check->Suivant;
                    }
                }
                p_check = p_check->Suivant;
            }
            fprintf(f, ";\n");
            
            currA = currA->Suivant;
        }
        currP = currP->Suivant;
    }
    fprintf(f,"\n\n //=========== Ecriture des sorties ========= \n\n");
     
    fprintf(f,"/* Pour la connexion avec les E/S du matériel: sortie(bitA,valeurA) à inserer manuellemnt */\n\n");
    fprintf(f," //============ Fin ecriture de sortie ===========\n\n");

    fprintf(f, " return EXIT_SUCCESS;\n}\n");
    fclose(f);
    printf("Génération du code en c terminée dans %s\n",LeFichier);
}
