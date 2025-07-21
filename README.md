
# **C_utils**

**C_utils** est une bibliothèque C fournissant des utilitaires variés :
Manipulation de **fichiers**
Traitement des **chaînes de caractères**
Fonctions **mathématiques** courantes
Structures de type **DataFrame (`cPandas`)** pour la manipulation de données tabulaires
Opérations sur les **matrices (`matrix_utils`)**

---

## **Table des matières**

- [Installation](#installation)
- [Modules et Fonctions](#modules-et-fonctions)
  - [DataFrame (`cPandas`)](#dataframe-cpandas)
  - [Matrices (`matrix_utils`)](#matrices-matrix_utils)
  - [Utilitaires de fichiers (`file_utils`)](#utilitaires-de-fichiers-file_utils)
  - [Fonctions mathématiques (`math_utils`)](#fonctions-mathématiques-math_utils)
  - [Fonctions sur les chaînes (`string_utils`)](#fonctions-sur-les-chaînes-string_utils)
- [Exemple complet](#exemple-complet)
- [Licence](#licence)

---

## **Installation**

Le fichier principal **`main.c`** doit être placé à la racine du projet.

Compilez avec :

```sh
gcc -Iinclude src/*.c main.c -o c_utils
./c_utils
```

ou avec le **Makefile** fourni :

```sh
make
./c_utils
```

Pour nettoyer les fichiers compilés :

```sh
make clean
```

---

## **Modules et Fonctions**

---

### **DataFrame (`cPandas`)**

Permet de manipuler des tableaux de données hétérogènes (int, double, string).

#### **Création et destruction**

```c
DataFrame* df_create(int n_cols);
void df_free(DataFrame* df);
```

#### **Lecture et écriture CSV**

```c
DataFrame* df_read_csv(const char* filename);
int df_to_csv(DataFrame* df, const char* filename);
```

#### **Informations et affichage**

```c
void df_info(DataFrame* df);
void df_head(DataFrame* df, int n);
void df_shape(DataFrame* df, int* out_rows, int* out_cols);
```

#### **Accès aux colonnes**

```c
Column* df_get_column(DataFrame* df, const char* col_name);
int df_get_column_index(DataFrame* df, const char* col_name);
```

#### **Exemple**

```c
DataFrame* df = df_read_csv("data.csv");
df_info(df);
df_head(df, 3);
df_free(df);
```

---

### **Matrices (`cMatrix`)**

Manipulation simple et avancée de matrices.

#### **Création et destruction**

```c
Matrix_t* mat_create(int rows, int cols);
void mat_free(Matrix_t* m);
Matrix_t* mat_identity(int n);
Matrix_t* mat_copy(Matrix_t* m);
```

#### **Affichage et informations**

```c
void mat_print(Matrix_t* m);
double mat_trace(Matrix_t* m);
```

#### **Opérations de base**

```c
Matrix_t* mat_add(Matrix_t* a, Matrix_t* b);
Matrix_t* mat_sub(Matrix_t* a, Matrix_t* b);
Matrix_t* mat_scalar_mul(Matrix_t* a, double k);
Matrix_t* mat_transpose(Matrix_t* a);
Matrix_t* mat_mul(Matrix_t* a, Matrix_t* b);
```

#### **Opérations avancées**

```c
double mat_determinant(Matrix_t* m);
Matrix_t* mat_inverse(Matrix_t* m);
```

#### **Exemple**

```c
Matrix_t* A = mat_create(2, 2);
A->data[0][0] = 4; A->data[0][1] = 7;
A->data[1][0] = 2; A->data[1][1] = 6;

Matrix_t* Inv = mat_inverse(A);

printf("A:\n");
mat_print(A);

printf("A^-1:\n");
mat_print(Inv);

mat_free(A);
mat_free(Inv);
```

---

### **Utilitaires de fichiers (`file_utils`)**

#### **Lire tout le contenu d’un fichier**

```c
char* file_read_all(const char* filename);
```

Retourne le contenu du fichier sous forme de chaîne (à libérer avec `free`).

#### **Écrire dans un fichier**

```c
int file_write_all(const char* filename, const char* content);
```

Écrit `content` dans le fichier. Retourne 0 en cas de succès.

#### **Lire un fichier ligne par ligne**

```c
char** file_read_lines(const char* filename, int* out_count);
```

Retourne un tableau de chaînes (une par ligne). `out_count` reçoit le nombre de lignes.

---

### **Fonctions mathématiques (`math_utils`)**

#### **Factorielle**

```c
int math_factorial(int n);
```

Calcule n! (factorielle de n).

#### **PGCD et PPCM**

```c
int math_gcd(int a, int b);
int math_lcm(int a, int b);
```

- **PGCD** : Plus Grand Commun Diviseur.
- **PPCM** : Plus Petit Commun Multiple.

#### **Moyenne, médiane, variance**

```c
double math_mean(double* arr, int size);
double math_median(double* arr, int size);
double math_variance(double* arr, int size);
```

---

### **Fonctions sur les chaînes (`string_utils`)**

#### **Suppression des espaces**

```c
char* str_strip(char* s);
```

Retourne une nouvelle chaîne sans espaces en début/fin.

#### **Conversion casse**

```c
char* str_lower(char* s);
char* str_upper(char* s);
```

Retourne une nouvelle chaîne en minuscules/majuscules.

#### **Remplacement de sous-chaîne**

```c
char* str_replace(char* s, char* old, char* New);
```

Remplace toutes les occurrences de `old` par `New` dans `s`.

#### **Découpage et jointure**

```c
char** str_split(char* s, char* sep, int* out_count);
char* str_join(char* sep, char** parts, int count);
```

---

## **Exemple complet**

```c
#include "dataframe.h"
#include "matrix.h"
#include "math_utils.h"
#include "string_utils.h"

int main() {
    DataFrame* df = df_read_csv("data.csv");
    df_info(df);
    df_head(df, 5);

    double vals[] = {1, 2, 3, 4, 5};
    printf("Variance : %.2f\n", math_variance(vals, 5));

    Matrix_t* I = mat_identity(3);
    printf("Matrice identité :\n");
    mat_print(I);

    char* txt = str_upper("bonjour");
    printf("%s\n", txt);

    mat_free(I);

    return 0;
}
```

---

## **Licence**

Projet personnel, libre de droits.
