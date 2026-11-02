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

static void test_set_single_bit(void){
    uint8_t buf[4];
    bitmap_t bmap; 
    bitmap_init(&bmap, buf, 32);

    for (uint32_t i=0; i<32; i++){
        bitmap_set(&bmap, i);
        for(uint32_t j=0; j<32; j++){
            if(j<=i) assert(bitmap_is_set(&bmap, j)==1 && "Errore nel settare i bit\n");
            else if(j>1) assert(bitmap_is_set(&bmap, j)==0 && "Errore nel settare i bit");
        }
    }
    printf("test_set_single_bit OK\n");
}

int main(void){
    test_init_zeros();
    test_set_single_bit();

    printf("Tutti i test della bitmap sono passati\n");
    return 0;
}