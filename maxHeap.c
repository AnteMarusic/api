/*
 * questo MaxHeap gestisce al massimo 512 interi positivi.
 * fornisce la possibilità di inserire un elemento nuovo
 * eliminare un elemento esistente
 * ritornare il massimo
 * eliminare l'intero heap
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maxHeap.h"

const int MAX_HEAP_STARTING_DIM = 8;
//moltiplico la capacità dell'array da estendere per NEW_CAPACITY;
const int NEW_CAPACITY = 2;

/*
 * costruttore del max heap
 */
struct Heap max_heap_create_stack () {
    struct Heap heap;
    int *newArray = (int*)malloc(MAX_HEAP_STARTING_DIM * sizeof(int));
    heap.array = newArray;
    heap.dim = MAX_HEAP_STARTING_DIM;
    heap.heap_dim = 0;

    return heap;
}

struct Heap* max_heap_create () {
    struct Heap *heap = malloc (sizeof (struct Heap));
    int *newArray = (int*)malloc(MAX_HEAP_STARTING_DIM * sizeof(int));
    heap->array = newArray;
    heap->dim = MAX_HEAP_STARTING_DIM;
    heap->heap_dim = 0;
    return heap;
}


/*
 * metodo privato da chiamare prima degli inserimenti. garantisce che ci sia sempre spazio nell'array che contiene l'heap
 */
void max_heap_ensure_capacity (struct Heap *this) {
    if (this->heap_dim == this->dim) {
        int *newArray = (int*)malloc(this->dim * NEW_CAPACITY * sizeof(int));
        //controllo da levare
        if (newArray == NULL) {
            printf("allocazione fallita in ensure_capacity di maxHeap.\n");
        }
        for (int i = 0; i < this->dim; i++) {
            newArray[i] = this->array[i];
        }
        free(this->array);
        this->array = newArray;
        this->dim = this->dim * NEW_CAPACITY;
    }
}

int parent (struct Heap *this, int i) {
    return this->array[parent_index(i)];
}

int left (struct Heap *this, int i) {
    return this->array[left_index(i)];
}

int right (struct Heap *this, int i) {
    return this->array[right_index(i)];
}

int max_heap_get (struct Heap *this, int i) {
    return this->array[i];
}

int left_index (int i) {
    return i*2 + 1;
}

int right_index (int i) {
    return i*2 + 2;
}

int parent_index (int i){
    return (i - 1)/2;
}

int max_heap_get_max (struct Heap *this) {
    if (this->heap_dim == 0) {
        return -1;
    }
    return this->array[0];
}

/*
 * rimozione di un elemento:
 * (1) cerco l'elemento da rimuovere con una max_heap_search binaria sull'array che rappresenta l'heap
 * (2) ogni sottoalbero di un heap è a sua volta un heap, quindi una volta trovato l'elemento lo rimuovo e lo scambio con
 *      l'ultimo elemento dell'heap. Ora chiamo la procedura che fa bubble down dell'elemento appena inserito
 * @returns true se l'elemento è stato rimosso (esisteva e ora non c'è più)
 *      false se l'elemento non è stato rimosso (perchè non esisteva)
 */
enum boolean max_heap_remove (struct Heap *this, int el) {
    int index = max_heap_search(this, el);
    if (index == -1) {
        return false;
    }
    this->array[index] = this->array[this->heap_dim - 1];
    this->heap_dim--;
    max_heap_bubble_down(this, index);
    return true;
}

void max_heap_bubble_down (struct Heap *this, int index) {
    int max = index;
    if (left_index(index) < this->heap_dim && left(this, index) > max_heap_get(this, max)) {
        max = left_index(index);
    }
    if (right_index(index) < this->heap_dim && right(this, index) > max_heap_get(this, max)) {
        max = right_index(index);
    }
    if (max != index) {
        max_heap_swap(this, index, max);
        max_heap_bubble_down(this, max);
    }
}

/*
 * cerca l'elemento nell'heap. le dimensioni dell'heap vengono prese dalla struct che rappresenta l'heap
 * @returns l'indice se l'elemento è presente, -1 altrimenti
 * O(n) può essere migliorata la costante sfruttando il fatto che i discendenti di un elemento sono sempre minori del padre
 */
int max_heap_search (struct Heap *this, int el) {
    int i = 0;
    for (i = 0; i < this->heap_dim; i++) {
        if (this->array[i] == el) {
            return i;
        }
    }
    return -1;
}

/*
 * metodo privato che scambia di posizione il primo elemento con il secondo
 */
void max_heap_swap (struct Heap *this, int i, int j) {
    int temp = this->array[i];
    this->array[i] = this->array[j];
    this->array[j] = temp;
}

/*
 * metodo privato che fa risalire un elemento fino alla posizione corretta
 * @param index è l'indice dell'elemento da far risalire
 */
void max_heap_bubble_up (struct Heap *this, int index) {
    if (index == 0) {
        return;
    }
    if (max_heap_get(this, index) > parent(this, index)) {
        max_heap_swap(this, index, parent_index(index));
        max_heap_bubble_up(this, parent_index(index));
    }
}

/*
 * inserisce un elemento nell'heap e lo fa risalire fino alla posizione corretta
 * @returns true se l'elemento è stato inserito
 *     false se l'elemento non è stato inserito (perchè già esisteva)
 */
enum boolean max_heap_insert (struct Heap *this, int el) {
    int temp = max_heap_search(this, el);
    if (temp != -1) {
        return false;
    }
    else {
        //non è presente quindi lo inserisco
        max_heap_ensure_capacity(this);
        this->array[this->heap_dim] = el;
        this->heap_dim++;
        max_heap_bubble_up(this, this->heap_dim - 1);
        return true;
    }
}

/*
 * metodo che stampa l'heap
 */
void max_heap_print_array (struct Heap *this) {
    if (this->heap_dim == 0) {
        SHOW("vuoto");
    }
    for (int i = 0; i < this->heap_dim; i++) {
        SHOW("%d ", this->array[i]);
    }
}

/*
 *  metodo che stampa l'heap come se fosse un albero è una DFS dell'heap
 */
void max_heap_print_tree(struct Heap *this) {
    int i, pow = 1, tot = 0;
    for (i = 0; i < this->heap_dim; i ++) {
        printf("%d ", max_heap_get(this, i));
        if (i == tot) {
            pow *= 2;
            tot = tot + pow;
            printf("\n");
        }
    }

}

void max_heap_destroy (struct Heap *this) {
    free(this->array);
    free(this);
}
