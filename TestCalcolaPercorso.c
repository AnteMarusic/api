#include "autostrada.h"
#include <stdio.h>
#include <stdlib.h>

/*
int main () {
    int posizioni[] = {6,8,10,12,14,16,18,20,22,24,26,28};
    int ranges[] = {2,2,2,2,2,2,2,2,2,2,2,2};
    int partenza = 22;
    int arrivo = 8;
    struct Percorso *percorso;
    //int *percorso = calcola_percorso(posizioni, ranges, partenza, arrivo);
    //stampa_percorso(percorso);
    int partenza_index = general_binary_search(posizioni, sizeof(posizioni)/sizeof(int), partenza);
    int arrivo_index = general_binary_search(posizioni,sizeof(posizioni)/sizeof(int), arrivo);
    printf("Partenza index: %d\n", partenza_index);
    printf("Arrivo index: %d\n", arrivo_index);
    percorso = autostrada_pianifica_percorso(posizioni, sizeof(posizioni)/sizeof(int), ranges, partenza, arrivo);
    percorso_stampa_percorso(percorso);
    return 0;
}
*/

/*test cases
    int posizioni[] = {10,20,30,40,50,60,70,80,90,100,120};
    int ranges[] = {20,20,20,20,20,20,20,20,20,20,20};

    int posizioni[] = {2,13,15,16,22,24,27,33,35,36,41,42};
    int ranges[] = {10,10,10,10,10,10,10,10,10,10,10,10};

    int posizioni[] = {6,8,10,12,14,16,18,20,22,24,26,28};
    int ranges[] = {2,2,2,2,2,2,2,2,2,2,2,2};
 */