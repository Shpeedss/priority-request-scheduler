# RFC 9213 Uyumlu API Gateway İstek Zamanlayıcısı

Bu proje, bir sisteme gelen API isteklerini sıradan bir "ilk giren ilk çıkar" mantığıyla değil, RFC 9213 (Extensible HTTP Priorities) standardına uygun olarak kritiklik seviyesine göre işleyen bir simülasyondur.

## Teknik Özellikler ve Kazanımlar
* **C89/C90 Standartları:** Gömülü sistem derleyicileriyle tam uyumluluk.
* **Veri Yapısı:** Zaman karmaşıklığını minimuma indirmek için sıradan diziler yerine **Min-Heap** (Minimum Yığıt) veri yapısı kullanılmıştır. En öncelikli işleme erişim maliyeti O(1)'dir.
* **Dinamik Bellek Yönetimi:** Gelen istek sayısına göre kapasite `realloc` ile dinamik olarak artırılır. İşlem bitiminde `free()` kullanılarak %100 sıfır bellek sızıntısı (zero memory leak) sağlanmıştır.
* **Modüler Mimari:** Kavramların Ayrılığı (Separation of Concerns) ilkesi gereği sistem 3 izole katmana bölünmüştür.

## Dosya Yapısı (Mimari)
1. `rfc_parser.h` & `rfc_parser.c`: HTTP başlıklarından urgency (aciliyet) değerini ayrıştıran katman.
2. `priority_queue.h` & `priority_queue.c`: Min-Heap algoritması ve bellek yönetiminin yapıldığı çekirdek katman.
3. `main.c`: Sistemin simüle edildiği ve test edildiği ana katman.
