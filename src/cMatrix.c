#include <stdio.h>
#include <stdlib.h>
#include "../include/cMatrix.h"

Matrix_t* mat_create(int rows, int cols){
    if(rows <= 0 || cols <= 0) return NULL;

    Matrix_t* mat = malloc(sizeof(Matrix_t));
    if(!mat) return NULL;

    mat -> rows = rows;
    mat -> cols = cols;

    mat -> data = (double**)malloc(rows * sizeof(double*));
    if(!mat -> data){
        free(mat);
        return NULL;
    }

    for(int i = 0; i < rows; i++){
        mat -> data[i] = (double*)malloc(cols * sizeof(double));
        if(!mat -> data[i]){
            for(int k = 0; k < i; k++) free(mat -> data[k]);
            free(mat -> data);
            free(mat);
            return NULL;
        }
        for(int j = 0; j < cols; j++){
            mat -> data[i][j] = 0.0;
        }
    }

    return mat;
}

void mat_free(Matrix_t* mat) {
    if (!mat) return; 
    for (int i = 0; i < mat -> rows; i++) {
        free(mat -> data[i]);
    }
    free(mat -> data);
    free(mat);
}

void mat_print(Matrix_t* mat){
    if(!mat){
        printf("Matrice vide (NULL)\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < mat -> rows; i++){
        printf("( ");
        for(int j = 0; j < mat -> cols; j++){
            printf("%.2f ", mat -> data[i][j]);
        }
        printf(")\n");
    }

    printf("\n");
}

Matrix_t* mat_identity(int n){
    if (n <= 0) return NULL;
    Matrix_t* mat = mat_create(n, n);
    if(!mat) return NULL;
    for(int i = 0; i < n; i++){
        mat -> data[i][i] = 1.0;
    }

    return mat;
}

Matrix_t* mat_copy(Matrix_t* mat){
    if (!mat) return NULL;
    Matrix_t* new_mat = mat_create(mat -> rows, mat -> cols);
    if (!new_mat) return NULL;
    for(int i = 0; i < mat -> rows; i++){
        for(int j = 0; j < mat -> cols; j++){
            new_mat -> data[i][j] = mat -> data[i][j];
        }
    }

    return new_mat;
}

double mat_trace(Matrix_t* mat){
    if(mat -> rows != mat -> cols){
        printf("Ereur dimensions\n");
        exit(EXIT_FAILURE);
    }
    double somme = 0;
    for(int i = 0; i < mat -> rows; i++){
        somme = somme + mat -> data[i][i];
    }
    return somme;
}