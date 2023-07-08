
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LENGTH 100000
#include "autostrada.h"


int main() {
    char input[MAX_LENGTH];
    char *command; //comando da eseguire
    int n; //numero di macchine da inserire
    int gittata; //gittata
    int i; //indice for
    int posizione_stazione;
    int posizione_stazione_arrivo;
    char *token;
    struct Autostrada autostrada = autostrada_create ();

    while (fgets(input, MAX_LENGTH, stdin) != NULL) {
        input[strcspn(input, "\n")] = '\0'; // Remove the newline character
        command = strtok(input, " "); // prendo il comando
        //esempio di stringa aggiungi-stazione 10 3 100 200 300
        if (strcmp(command, "aggiungi-stazione") == 0) {
            token = strtok(NULL, " "); // prendo la posizione della stazione
            posizione_stazione = atoi(token);
            fprintf(stderr, "posizione stazione da aggiungere: %d\n", posizione_stazione);
            //autostrada_stazione_create_and_insert(&autostrada, posizione_stazione);
            if (autostrada_contains(&autostrada, posizione_stazione)) {
                printf("non aggiunta\n");
            }
            else {
                struct Stazione* stazione = stazione_create(posizione_stazione);

                token = strtok(NULL, " "); // prendo il numero di macchine da inserire
                n = atoi(token);
                fprintf(stderr, "macchine da inserire: %d\n gittate: ", n);
                for (i = 0; i < n; i++) {
                    token = strtok(NULL, " "); // Get the next token
                    gittata = atoi(token); // Convert the token to an integer and store it in the array
                    fprintf(stderr, "%d ", gittata);
                    stazione_insert(stazione, gittata);
                }
                autostrada_insert_stazione(&autostrada, stazione);
                autostrada_print(&autostrada);
            }
        }
        else if (strcmp(command, "demolisci-stazione") == 0) {
            token = strtok(NULL, " "); // prendo la posizione della stazione
            posizione_stazione = atoi(token);
            fprintf(stderr, "posizione stazione da demolire: %d\n", posizione_stazione);
            if (autostrada_stazione_elimina_stazione(&autostrada, posizione_stazione)) {
                printf("demolita\n");
                autostrada_print(&autostrada);
            }
            else {
                printf("non demolita\n");
            }
            fprintf(stderr, "\n");
        }
        //aggiungi-auto distanza-stazione autonomia-auto-da-aggiungere
        else if (strcmp(command, "aggiungi-auto") == 0) {
            token = strtok(NULL, " "); // prendo la posizione della stazione
            posizione_stazione = atoi(token);
            fprintf(stderr, "posizione stazione in cui inserire auto: %d\n", posizione_stazione);
            token = strtok(NULL, " "); // prendo la posizione della stazione
            gittata = atoi(token);
            fprintf(stderr, "gittata macchina da inserire: %d\n", gittata);
            if (autostrada_stazione_aggiungi_auto(&autostrada, posizione_stazione, gittata)) {
                printf ("aggiunta\n");
                autostrada_print(&autostrada);
            }
            else {
                printf ("non aggiunta\n");
            }
            fprintf(stderr, "\n");
        }
        //rottama-auto distanza-stazione autonomia-auto-da-rottamare
        else if (strcmp(command, "rottama-auto") == 0) {
            token = strtok(NULL, " "); // prendo la posizione della stazione
            posizione_stazione = atoi(token);
            fprintf(stderr, "posizione stazione in cui rottamare auto: %d\n", posizione_stazione);
            token = strtok(NULL, " "); // prendo la posizione della stazione
            gittata = atoi(token);
            fprintf(stderr, "gittata macchina da rottamare: %d\n", gittata);
            if (autostrada_contains(&autostrada, posizione_stazione)) {
                if (autostrada_stazione_elimina_auto(&autostrada, posizione_stazione, gittata)) {
                    printf ("rottamata\n");
                    autostrada_print(&autostrada);
                }
                else {
                    printf ("non rottamata\n");
                }
            }
            else {
                printf ("non rottamata\n");
            }
            fprintf(stderr, "\n");
        }
        //pianifica-percorso distanza-stazione-partenza distanza-stazione-arrivo
        else if (strcmp(command, "pianifica-percorso") == 0) {
            token = strtok(NULL, " "); // prendo la posizione della stazione
            posizione_stazione = atoi(token);
            fprintf(stderr, "posizione partenza: %d\n", posizione_stazione);
            token = strtok(NULL, " "); // prendo la posizione della stazione
            posizione_stazione_arrivo = atoi(token);
            fprintf(stderr, "posizione arrivo: %d\n", posizione_stazione_arrivo);
            struct Percorso *percorso;
            percorso = autostrada_pianifica_percorso(&autostrada, posizione_stazione, posizione_stazione_arrivo);
            percorso_stampa_percorso(percorso);
            fprintf(stderr, "\n");
        }
        else {
            printf("Comando sconosciuto\n");
        }
    }

    return 0;
}

