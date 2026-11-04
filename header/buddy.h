#ifndef BUDDY_H
#define BUDDY_H

#include <stddef.h>
#include "bitmap.h"

#define BUDDY_TOTAL_SIZE (1024*1024) //1MB
#define BUDDY_MIN_BLOCK_SIZE 32 //32B
#define BUDDY_NUM_LEVELS 15
#define BUDDY_HEADER_SIZE 8


typedef struct {
    uint8_t* memory_pool; //buffer allocato esternamente
    uint32_t min_block_size; //dimensione minima del blocco in bytes
    bitmap_t split_bits; //bitmap dei blocchi divisi
    bitmap_t alloc_bits; //bitmap dei blocchi allocati
} buddy_t;

//byte di buffer necessari per le 2 bitmap
size_t buddy_calc_size(uint32_t num_levels);

//ret 0=ok; -1 = param incoerenti o buffer troppo piccolo
int buddy_init(buddy_t* bud, uint8_t* buffer, size_t buffer_size, uint8_t* memory, size_t memory_size, uint32_t num_levels);

void *buddy_alloc(buddy_t* bud, size_t size);
void buddy_free(buddy_t* bud, void* ptr);

// funzioni pure sugli indici 
uint32_t buddy_level(uint32_t i);
uint32_t buddy_parent(uint32_t i);
uint32_t buddy_buddy(uint32_t i);
size_t   buddy_node_offset(const buddy_t *b, uint32_t i);

#endif