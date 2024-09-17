#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#define DATA_PATH "./database"
#define INITIAL_COUNTER 0 //initial table counter
#define MAX_COL 16 //max number of table's columns
#define MAX_CHAR 128 //max number of table's entry
#define MAX_NAME 128 //max rows in table file
#define MAX_ROWS_PER_CHUNK 10 //max rows in table file

/**
 * @brief   Creates first & initial table's chunk file.
 * 
 * @param   name_0 First table chunk name. 
 */
int createInitialChunk(char* name_0) {
    FILE *f = fopen(name_0, "w");
    if(f == NULL) return -1;
    fclose(f);
    return 1;
}   

/**
 * @brief   Creates initial table's state file.
 * 
 * @param   name Table name. 
 * @param   name_s Table state file name. 
 * @param   col Table's columns name. 
 */
int createInitialState(char* name, char* name_s, char* col[]) {
    FILE *f_s = fopen(name_s, "w");
    if(f_s == NULL) return -1;
    fprintf(f_s, "%s %i %i\n", name, INITIAL_COUNTER, MAX_ROWS_PER_CHUNK);
    for(int i = 0; i < MAX_COL; i++) {
        if(col[i] == NULL) break;
        fprintf(f_s, "%s ", col[i]);
    }
    fclose(f_s);
    return 1;
}   

/**
 * @brief   Creates new table and save it to file.
 * 
 * @param   name Table name. 
 * @param   col Table's columns name. 
 */
int createTable(char* name, char* col[]) {
    FILE *f, *f_s;

    char* name_0 = malloc(sizeof(char) * strlen(name));
    char* name_s = malloc(sizeof(char) * strlen(name));
    strcpy(name_0, name);
    strcpy(name_s, name);
    strcat(name_0, "_0");
    strcat(name_s, "_s");

    //check if name is unique
    f = fopen(name_0, "r");
    f_s = fopen(name_s, "r");
    if(f != NULL || f_s != NULL) {
        printf("<- Error! Table with given name already exists.\n");
        if(f != NULL) fclose(f);
        if(f_s != NULL) fclose(f_s);
        return -1;
    }

    //check if columns are unique
    for(int i = 0; i < MAX_COL; i++) {
        for(int j = 0; j < MAX_COL; j++) {
            if(col[i] != NULL 
            && col[j] != NULL 
            && i != j 
            && strcmp(col[i], col[j]) == 0) {
                printf("<- Error! Columns are not unique.\n");
                return -1;
            }
        }
    }

    if(createInitialChunk(name_0) == -1) return -1;
    if(createInitialState(name, name_s, col) == -1) return -1;

    printf("<- Table has been created.\n");
    free(name_0);
    free(name_s);
    return 1;
} 
