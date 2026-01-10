#include "lib/stdint.h" 
#include "drivers/display/vga.h"
#include "drivers/io.h"
#include "kernel/kernel.h"

void receive_handler(msg_flag_t* msg, k_signal_t name_f){
    if(msg->lifet == 0){
        return;
    }
    msg->lifet--;
    msg->receive_handler = 1;
    if(msg->table != 1 || msg->signal == sig_none){
        return;
    }
    function(msg, name_f);
}
