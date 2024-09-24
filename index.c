#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "./src/common.h"
#include "./src/command.h"
#include "./src/create.h"


int main(int argc, char const *argv[]){
    printf("#################\n");
    printf("# tiny-database #\n");
    printf("#################\n");

    // creates db dir
    struct stat st = {0};
    if (stat(DATABASE_PATH, &st) == -1) {
        mkdir(DATABASE_PATH, 0700);
    }

    int open = 0;
    while (open >= 0){
        printf("-> ");
        char in[1024];
        fgets(in, 1024, stdin);
        // removes trailing new line
        if ((strlen(in) > 0) && (in[strlen (in) - 1] == '\n')){
            in[strlen (in) - 1] = '\0';
        }
        open = commandInterpreter(in);
    }   
    
    return 0;
}
