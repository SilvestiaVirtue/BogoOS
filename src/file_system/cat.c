#include "file_system/fs.h"
#include "lib/string.h"
#include "lib/stdint.h"
#include "drivers/display/vga.h"

static uint8_t buffer_list[BLOCK_SIZE];                            

void cat(){
    read_blocks(3, buffer_list);
    struct inode *inodes = (struct inode *)buffer_list;
    uint32_t data_block = inodes[2].blocks[0];
    uint32_t size_data = inodes[2].size;
    memset(buffer_list, 0, BLOCK_SIZE);
    read_blocks(data_block, buffer_list);
    for(uint32_t i = 0; i < size_data; i++){
        if(buffer_list[i] == '\0'){
            break;
        }
        print_char(buffer_list[i]);
    }
    print("\n");
}
