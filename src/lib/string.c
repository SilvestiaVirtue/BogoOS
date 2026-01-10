#include "string.h"
#include "lib/stdint.h"




size_t strlen(const char* str){
    size_t len_str = 0;
    while(str[len_str]){
        len_str++;
    }
    return len_str;
}



int strcmp(const char* str1, const char* str2){
    while(*str1 && (*str1 == *str2)){
        str1++;
        str2++;
    }
    return *(unsigned char*)str1 - *(unsigned char*)str2;
}


char* strcpy(char* dest, const char* src){
    int i = 0;
    while(src[i] != '\0'){
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}



void* memset(void* dest, int val, size_t len){
    unsigned char* ptr = (unsigned char*)dest;
    while(len-- > 0){
        *ptr = (unsigned char)val;
        ptr++;
    }
    return dest;
}



void* memcpy(void* dest, const void* src, size_t len){
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;
    for(size_t i = 0; i < len; i++){
        d[i] = s[i];
    }
    return d;
}

char* strchr(const char *s, int c){
    while(*s != (char) c){
        if(*s == '\0'){
            return 0;
        }
        s++;
    }
    return (char *)s;
}

char* strlok(char* str, const char *separator){
    static char *last;

    if(str != 0){
        last = str;
    }
    if(last == 0 || *last == '\0'){
        return 0;
    }

    char* start = last;
    while(*start != '\0'){
        int is_separator = 0;
        for(int i = 0; separator[i] != '\0'; i++){
            if(*start == separator[i]){
                is_separator = 1;
                break;
            }
        }
        if(!is_separator){
            break;
        }
        start++;
    }
    if(*start == '\0'){
        last = 0;
        return 0;
    }
    char* end = start;
    while(*end != '\0'){
        int is_separator = 0;
        for(int i = 0; separator[i] != '\0'; i++){
            if(*end == separator[i]){
                is_separator = 1;
                break;
            }
        }
        if(is_separator){
            *end = '\0';
            last = end + 1;
            return start;
        }
        end++;
    }
    last = 0;
    return start;
}

char *optarg = NULL; 
int optind = 1;  
int optopt;     

int getopt(int argc, char* argv[], char* optstring){
    static char *current_word = agrv[optind];
    if(current_word == 0 || current_word[0] == '\0'){
        if(optind >= argc || argv[optind][0] == '-' || argv[optind][0] == '\0'){
            return -1;
        }
        if(strcmp(argv[optind], "--") == 0){
            optind++;
            return -1;
        }
        current_word = argv[optind] + 1;
    }
    char c = *current_word++;
    char* p = strchr(optstring, c);

    if(p == NULL || c = ':'){
        optopt = c;
        return '.';
    }
    if(p[1] == ':'){
        if(current_word == '\0'){
            optarg = current_word;
            cuurent_word = 0;
        }else if(opind + 1 < argc){
            optarg = argv[optind++];
            current_word = 0;
        }else {
            optopt = c;
            return ':';
        }
    }
    if(current_word == 0 || *current_word == 0){
        optind++;
    }
    return c;
}
