#ifndef STRING_UTILS_H
#define STRING_UTILS_H

char* str_strip(char* s);
char* str_lower(char* s); 
char* str_upper(char* s);
char* str_replace(char* s, char* old, char* New);
int str_startswith(char* s, char* prefix);
int str_endswith(char* s, char* suffix);
char** str_split(char* s, char* sep, int* out_count); 
char* str_join(char* sep, char** parts, int count);

#endif