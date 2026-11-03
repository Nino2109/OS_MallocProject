#include "bitmap.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static void test_init_zeros(void){
    uint8_t buf[4]; //32 bit (4byte) per test
    memset(buf, 0xFF, sizeof(buf));
    bitmap_t bmap;
    bitmap_init(&bmap, buf, 32);
    for(uint32_t i=0; i<32; i++){
        assert(bitmap_is_set(&bmap, i)==0 && "Errore init non zeri\n");
    }
    printf("test_init_zeros OK\n");
}

static void test_set_bit(void){
    uint8_t buf[4];
    bitmap_t bmap; 
    bitmap_init(&bmap, buf, 32);

    //funzionalità base del set
    for (uint32_t i=0; i<32; i++){
        bitmap_set(&bmap, i);
        for(uint32_t j=0; j<32; j++){
            if(j<=i) assert(bitmap_is_set(&bmap, j)==1 && "Errore nel settare i bit\n");
            else assert(bitmap_is_set(&bmap, j)==0 && "Errore nel settare i bit\n");
        }
    }

    //controllo ripetizione, set di 1 fa 1
    for (uint32_t i=0; i<32; i++){
        bitmap_set(&bmap, i);
        assert(bitmap_is_set(&bmap, i)==1);
    }
    
    printf("test_set_bit OK\n");
}

static void test_byte_edges(void){
    uint8_t buf[4];
    bitmap_t bmap;
    bitmap_init(&bmap, buf, 32);

    bitmap_set(&bmap, 7);
    assert(bitmap_is_set(&bmap, 7)==1);
    assert(bitmap_is_set(&bmap, 6)==0);
    assert(bitmap_is_set(&bmap, 8)==0);

    bitmap_set(&bmap, 8);
    assert(bitmap_is_set(&bmap, 7)==1);
    assert(bitmap_is_set(&bmap, 9)==0);
    assert(bitmap_is_set(&bmap, 8)==1);

    bitmap_clear(&bmap, 7);
    assert(bitmap_is_set(&bmap, 7)==0);
    assert(bitmap_is_set(&bmap, 8)==1);

    printf("test_byte_edges OK\n");
}

static void test_clear_bit(void){
    uint8_t buf[4];
    bitmap_t bmap; 
    bitmap_init(&bmap, buf, 32);

    //funzione base
    bitmap_set(&bmap, 3);
    bitmap_set(&bmap, 5);
    bitmap_clear(&bmap, 3);
    assert(bitmap_is_set(&bmap,3)==0);
    assert(bitmap_is_set(&bmap, 4) == 0);
    assert(bitmap_is_set(&bmap,5)==1);

    //controllo ripetizione; clear di 0 fa sempre 0 e non sporca
    bitmap_clear(&bmap, 3);
    assert(bitmap_is_set(&bmap,3)==0);
    assert(bitmap_is_set(&bmap, 4) == 0);
    assert(bitmap_is_set(&bmap,5)==1);
    
    printf("test_clear_bit OK\n");
}

static void test_bytes_needed(void){
    assert(bitmap_bytes_needed(0)==0);
    assert(bitmap_bytes_needed(1)==1);
    assert(bitmap_bytes_needed(8)==1);
    assert(bitmap_bytes_needed(9)==2);
    assert(bitmap_bytes_needed(16)==2);
    assert(bitmap_bytes_needed(17)==3);

    printf("test_bytes_needed OK\n");
}

int main(void){
    test_init_zeros();
    test_set_bit();
    test_byte_edges();
    test_clear_bit();
    test_bytes_needed();

    printf("Tutti i test della bitmap sono passati\n");
    return 0;
}