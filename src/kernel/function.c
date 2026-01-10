#include "lib/stdint.h" 
#include "drivers/display/vga.h"
#include "drivers/io.h"
#include "drivers/input/keyboard.h" 
#include "file_system/fs.h"
#include "kernel/kernel.h"
#include "bogoshell/shell.h"

void function(msg_flag_t* msg, k_signal_t name_f){
    if(msg->lifet == 0){
        return;
    }
    msg->lifet--;
    msg->function = 1;
    if(msg->receive_handler != 1 || msg->signal == sig_none){
        return;
    }
    switch (name_f)
    {
    case sig_driver_keyboard:
        keyboard(msg);
        break;
    case sig_shell_ls:
        cmd_ls();
        break;
    case sig_shell_hi:
        cmd_hi();
        break;
    case sig_shell_bogo:
        cmd_bogo();
        break;
    case sig_shell_clear:
        cmd_clear();
        break;
    case sig_shell_help:
        cmd_help();
        break;
    case sig_shell_cat:
        cmd_cat();
        break;
    default:
        msg->completed = 0;
    }
    msg->completed = 1;
    return;
}
