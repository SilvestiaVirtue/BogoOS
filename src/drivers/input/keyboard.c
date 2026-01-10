#include "lib/string.h"
#include "drivers/io.h"
#include "drivers/display/vga.h"
#include "lib/stdint.h"
#include "bogoshell/shell.h"
#include "kernel/kernel.h"


static char buffer[1024];
static int buffer_idx = 0;
static uint8_t  shift_pressed = 0;

static uint8_t capslock_pressed = 0;

unsigned char qwerty_us_upper[128] = {
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
    0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\"', '~', 0,
    '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, '*', 0, ' ', 0
};

unsigned char qwerty_us[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',   
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',      
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,         
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0
};



void keyboard(msg_flag_t* msg){
    if( (uint32_t)msg->data == 0x2A || (uint32_t)msg->data == 0x36){
        shift_pressed = 1;
        return;
    }
    if( (uint32_t)msg->data == 0xAA || (uint32_t)msg->data == 0xB6){
        shift_pressed = 0;
        return;
    }
    if( (uint32_t)msg->data == 0x4D){
        scroll_right(&buffer_idx, buffer);
        return;
    }
    if((uint32_t)msg->data == 0x4B){
        scroll_left(&buffer_idx);
        return;
    }
    if((uint32_t)msg->data == 0x3A){
        capslock_pressed = !capslock_pressed;
        return;
    }
    if((uint32_t)msg->data == 0x0E){
        if(buffer_idx > 0){
            backspace();
            buffer_idx--;
            buffer[buffer_idx] = '\0';
        }
        return;
    }
    if((uint32_t)msg->data & 0x80){
        return;
    }
    if((uint32_t)msg->data == 0x1C){
        if(buffer[0] == '\0'){
            new_str();
            prompt_str_called();
            update_cursor(cursor_x,  cursor_y);
            return;
        }
        new_str();
        shell(buffer);
        prompt_str_called();
        update_cursor(cursor_x,  cursor_y);
        buffer_idx = 0;
        buffer[buffer_idx] = '\0';
        return;
    }
    if(! ((uint32_t)msg->data & 0x80) && (uint32_t)msg->data < 128){
        int double_upper = shift_pressed ^ capslock_pressed;
        char letter = double_upper ? qwerty_us_upper[(uint32_t)msg->data] : qwerty_us[(uint32_t)msg->data];
        if( letter > 0){
            char str[2] = {letter, 0};
            buffer[buffer_idx] = letter;
            buffer_idx++;
            buffer[buffer_idx] = '\0';
            print(str);
            update_cursor(cursor_x,  cursor_y);
        }
    }
}
