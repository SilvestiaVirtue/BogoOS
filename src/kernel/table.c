#include "lib/stdint.h" 
#include "drivers/display/vga.h"
#include "drivers/io.h"
#include "drivers/input/keyboard.h" 
#include "file_system/fs.h"
#include "kernel/kernel.h"

void table(msg_flag_t* msg){
    if(msg->lifet == 0){
        return;
    }
    msg->lifet--;
    k_signal_t name_f;
    msg->table = 1;
    if(msg->sender_handler != 1 || msg->signal == sig_none){
        return;
    }
    switch (msg->signal)
    {
    case sig_driver_keyboard:
        name_f = sig_driver_keyboard;
        break;
    case sig_shell_ls:
        name_f = sig_shell_ls;
        break;
    case sig_shell_hi:
        name_f = sig_shell_hi;
        break;
    case sig_shell_bogo:
        name_f = sig_shell_bogo;
        break;
    case sig_shell_clear:
        name_f = sig_shell_clear;
        break;
    case sig_shell_help:
        name_f = sig_shell_help;
        break;
    case sig_shell_cat:
        name_f = sig_shell_cat;
        break;
    default:
        msg->table = 0;
    }
    receive_handler(msg, name_f);
}
