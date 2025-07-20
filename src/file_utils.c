#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/file_utils.h"

char* file_read_all(const char* filename) {
    FILE *file = fopen(filename, "rb"); 
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file); 
    char *buffer = malloc(size + 1);
    if (!buffer) {
        perror("malloc");
        fclose(file);
        return NULL;
    }
    size_t bytesRead = fread(buffer, 1, size, file);
    buffer[bytesRead] = '\0'; 
    fclose(file);
    return buffer; 
}

int file_write_all(const char* filename, const char* content){
    FILE *file = fopen(filename, "w"); 
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    size_t written = fwrite(content, 1, strlen(content), file);
    fclose(file);
    if (written != strlen(content)) {
        fprintf(stderr, "Erreur: tout n'a pas ete ecrit\n");
        exit(EXIT_FAILURE);
    }
    return 0; 
}

char** file_read_lines(const char* filename, int* out_count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        return NULL;
    }
    char **lines = NULL;
    int count = 0;
    char buffer[1024]; 
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        lines = realloc(lines, sizeof(char*) * (count + 1));
        if (!lines) {
            perror("realloc");
            fclose(file);
            return NULL;
        }
        lines[count] = strdup(buffer);
        if (!lines[count]) {
            perror("strdup");
            fclose(file);
            return NULL;
        }
        count++;
    }
    fclose(file);
    *out_count = count;
    return lines;
}