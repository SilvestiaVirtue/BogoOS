#include "kernel/kernel.h"
#include "lib/stdint.h"
#include "drivers/display/vga.h"
#include "bogoshell/shell.h"


void list_msg(){
    msg_flag_t msg;
    msg.signal = sig_shell_ls;
    msg.data = (void *)0;
    msg.kernel = 1;
    msg.sender_handler = 0;
    msg.table = 0;
    msg.receive_handler = 0;
    msg.function = 0;
    msg.lifet = 10;
    msg.completed = 0;
    sender_handler(&msg);
}

void cat_msg(){
    msg_flag_t msg;
    msg.signal = sig_shell_cat;
    msg.data = (void *)0;
    msg.kernel = 1;
    msg.sender_handler = 0;
    msg.table = 0;
    msg.receive_handler = 0;
    msg.function = 0;
    msg.lifet = 10;
    msg.completed = 0;
    sender_handler(&msg);
}

void hi_msg(){
    msg_flag_t msg;
    msg.signal = sig_shell_hi;
    msg.data = (void *)0;
    msg.kernel = 1;
    msg.sender_handler = 0;
    msg.table = 0;
    msg.receive_handler = 0;
    msg.function = 0;
    msg.lifet = 10;
    msg.completed = 0;
    sender_handler(&msg);
}

void bogo_msg(){
    msg_flag_t msg;
    msg.signal = sig_shell_bogo;
    msg.data = (void *)0;
    msg.kernel = 1;
    msg.sender_handler = 0;
    msg.table = 0;
    msg.receive_handler = 0;
    msg.function = 0;
    msg.lifet = 10;
    msg.completed = 0;
    sender_handler(&msg);
}

void help_msg(){
    print("123");
    msg_flag_t msg;
    msg.signal = sig_shell_help;
    msg.data = (void *)0;
    msg.kernel = 1;
    msg.sender_handler = 0;
    msg.table = 0;
    msg.receive_handler = 0;
    msg.function = 0;
    msg.lifet = 10;
    msg.completed = 0;
    sender_handler(&msg);
}

void clear_msg(){
    msg_flag_t msg;
    msg.signal = sig_shell_clear;
    msg.data = (void *)0;
    msg.kernel = 1;
    msg.sender_handler = 0;
    msg.table = 0;
    msg.receive_handler = 0;
    msg.function = 0;
    msg.lifet = 10;
    msg.completed = 0;
    sender_handler(&msg);
}
