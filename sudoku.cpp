#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in) {
    cout << "Failed!" << '\n';
  }
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3)) {
    cout << "  +===========+===========+===========+" << '\n';
  } else {
    cout << "  +---+---+---+---+---+---+---+---+---+" << '\n';
  }
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << '\n';
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) {
    cout << (char) ('1'+r) << "   ";
  }
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */
/* Function to check if board is complete */
bool is_complete(const char board[9][9]) {
	/* Function to check if board is complete 
	 * by ensure there is no '.' in board 2d
	 * array */
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (board[i][j] == '.' || board[i][j] < '1' || board[i][j] > '9') {
				return false;
			}
		}
	}
	return true;
}

/* Function which returns the grid bounds to check for a given position.
 * This is a helper function for make move */
void get_bounds(const int row, const int col, int grid_bounds[]) {
	 grid_bounds[0] = col - col % 3;
	 grid_bounds[1] = grid_bounds[0] + 2;
	 grid_bounds[2] = row - row % 3;
	 grid_bounds[3] = grid_bounds[2] + 2;
}

/* Function to check if there is a duplicate for digit in the row
 * and col */
bool isDuplicatedRowCol(int row, int col, char digit, char board[9][9]) {
	// Check Col
	for (int i = 0; i < 9; i++) {
		if (board[row][i] == digit && i != col) return true;
	}
	// Check Row
	for (int j = 0; j < 9; j++) {
		if (board[j][col] == digit && j != row) return true;
	}
	return false;
}

/* Function to check if there is a duplicate for digit in the grid */
bool isDuplicatedInGrid(int row, int col, char digit, char board[9][9]) {	
	/* Declare array which contains the grid bound for 
	 * digit at the current location. 
	 * elm[0], elm[1] = Left, Right bound, 
	 * elm[2], elm[3] = Top, Bottom bound */
	int grid_bounds[4]; 
	
	/* Function which retrieves the grid bound */
	get_bounds(row, col, grid_bounds);
	
	/* Check if digit i repeated within the grid bound */
	for (int i = grid_bounds[2]; i <= grid_bounds[3]; i++) {
		for (int j = grid_bounds[0]; j <= grid_bounds[1]; j++) {
			if ( i != row && j != col) {
				if (board[i][j] == digit) return true;
			}
		}
	}
	return false;
}

/* Function to check if move can be made, if move is valid
 * return True and make move, otherwise return False */
bool make_move(const char position[2], char digit, char board[9][9]) {
	/* Convert row and col to int 0 - 8 to allow easy access of the
	 * board array */
	int row = position[0] - 'A'; int col = position[1] - '1';

	/* Guard to check against invalid out of bound moves */
	if (row < 0 || row > 8 || col > 8 || col < 0) return false;

	/* Guard to check if board location is empty */
	if (board[row][col] != '.') return false;

	/* Guard to check against insertation of digit at
	 * position (row, col) which would result in the 
	 * duplication of the digit along the row and col */ 	
	if (isDuplicatedRowCol(row, col, digit, board)) return false;

	/* Guard to check against insertation of digit at
	 * position (row, col) which would result in the 
	 * duplication of the digit in the grid */
	if (isDuplicatedInGrid(row, col, digit, board)) return false;

	
	/* Assign board value with digit since it passess all the checks
	 * and return true */
	board[row][col] = digit;
	return true;
}

/* Function which creates a copy of the board and save it in 
 * another file */
bool save_board(const char inputFile[], const char board[9][9]) {
	ofstream output_file;
	output_file.open(inputFile);
  	
	/* Guard to ensure that the file has been opened otherwise, error */
	if (!output_file) return false;	
  	assert(output_file);	
	
	/* Loop through every character on the 9 x 9 board and write into
	 * output file */
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			output_file.put(board[i][j]);
		}
		output_file.put('\n');
	}
	output_file.close();
	return true;
}

/* Function that solves an Sudoku board using the recursive 
 * Backtracking algorithm */
bool solve_board(char board[9][9], bool init /*=True*/, bool disp_count /*=False*/) {
	char position[2];

	/* Variable to Keep track of how many times the solve board 
	   function has been recursively called. If solve board is
	   called for the first time for a new puzzle, the value
	   should be reseted to 0.*/
	static int recursion = 0;
	
	/* Variable to keep track if the puzzle has been solved 
	 * this variable is used to avoid the need to run the is_complete
	 * function when the puzzle has been solved and the function
	 * is being popped from the stack */
	static bool solved = false;

	if (init) {
		/* Check if the board is a valid board - Check only carried
		 * out at the first call of the function */
		if (!isValidSudoku(board)) {
			cout << "Not a valid sudoku board" << endl;
			return false;
		}

		/* The recursion count and the solved function 
		 * needs to be reseted everytime the solve_board 
		 * function is being called for a new puzzle */
		recursion = 0;
		solved = is_complete(board);
	}

	recursion++;

	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			// Converting row - col to the Grid System as defined in the specification
			position[0] = row + 'A'; position[1] =  col + '1';
			if (board[row][col] == '.') {
				for (char try_digit = '1' ; try_digit <= '9'; try_digit++) {
					if (make_move(position, try_digit, board)) {
						solve_board(board, false, disp_count);
						if (solved || is_complete(board)) {
							solved = true;
							/* Optimisation - by setting solved = true, is_complete will not
							 * need to be computed everytime when the recursive calls are being
							 * popped from the stack after the puzzle has been solved*/
							break;
						} else {
							board[row][col] = '.';
						}
					};	
				}
				return is_complete(board);
			}
		}
	}
	if (disp_count)
		cout << "Board is solved. Number of recursive calls = " << recursion << endl;
	return is_complete(board);
}

/* Function to check an empty board or completed board is a valid sudoku board */
bool isValidSudoku(char board[9][9]) {
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {	
			if (board[row][col] != '.') {
				/* Guard to check for duplication along the row and col */ 	
				if (isDuplicatedRowCol(row, col, board[row][col], board)) return false;

				/* Guard to check for duplication in the grid */
				if (isDuplicatedInGrid(row, col, board[row][col], board)) return false;
			}
		}
	}
	return true;
}
