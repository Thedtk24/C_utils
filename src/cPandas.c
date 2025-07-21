#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/string_utils.h"
#include "../include/cPandas.h"

void df_free(DataFrame* df) {
    if (!df) return; 
    for (int i = 0; i < df->n_cols; i++) {
        Column* col = &df->columns[i];
        for (int j = 0; j < df->n_rows; j++) {
            if (col->data[j]) {
                free(col->data[j]);
            }
        }
        free(col->data);
        free(col->name);
    }
    free(df->columns);
    free(df);
}

void df_info(DataFrame* df) {
    if (!df) {
        printf("DataFrame est NULL.\n");
        return;
    }
    printf("DataFrame: %d rows × %d columns\n", df->n_rows, df->n_cols);
    printf("---------------------------------\n");
    for (int i = 0; i < df->n_cols; i++) {
        Column* col = &df->columns[i];
        const char* type_str = "UNKNOWN";
        switch (col->type) {
            case TYPE_INT:    type_str = "int"; break;
            case TYPE_DOUBLE: type_str = "double"; break;
            case TYPE_STRING: type_str = "string"; break;
        }
        printf("[%d] %s (%s)\n", i, col->name, type_str);
    }
}

DataFrame* df_create(int n_cols) {
    if (n_cols <= 0) return NULL;
    DataFrame* df = (DataFrame*)malloc(sizeof(DataFrame));
    if (!df) return NULL;
    df->n_rows = 0;
    df->n_cols = n_cols;
    df->columns = (Column*)malloc(sizeof(Column) * n_cols);
    if (!df->columns) {
        free(df);
        return NULL;
    }
    for (int i = 0; i < n_cols; i++) {
        df->columns[i].name = NULL;    
        df->columns[i].type = TYPE_STRING; 
        df->columns[i].data = NULL;   
    }
    return df;
}

void df_head(DataFrame* df, int n) {
    if (!df) {
        printf("DataFrame est NULL.\n");
        return;
    }
    if (df->n_rows == 0) {
        printf("DataFrame vide: %d colonnes, pas de rangés.\n", df->n_cols);
        return;
    }
    if (n > df->n_rows) n = df->n_rows; 
    for (int c = 0; c < df->n_cols; c++) {
        printf("%s\t", df->columns[c].name ? df->columns[c].name : "(null)");
    }
    printf("\n");
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < df->n_cols; c++) {
            Column* col = &df->columns[c];
            if (col->data == NULL) {
                printf("NULL\t");
                continue;
            }
            switch (col->type) {
                case TYPE_INT:
                    printf("%d\t", *((int*)col->data[r]));
                    break;
                case TYPE_DOUBLE:
                    printf("%.2f\t", *((double*)col->data[r]));
                    break;
                case TYPE_STRING:
                    printf("%s\t", (char*)col->data[r]);
                    break;
                default:
                    printf("?\t");
            }
        }
        printf("\n");
    }
}

void df_shape(DataFrame* df, int* out_rows, int* out_cols) {
    if (!df) {
        if (out_rows) *out_rows = 0;
        if (out_cols) *out_cols = 0;
        return;
    }
    if (out_rows) *out_rows = df->n_rows;
    if (out_cols) *out_cols = df->n_cols;
}

static ColumnType detect_type(const char* s) {
    int has_dot = 0;
    for (int i = 0; s[i]; i++) {
        if (s[i] == '.') has_dot = 1;
        else if (!isdigit((unsigned char)s[i]) && s[i] != '-' && s[i] != '+')
            return TYPE_STRING;
    }
    return has_dot ? TYPE_DOUBLE : TYPE_INT;
}

