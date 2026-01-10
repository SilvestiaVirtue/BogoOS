#ifndef FS_H
#define FS_H
#include "lib/stdint.h"

#define BLOCK_SIZE 512
#define MAX_BLOCKS 128
#define SUPERBLOCK_IDX 0 
#define FREE_INODE 256 
#define BITMAP_DATA_IDX 2
#define BITMAP_TABLES_IDX 1
#define INODE_TABLES_IDX 3
#define DATA_BLOCKS_IDX 34
#define DIRECT_BLOCKS 12

struct superblock {    
    uint32_t identification_number; 
    uint32_t total_block;
    uint32_t free_block;
    uint32_t free_inode;
    uint32_t inode_table_ptr;
    uint32_t data_block_ptr;
}; 

struct inode { 
    uint32_t id;
    uint32_t type;
    uint32_t permissions; 
    uint32_t size;
    uint32_t hard_links;
    uint32_t blocks[DIRECT_BLOCKS];
};

struct dirent {        
    uint32_t inode_num; 
    char name[28];      
};
extern uint8_t bitmap_inode[BLOCK_SIZE];

extern uint8_t bitmap_data[BLOCK_SIZE];

extern uint8_t tables_inode[BLOCK_SIZE];

extern uint8_t disk[MAX_BLOCKS][BLOCK_SIZE]; 


void read_blocks(int num_block, void* buf);
void ramdisk_init();
void write_blocks(int num_block, void* buf);

void create_root_dir();

void create_table_inode();
void create_bitmap_inode();

void format_fs();

void bitmap_set(uint8_t *bitmap, uint32_t idx);
void bitmap_clear(uint8_t *bitmap, uint32_t idx);
int bitmap_test(uint8_t *bitmap, uint32_t idx);
int find_free_bit(uint8_t *bitmap);

void create_root_dir();

void list();
void cat();

#endif
