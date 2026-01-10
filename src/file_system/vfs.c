#include "file_system/fs.h"
#include "lib/string.h"


uint8_t bitmap_inode[BLOCK_SIZE] = {0};
uint8_t bitmap_data[BLOCK_SIZE] = {0};
uint8_t tables_inode[BLOCK_SIZE] = {0};

void format_fs(){
    ramdisk_init();
    uint8_t temp_sb[BLOCK_SIZE] = {0};
    struct superblock sb = {
                            10000,
                            MAX_BLOCKS ,
                            MAX_BLOCKS - 37,
                            FREE_INODE - 2,
                            INODE_TABLES_IDX,
                            DATA_BLOCKS_IDX,
    };
    memcpy(temp_sb, &sb, sizeof(sb));
    write_blocks(SUPERBLOCK_IDX, temp_sb);
    memset(bitmap_data, 0, BLOCK_SIZE);
    for(int i = 0; i <= DATA_BLOCKS_IDX; i++){
        bitmap_set(bitmap_data, i);
    }
    bitmap_set(bitmap_data, 35);
    bitmap_set(bitmap_data, 36);
    write_blocks(BITMAP_DATA_IDX, bitmap_data);
    create_bitmap_inode();
    create_table_inode();
    create_root_dir();
}
