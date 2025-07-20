#ifndef CPANDAS_H
#define CPANDAS_H

typedef enum {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_STRING
} ColumnType;

typedef struct {
    char* name;       
    ColumnType type;    
    void** data;       
} Column;

typedef struct {
    int n_rows;        
    int n_cols;       
    Column* columns;    
} DataFrame;

DataFrame* df_create(int n_cols);
void df_free(DataFrame* df);
void df_info(DataFrame* df);
void df_head(DataFrame* df, int n);
void df_shape(DataFrame* df, int* out_rows, int* out_cols);
DataFrame* df_read_csv(const char* filename);
int df_to_csv(DataFrame* df, const char* filename);
Column* df_get_column(DataFrame* df, const char* col_name);
int df_get_column_index(DataFrame* df, const char* col_name);

#endif