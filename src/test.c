#define UNIQ(id, name, func, type,  waxed) \
    static void wrapper_##func(void* data) { \
        if (data == 0) { \
            ((void(*)(void))func)(); \
            if(waxed == 0){
                return 0;
            }
        } else { \
            if (__builtin_types_compatible_p(type, char*)) { \
                func((type)data); \
            } else { \
                func(*(type*)data); \
            } \
        } \
    }
VGA_LIST
#undef UNIQ

typedef struct {
    mod_key_t modkeys;
    fifo_buf_t fifo;
}ps2_t;

static const struct key_entry keymap[128] = 
{
    [0x01] = {0x1B, 0x1B}, 
    [0x02] = {'1', '!'},   [0x03] = {'2', '@'},   [0x04] = {'3', '#'},
    [0x05] = {'4', '$'},   [0x06] = {'5', '%'},   [0x07] = {'6', '^'},
    [0x08] = {'7', '&'},   [0x09] = {'8', '*'},   [0x0A] = {'9', '('},
    [0x0B] = {'0', ')'},   [0x0C] = {'-', '_'},   [0x0D] = {'=', '+'},
    [0x0E] = {'\b', '\b'}, 
    [0x0F] = {'\t', '\t'}, 
    [0x10] = {'q', 'Q'},   [0x11] = {'w', 'W'},   [0x12] = {'e', 'E'},
    [0x13] = {'r', 'R'},   [0x14] = {'t', 'T'},   [0x15] = {'y', 'Y'},
    [0x16] = {'u', 'U'},   [0x17] = {'i', 'I'},   [0x18] = {'o', 'O'},
    [0x19] = {'p', 'P'},   [0x1A] = {'[', '{'},   [0x1B] = {']', '}'},
    [0x1C] = {'\n', '\n'}, 
    [0x1E] = {'a', 'A'},   [0x1F] = {'s', 'S'},   [0x20] = {'d', 'D'},
    [0x21] = {'f', 'F'},   [0x22] = {'g', 'G'},   [0x23] = {'h', 'H'},
    [0x24] = {'j', 'J'},   [0x25] = {'k', 'K'},   [0x26] = {'l', 'L'},
    [0x27] = {';', ':'},   [0x28] = {'\'', '\"'}, [0x29] = {'`', '~'},
    [0x2B] = {'\\', '|'},  [0x2C] = {'z', 'Z'},   [0x2D] = {'x', 'X'},
    [0x2E] = {'c', 'C'},   [0x2F] = {'v', 'V'},   [0x30] = {'b', 'B'},
    [0x31] = {'n', 'N'},   [0x32] = {'m', 'M'},   [0x33] = {',', '<'},
    [0x34] = {'.', '>'},   [0x35] = {'/', '?'},   [0x39] = {' ', ' '},
    [0x47] = {'7', '7'},   [0x48] = {'8', '8'},   [0x49] = {'9', '9'},
    [0x4A] = {'-', '-'},   [0x4B] = {'4', '4'},   [0x4C] = {'5', '5'},
    [0x4D] = {'6', '6'},   [0x4E] = {'+', '+'},   [0x4F] = {'1', '1'},
    [0x50] = {'2', '2'},   [0x51] = {'3', '3'},   [0x52] = {'0', '0'},
    [0x53] = {'.', '.'}
}


static vga_t vga;

static inline uint32_t __get_index_cursor()
{
    return (uint32_t) vga.cursor.Y * VGA_WIGHT + vga.cursor.X;
}

static inline void __update_cursor()
{
    uint32_t index = __get_index_cursor();
    outb(VGA_CTRL_REGISTER, 0x0F);
    outb(VGA_DATA_REGISTER, (uint8_t) (index & 0xFF));
    outb(VGA_CTRL_REGISTER, 0x0E);
    outb(VGA_DATA_REGISTER, (uint8_t) ((index >> 8) & 0xFF));
}

void vga_new_str() // интерфейсный в некоторых случаях
{
    vga.cursor.X = 0;
    if(vga.cursor.Y < VGA_HEIGHT - 1){
        vga.cursor.Y++;
    }else{
        __scroll_down();
    }
    __update_cursor();
}

void vga_clear() // интерфейсный
{
    asm volatile("cli");
    for(uint32_t i = 0 ; i < VGA_SIZE; i++){
        vga.buffer[i] = (uint16_t) ' ' | (uint16_t)vga.color<< 8; 
    }
    vga.cursor.X = 0;
    vga.cursor.Y = 0;
    __update_cursor();
    asm volatile("sti");
}

