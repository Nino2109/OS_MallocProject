#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "buddy.h"
#include "bitmap.h"

#define LAST_NODE ((1u << (BUDDY_NUM_LEVELS+1)) -1)
#define LAST_INNER ((1u << BUDDY_NUM_LEVELS) -1) //ultimo parent
#define NUM_BITS   (1u << (BUDDY_NUM_LEVELS + 1))
#define BITMAP_BYTES (NUM_BITS / 8) 
static uint8_t bufs[2 * BITMAP_BYTES]; 
static uint8_t pool[BUDDY_TOTAL_SIZE];


static void test_buddy_calc_size(void){
    assert(buddy_calc_size(BUDDY_NUM_LEVELS)== (2 * BITMAP_BYTES)); 
    assert(buddy_calc_size(1)==2);

    printf("test_buddy_calc_size OK\n");
}

static void test_buddy_init_ok(void){
    static buddy_t bud;
    memset(bufs, 0xFF, sizeof(bufs));
    int ret = buddy_init(&bud, bufs, sizeof(bufs), pool, sizeof(pool),BUDDY_NUM_LEVELS);
    assert(ret == 0);
    assert(bud.memory_pool == pool);
    assert(bud.memory_size == BUDDY_TOTAL_SIZE);
    assert(bud.min_block_size == BUDDY_MIN_BLOCK_SIZE);
    assert(bud.num_levels == BUDDY_NUM_LEVELS);
    assert(bud.alloc_bits.buffer == bud.split_bits.buffer + BITMAP_BYTES);
    for(uint32_t i=0; i<NUM_BITS;i++){
        assert(bitmap_is_set(&bud.split_bits, i)==0);
        assert(bitmap_is_set(&bud.alloc_bits,i)==0);
    }

    printf("test_buddy_init_ok OK\n");
}

static void test_buddy_init_fail(void){
    static buddy_t bud, ref;
    memset(&bud, 0xAB, sizeof(bud));
    memset(&ref, 0xAB, sizeof(ref));

    assert(buddy_init(&bud, NULL, sizeof(bufs), pool, sizeof(pool), BUDDY_NUM_LEVELS) == -1);
    assert(memcmp(&bud, &ref, sizeof bud) == 0);

    assert(buddy_init(&bud, bufs, sizeof(bufs), NULL, sizeof(pool), BUDDY_NUM_LEVELS) == -1);
    assert(memcmp(&bud, &ref, sizeof bud) == 0);

    assert(buddy_init(&bud, bufs, buddy_calc_size(BUDDY_NUM_LEVELS) -1, pool, sizeof(pool), BUDDY_NUM_LEVELS) == -1);
    assert(memcmp(&bud, &ref, sizeof bud) == 0);

    assert(buddy_init(&bud, bufs, sizeof(bufs), pool, BUDDY_TOTAL_SIZE+1, BUDDY_NUM_LEVELS) == -1);
    assert(memcmp(&bud, &ref, sizeof bud) == 0);

    assert(buddy_init(&bud, bufs, sizeof(bufs), pool, sizeof(pool), 0) == -1);
    assert(memcmp(&bud, &ref, sizeof bud) == 0);

    assert(buddy_init(&bud, bufs, sizeof(bufs), pool, sizeof(pool), 31) == -1);
    assert(memcmp(&bud, &ref, sizeof bud) == 0);

    assert(buddy_init(NULL, bufs, sizeof(bufs), pool, sizeof(pool), BUDDY_NUM_LEVELS) == -1);
    assert(memcmp(&bud, &ref, sizeof bud) == 0);

    printf("test_buddy_init_fail OK\n");
}



static void test_buddy_level(void){
    //primi casi noti
    assert(buddy_level(1)==0);
    assert(buddy_level(2)==1);
    assert(buddy_level(LAST_NODE)==BUDDY_NUM_LEVELS);
    for(uint32_t i=2;i<=LAST_NODE;i++){
        assert(buddy_level(buddy_parent(i))+1 == buddy_level(i));
    }
    printf("test_buddy_level OK\n");
}
static void test_buddy_sibling(void){
    //primi casi noti
    assert(buddy_sibling(2)==3);
    assert(buddy_sibling(3)==2);
    assert(buddy_sibling(4)==5);
    assert(buddy_sibling(5)==4);

    for(uint32_t i=2;i<=LAST_NODE;i++){
        assert(buddy_sibling(buddy_sibling(i))==i);
        assert(buddy_sibling(i)!=i);
        assert(buddy_level(buddy_sibling(i))==buddy_level(i));
    }
    
    printf("test_buddy_sibling OK\n");
}
static void test_buddy_parent(void){
    //primi casi noti
    assert(buddy_parent(2)==1);
    assert(buddy_parent(3)==1);
    assert(buddy_parent(5)==2);
    assert(buddy_parent(6)==3);
    assert(buddy_parent(7)==3);
    assert(buddy_parent(LAST_NODE)== LAST_NODE/2);

    for(uint32_t i=2;i <= LAST_NODE;i++){
        assert(buddy_parent(i)==buddy_parent(buddy_sibling(i)));
    }
    printf("test_buddy_parent OK\n");
}
static void test_buddy_node_offset(void){
    buddy_t bud;
    memset(&bud, 0, sizeof bud);
    bud.memory_size = BUDDY_TOTAL_SIZE;
    bud.num_levels = BUDDY_NUM_LEVELS;

    assert(buddy_node_offset(&bud, 1)==0);
    for(uint32_t i=1;i<=LAST_INNER;i++){
        size_t node_size = bud.memory_size >> buddy_level(i);
        size_t offset = buddy_node_offset(&bud, i); 
        assert(buddy_node_offset(&bud, 2*i)== offset);
        assert(buddy_node_offset(&bud, (2*i)+1)== offset + (node_size/2));
    }
    printf("test_buddy_node_offset OK\n");
}

int main(void){
    test_buddy_level();
    test_buddy_sibling();
    test_buddy_parent();
    test_buddy_node_offset();
    test_buddy_calc_size();
    test_buddy_init_ok();
    test_buddy_init_fail();

    printf("Tutti test buddy OK\n");
    return 0;
}