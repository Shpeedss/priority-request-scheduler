#include "rfc_parser.h"
#include <string.h>

int parse_urgency(const char* header) {
    const char* ptr;
    /* Gelen header icinde "u=" kismini arariz */
    ptr = strstr(header, "u=");
    if (ptr != NULL) {
        /* RFC 9213'e gore urgency 0 (en yuksek) ile 7 (en dusuk) arasindadir. */
        return ptr[2] - '0';
    }
    /* Eger belirtilmemisse varsayilan urgency degeri 3'tur. */
    return 3;
}
