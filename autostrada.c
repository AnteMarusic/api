/*
 * questa classe rappresenta l'autostrada, ovvero un array di stazioni ordinato per posizione crescente
 * ogni stazione contiene la posizione e un heap di macchine
 * sono implementati i metodi per inserire una stazione, per cercare una stazione, per creare una stazione
 * per rimuovere una stazione
 * per cercare il percorso tra due stazioni
 */


#include "autostrada.h"
#include "maxHeap.h"
#include <stdio.h>
#include <stdlib.h>

const int AUTOSTRADA_STARTING_DIM = 10;
const int INCREASE = 10;
const int INFINITE = 2147483647;

struct Autostrada autostrada_create () {
    struct Autostrada autostrada;
    autostrada.stazioni = malloc(sizeof(struct Stazione) * AUTOSTRADA_STARTING_DIM);
    autostrada.numero_stazioni = 0;
    autostrada.array_dim = AUTOSTRADA_STARTING_DIM;
    return autostrada;
}

/*
 * TODO: migliorarela ricerca del punto dove inserire
 * garantito che il valore non sia già presente nell'array
 * costo O(n)
 * penso che la max_heap_search del punto dove inserire si possa fare con una specie di binary search
 * @requires che la stazione non sia presente nell'autostrada
 */
void autostrada_insert_stazione (struct Autostrada *this, struct Stazione *to_insert) {
    int i;
    autostrada_ensure_capacity(this);

    for (i = 0; i < this->numero_stazioni; i++) {
        if (this->stazioni[i].posizione > to_insert->posizione) {
            break;
        }
    }
    for (int j = this->numero_stazioni; j > i; j--) {
        this->stazioni[j] = this->stazioni[j-1];
    }
    this->stazioni[i] = *to_insert;
    this->numero_stazioni++;
}

void autostrada_ensure_capacity (struct Autostrada *this) {
    if (this->numero_stazioni == this->array_dim) {
        struct Stazione *newArray = (struct Stazione*)malloc((this->numero_stazioni + INCREASE) * sizeof(struct Stazione));
        //controllo da levare
        if (newArray == NULL) {
            printf("allocazione fallita in ensure_capacity di Autostrada.\n");
        }
        for (int i = 0; i < this->array_dim; i++) {
            newArray[i] = this->stazioni[i];
        }
        free(this->stazioni);
        this->stazioni = newArray;
        this->array_dim = this->array_dim + INCREASE;
    }
}


enum boolean autostrada_contains (struct Autostrada *this, int geoPosizione) {
    //implementation of binary search
    if(autostrada_binary_search(this, geoPosizione) == -1) {
        return false;
    }
    else {
        return true;
    }
}

/*
 * @param element: posizione della stazione da cercare
 * restituisce l'indice a cui si trova la stazione cercata
 * usando binary search perchè l'array è ordinato in base alla posizione delle stazioni in ordine crescente
 */
int autostrada_binary_search (struct Autostrada *this, int element) {
    //implementation of binary search
    int start = 0;
    int end = this->numero_stazioni - 1;
    int middle = (start + end) / 2;
    while (start <= end) {
        if (this->stazioni[middle].posizione == element) {
            return middle;
        } else if (this->stazioni[middle].posizione < element) {
            start = middle + 1;
        } else {
            end = middle - 1;
        }
        middle = (start + end) / 2;
    }
    return -1;
}

void autostrada_print (struct Autostrada *this) {
    for (int i = 0; i < this->numero_stazioni; i++) {
        fprintf(stderr, "stazione %d: %d, range: %d, auto: ", i, this->stazioni[i].posizione, max_heap_get_max(this->stazioni[i].heap));
        max_heap_print_array(this->stazioni[i].heap);
        printf("\n");
    }
}

/*
 * @param geoPosizione: stazione da rimuovere
 * se la stazione è presente la rimuove, shifta tutto quello che c'è a destra di una geoPosizione verso sinistra e ritorna true
 * altrimenti non fa niente e ritorna false
 */
enum boolean autostrada_stazione_elimina_stazione (struct Autostrada *this, int geoPosizione) {
    int index = autostrada_binary_search(this, geoPosizione);
    if (index == -1) {
        return false;
    }
    else {
        if (index == this->numero_stazioni - 1) {
            this->numero_stazioni--;
            return true;
        }
        else {
            for (int i = index; i < this->numero_stazioni - 1; i++) {
                this->stazioni[i] = this->stazioni[i+1];
            }
            this->numero_stazioni--;
            return true;
        }
    }
}

