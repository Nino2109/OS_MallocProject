#include "bitmap.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static void test_init_zeros(void){
    uint8_t buf[4]; //32 bit (4byte) per test
    memset(buf, 0xFF, sizeof(buf));
    bitmap_t bmap;
    bitmap_init(&bm, buf, 32);
    for(int i=0; i<32; i++){
        if (bitmap_is_set(bmap, i)!=0) assert("Errore init non zeri");
    }
    printf("test_init_zeros OK");
    return 0;
}

static void test_set_single_bit(void){
    
    return 0;
}

int main(void){
    test_init_zeros();
    test_set_single_bit();

    printf("Tutti i test della bitmap sono passati\n");
    return 0;
}