//
// Created by Ante Marusic on 08/06/23.
//

#ifndef API_AUTOSTRADA_H
#define API_AUTOSTRADA_H
#include "maxHeap.h"
#include "utility.h"
struct Stazione {
    struct Heap *heap;
    int posizione;
};
struct Autostrada {
    struct Stazione *stazioni;
    int numero_stazioni;
    int array_dim;
};
struct Percorso {
    int *posizioni;
    int dim;
};

//da fare
//public


//public
struct Autostrada autostrada_create ();
enum boolean autostrada_contains (struct Autostrada *this, int geoPosizione);
struct Stazione* stazione_create (int posizione);
enum boolean stazione_insert(struct Stazione *this, int gittata);
void autostrada_print (struct Autostrada *this);
enum boolean autostrada_stazione_elimina_stazione (struct Autostrada *this, int geoPosizione);
struct Percorso* autostrada_pianifica_percorso (struct Autostrada *this, int geoPartenza, int geoArrivo);
void percorso_stampa_percorso (struct Percorso *percorso);
enum boolean autostrada_stazione_aggiungi_auto (struct Autostrada *this, int geoPosizione, int gittata);
void autostrada_insert_stazione (struct Autostrada *this, struct Stazione *to_insert);
enum boolean autostrada_stazione_elimina_auto (struct Autostrada *this, int geoPosizione, int gittata);

//test
struct Percorso* calcola_percorso_test (int *posizioni, int posizioni_dim, int *ranges, int partenza, int arrivo);
struct Percorso* calcola_percorso_avanti (int *posizioni, int posizioni_dim, int *ranges, int partenza, int arrivo, int index_partenza, int index_arrivo);
struct Percorso* calcola_percorso_indietro (int *posizioni, int posizioni_dim, int *ranges, int partenza, int arrivo, int index_partenza, int index_arrivo);
int general_binary_search (int *posizioni, int dim, int element);
void stampa_array (int *array, int dim);

//private
void autostrada_ensure_capacity (struct Autostrada *this);
int autostrada_binary_search (struct Autostrada *this, int element);
int autostrada_stazione_get_gittata (struct Autostrada *this, int indice);
#endif //API_AUTOSTRADA_H
