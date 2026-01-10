#include "file_system/fs.h"

void bitmap_set(uint8_t *bitmap, uint32_t idx) {
    bitmap[idx / 8] |= (1 << (idx % 8));
}

void bitmap_clear(uint8_t *bitmap, uint32_t idx) {
    bitmap[idx / 8] &= ~(1 << (idx % 8));
}

int bitmap_test(uint8_t *bitmap, uint32_t idx) {
    return (bitmap[idx / 8] >> (idx % 8)) & 1;
}

int find_free_bit(uint8_t *bitmap){
    for(int i = 35; i < MAX_BLOCKS; i++){
        if(bitmap_test(bitmap, i) == 0){
            return i;
        }
    }
    return -1;
}
