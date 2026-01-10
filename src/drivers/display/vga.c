#include "vga.h"
#include "drivers/io.h"
#include "lib/string.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_COLOR_WHITE 0x0F
uint8_t cursor_x = 0;
uint8_t cursor_y = 0;
uint8_t min_x = 9;
uint8_t shell_start_x = 0;
uint8_t shell_start_y = 0;


void update_cursor(int x, int y){
    uint16_t pos = y * VGA_WIDTH + x;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void backspace(){
    if(cursor_x == shell_start_x && cursor_y == shell_start_y){
        return;
    }
    if(cursor_x > 0){
        cursor_x--;
    }
    else if(cursor_y > shell_start_y){
        cursor_y--;
        cursor_x = VGA_WIDTH - 1;
    }
    uint16_t*  video_memory = (uint16_t*) 0xB8000;
    int index = cursor_y * VGA_WIDTH + cursor_x;
    video_memory[index] = (VGA_COLOR_WHITE << 8 ) | ' ';
    update_cursor(cursor_x, cursor_y);
}

void clear(void){
    for(int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++){
        uint16_t*  video_memory = (uint16_t*) 0xB8000;
        video_memory[i] = (VGA_COLOR_WHITE << 8 ) | ' ';
    }
    cursor_x = 0;
    cursor_y = 0;
    update_cursor(cursor_x, cursor_y);
}


void new_str(void){
    cursor_x = 0;
    if( cursor_y < VGA_HEIGHT - 1){
        cursor_y++;
    }else{
        scroll_down();
    }
}

void new_str_for_cursor(){
    new_str();
    prompt_str_called();
    shell_start_x = cursor_x;
    shell_start_y = cursor_y;
}

void print(const char* str){
    uint16_t*  video_memory = (uint16_t*) 0xB8000;
    for(int i = 0; str[i] != '\0'; i++){
        if(str[i] == '\n'){
            new_str();
            continue;
        }
        int index = cursor_y * VGA_WIDTH + cursor_x;
        video_memory[index] = (VGA_COLOR_WHITE << 8) | str[i];
        cursor_x++;
        if(VGA_WIDTH <= cursor_x){
            new_str();
        }
    }
}
void print_char(const char str){
    uint16_t*  video_memory = (uint16_t*) 0xB8000;
    int index = cursor_y * VGA_WIDTH + cursor_x;
    video_memory[index] = (VGA_COLOR_WHITE << 8) | str;
    cursor_x++;
    if(VGA_WIDTH <= cursor_x){
        new_str();
    }
}

void prompt_str_called(){
    print("[user] >>");
    shell_start_x = cursor_x;
    shell_start_y = cursor_y;
}

void scroll_down(){
    uint16_t*  video_memory = (uint16_t*) 0xB8000;
    for(int i = 0; i < (VGA_HEIGHT - 1) * VGA_WIDTH; i++){
        video_memory[i] = video_memory[i+ VGA_WIDTH];
    }
    for(int i = (VGA_HEIGHT - 1) * VGA_WIDTH; i < (VGA_WIDTH * VGA_HEIGHT); i++){
        video_memory[i] = (VGA_COLOR_WHITE << 8) | ' ';
    }
    if(shell_start_y > 0){
        shell_start_y--;
    }   
}


void scroll_left(int *buffer_idx){
    if(cursor_x > shell_start_x){
        (*buffer_idx)--;
        cursor_x--;
        update_cursor(cursor_x, cursor_y);
    }
}

void scroll_right(int *buffer_idx, char *buffer){
    int len = strlen(buffer);
    if(len> *buffer_idx){
        (*buffer_idx)++;
        cursor_x++;
        update_cursor(cursor_x, cursor_y);
    }
}