//private
int autostrada_stazione_get_gittata (struct Autostrada *this, int indice) {
    return max_heap_get_max(this->stazioni[indice].heap);
}

struct Percorso* autostrada_pianifica_percorso (struct Autostrada *this, int geoPartenza, int geoArrivo) {
    int *ranges = malloc(sizeof(int) * this->numero_stazioni);
    int *posizioni = malloc(sizeof(int) * this->numero_stazioni);
    printf("numero stazioni: %d\n", this->numero_stazioni);
    struct Percorso *temp;
    for (int i = 0; i < this->numero_stazioni; i ++) {
        ranges[i] = autostrada_stazione_get_gittata(this, i);
        posizioni[i] = this->stazioni[i].posizione;
    }
    fprintf(stderr, "posizioni: ");
    stampa_array(posizioni, this->numero_stazioni);
    fprintf(stderr, "\n");
    fprintf(stderr, "ranges: ");
    stampa_array(ranges, this->numero_stazioni);
    fprintf(stderr, "\n");
    temp = calcola_percorso_test (posizioni, this->numero_stazioni, ranges, geoPartenza, geoArrivo);
    free(ranges);
    free(posizioni);
    return temp;
}

void percorso_stampa_percorso (struct Percorso *percorso) {
    int i;
    printf ("Percorso: ");
    if (percorso == NULL || percorso->dim == 0) {
        printf("NULL\n");
    }
    else {
        for (i = 0; i < percorso->dim; i++) {
            printf("%d ", percorso->posizioni[i]);
        }
    }
    printf ("\n");
}

enum boolean autostrada_stazione_aggiungi_auto (struct Autostrada *this, int geoPosizione, int gittata) {
    int indice = autostrada_binary_search(this, geoPosizione);
    if (indice < 0) {
        return false;
    }
    return max_heap_insert (this->stazioni[indice].heap, gittata);
}

struct Stazione* stazione_create (int posizione) {
    struct Stazione *stazione = malloc(sizeof(struct Stazione));
    stazione->heap = max_heap_create();
    stazione->posizione = posizione;
    return stazione;
}

enum boolean stazione_insert (struct Stazione *this, int gittata) {
    return max_heap_insert(this->heap, gittata);
}

/*
 * @requires che la stazione esiste
 */
enum boolean autostrada_stazione_elimina_auto (struct Autostrada *this, int geoPosizione, int gittata) {
    int index = autostrada_binary_search(this, geoPosizione);
    return max_heap_remove(this->stazioni[index].heap, gittata);
}

///////////////////////////////////////////

int general_binary_search (int *posizioni, int dim, int element) {
    //implementation of binary search
    int start = 0;
    int end = dim - 1;
    int middle = (start + end) / 2;
    while (start <= end) {
        if (posizioni[middle] == element) {
            return middle;
        } else if (posizioni[middle] < element) {
            start = middle + 1;
        } else {
            end = middle - 1;
        }
        middle = (start + end) / 2;
    }
    return -1;
}

void stampa_array (int *array, int dim) {
    for (int i = 0; i < dim; i++) {
        fprintf(stderr, "%d ", array[i]);
    }
}

/*
 * TODO gestire il caso limite partenza == arrivo
 * parametri
 * posizioni sarebbe l'array che contiene le posizioni di TUTTE le stazioni
 * ranges: array che contiene le gittate di TUTTE le posizioni. è indicizzato come posizioni
 * posizioni_dim è la dimensione di posizioni (che è uguale a quella di ranges)
 * partenza: posizione della stazione di partenza
 * arrivo: posizione della stazione di arrivo
 *
 * variabili locali
 * costi: array di costi
 * precendente: array di precedenti
 * dim: dimensione dell'array di costi e di precedenti
 * per rendere la funzione più testabile gli passo degli array, non la struct in cui la gittata si dovrebbe ricavare dall'albero delle gittate
 * in entrambi i versi di percorrenza costi e precedente si riempiono da sinistra verso destra
*/
struct Percorso* calcola_percorso_test (int *posizioni, int posizioni_dim, int *ranges, int partenza, int arrivo) {
    int index_partenza = general_binary_search(posizioni, posizioni_dim, partenza);
    int index_arrivo = general_binary_search(posizioni, posizioni_dim, arrivo);
    if (index_partenza == -1 || index_arrivo == -1) {
        return NULL;
    } else {
        if (index_partenza < index_arrivo) {
            return calcola_percorso_avanti (posizioni, posizioni_dim, ranges, partenza, arrivo, index_partenza, index_arrivo);
        }
        else {
            return calcola_percorso_indietro (posizioni, posizioni_dim, ranges, partenza, arrivo, index_partenza, index_arrivo);
        }
    }
}


