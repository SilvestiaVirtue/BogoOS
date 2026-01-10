global keyboard_handler_asm
extern keyboard_handler_main 

keyboard_handler_asm:
    pushad          
    call keyboard_handler_main
    popad           
    iretd 
