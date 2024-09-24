#include <time.h>
#include "./create.h"

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
 * @brief   Loads table chunk from file to memory.
 *          Chunk is also pushed into `table_chunks_stack`. 
 * 
 * @param   chunk_name  Name of the table's chunk file.
 * @param   state_name  Name of the table's state file.
 *                 
 * @return Returns 1 if success, returns 0 if error ocurred.
 */
int loadTableChunk(char* chunk_name, char* state_name);
