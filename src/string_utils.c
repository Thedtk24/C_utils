#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char* str_strip(const char* s){
    const char* new_word;
    static char buffer[100]; 
    int i = 0;

    if (!isspace((unsigned char)s[0])) {
        for (i = 0; i < strlen(s); i++) {
            if (isspace((unsigned char)s[i])) {
                break; 
            }
        }
        strncpy(buffer, s, i);
        buffer[i] = '\0';
        return buffer;
    }
    else{
        int j = 0;
        while (s[j] != '\0' && isspace((unsigned char)s[j])) {
            j++;
        }
        new_word = &s[j];

        int k = 0;
        for (k = 0; k < strlen(new_word); k++) {
            if (isspace((unsigned char)new_word[k])) {
                break; 
            }
        }
        strncpy(buffer, new_word, k);
        buffer[k] = '\0';
        return buffer;
    }

    return s;
}