static inline void __vga_print_char(const char S)
{
    if (S == '\0') {
        return;
    }
    if(S == '\n'){
        vga_new_str();
        return;
    }
    
    uint32_t index = __get_index_cursor();
    vga.buffer[index] = (uint16_t) S | (uint16_t)vga.color << 8;
    vga.cursor.X++;
    if(VGA_WIDTH <= vga.cursor.X){
        vga_new_str();
    }else{
        __update_cursor();
    }
}


////////////////////////////////

void vga_print_int(int N) // интерфейсный
{
    char buffer[32];
    intoa(N, buffer);
    vga_print_string(buffer);
    __update_cursor();

}

void vga_print_uint(uint32_t N) // интерфейсный
{
    char buffer[32];
    uintoa(N, buffer);
    vga_print_string(buffer);
    __update_cursor();

}

void vga_print_hex(uint32_t NHEX) // интерфейсный
{
    char buffer[32];
    vga_print_string("0x");
    uintoa(NHEX, buffer);
    vga_print_string(buffer);
    __update_cursor();

}


//////////////////////////////// 



void vga_delete_char() // интерфейсный
{
    asm volatile("cli");
    if(vga.cursor.Y == vga.border.Y && vga.cursor.X <= vga.border.Y){
        asm volatile("sti");
        return;
    }
    if(vga.cursor.X == 0) {
        if(vga.cursor.Y > vga.border.Y) {
            vga.cursor.Y--;
            vga.cursor.X = VGA_WIDTH - 1;
        } else {
            asm volatile("sti");
            return;
        }
    } else {
        vga.cursor.X--;
    }
    uint32_t index = __get_index_cursor();
    vga.buffer[index] = (uint16_t) ' ' | (uint16_t)color << 8;
    __update_cursor();
    asm volatile("sti");
}



void vga_print_string(const char* str) // интерфейсный
{
    asm volatile("cli");
    for(uint32_t i = 0; str[i] != '\0'; i++) {
        __vga_print_char(str[i]);
    }
    __update_cursor();
    asm volatile("sti");
}

static inline void __scroll_down()
{
    for(uint32_t i = 0; i < (VGA_HEIGHT - 1) * VGA_WIDTH; i++){
        vga.buffer[i] = vga.buffer[i + VGA_WIDTH];
    }
    for(uint32_t i = (VGA_HEIGHT - 1) * VGA_WIDTH; i < (VGA_WIDTH * VGA_HEIGHT); i++){
        vga.buffer[i] = (uint16_t) ' ' | (uint16_t)vga.color << 8;
    }
    if(vga.border.Y > 0){
        vga.border.Y--;
    }
}
void change_cursor(cursor_t X_Y) // интерфейсный 
{
    asm volatile("cli");
    vga.cursor.X = X_Y.X;
    vga.cursor.Y = X_Y.Y;
    __update_cursor();
    asm volatile("sti");
}



void change_color(color_t COLOR) // интерфейсный 
{
    vga.color = COLOR;
}

void change_border(border_t X_Y) // интерфейсный
{
    asm volatile("cli");
    vga.border.X = X_Y.X;
    vga.border.Y = X_Y.Y;
    asm volatile("sti");
}

void __init__ init_vga(void)
{
    vga.buffer = (uint16_t*)VGA_ADDRESS;
    vga.cursor.X = 0;
    vga.cursor.Y = 0;
    vga.border.X = 0;
    vga.border.Y = 0;
    vga.color = VGA_WHITE;
    CREATE_PROCESS(vga_process, "VGA", 1, wait);
}





process_t* process_list = 0;   
process_t* current_process = 0; 
static uint32_t pid_counter = 1; 

static inline uint32_t __get_next_pid()
{
    return pid_counter++;
}

uint32_t existence_process_by_name(char* name)
{
    if (process_list == 0) return 0;
    process_t* temp = process_list;
    do {
        if(strncmp(temp->pname, name, 32) == 0){
            return 1;
        }
        temp = temp->next;
    } while(temp != process_list);
    return 0; 
}

uint32_t get_id_by_name_process(char* name)
{
    if (process_list == 0) return 0;
    process_t* temp = process_list;
    do {
        if(strncmp(temp->pname, name, 32) == 0){
            return temp->PID;
        }
        temp = temp->next;
    } while(temp != process_list);
    return 0;
}

process_t* find_process_by_pid(uint32_t pid)
{
    if (process_list == 0) return 0;
    process_t* temp = process_list;
    do {
        if (temp->PID == pid) {
            return temp; 
        }
        temp = temp->next;
    } while (temp != process_list); 
    return 0;
}

