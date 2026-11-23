#include <assert.h>
#include "buddy.h"
#include "bitmap.h"


int32_t buddy_level_for_size(const buddy_t* bud, size_t size){
    if(size==0 || size>bud->memory_size -BUDDY_HEADER_SIZE) return -1;
    size_t need = size + BUDDY_HEADER_SIZE;
    int32_t level = bud->num_levels;
    while ((bud->memory_size >> level)<need){
        level--;
    }
    return level;
}


uint32_t buddy_find_free_node(const buddy_t* bud, uint32_t level){
    assert(bud!=NULL);
    assert(level <= bud->num_levels);
    for (uint32_t n=1u<<level; n<=(1u<<(level+1))-1; n++){
        if (bitmap_is_set(&bud->split_bits, n) || bitmap_is_set(&bud->alloc_bits, n)){
            continue;
        }
        int ok = 1;
        uint32_t p = n;
        while(p>1){
            p = buddy_parent(p);
            if (!bitmap_is_set(&bud->split_bits, p)){
                ok = 0;
                break;
            }
        }
        if (ok==1) return n;
    }
    return 0;
}



//ret 0=ok; -1 = param incoerenti o buffer troppo piccolo
int buddy_init(buddy_t* bud, uint8_t* buffer, size_t buffer_size, uint8_t* memory, size_t memory_size, uint32_t num_levels){
    if(bud==NULL || buffer==NULL || memory==NULL || num_levels<1 || num_levels>=31){
        return -1;
    }
    size_t min_block = memory_size >> num_levels;
    if((min_block<<num_levels)!=memory_size) return -1;
    if ((min_block & (min_block -1)) != 0) return -1;
    if(min_block <= BUDDY_HEADER_SIZE) return -1;
    if(buffer_size < buddy_calc_size(num_levels)) return -1;

    bud->memory_pool = memory;
    bud->memory_size = memory_size;
    bud->num_levels = num_levels;
    bud->min_block_size = min_block;
    uint32_t bits = 1u << (num_levels+1);
    size_t bytes = bitmap_bytes_needed(bits);
    bitmap_init(&bud->split_bits, buffer, bits);
    bitmap_init(&bud->alloc_bits, buffer+bytes, bits);
    return 0;
}

size_t buddy_calc_size(uint32_t num_levels){
    uint32_t bits_needed = (1u << (num_levels+1));
    size_t bytes_needed = bitmap_bytes_needed(bits_needed);
    return bytes_needed * 2;
}

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
    uint32_t posizione = idx - (1u<<level);
    return ((size_t)posizione * block_size);  
}
