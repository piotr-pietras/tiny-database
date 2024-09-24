#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include "./create.h"
#include "./common.h"

#define MAX_TABLE_CHUNK_LOADED 124 //max number of chunks loaded to memory

struct TableChunk {
    char* name;
    char* src;
    int counter;
    int chunk_size;

    int to_replace; // if 1 it flags the object to be replaced
    int to_save; // if 1 if flags that object has to be saved

    char* col_names[MAX_COL];
    char* data[MAX_ROWS_PER_CHUNK][MAX_COL];

    time_t loaded_timestamp;
    time_t lastly_mentioned;
};

struct TableChunk table_chunks_stack[MAX_TABLE_CHUNK_LOADED];

/**
 * @brief   Pushes chunk into stack. 
 *          It returns -1 if there is no more space in the stack.
 * 
 * @param   chunk [TableChunk]
 */
int pushTableChunk(struct TableChunk* chunk) {
    for(int i = 0; i < MAX_TABLE_CHUNK_LOADED; i++) {
        struct TableChunk* cur = &table_chunks_stack[i];
        if(cur->name == NULL || cur->to_replace == 1){
            table_chunks_stack[i] = *chunk;
            return i;
        }
    }
    return -1;
}

/**
 * @brief   Free one space in array of chunks.
 *          It returns -1 if there is no valid chunk to be freed.
 *          Otherwise it return index of chunk flaged as to_replace.
 */
int freeOneChunk() {
    int to_free = -1;
    time_t expiration = LONG_MAX;
    for(int i = 0; i < MAX_TABLE_CHUNK_LOADED; i++) {
        if(table_chunks_stack[i].lastly_mentioned < expiration){
            expiration = table_chunks_stack[i].lastly_mentioned;
            to_free = i;
        }
    }
    if(to_free == -1) return -1;
    table_chunks_stack[to_free].to_replace = 1;
    return to_free;
}

/**
 * @brief   Mentioning chunk updates chunk's lastly_mentioned property
 *          It allows to leave chunk in memory for longer time
 * 
 * @param   chunk_name [TableChunk]
 */
int mentionChunk(char* chunk_name) {

}

/**
 * @brief   Populates chunk with table's states from file.
 * 
 * @param   f_s [FILE] Table state file. 
 * @param   chunk [TableChunk]
 */
void populateChunkStateFromFile(FILE* f_s, struct TableChunk* chunk) {
    int i = 0, j = 0;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), f_s) != NULL) {
        char* token = strtok(buffer, " ");
        while(token != NULL) {
            if(i == 0) {
                if(j == 0) { //TODO: easier ???
                    char* src = malloc(sizeof(char) * strlen(token));
                    strcpy(src, token);
                    chunk->src = src;
                }
                if(j == 1) chunk->counter = atoi(token);
                if(j == 2) chunk->chunk_size = atoi(token);
            } 
            if(i == 1) chunk->col_names[j] = token;
            token = strtok(NULL, " ");
            j++;
        }
        i++;
    }
}

/**
 * @brief   Populates chunk with table's data from file.
 * 
 * @param   f [FILE] Table data file. 
 * @param   chunk [TableChunk]
 */
void populateChunkDataFromFile(FILE* f, struct TableChunk* chunk) {
    int i = 0, j = 0;
    char buffer[MAX_CHAR * MAX_COL + MAX_COL];
    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        char* token = strtok(buffer, " ");
        j = 0;
        while(token != NULL) {
            chunk->data[i][j] = token;
            token = strtok(NULL, " ");
            j++;
        }
        i++;
    }
}

/**
 * @brief   Loads table chunk from file to memory.
 *          Chunk is also pushed into `table_chunks_stack`. 
 * 
 * @param   chunk_name  Name of the table's chunk file.
 * @param   state_name  Name of the table's state file.
 *                 
 * @return Returns 1 if success, returns 0 if error ocurred.
 */
int loadTableChunk(char* name, char* chunk_index) {
    int i, j;
    FILE *f, *f_s;
    char* chunk_name = buildChunkName(name, chunk_index);
    char* chunk_path = buildChunkPath(name, chunk_index);
    char* state_path = buildStatePath(name);

    f = fopen(chunk_path, "r");
    if(f == NULL) {
        printf("<- Error! Table chunk not found.\n");
        free(chunk_name);
        free(chunk_path);
        free(state_path);
        return 0;
    }
    f_s = fopen(state_path, "r");
    if(f_s == NULL) {
        printf("<- Error! Table state not found.\n");
        free(chunk_name);
        free(chunk_path);
        free(state_path);
        return 0;
    }

    struct TableChunk chunk;
    populateChunkStateFromFile(f_s, &chunk);
    populateChunkDataFromFile(f, &chunk);
    time_t timestamp = time(NULL);
    chunk.loaded_timestamp = timestamp;
    chunk.lastly_mentioned = timestamp;
    chunk.name = chunk_name;
    chunk.to_replace = 0;
    chunk.to_save = 0;

    if(pushTableChunk(&chunk) == -1) {
      freeOneChunk();
      pushTableChunk(&chunk);
    };

    printf("<- Table chunk has been loaded to memory.\n");
    fclose(f);
    fclose(f_s);
    free(chunk_path);
    free(state_path);
    return 1;
}
