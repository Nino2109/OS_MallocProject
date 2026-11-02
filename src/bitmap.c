#include "bitmap.h"
#include <stdio.h>
#include <stddef.h>
#include <assert.h> 
#include <string.h> //per memset

//inizializzo la bitmap con buffer esterno e mette tutto a 0
void bitmap_init(bitmap_t* bmap, uint8_t* bf, uint32_t num_bits){
    assert(bf!=NULL);
    bmap->buffer = bf;
    bmap->num_bits = num_bits;
    bmap->buffer_size = bitmap_bytes_needed(num_bits);

    //pulizia a zero
    memset(bf, 0, bmap->buffer_size); //memset perchè più rapidi di pulizia bitabit con bitmap_clear

} //il buffer deve essere almeno bitmap_bytes_needed(num_bits) byte

//ritorna il numero di byte della bitmap
uint32_t bitmap_bytes_needed(uint32_t bits){
    uint32_t bytes_needed = (bits + 7)/8;
    return bytes_needed;
}; 


//Operazioni sui bit 
//imposto a 1 il bit dell'indice
void bitmap_set(bitmap_t* bmap, uint32_t index){
    uint8_t mask = 1 << (index % 8);
    bmap->buffer[index/8] |= mask;
} 

//imposto a 0 il bit dell'indice
void bitmap_clear(bitmap_t* bmap, uint32_t index){
    uint8_t mask = 1 << (index % 8);
    bmap->buffer[index/8] &= ~mask;
} 

//controllo bit impostato; ritorna 1 se il bit è impostato, 0 altrimenti 
int bitmap_is_set(const bitmap_t *bmap, uint32_t index){
    uint8_t mask = 1 << (index % 8);
    if (bmap->buffer[index/8] & mask) return 1;
    return 0;
} 