#include "lib/stdint.h" 
#include "drivers/display/vga.h"
#include "drivers/io.h"
#include "drivers/input/keyboard.h" 
#include "file_system/fs.h"
#include "kernel/kernel.h"

void sender_handler(msg_flag_t* msg){
    if(msg->lifet == 0){
        return;
    }
    msg->lifet--;
    msg->sender_handler = 1;
    if(msg->kernel != 1 || msg->signal == sig_none){
        return;
    }
    table(msg);
}
