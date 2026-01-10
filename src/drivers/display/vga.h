#ifndef VGA_H
#define VGA_H

#include "lib/stdint.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_COLOR_WHITE 0x07


extern uint8_t cursor_x;
extern uint8_t cursor_y;

void clear(void);
void print(const char* str);
void new_str(void);
void backspace();
void update_cursor(int x, int y);
void prompt_str_called();
void scroll_down();
void new_str_for_cursor();
void print_char(const char str);
void scroll_left(int* buffer_idx);
void scroll_right(int* buffer_idx, char *buffer);

#endif
