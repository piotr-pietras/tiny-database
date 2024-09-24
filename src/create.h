#define INITIAL_COUNTER 0 //initial table counter
#define MAX_COL 16 //max number of table's columns
#define MAX_CHAR 128 //max number of table's entry
#define MAX_NAME 128 //max rows in table file
#define MAX_ROWS_PER_CHUNK 10 //max rows in table file

/**
 * @brief   Creates new table and save it to file.
 * 
 * @param   name Table name. 
 * @param   col Table's columns name. 
 */
int createTable(char* name, char* col[]);
