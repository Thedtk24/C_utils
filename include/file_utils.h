#ifndef FILE_UTILS_C
#define FILE_UTILS_C

char* file_read_all(const char* filename); 
int file_write_all(const char* filename, const char* content);
char** file_read_lines(const char* filename, int* out_count);

#endif