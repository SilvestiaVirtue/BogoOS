#include "lib/stdint.h"
#include "file_system/fs.h"
#include "lib/string.h"

uint8_t disk[MAX_BLOCKS][BLOCK_SIZE]; 


void read_blocks(int num_block, void* buf){
    if(num_block >= MAX_BLOCKS){
        return;
    }
    memcpy(buf, disk[num_block], 512);
}

void write_blocks(int num_block, void* buf){
    if(num_block >= MAX_BLOCKS){
        return;
    }
    memcpy(disk[num_block], buf, 512);
}
void ramdisk_init(){
    memset(disk, 0, sizeof(disk));
    return;
} 
