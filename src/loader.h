#include <time.h>
#include "./create.h"

#define MAX_TABLE_CHUNK_LOADED 1 //max number of chunks loaded to memory

struct TableChunk {
    char* name;
    char* src;
    int counter;
    int chunk_size;

    char* col_names[MAX_COL];
    char* data[MAX_ROWS_PER_CHUNK][MAX_COL];

    time_t loaded_timestamp;
    time_t lastly_mentioned;
};

struct TableChunk table_chunks_stack[MAX_TABLE_CHUNK_LOADED];

int loadTableChunk(char* chunkName, char* chunkState);
