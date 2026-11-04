#include <stdio.h>
#include <assert.h>
#include "buddy.h"

static void test_buddy_level(void){
    //primi casi noti
    assert(buddy_level(1)==0);
    assert(buddy_level(2)==1);
    for(uint32_t i=2;i<=(1u << (BUDDY_NUM_LEVELS +1))-1;i++){
        assert(buddy_level(buddy_parent(i))+1 == buddy_level(i));
    }
    printf("test_buddy_level OK\n");
}
static void test_buddy_sibling(){
    //primi casi noti
    assert(buddy_parent(2)==1);
    assert(buddy_parent(3)==1);

    for(uint32_t i=2;i<=(1u << (BUDDY_NUM_LEVELS +1))-1;i++){
        assert(buddy_parent(i)==buddy_parent(buddy_sibling(i)));
    }
    
    printf("test_buddy_sibling OK\n");
}
static void test_buddy_parent(){

    for(uint32_t i=2;i<=(1u << (BUDDY_NUM_LEVELS +1))-1;i++){
        assert(buddy_parent(i)==buddy_parent(buddy_sibling(i)));
    }
    printf("test_buddy_parent OK\n");
}
void test_buddy_node_offset(){}

int main(void){
    test_buddy_level();
    test_buddy_sibling();
    test_buddy_parent();


    printf("Tutti test buddy OK\n");
    return 0;
}