process_t* CREATE_PROCESS(void(*function)(), char* name, uint8_t right, pid_state_t state)
{
    process_t* proc = (process_t*)malloc(sizeof(process_t));
    if(!proc){
        goto error;
    }
    uint32_t* start_stack = (uint32_t*)malloc(4096);
    if(!start_stack){
        goto error_mem;
    }
    uint32_t* esp = start_stack + 1024;
    *(--esp) = 0x202;              // EFLAGS (Interrupts Enabled)
    *(--esp) = 0x08;               // CS (Kernel Code Segment)
    *(--esp) = (uint32_t)function; // EIP (Точка входа)
    *(--esp) = 0; // EAX
    *(--esp) = 0; // ECX
    *(--esp) = 0; // EDX
    *(--esp) = 0; // EBX
    *(--esp) = 0; // ESP (игнорируется popa)
    *(--esp) = 0; // EBP
    *(--esp) = 0; // ESI
    *(--esp) = 0; // EDI
    *(--esp) = 0x10; // DS
    *(--esp) = 0x10; // ES
    *(--esp) = 0x10; // FS
    *(--esp) = 0x10; // GS/ eflags

    proc->esp = (uint32_t)esp;
    proc->PID = get_next_pid();
    strncpy(proc->pname, name, 32);
    proc->pright = right;
    proc->state = state;
    memset(&proc->mailbox, 0, sizeof(mailbox_t)); 
    proc->ishas_msg = 0;
    if(process_list == 0){
        process_list = proc;
        proc->next = proc;
    }else{
        process_t* last = process_list;
        while(last->next != process_list){
            last = last->next;
        }
        proc->next = process_list;
        last->next = proc;
        process_list = proc;
    }
    proc->towhom = 0;
    return proc;
}

error_mem:
    free(proc);

error:
    return 0;









void init_ata()
{
    uint32_t ahci_base = scan_buses(); 
    if (ahci_base == 0) return;
    HBA_MEM_t *BAR5 = (HBA_MEM_t*)ahci_base;
    BAR5->GHC |= (1U << 31); 
    uint32_t PI = BAR5->PI;
    for(uint32_t i = 0; i < COUNT_PORTS; i++){
        if((PI >> i) & 1){
            HBA_PORT_t *port = &BAR5->PORTS[i];
            uint32_t DET = port->SSTS & 0x0F;
            if(DET != 3) continue;
            if (port->SIG == 0) {
                port->CMD |= (1 << 4); 
                for(int wait = 0; wait < 1000000; wait++) __asm__("nop");
                port->CMD &= ~(1 << 4); 
            }
            uint32_t sig = port->SIG;
            if(sig == 0x00000101 || sig == 0xEB140101){
                port->CMD &= ~((1 << 0) | (1 << 4));
                while(port->CMD & (1 << 15 | 1 << 14)); 
                rebase(port);
                disk_port = port;
                return;
            }
        }
    }
    CREATE_PROCESS()
}








#define UNIQ(id, name, func, type, waxed, returned_type, type_func)                                               \
    static type_func wrapper_##func(void* data) {                                                                 \
        if (waxed == 0) {                                                                                         \
            __builtin_choose_expr(                                                                                \
                __builtin_types_compatible_p(type_func, void),                                                    \
                (void)((void(*)(void))func)(),                                                                    \
                return (type_func)((returned_type(*)(void))func)()                                                \
            );                                                                                                    \
        } else {                                                                                                  \
            __builtin_choose_expr(                                                                                \
                __builtin_types_compatible_p(type_func, void),                                                    \
                (void)__builtin_choose_expr(                                                                      \
                    (__builtin_types_compatible_p(type, char*) || __builtin_types_compatible_p(type, void*)),     \
                    ((void(*)(type))func)((type)data),                                                            \
                    ((void(*)(type))func)(*(type*)data)),                                                         \
                return (type_func)__builtin_choose_expr(                                                          \
                    (__builtin_types_compatible_p(type, char*) || __builtin_types_compatible_p(type, void*)),     \
                    func((type)data),                                                                             \
                    func(*(type*)data))                                                                           \
            );                                                                                                    \
        }                                                                                                         \
        /* Финальный возврат для не-void функций, чтобы компилятор не ругался */                                  \
        __builtin_choose_expr(                                                                                    \   
            __builtin_types_compatible_p(type_func, void),                                                        \
            (void)0,                                                                                              \
            return (type_func)0                                                                                   \
        );                                                                                                        \
    }                                                                                                               
VGA_LIST
#undef UNIQ
