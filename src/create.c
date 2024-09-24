#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "./common.h"

#define INITIAL_COUNTER 0 //initial table counter
#define MAX_COL 16 //max number of table's columns
#define MAX_CHAR 128 //max number of table's entry
#define MAX_NAME 128 //max rows in table file
#define MAX_ROWS_PER_CHUNK 10 //max rows in table file

/**
 * @brief   Creates first & initial table's chunk file.
 * 
 * @param   chunk0_path First table chunk path. 
 */
int createInitialChunk(char* chunk0_path) {
    FILE *f = fopen(chunk0_path, "w");
    if(f == NULL) return -1;
    fclose(f);
    return 1;
}   

/**
 * @brief   Creates initial table's state file.
 * 
 * @param   name Table name. 
 * @param   state_path Table state file path. 
 * @param   col Table's columns name. 
 */
int createInitialState(char* name, char* state_path, char* col[]) {
    FILE *f_s = fopen(state_path, "w");
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

    char* chunk0_path = buildChunkPath(name, 0);
    char* state_path = buildStatePath(name);

    //check if name is unique
    f = fopen(chunk0_path, "r");
    f_s = fopen(state_path, "r");
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

    if(createInitialChunk(chunk0_path) == -1) return -1;
    if(createInitialState(name, state_path, col) == -1) return -1;

    printf("<- Table has been created.\n");
    free(chunk0_path);
    free(state_path);
    return 1;
} 
