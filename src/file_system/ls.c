#include "file_system/fs.h"
#include "lib/string.h"
#include "lib/stdint.h"
#include "drivers/display/vga.h"

static uint8_t buffer_list[BLOCK_SIZE];                            

void list(){
    read_blocks(3, buffer_list);
    struct inode *inodes = (struct inode *)buffer_list;
    uint32_t data_block = inodes[1].blocks[0];
    read_blocks(data_block, buffer_list);
    struct dirent *dir = (struct dirent *)buffer_list;
    for(int i = 0; i < 3; i++){
        if(dir[i].inode_num != 0){
            for(int j = 0; j < 28; j++){
                char c = dir[i].name[j];
                if(c == '\0'){
                    break;
                }
                print_char(c);
            }
            print("\n");
        }
    }
}
