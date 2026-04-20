#include "priority_queue.h"
#include <stdlib.h>
#include <stdio.h>

/* Yardimci Takas Fonksiyonu */
void swap(APIRequest *a, APIRequest *b) {
    APIRequest temp = *a;
    *a = *b;
    *b = temp;
}

MinHeap* create_heap(int initial_capacity) {
    MinHeap* h = (MinHeap*)malloc(sizeof(MinHeap));
    if (h == NULL) return NULL;
    
    h->size = 0;
    h->capacity = initial_capacity;
    h->heap_array = (APIRequest*)malloc(initial_capacity * sizeof(APIRequest));
    
    if (h->heap_array == NULL) {
        free(h);
        return NULL;
    }
    return h;
}

void destroy_heap(MinHeap* h) {
    if (h != NULL) {
        if (h->heap_array != NULL) {
            free(h->heap_array);
        }
        free(h);
    }
}

/* Yukari Dogru Duzenleme (Insert sonrasi) */
void heapify_up(MinHeap* h, int index) {
    int parent = (index - 1) / 2;
    /* Kucuk degerlerin ust dugumlere cikmasi saglanir */
    while (index > 0 && h->heap_array[index].urgency < h->heap_array[parent].urgency) {
        swap(&h->heap_array[index], &h->heap_array[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

/* Asagi Dogru Duzenleme (Extract sonrasi) */
void heapify_down(MinHeap* h, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < h->size && h->heap_array[left].urgency < h->heap_array[smallest].urgency) {
        smallest = left;
    }

    if (right < h->size && h->heap_array[right].urgency < h->heap_array[smallest].urgency) {
        smallest = right;
    }

    if (smallest != index) {
        swap(&h->heap_array[index], &h->heap_array[smallest]);
        heapify_down(h, smallest);
    }
}

void insert(MinHeap* h, APIRequest req) {
    /* Kapasite dolduysa dinamik olarak realloc ile genislet */
    if (h->size == h->capacity) {
        h->capacity *= 2;
        h->heap_array = (APIRequest*)realloc(h->heap_array, h->capacity * sizeof(APIRequest));
    }
    
    h->heap_array[h->size] = req;
    heapify_up(h, h->size);
    h->size++;
}

APIRequest extract_min(MinHeap* h) {
    APIRequest min_req;
    min_req = h->heap_array[0]; /* En yuksek oncelikli (en kucuk urgency) islem */
    
    h->heap_array[0] = h->heap_array[h->size - 1];
    h->size--;
    heapify_down(h, 0);
    
    return min_req;
}

int is_empty(MinHeap* h) {
    return h->size == 0;
}
