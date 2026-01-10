#include "lib/stdint.h" 
#include "drivers/display/vga.h"
#include "drivers/io.h"
#include "kernel/kernel.h"
#include "kernel/idt.h"
#include "file_system/fs.h"

void idt_init();
void pic_remap();

void kernel(void){
    idt_init();
    pic_remap();
    format_fs();
    prompt_str_called();
    outb(0x21, 0xFD);
    outb(0xA1, 0xFF);
    asm("sti"); 
    while(1) {
        asm("hlt");
    }
}
