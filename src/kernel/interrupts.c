#include "kernel/kernel.h"
#include "drivers/io.h"
#include "lib/stdint.h"
#include "drivers/display/vga.h"

void keyboard_handler_main(){
    uint8_t scancode = inb(0x60);
    msg_flag_t msg;
    msg.signal = sig_driver_keyboard;
    msg.data = (void *)(uint32_t)scancode;
    msg.kernel = 1;
    msg.sender_handler = 0;
    msg.table = 0;
    msg.receive_handler = 0;
    msg.function = 0;
    msg.lifet = 10;
    msg.completed = 0;
    sender_handler(&msg);
    outb(0x20, 0x20);
}
