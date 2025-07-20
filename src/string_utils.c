#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* str_strip(char* s){
    char* new_word;
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

char* str_lower(char* s){
    static char buffer[100]; 
    strncpy(buffer, s, strlen(s));
    for(int i = 0; i < strlen(buffer); i++){
        buffer[i] = tolower(buffer[i]);
    }

    return buffer;
}

char* str_upper(char* s){
    static char buffer[100]; 
    strncpy(buffer, s, strlen(s));
    for(int i = 0; i < strlen(buffer); i++){
        buffer[i] = toupper(buffer[i]);
    }

    return buffer;
}

char* str_replace(char* s, char* old, char* New){
    int i, count = 0;
    int new_len = strlen(New);
    int old_len = strlen(old);

    for (i = 0; s[i] != '\0'; i++) {
        if (strstr(&s[i], old) == &s[i]) {
            count++;
            i += old_len - 1;
        }
    }
    char *result = malloc(i + count * (new_len - old_len) + 1);
    if (!result) return NULL;
    i = 0;
    while (*s) {
        if (strstr(s, old) == s) {
            strcpy(&result[i], New);
            i += new_len;
            s += old_len;
        } else {
            result[i++] = *s++;
        }
    }
    result[i] = '\0';
    return result;
}

int str_startswith(char* s, char* prefix){
    size_t len_prefix = strlen(prefix);
    size_t len_s = strlen(s);

    if (len_prefix > len_s) {
        return 0; 
    }

    return strncmp(s, prefix, len_prefix) == 0;
}

int str_endswith(char* s, char* suffix) {
    size_t len_s = strlen(s);
    size_t len_suffix = strlen(suffix);

    if (len_suffix > len_s) {
        return 0;
    }
    return strcmp(s + len_s - len_suffix, suffix) == 0;
}

char** str_split(char* s, char* sep, int* out_count) {
    char** result = NULL;
    int count = 0;
    char* token;
    char* str = strdup(s);
    token = strtok(str, sep);

    while (token != NULL) {
        result = realloc(result, sizeof(char*) * (count + 1));
        result[count] = strdup(token); 
        count++;
        token = strtok(NULL, sep);
    }
    free(str);  
    *out_count = count;
    return result;
}

char* str_join(char* sep, char** parties, int count) {
    if (count == 0) {
        char* vide = malloc(1);
        vide[0] = '\0';
        return vide;
    }

    size_t sep_len = strlen(sep);
    size_t total_len = 0;

    for (int i = 0; i < count; i++) {
        total_len += strlen(parties[i]);
        if (i < count - 1) {
            total_len += sep_len;
        }
    }
    char* result = malloc(total_len + 1); 
    if (!result) return NULL;
    result[0] = '\0';

    for (int i = 0; i < count; i++) {
        strcat(result, parties[i]);
        if (i < count - 1) {
            strcat(result, sep);
        }
    }
    return result;
}