#include <assert.h>
#include "buddy.h"

// funzioni AUSILIARE sugli indici, da 1 (radice) 
//calcola il livello del nodo
uint32_t buddy_level(uint32_t idx){
    assert(idx>=1 && "Radice parte da 1: buddy_level error");
    uint32_t level = 0;
    while(idx>1){
        idx = idx/2;
        level++;
    }
    return level;
}
//calcola il parent del nodo 
uint32_t buddy_parent(uint32_t idx){
    assert(idx>1 && "Radice parte da 1: buddy_parent error");
    return idx/2;
}
//calcola il fratello del nodo
uint32_t buddy_sibling(uint32_t idx){
    assert(idx>1 && "Radice parte da 1: buddy_sibling error");
    return idx ^ 1;
}

//calcola l'offset del nodo nel memory_pool
size_t buddy_node_offset(const buddy_t *bud, uint32_t idx){
    assert(idx>=1 && "Radice parte da 1: buddy_node_offset error");
    uint32_t level = buddy_level(idx);
    size_t block_size = bud->memory_size >> level;
    uint32_t posizione = idx - (1<<level);
    return ((size_t)posizione * block_size);  
}
