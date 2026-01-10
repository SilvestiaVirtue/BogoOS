#include "lib/string.h"
#include "drivers/display/vga.h"
#include "bogoshell/shell.h"

#define NULL ((void*)0)

struct command{
    char* name;
    void (*func)();
};


void name_help(){
    help_msg();
    return;
}

void name_clear(){
    clear_msg();
    return;
}

void name_ls(){
    list_msg();
    return;
}

void name_hi(){
    hi_msg();
    return;
}

void name_bogo(){
    bogo_msg();
    return;
}

void name_cat(){
    cat_msg();
    return;
}

struct command list_commands[] = {{"help", name_help},
                                {"clear", name_clear},
                                {"hi", name_hi},
                                {"bogo", name_bogo},
                                {"ls", name_ls},
                                {"cat", name_cat},
                                {NULL, NULL}
                            };

void shell(char* buffer){
    int search_status = 0;
    for(int i = 0; list_commands[i].name != NULL; i++){
        if(strcmp(buffer, list_commands[i].name) == 0){
            search_status = 1;
            list_commands[i].func();
            break;
        }
    }
    if(!search_status){
        print("Command not found\n");
    }
}
