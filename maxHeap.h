//
// Created by Ante Marusic on 30/05/23.
//

#ifndef API_MAXHEAP_H
#define API_MAXHEAP_H
enum boolean {
    false,
    true
};

struct Heap {
    int *array;
    int dim;
    int heap_dim;
};

//public
struct Heap* max_heap_create ();
int max_heap_get_max (struct Heap *this);
void max_heap_print_array (struct Heap *this);
void max_heap_print_tree (struct Heap *this);
enum boolean max_heap_remove (struct Heap *this, int el);
enum boolean max_heap_insert (struct Heap *this, int el);
void max_heap_destroy (struct Heap *this);

//deprecated
struct Heap max_heap_create_stack ();

//private
void max_heap_ensure_capacity (struct Heap *this);
int parent (struct Heap *this, int i);
int left (struct Heap *this, int i);
int right (struct Heap *this, int i);
int max_heap_get (struct Heap *this, int i);
int left_index (int i);
int right_index (int i);
int parent_index (int i);
int max_heap_search (struct Heap *this, int el);
void max_heap_swap (struct Heap *this, int i, int j);
void max_heap_bubble_up (struct Heap *this, int index);
void max_heap_bubble_down (struct Heap *this, int index);
#endif //API_MAXHEAP_H