DataFrame* df_read_csv(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Erreur: ouverture fichier %s\n", filename);
        return NULL;
    }
    char line[1024];
    int row_count = 0;
    if (!fgets(line, sizeof(line), f)) {
        fclose(f);
        return NULL;
    }
    int n_cols;
    char** col_names = str_split(str_strip(line), ",", &n_cols);
    DataFrame* df = df_create(n_cols);
    for (int i = 0; i < n_cols; i++) {
        df->columns[i].name = strdup(col_names[i]);
        df->columns[i].type = TYPE_INT;  
        df->columns[i].data = NULL;
        free(col_names[i]);
    }
    free(col_names);
    char*** temp_data = malloc(sizeof(char**) * 10000); 
    while (fgets(line, sizeof(line), f)) {
        int count;
        char** values = str_split(str_strip(line), ",", &count);
        if (count != n_cols) continue; 
        temp_data[row_count++] = values;
    }
    fclose(f);
    df->n_rows = row_count;
    for (int c = 0; c < n_cols; c++) {
        for (int r = 0; r < row_count; r++) {
            ColumnType t = detect_type(temp_data[r][c]);
            if (t == TYPE_STRING || 
               (t == TYPE_DOUBLE && df->columns[c].type == TYPE_INT)) {
                df->columns[c].type = t;
                if (t == TYPE_STRING) break;
            }
        }
    }
    for (int c = 0; c < n_cols; c++) {
        df->columns[c].data = malloc(sizeof(void*) * row_count);
        for (int r = 0; r < row_count; r++) {
            switch (df->columns[c].type) {
                case TYPE_INT: {
                    int* val = malloc(sizeof(int));
                    *val = atoi(temp_data[r][c]);
                    df->columns[c].data[r] = val;
                    break;
                }
                case TYPE_DOUBLE: {
                    double* val = malloc(sizeof(double));
                    *val = atof(temp_data[r][c]);
                    df->columns[c].data[r] = val;
                    break;
                }
                case TYPE_STRING: {
                    df->columns[c].data[r] = strdup(temp_data[r][c]);
                    break;
                }
            }
        }
    }
    for (int r = 0; r < row_count; r++) {
        for (int c = 0; c < n_cols; c++) {
            free(temp_data[r][c]);
        }
        free(temp_data[r]);
    }
    free(temp_data);
    return df;
}

int df_to_csv(DataFrame* df, const char* filename) {
    if (!df || !filename) return 0;
    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("Error: ouverture fichier %s pour écriture\n", filename);
        return 0;
    }
    for (int c = 0; c < df->n_cols; c++) {
        fprintf(f, "%s", df->columns[c].name ? df->columns[c].name : "");
        if (c < df->n_cols - 1) fprintf(f, ",");
    }
    fprintf(f, "\n");
    for (int r = 0; r < df->n_rows; r++) {
        for (int c = 0; c < df->n_cols; c++) {
            Column* col = &df->columns[c];
            if (col->data && col->data[r]) {
                switch (col->type) {
                    case TYPE_INT:
                        fprintf(f, "%d", *((int*)col->data[r]));
                        break;
                    case TYPE_DOUBLE:
                        fprintf(f, "%.10g", *((double*)col->data[r]));
                        break;
                    case TYPE_STRING:
                        fprintf(f, "%s", (char*)col->data[r]);
                        break;
                }
            }
            if (c < df->n_cols - 1) fprintf(f, ",");
        }
        fprintf(f, "\n");
    }
    fclose(f);
    return 1; 
}

Column* df_get_column(DataFrame* df, const char* col_name) {
    if (!df || !col_name) return NULL;
    for (int i = 0; i < df->n_cols; i++) {
        if (df->columns[i].name && strcmp(df->columns[i].name, col_name) == 0) {
            return &df->columns[i];
        }
    }
    return NULL; 
}

int df_get_column_index(DataFrame* df, const char* col_name) {
    if (!df || !col_name) return -1;
    for (int i = 0; i < df->n_cols; i++) {
        if (df->columns[i].name && strcmp(df->columns[i].name, col_name) == 0) {
            return i;
        }
    }
    return -1; 
}