/*
 * TODO mettere un controllo che permette di bloccare il ciclo prima nel caso in cui è impossibile che ci sia un percorso
 * ad esempio se dalla prima stazione non esce nessun arco sono fregato
 */
struct Percorso* calcola_percorso_avanti (int *posizioni, int posizioni_dim, int *ranges, int partenza, int arrivo, int index_partenza, int index_arrivo) {
    int *costi;
    int *precedente;
    int precedente_dim; //dimensione dell'array costi e precedente e quindi numero di iterazioni del ciclo
    int range; //massimo range della stazione i-esima
    int i; //for index
    int j; //while index
    //enum boolean flag = true;
    //inizializzazione degli array di costi e precedenti
    precedente_dim = index_arrivo - index_partenza + 1;
    costi = malloc(sizeof(int) * precedente_dim);
    precedente = malloc(sizeof(int) * precedente_dim);
    for (i = 0; i < precedente_dim; i++) {
        costi[i] = INFINITE;
        precedente[i] = -1;
    }
    costi[0] = 0;
    fprintf(stderr, "costi: ");
    stampa_array(costi, precedente_dim);
    fprintf(stderr, "\nprecedente: ");
    stampa_array(precedente, precedente_dim);
    fprintf(stderr, "\n");
    //compilazione degli array di costi e precedenti

    for (i = index_partenza; i < index_arrivo; i++) {
        if (costi[i-index_partenza] == INFINITE) { //controllo di impossibilità di fare il percorso
            return NULL;
        }
        /*
        if (!flag) { //sbagliatooooo
            return NULL;
        }
        flag = false;
         */
        fprintf(stderr, "i: %d\n", i); //debug
        range = ranges[i]; //prendo il range corrente
        j = i + 1; //j scorre tutti i successivi
        while (j <= index_arrivo && posizioni[j] <= posizioni[i] + range) {
            fprintf(stderr, "j: %d\n", j);
            if (costi[j - index_partenza] > costi[i - index_partenza] + 1) { // se il costo è uguale non sostituisco (previlegio la stazione che viene prima in ordine)
                costi[j - index_partenza] = costi[i - index_partenza] + 1;
                precedente[j - index_partenza] = i;
                fprintf(stderr, "costi: ");
                stampa_array(costi, precedente_dim);
                fprintf(stderr, "\n precedente: ");
                stampa_array(precedente, precedente_dim);
                //flag = true;
            } else {
                fprintf(stderr, "non aggiorno il costo \n");
            }
            j++;
        }
    }
    if (precedente[precedente_dim - 1] == -1) {
        return NULL;
    } else {
        //inizializzazione array del percorso
        int percorso_dim = costi[precedente_dim - 1] + 1;
        int *percorso = malloc(sizeof(int) * percorso_dim); //dimensione = costo + 1 (fine percorso)
        for (i = 0; i < percorso_dim; i++) {
            percorso[i] = 0;
        }
        struct Percorso *p = malloc(sizeof(struct Percorso));
        p->dim = percorso_dim;
        int index = precedente[precedente_dim - 1];
        int costo = costi[precedente_dim - 1];
        percorso[percorso_dim - 1] = arrivo;
        while (costo > 0) {
            percorso[costo - 1] = posizioni[index];
            index = precedente[index - index_partenza];
            costo--;
        }
        p->posizioni = percorso;
        return p;
    }
}
struct Percorso* calcola_percorso_indietro (int *posizioni, int posizioni_dim, int *ranges, int partenza, int arrivo, int index_partenza, int index_arrivo) {
    int *costi;
    int *precedente;
    int precedente_dim; //dimensione dell'array costi e precedente e quindi numero di iterazioni del ciclo
    int range; //massimo range della stazione i-esima
    int i; //for index
    int j; //while index
    //inizializzazione costi e precedente
    precedente_dim = index_partenza - index_arrivo + 1;
    costi = malloc(sizeof(int) * precedente_dim);
    precedente = malloc(sizeof(int) * precedente_dim);
    for (i = 0; i < precedente_dim; i++) {
        costi[i] = INFINITE;
        precedente[i] = -1;
    }
    costi[precedente_dim - 1] = 0;
    fprintf(stderr, "costi: ");
    stampa_array(costi, precedente_dim);
    fprintf(stderr, "\nprecedente: ");
    stampa_array(precedente, precedente_dim);
    fprintf(stderr, "\n");
    //compilazione degli array di costi e precedenti
    for (i = index_partenza; i > index_arrivo; i--) {
        if (costi[i-index_arrivo] == INFINITE) {
            return NULL;
        }
        fprintf(stderr, "i: %d\n", i);
        range = ranges[i];
        j = i - 1;
        while (j >= index_arrivo && posizioni[j] >= posizioni[i] - range) {
            fprintf(stderr, "j: %d\n", j);
            if (costi[j - index_arrivo] >= costi[i - index_arrivo] + 1) { //se il costo è uguale sostituisco (previlegio la stazione che viene prima in ordine crescente)
                costi[j - index_arrivo] = costi[i - index_arrivo] + 1;
                precedente[j - index_arrivo] = i;
                fprintf(stderr, "costi: ");
                stampa_array(costi, precedente_dim);
                fprintf(stderr, "\nprecedente: ");
                stampa_array(precedente, precedente_dim);
                fprintf(stderr, "\n");
            }
            else {
                fprintf (stderr, "costo peggiore\n");
            }
            j--;
        }
    }
    if (precedente[0] == -1) {
        return NULL;
    } else {
        int percorso_dim = costi[0] + 1;
        int *percorso = malloc(sizeof(int) * percorso_dim);
        for (i = 0; i < percorso_dim; i++) {
            percorso[i] = 0;
        }
        struct Percorso *p = malloc(sizeof(struct Percorso));
        p->dim = percorso_dim;

        int index = precedente[0];
        int costo = costi[0];
        percorso[percorso_dim - 1] = arrivo;
        while (costo > 0) {
            percorso[costo - 1] = posizioni[index];
            stampa_array(percorso, percorso_dim);
            costo--;
        }
        p->posizioni = percorso;
        return p;
    }
    /*
        int index = precedente[precedente_dim - 1];
        int costo = costi[precedente_dim - 1];
        percorso[percorso_dim - 1] = arrivo;
        while (costo > 0) {
            percorso[costo - 1] = posizioni[index];
            stampa_array(percorso, percorso_dim);
            index = precedente[index - index_partenza];
            costo--;
        }
        p->posizioni = percorso;
        return p;
    }
     */
}


