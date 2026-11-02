#ifndef BITMAP_H
#define BITMAP_H

#include <stdint.h>

typedef struct{
    uint8_t* buffer; //buffer allocato esternamente
    uint32_t buffer_size; //dimensione del buffer in bytes
    uint32_t num_bits; //numero di bit
} bitmap_t;

//inizializzo la bitmap con buffer esterno e mette tutto a 0
void bitmap_init(bitmap_t* bmap, uint8_t* bf, uint32_t num_bits); //il buffer deve essere almeno bitmap_bytes_needed(num_bits) byte

//ritorna il numero di byte della bitmap
uint32_t bitmap_bytes_needed(uint32_t bits); 


//Operazioni sui bit 
//imposto a 1 il bit dell'indice
void bitmap_set(bitmap_t* bmap, uint32_t index); 

//imposto a 0 il bit dell'indice
void bitmap_clear(bitmap_t* bmap, uint32_t index); 

//controllo bit impostato; ritorna 1 se il bit è impostato, 0 altrimenti 
int bitmap_is_set(const bitmap_t *bmap, uint32_t index); 

#endif