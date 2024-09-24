#include <string.h>
#include <stdlib.h>

#define DATABASE_PATH "./database"

/**
 * @brief   Builds table's chunk name
 * 
 * @param   table_name
 * @param   chunk_index
 *                 
 * @return Returns chunk name.
 */
char* buildChunkName(char* table_name, char* chunk_index) {
    char* chunk_name = malloc(sizeof(char) * 128);
    strcpy(chunk_name, table_name);
    strcat(chunk_name, "_");
    strcat(chunk_name, chunk_index);
    return chunk_name;
}

/**
 * @brief   Builds table's state name
 * 
 * @param   table_name
 *                 
 * @return Returns state name.
 */
char* buildStateName(char* table_name) {
    char* state_name = malloc(sizeof(char) * 128);
    strcpy(state_name, table_name);
    strcat(state_name, "_s");
    return state_name;
}

/**
 * @brief   Builds table's chunk path
 * 
 * @param   table_name
 * @param   chunk_index
 *                 
 * @return Returns chunk path.
 */
char* buildChunkPath(char* table_name, char* chunk_index) {
    char* chunk_name = buildChunkName(table_name, chunk_index);
    char* chunk_path = malloc(sizeof(char) * 256);
    strcpy(chunk_path, DATABASE_PATH);
    strcat(chunk_path, "/");
    strcat(chunk_path, chunk_name);
    free(chunk_name);
    return chunk_path;
}

/**
 * @brief   Builds table's state path
 * 
 * @param   table_name
 *                 
 * @return Returns state path.
 */
char* buildStatePath(char* table_name) {
    char* state_name = buildStateName(table_name);
    char* state_path = malloc(sizeof(char) * 256);
    strcpy(state_path, DATABASE_PATH);
    strcat(state_path, "/");
    strcat(state_path, state_name);
    free(state_name);
    return state_path;
}