/*
 * int* autostrada_pianifica_percorso (struct Autostrada *this, int partenza, int arrivo) {
    int *costi;
    int *precedente;
    int dim; //dimensione dell'array costi e precedente e quindi numero di iterazioni del ciclo
    int range; //massimo range della stazione i-esima
    int i; //for index
    int j; //while index

    int index_partenza = autostrada_binary_search(this, partenza);
    int index_arrivo = autostrada_binary_search(this, arrivo);
    if (index_partenza == -1 || index_arrivo == -1) {
        return NULL;
    }
    else {
        if(index_partenza < index_arrivo) {
            dim = index_arrivo - index_partenza + 1;
        }
        else {
            dim = index_partenza - index_arrivo + 1;
        }
        costi = malloc(sizeof(int) * dim);
        precedente = malloc(sizeof(int) * dim);
        for (i = 0; i < dim; i++) {
            costi[i] = INFINITE;
            precedente[i] = INFINITE;
        }
        for (i = 0; i < dim; i ++) {
            range = max_heap_get_max(&this->stazioni[index_partenza + i].heap);
            j = i + 1;
            while (j <= index_arrivo && this->stazioni[j].posizione <= range) {
                if (costi[j] > costi[i] + 1) {
                    costi[j] = costi[i] + 1;
                    precedente[j] = i;
                }
                j++;
            }
        }
        if (precedente[dim - 1] == INFINITE) {
            return NULL;
        }
        else {
            int *percorso = malloc(sizeof(int) * costi[dim - 1]);
            int index = dim - 1;
            int k = costi[dim - 1] - 1;
            while (index != INFINITE) {
                percorso[k] = this->stazioni[index_partenza + index].posizione;
                index = precedente[index];
                k--;
            }
            return percorso;
        }
    }
}*/

