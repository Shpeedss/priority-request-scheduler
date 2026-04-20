#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

/* API Istegi Veri Yapisi */
typedef struct {
    int request_id;
    int urgency; /* Öncelik degeri (Min-Heap icin anahtar) */
    char method[10];
    char path[50];
} APIRequest;

/* Dinamik Min-Heap Veri Yapisi */
typedef struct {
    APIRequest *heap_array;
    int size;
    int capacity;
} MinHeap;

/* Fonksiyon Prototipleri */
MinHeap* create_heap(int initial_capacity);
void destroy_heap(MinHeap* h);
void insert(MinHeap* h, APIRequest req);
APIRequest extract_min(MinHeap* h);
int is_empty(MinHeap* h);

#endif
