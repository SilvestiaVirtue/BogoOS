#include "file_system/fs.h"

void create_table_inode(){
    for(int i = 3; i <= DATA_BLOCKS_IDX;i++){
        write_blocks(i, tables_inode);
    }
}

void create_bitmap_inode(){
    bitmap_set(bitmap_inode, 0);
    bitmap_set(bitmap_inode, 1);
    bitmap_set(bitmap_inode, 2);
    write_blocks(BITMAP_TABLES_IDX, bitmap_inode);
}
