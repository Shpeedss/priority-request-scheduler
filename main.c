#include <stdio.h>
#include <string.h>
#include "priority_queue.h"
#include "rfc_parser.h"

int main() {
    MinHeap* gateway_queue;
    APIRequest req1, req2, req3;
    APIRequest processed_req;

    /* Heap'i baslangic kapasitesiyle olusturuyoruz */
    gateway_queue = create_heap(2);

    /* 1. Istek - Standart API Cagirisi */
    req1.request_id = 101;
    strcpy(req1.method, "GET");
    strcpy(req1.path, "/api/users");
    req1.urgency = parse_urgency("u=5, i=?0"); /* Urgency 5 */

    /* 2. Istek - Odeme Islemi (Kritik) */
    req2.request_id = 102;
    strcpy(req2.method, "POST");
    strcpy(req2.path, "/api/checkout");
    req2.urgency = parse_urgency("u=1, i=?1"); /* Urgency 1 (En Oncelikli) */

    /* 3. Istek - Arka plan verisi */
    req3.request_id = 103;
    strcpy(req3.method, "GET");
    strcpy(req3.path, "/api/assets");
    req3.urgency = parse_urgency("u=7"); /* Urgency 7 (En Dusuk) */

    printf("Gelen Istekler Kuyruga Ekleniyor...\n");
    insert(gateway_queue, req1);
    insert(gateway_queue, req2);
    insert(gateway_queue, req3);
    
    printf("\n--- API Gateway Islem Sirasi (Priority Request Scheduler) ---\n");
    while (!is_empty(gateway_queue)) {
        processed_req = extract_min(gateway_queue);
        printf("[ISLENDI] ID: %d | Urgency: %d | Method: %s | Path: %s\n", 
               processed_req.request_id, processed_req.urgency, 
               processed_req.method, processed_req.path);
    }

    /* Dinamik bellek alanlarini temizleme (Sifir Bellek Sizintisi garantisi) */
    destroy_heap(gateway_queue);
    
    return 0;
}
