#define DATABASE_PATH "./database"

/**
 * @brief   Builds table's chunk name
 * 
 * @param   table_name
 * @param   chunk_index
 *                 
 * @return Returns chunk name.
 */
char* buildChunkName(char* table_name, char* chunk_index);

/**
 * @brief   Builds table's state name
 * 
 * @param   table_name
 *                 
 * @return Returns state name.
 */
char* buildStateName(char* table_name);

/**
 * @brief   Builds table's chunk path
 * 
 * @param   table_name
 * @param   chunk_index
 *                 
 * @return Returns chunk path.
 */
char* buildChunkPath(char* table_name, char* chunk_index);

/**
 * @brief   Builds table's state path
 * 
 * @param   table_name
 *                 
 * @return Returns state path.
 */
char* buildStatePath(char* table_name);
