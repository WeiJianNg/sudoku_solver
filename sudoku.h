void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);

/* Function to check if board is complete */
bool is_complete(const char board[9][9]);

/* Function which returns the grid bounds for a given position */
void get_bounds(const int row, const int col, int grid_bounds[]);

/* Function to check if there is a duplicate for digit in the grid */
bool isDuplicatedInGrid(int row, int col, char digit, char board[9][9]);

/* Function to check if there is a duplicate for digit in the row and col */
bool isDuplicatedRowCol(int row, int col, char digit, char board[9][9]);

/* Function to mave move, return True if move can be made and
 * modify board, return False if move can't be made and do not
 * change board */
bool make_move(const char position[2], char digit, char board[9][9]);

/* Function which writes the two-dimensional character array board
 * to a file with name filename */
bool save_board(const char inputFile[], const char board[9][9]);

/* Function to sudoku puzzle */
bool solve_board(char board[9][9], bool init = true, bool disp_count = false);

/* Function to check an empty board or completed board is a valid sudoku board */
bool isValidSudoku(char board[9][9]);
