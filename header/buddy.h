#ifndef BUDDY_H
#define BUDDY_H

#include <stddef.h>
#include <stdint.h>
#include "bitmap.h"

#define BUDDY_TOTAL_SIZE (1024*1024) //1MB
#define BUDDY_MIN_BLOCK_SIZE 32 //32B
#define BUDDY_NUM_LEVELS 15
#define BUDDY_HEADER_SIZE 8

_Static_assert((BUDDY_MIN_BLOCK_SIZE << BUDDY_NUM_LEVELS) == BUDDY_TOTAL_SIZE, "livelli e blocco minimo non coerenti con la dim totale");

typedef struct {
    uint8_t* memory_pool; //buffer allocato esternament
    size_t min_block_size; //dimensione minima dei blocchi
    bitmap_t split_bits; //bitmap dei blocchi divisi
    bitmap_t alloc_bits; //bitmap dei blocchi allocati
    size_t memory_size; //dimensione del buffer allocato esternamente
    uint32_t num_levels; //numero di livelli della struttura
} buddy_t;

//byte di buffer necessari per le 2 bitmap
size_t buddy_calc_size(uint32_t num_levels);

//ret 0=ok; -1 = param incoerenti o buffer troppo piccolo
int buddy_init(buddy_t* bud, uint8_t* buffer, size_t buffer_size, uint8_t* memory, size_t memory_size, uint32_t num_levels);

//restituisce un puntatore (start + BUDDY_HEADER_SIZE); null se non c'è memoria
void *buddy_alloc(buddy_t* bud, size_t size);

//libera e fonde i blocchi; se null ignora?
void buddy_free(buddy_t* bud, void* ptr);

// funzioni sugli indici, da 1 (radice) 
//calcola il livello del nodo
uint32_t buddy_level(uint32_t i);
//calcola il parent del nodo 
uint32_t buddy_parent(uint32_t i);
//calcola il fratello del nodo
uint32_t buddy_sibling(uint32_t i);
//calcola l'offset del nodo nel memory_pool
size_t   buddy_node_offset(const buddy_t *bud, uint32_t i);

#endif