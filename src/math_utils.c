#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/math_utils.h"

int math_factorial(int n){
    if(n < 0){
        fprintf(stderr, "Erreur factoriel: n ne peut pas être négatif (%d)\n", n);
        exit(EXIT_FAILURE);
    }
    else if(n == 0){
        return 1;
    }

    int result = 1;

    for(int i = 1; i <= n; i++){
        result = result * i;
    }

    return result;
}

int math_gcd(int a, int b){
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int math_lcm(int a, int b){
    return ((a * b)/math_gcd(a,b));
}

double math_mean(double* arr, int size){
    double sum = 0;

    for(int i = 0; i < size; i++){
        sum = sum + arr[i];
    }

    return (sum/size);
}

double math_median(double* arr, int size){
    if (size <= 0) {
        fprintf(stderr, "Erreur: taille du tableau invalide (%d)\n", size);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] > arr[j]) {
                double temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    if (size % 2 == 1) { 
        return arr[size / 2];                
    } else {                                   
        return (arr[size/2 - 1] + arr[size/2]) / 2.0; 
    }
}

double math_variance(double* arr, int size) {
    if (size <= 0) {
        fprintf(stderr, "Erreur: taille invalide (%d)\n", size);
        exit(EXIT_FAILURE);
    }

    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    double mean = sum / size;

    double variance = 0.0;
    for (int i = 0; i < size; i++) {
        double diff = arr[i] - mean;
        variance += diff * diff;
    }

    return variance / size; 
}