/*
int main() {
    char input[MAX_LENGTH];
    char *command; //comando da eseguire
    int n; //numero di macchine da inserire
    int gittata; //gittata
    int i; //indice for
    int posizione_stazione;
    int posizione_stazione_arrivo;
    char *token;
    struct Autostrada autostrada = autostrada_create ();

    while (fgets(input, MAX_LENGTH, stdin) != NULL) {
        input[strcspn(input, "\n")] = '\0'; // Remove the newline character
        command = strtok(input, " "); // prendo il comando
        //esempio di stringa aggiungi-stazione 10 3 100 200 300
        if (strcmp(command, "aggiungi-stazione") == 0) {
            token = strtok(NULL, " "); // prendo la posizione della stazione
            posizione_stazione = atoi(token);
            //printf("posizione stazione da aggiungere: %d\n", posizione_stazione);
            //autostrada_stazione_create_and_insert(&autostrada, posizione_stazione);
            if (autostrada_contains(&autostrada, posizione_stazione)) {
                printf("non aggiunta\n");
            }
            else {
                struct Stazione* stazione = stazione_create(posizione_stazione);

                token = strtok(NULL, " "); // prendo il numero di macchine da inserire
                n = atoi(token);
                //printf("macchine da inserire: %d\n gittate: ", n);
                for (i = 0; i < n; i++) {
                    token = strtok(NULL, " "); // Get the next token
                    gittata = atoi(token); // Convert the token to an integer and store it in the array
                    //printf("%d ", gittata);
                    stazione_insert(stazione, gittata);
                    //autostrada_stazione_aggiungi_auto(&autostrada, posizione_stazione, gittata);
                }
                autostrada_insert_stazione(&autostrada, stazione);
                printf("aggiunta\n");
                //printf("\n");
                //printf("\n");
                //autostrada_print(&autostrada);
                //printf("\n");
            }
        }
        else if (strcmp(command, "demolisci-stazione") == 0) {
            token = strtok(NULL, " "); // prendo la posizione della stazione
            posizione_stazione = atoi(token);
            //printf("posizione stazione da demolire: %d\n", posizione_stazione);
            if (autostrada_stazione_elimina_stazione(&autostrada, posizione_stazione)) {
                printf("demolita\n");
                //autostrada_print(&autostrada);
            }
            else {
                printf("non demolita\n");
            }
            //printf("\n");
        }
            //aggiungi-auto distanza-stazione autonomia-auto-da-aggiungere
        else if (strcmp(command, "aggiungi-auto") == 0) {
            token = strtok(NULL, " "); // prendo la posizione della stazione
            posizione_stazione = atoi(token);
            //printf("posizione stazione in cui inserire auto: %d\n", posizione_stazione);
            token = strtok(NULL, " "); // prendo la posizione della stazione
            gittata = atoi(token);
            //printf("gittata macchina da inserire: %d\n", gittata);
            if (autostrada_stazione_aggiungi_auto(&autostrada, posizione_stazione, gittata)) {
                printf ("aggiunta\n");
                //autostrada_print(&autostrada);
            }
            else {
                printf ("non aggiunta\n");
            }
            //printf("\n");
        }
            //rottama-auto distanza-stazione autonomia-auto-da-rottamare
        else if (strcmp(command, "rottama-auto") == 0) {
            token = strtok(NULL, " "); // prendo la posizione della stazione
            posizione_stazione = atoi(token);
            //printf("posizione stazione in cui rottamare auto: %d\n", posizione_stazione);
            token = strtok(NULL, " "); // prendo la posizione della stazione
            gittata = atoi(token);
            //printf("gittata macchina da rottamare: %d\n", gittata);
            if (autostrada_contains(&autostrada, posizione_stazione)) {
                if (autostrada_stazione_elimina_auto(&autostrada, posizione_stazione, gittata)) {
                    printf ("rottamata\n");
                    //autostrada_print(&autostrada);
                }
                else {
                    printf ("non rottamata\n");
                }
            }
            else {
                printf ("non rottamata\n");
            }
            //printf("\n");
        }
            //pianifica-percorso distanza-stazione-partenza distanza-stazione-arrivo
        else if (strcmp(command, "pianifica-percorso") == 0) {
            token = strtok(NULL, " "); // prendo la posizione della stazione
            posizione_stazione = atoi(token);
            //printf("posizione partenza: %d\n", posizione_stazione);
            token = strtok(NULL, " "); // prendo la posizione della stazione
            posizione_stazione_arrivo = atoi(token);
            //printf("posizione arrivo: %d\n", posizione_stazione_arrivo);
            struct Percorso *percorso;
            percorso = autostrada_pianifica_percorso(&autostrada, posizione_stazione, posizione_stazione_arrivo);
            percorso_stampa_percorso(percorso);
            //printf("\n");
        }
        else {
            printf("Comando sconosciuto\n");
        }
    }

    return 0;
}
*/