/*
 *     int *costi;
    int *precedente;
    int precedente_dim; //dimensione dell'array costi e precedente e quindi numero di iterazioni del ciclo
    int range; //massimo range della stazione i-esima
    int i; //for index
    int j; //while index

    int index_partenza = general_binary_search(posizioni, posizioni_dim, partenza);
    int index_arrivo = general_binary_search(posizioni, posizioni_dim, arrivo);
    if (index_partenza == -1 || index_arrivo == -1) {
        return NULL;
    } else {
        //inizializzazione degli array di costi e precedenti
        if (index_partenza < index_arrivo) {
            precedente_dim = index_arrivo - index_partenza + 1;
        } else {
            precedente_dim = index_partenza - index_arrivo + 1;
        }
        costi = malloc(sizeof(int) * precedente_dim);
        precedente = malloc(sizeof(int) * precedente_dim);
        for (i = 0; i < precedente_dim; i++) {
            costi[i] = INFINITE;
            precedente[i] = -1;
        }
        if (index_partenza < index_arrivo) {
            costi[0] = 0;
        } else {
            costi[precedente_dim - 1] = 0;
        }
        printf("costi: ");
        stampa_array(costi, precedente_dim);
        printf("precedente: ");
        stampa_array(precedente, precedente_dim);
        //compilazione degli array di costi e precedenti
        if (index_partenza < index_arrivo) {
            for (i = index_partenza; i < index_arrivo; i ++) {
                printf("i: %d\n", i); //debug
                range = ranges[i]; //prendo il range corrente
                j = i + 1; //j scorre tutti i successivi
                while (j <= index_arrivo && posizioni[j] <= posizioni[i] + range) {
                    printf("j: %d\n", j);
                    if (costi[j - index_partenza] > costi[i - index_partenza] + 1) { // se il costo è uguale non sostituisco (previlegio la stazione che viene prima in ordine)
                        costi[j - index_partenza] = costi[i - index_partenza] + 1;
                        precedente[j - index_partenza] = i;
                        printf("costi: ");
                        stampa_array(costi, precedente_dim);
                        printf("precedente: ");
                        stampa_array(precedente, precedente_dim);
                    }
                    else {
                        printf ("non aggiorno il costo \n");
                    }
                    j++;
                }
            }
        }
        else { //index_partenza > index_arrivo
            for (i = index_partenza; i > index_arrivo; i--) {
                printf("i: %d\n", i);
                range = ranges[i];
                j = i - 1;
                while (j >= index_arrivo && posizioni[j] >= posizioni[i] - range) {
                    printf("j: %d\n", j);
                    if (costi[precedente_dim - j - ] > costi[i - index_arrivo] + 1) {
                        costi[j - index_arrivo] = costi[i - index_arrivo] + 1;
                        precedente[j - index_arrivo] = i;
                        printf("costi: ");
                        stampa_array(costi, precedente_dim);
                        printf("precedente: ");
                        stampa_array(precedente, precedente_dim);
                    }
                    j--;
                }
            }
        }
        if (index_partenza < index_arrivo) {
            if (precedente[precedente_dim - 1] == INFINITE) {
                return NULL;
            }
            else {
                //inizializzazione array del percorso
                int percorso_dim = costi[precedente_dim - 1] + 1;
                int *percorso = malloc(sizeof(int) * percorso_dim); //dimensione = costo + 1 (fine percorso)
                for (i = 0; i < percorso_dim; i++) {
                    percorso[i] = 0;
                }
                struct Percorso *p = malloc(sizeof(struct Percorso));
                p->dim = percorso_dim;
                int index = precedente [precedente_dim - 1];
                int costo = costi[precedente_dim - 1];
                percorso[percorso_dim - 1] = arrivo;
                while (costo > 0) {
                    percorso[costo - 1] = posizioni[index];
                    stampa_array(percorso, percorso_dim);
                    index = precedente[index - index_partenza];
                    costo--;
                }
                p->posizioni = percorso;
                return p;
            }
        } else {
            if (precedente[0] == INFINITE) {
                return NULL;
            } else {
                int *percorso = malloc(sizeof(int) * costi[0]);
                for (i = 0; i < costi[0]; i++) {
                    percorso[i] = 0;
                }
                struct Percorso *p = malloc(sizeof(struct Percorso));
                p->dim = costi[0];
                int index = index_arrivo;
                int k = costi[0];
                while (k > 0) {
                    percorso[k] = posizioni[index];
                    stampa_array(percorso, costi[0]);
                    index = precedente[index];
                    k--;
                }
                p->posizioni = percorso;
                return p;
            }
        }
    }
 */
