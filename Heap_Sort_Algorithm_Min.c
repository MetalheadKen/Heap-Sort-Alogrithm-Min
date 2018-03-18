#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct _Heap {
    int *data;
    int size;
} Heap;

int  Heap_Sort(int, Heap *, int);

int  Root(Heap *);
void Make_Heap(int, Heap *);
void Sift_Down(Heap *, int);
int  Remove_Keys(int, Heap *, int);

int main(void)
{
    int  length, find_index, find_value;
    Heap heap;

    printf("Please enter the length of data: ");
    scanf("%d", &length);

    heap.data = (int *) calloc(length + 1, sizeof(heap.data[0]));

    /* Get random values */
    srand((unsigned int) time(NULL));
    for (int i = 1; i <= length; i++) {
        heap.data[i] = rand() % length;
    }

    printf("\nRaw data is:\n ");
    for (int i = 1; i <= length; i++) {
        printf("%d  ", heap.data[i]);
    }

    printf("\n\nPlease enter the index you want to find : ");
    scanf("%d", &find_index);

    find_value = Heap_Sort(length, &heap, find_index);

    printf("\nThe %dth value is: %d\n", find_index, find_value);
    
    return 0;
}

int Heap_Sort(int length, Heap *heap, int find_index)
{
    Make_Heap(length, heap);
    return Remove_Keys(length, heap, find_index);
}

/* Construct a heap tree */
void Make_Heap(int length, Heap *heap)
{
    heap->size = length;
    
    /* Start from a depth of (d - 1) of tree */
    for (int i = length / 2; i >= 1; i--) {
        Sift_Down(heap, i);
    }
}

/* Pop items into the value */
int Remove_Keys(int length, Heap *heap, int find_index)
{
    int find_value;

    for (int i = length; i >= find_index; i--) {
        find_value = Root(heap);
    }

    return find_value;
}

/* Remove an item at the root node */
int Root(Heap *heap)
{
    int key_out;
    
    key_out       = heap->data[1];
    heap->data[1] = heap->data[heap->size];
    heap->size    = heap->size - 1;

    Sift_Down(heap, 1);

    return key_out;
}

/* Adjust the tree from index i to a heap tree */
void Sift_Down(Heap *heap, int i)
{
    int  parent, smaller_child;
    int  sift_key;
    bool spot_found;

    sift_key   = heap->data[i];
    parent     = i;
    spot_found = false;

    while (2 * parent <= heap->size && !spot_found) {
        if (2 * parent < heap->size && heap->data[2 * parent] > heap->data[2 * parent + 1]) {
            smaller_child = 2 * parent + 1;
        } else {
            smaller_child = 2 * parent;
        }

        if (sift_key > heap->data[smaller_child]) {
            heap->data[parent] = heap->data[smaller_child];
            parent = smaller_child;
        } else {
            spot_found = true;
        }
    }

    heap->data[parent] = sift_key;
}
