# PyC_utils

**PyC** est une bibliothèque C fournissant des utilitaires pour la manipulation de fichiers, de chaînes de caractères, de calculs mathématiques courants, ainsi qu’une structure de type DataFrame pour la manipulation de données tabulaires.

---

## Table des matières

- [Installation](#installation)
- [Modules et Fonctions](#modules-et-fonctions)
  - [DataFrame (`cPandas`)](#dataframe-cpandas)
  - [Utilitaires de fichiers (`file_utils`)](#utilitaires-de-fichiers-file_utils)
  - [Fonctions mathématiques (`math_utils`)](#fonctions-mathématiques-math_utils)
  - [Fonctions sur les chaînes (`string_utils`)](#fonctions-sur-les-chaînes-string_utils)
- [Exemple complet](#exemple-complet)
- [Licence](#licence)

---

## Installation

Le fichier principal "main.c" à la racine du dossier.

Compilez avec :

```sh
gcc -Iinclude src/*.c main.c -o <nom_executable>
./<nom_executable>
```

---

## Modules et Fonctions

### DataFrame (`cPandas`)

Permet de manipuler des tableaux de données hétérogènes (int, double, string).

#### Création et destruction

```c
DataFrame* df_create(int n_cols);
void df_free(DataFrame* df);
```

- **df_create** : Alloue un DataFrame avec `n_cols` colonnes.
- **df_free** : Libère toute la mémoire associée au DataFrame.

#### Lecture et écriture CSV

```c
DataFrame* df_read_csv(const char* filename);
int df_to_csv(DataFrame* df, const char* filename);
```

- **df_read_csv** : Charge un fichier CSV dans un DataFrame.
- **df_to_csv** : Sauvegarde un DataFrame dans un fichier CSV.

#### Informations et affichage

```c
void df_info(DataFrame* df);
void df_head(DataFrame* df, int n);
void df_shape(DataFrame* df, int* out_rows, int* out_cols);
```

- **df_info** : Affiche les informations générales (colonnes, types, taille).
- **df_head** : Affiche les `n` premières lignes.
- **df_shape** : Récupère le nombre de lignes et de colonnes.

#### Accès aux colonnes

```c
Column* df_get_column(DataFrame* df, const char* col_name);
int df_get_column_index(DataFrame* df, const char* col_name);
```

- **df_get_column** : Retourne un pointeur vers la colonne nommée.
- **df_get_column_index** : Retourne l’indice d’une colonne par son nom.

#### Exemple

```c
DataFrame* df = df_read_csv("data.csv");
df_info(df);
df_head(df, 3);
df_free(df);
```

---

### Utilitaires de fichiers (`file_utils`)

#### Lire tout le contenu d’un fichier

```c
char* file_read_all(const char* filename);
```

- Retourne le contenu du fichier sous forme de chaîne (à libérer avec `free`).

#### Écrire dans un fichier

```c
int file_write_all(const char* filename, const char* content);
```

- Écrit `content` dans le fichier. Retourne 0 en cas de succès.

#### Lire un fichier ligne par ligne

```c
char** file_read_lines(const char* filename, int* out_count);
```

- Retourne un tableau de chaînes (une par ligne). `out_count` reçoit le nombre de lignes.

#### Exemple

```c
char* txt = file_read_all("notes.txt");
printf("%s\n", txt);
free(txt);
```

---

### Fonctions mathématiques (`math_utils`)

#### Factorielle

```c
int math_factorial(int n);
```

- Calcule n! (factorielle de n).

#### PGCD et PPCM

```c
int math_gcd(int a, int b);
int math_lcm(int a, int b);
```

- PGCD : Plus Grand Commun Diviseur.
- PPCM : Plus Petit Commun Multiple.

#### Moyenne, médiane, variance

```c
double math_mean(double* arr, int size);
double math_median(double* arr, int size);
double math_variance(double* arr, int size);
```

- Moyenne, médiane et variance d’un tableau de réels.

#### Exemple

```c
double vals[] = {1, 2, 3, 4};
printf("Moyenne : %.2f\n", math_mean(vals, 4));
```

---

### Fonctions sur les chaînes (`string_utils`)

#### Suppression des espaces

```c
char* str_strip(char* s);
```

- Retourne une nouvelle chaîne sans espaces en début/fin.

#### Conversion casse

```c
char* str_lower(char* s);
char* str_upper(char* s);
```

- Retourne une nouvelle chaîne en minuscules/majuscules.

#### Remplacement de sous-chaîne

```c
char* str_replace(char* s, char* old, char* New);
```

- Remplace toutes les occurrences de `old` par `New` dans `s`.

#### Début/fin de chaîne

```c
int str_startswith(char* s, char* prefix);
int str_endswith(char* s, char* suffix);
```

- Retourne 1 si la chaîne commence/finit par le motif.

#### Découpage et jointure

```c
char** str_split(char* s, char* sep, int* out_count);
char* str_join(char* sep, char** parts, int count);
```

- Découpe une chaîne selon un séparateur, ou joint un tableau de chaînes.

#### Exemple

```c
char* s = str_strip("   Hello World!   ");
printf("%s\n", s);
free(s);
```

---

## Exemple complet

```c
#include "../include/cPandas.h"
#include "../include/file_utils.h"
#include "../include/math_utils.h"
#include "../include/string_utils.h"

int main() {
    DataFrame* df = df_read_csv("data.csv");
    df_info(df);
    df_head(df, 5);

    double vals[] = {1, 2, 3, 4, 5};
    printf("Variance : %.2f\n", math_variance(vals, 5));

    char* txt = str_upper("bonjour");
    printf("%s\n", txt);

    return 0;
}
```

---

## Licence

Projet personnel, libre de droits.

---

Pour plus de détails, consultez les fichiers headers dans le dossier
