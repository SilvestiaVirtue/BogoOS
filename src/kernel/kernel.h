#ifndef KERNEL_H
#define KERNEL_H

#include "lib/stdint.h"

typedef enum {
    sig_none = 0,
    sig_driver_keyboard,
    sig_shell_ls,
    sig_shell_hi,
    sig_shell_clear,
    sig_shell_bogo,
    sig_shell_help,
    sig_shell_cat,
} k_signal_t;

typedef struct{
    k_signal_t signal;
    void* data;
    uint8_t kernel;
    uint8_t sender_handler;
    uint8_t table;
    uint8_t receive_handler;
    uint8_t function;
    uint32_t lifet;
    uint8_t completed;
} msg_flag_t;

void kernel(void);
void sender_handler(msg_flag_t* msg);
void table(msg_flag_t* msg);
void receive_handler(msg_flag_t* msg, k_signal_t name_f);
void function(msg_flag_t* msg, k_signal_t name_f);

#endif
