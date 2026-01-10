#include "lib/string.h"
#include "drivers/display/vga.h"
#include "bogoshell/shell.h"
#include "file_system/fs.h"
#include "kernel/kernel.h"

void cmd_hi(){
    print("hi, user\n");
}

void cmd_clear(){
    clear();
}

void cmd_bogo(){
    print("BOGOOOOS\n");
}

void cmd_help(){
    print("hi- greetings\n");
    print("help - helps with commands\n");
    print("ls - list file and directory\n");
    print("clear - clear display\n");
    print("bogo - bogooos\n");
}

void cmd_ls(){
    list();
}

void cmd_cat(){
    cat();
}
