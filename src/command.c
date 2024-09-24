#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./create.h"
#include "./loader.h"

#define CREATE "CREATE" //create table
#define LOAD "LOAD" //load table to memory
#define LIST "list" //list table chunks in memory
#define EXIT "exit" //exit app

int commandInterpreter(char* command) {
    int i = 0;
    char* token[1024];
    char* tmp = strtok(command, " ");
    while (tmp != NULL) {
        token[i] = tmp;
        tmp = strtok(NULL, " ");
        i++;
    }

    //TREE OF COMMANDS
    
    //CREATE [table_name] ...[col_names]
    if(strcmp(token[0], CREATE) == 0) {
        if(token[1] == NULL) {
            printf("<- Error! Table requires name.\n");
            return 0;
        }

        char* col[MAX_COL];
        for(int i = 0; i < MAX_COL + 2; i++) {
            if(i >= 2) col[i - 2] = token[i]; 
        }
        
        createTable(token[1], col);
        return 1;
    //LOAD [table_name] [table_chunk_index]
    } else if (strcmp(token[0], LOAD) == 0) {
        if(token[1] == NULL) {
            printf("<- Error! Table chunk not specified.\n");
            return 0;
        }
        if(token[2] == NULL) {
            printf("<- Error! Chunk index not specified.\n");
            return 0;
        }

        loadTableChunk(token[1], token[2]);
        return 1;
    //list
    } else if (strcmp(token[0], LIST) == 0) {
        for (int i = 0; i < MAX_TABLE_CHUNK_LOADED; i++){
            if(table_chunks_stack[i].name != NULL) {
                printf("<- %i) %s <-> %s\n", 
                    i, 
                    table_chunks_stack[i].name, 
                    table_chunks_stack[i].src);
            }
        }
        return 1;
    //exit
    } else if (strcmp(token[0], EXIT) == 0) {
        printf("<- Exiting...\n");
        return -1;
    //fail
    } else {
        printf("<- Error! Command is not recognized.\n");
        return 0;
    }
}
