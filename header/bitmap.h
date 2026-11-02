#include <stdint.h>
#include <stddef.h>

typedef struct{
    uint8_t* buffer; //buffer allocato esternamente
    uint32_t buffer_size; //dimensione del buffer
} bitmap_t;

void bitmap_init(bitmap_t* bmap, uint8_t* bf, uint32_t bf_size); //inizializzo la bitmap con buffer esterno e mette tutto a 0

void bitmap_set(bitmap_t* bmap, uint32_t index); //imposto a 1 il bit dell'indice

void bitmap_clear(bitmap_t* bmap, uint32_t index); //imposto a 0 il bit dell'indice

int bitmap_is_set(bitmap_t *bmap, uint32_t index); //controllo bit impostato; ritorna 1 se il bit è impostato, 0 altrimenti 

uint32_t bitmap_getBytes(bitmap_t *bmap); //ritorna il numero di byte della bitmap