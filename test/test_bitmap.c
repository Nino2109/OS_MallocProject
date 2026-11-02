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
    
    return;
}

int main(void){
    test_init_zeros();
    test_set_single_bit();

    printf("Tutti i test della bitmap sono passati\n");
    return 0;
}