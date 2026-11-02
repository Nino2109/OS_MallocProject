#include "bitmap.h"

//inizializzo la bitmap con buffer esterno e mette tutto a 0
void bitmap_init(bitmap_t* bmap, uint8_t* bf, uint32_t num_bits){
    if (bf!=null){
        bmap->buffer = bf;
        bmap.num_bits = num_bits;
        bmap.buffer_size = bitmap_bytes_needed(num_bits);
    }
    else{
        printf("Error initializing bitmap: bf null")
    }
    
} //il buffer deve essere almeno bitmap_bytes_needed(num_bits) byte

//ritorna il numero di byte della bitmap
uint32_t bitmap_bytes_needed(uint32_t bits){
    uint32_t bytes_needed = bits/8;
    return bytes_needed;
}; 


//Operazioni sui bit 
//imposto a 1 il bit dell'indice
void bitmap_set(bitmap_t* bmap, uint32_t index){
    bmap[index] = 1;
} 

//imposto a 0 il bit dell'indice
void bitmap_clear(bitmap_t* bmap, uint32_t index){
    bmap[index] = 0;
} 

//controllo bit impostato; ritorna 1 se il bit è impostato, 0 altrimenti 
int bitmap_is_set(const bitmap_t *bmap, uint32_t index){
    if (bmap[index]==1) return 1;
    return 0;
} 