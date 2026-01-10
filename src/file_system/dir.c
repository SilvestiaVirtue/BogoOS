#include "file_system/fs.h"
#include "lib/stdint.h"
#include "lib/string.h"

void create_root_dir(){
    uint8_t block[BLOCK_SIZE] = {0};
    memset(block, 0, BLOCK_SIZE);

    struct inode *inodes = (struct inode *)block;
    inodes[1].id = 1;
    inodes[1].type = 2;
    inodes[1].permissions = 7;
    inodes[1].size = 96;
    inodes[1].hard_links = 1;
    inodes[1].blocks[0] = 35;
    
    inodes[2].id = 2;
    inodes[2].type = 1;
    inodes[2].permissions = 7;
    inodes[2].size = 64;
    inodes[2].hard_links = 0;
    inodes[2].blocks[0] = 36;
    write_blocks(3, block);

    memset(block, 0, BLOCK_SIZE);
    struct dirent *dir = (struct dirent *)block;
    dir[0].inode_num = 1;
    strcpy(dir[0].name, ".");
    dir[1].inode_num = 1;
    strcpy(dir[1].name, "testdir\0");
    dir[2].inode_num = 2;
    strcpy(dir[2].name, "test.txt\0");
    write_blocks(35, block);
    memset(block, 0, BLOCK_SIZE);
    strcpy((char *)block, "Hello friends");
    write_blocks(36, block);
}
