#ifndef SHELL_H
#define SHELL_H

void shell(char* buffer);

void help_msg();
void hi_msg();
void list_msg();
void clear_msg();
void bogo_msg();
void cat_msg();

void cmd_hi();
void cmd_bogo();
void cmd_clear();
void cmd_ls();
void cmd_help();
void cmd_cat();

#endif
