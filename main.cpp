#include <iostream>
#include <cstdio>
#include "sudoku.h"

using namespace std;

int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============= Pre-supplied functions =============" << "\n\n";

  cout << "Calling load_board():" << '\n';
  load_board("easy.dat", board);

  cout << '\n' << "Displaying Sudoku board with display_board():" << '\n';
  display_board(board);
  cout << "Done!" << "\n\n";

  cout << "=================== Question 1 ===================" << "\n\n";

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete." << "\n\n";

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete." << "\n\n";

  cout << "=================== Question 2 ===================" << "\n\n";

  load_board("easy.dat", board);

  // Should be OK
  cout << "Putting '1' into I8 is ";
	if (!make_move("I8", '1', board)) {
	    cout << "NOT ";
	}
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  // Write more tests
  cout << "\nAdditional Tests" << endl << endl;
  
  // Test 1
  cout << "Putting '1' into I9 is ";
	if (!make_move("I9", '1', board)) {
	    cout << "NOT ";
	}
  cout << "a valid move."<< '\n';
  // Test 2
  cout << "Putting '1' into A8 is ";
	if (!make_move("A8", '1', board)) {
	    cout << "NOT ";
	}
  cout << "a valid move."<< '\n';
  // Test 3
  cout << "Putting '1' into B3 is ";
	if (!make_move("B3", '1', board)) {
	    cout << "NOT ";
	}
  cout << "a valid move."<< '\n';
  // Test 4
  cout << "Putting '1' into E3 is ";
	if (!make_move("E3", '1', board)) {
	    cout << "NOT ";
	}
  cout << "a valid move."<< '\n';
  // Test 5
  cout << "Putting '1' into D1 is ";
	if (!make_move("D1", '1', board)) {
	    cout << "NOT ";
	}
  cout << "a valid move."<< '\n';
  // Test 6
  cout << "Putting '8' into H2 is ";
	if (!make_move("H2", '8', board)) {
	    cout << "NOT ";
	}
  cout << "a valid move."<< '\n';
  
  cout << "=================== Question 3 ===================" << "\n\n";

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board)) {
    cout << "Save board to 'easy-copy.dat' successful." << '\n';
  } else {
    cout << "Save board failed." << '\n';
  }
  cout << '\n';

  cout << "=================== Question 4 ===================" << "\n\n";

  load_board("easy.dat", board);
  if (solve_board(board)) {
  	cout << "The 'easy' board has a solution:" << '\n';
	display_board(board);
  } else {
	cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';

  // write more tests

  load_board("medium.dat", board);
  if (solve_board(board)) {
     cout << "The 'medium' board has a solution:" << '\n';
     display_board(board);
  } else {
     cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';

  // Additional Test Cases
  load_board("test1.dat", board);
  if (solve_board(board)) {
	cout << "The 'test1' board has a solution:" << '\n';
	display_board(board);
  } else {
	cout << "A solution cannot be found." << '\n';
  }
  cout << '\n'; 

  load_board("test2.dat", board);
  if (solve_board(board)) {
	cout << "The 'test2' board has a solution:" << '\n';
	display_board(board);
  } else {
	cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';

  load_board("test3.dat", board);
  if (solve_board(board)) {
  	cout << "The 'test3' board has a solution:" << '\n';
	display_board(board);
  } else {
	cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';

  load_board("test4.dat", board);
  if (solve_board(board)) {
  	cout << "The 'test4' board has a solution:" << '\n';
	display_board(board);
  } else {
	cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';

  load_board("test5.dat", board);
  if (solve_board(board)) {
	cout << "The 'test5' board has a solution:" << '\n';
	display_board(board);
  } else {
	cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';
  
  cout << "=================== Question 5 ===================" << "\n\n";
  load_board("mystery1.dat", board);
  if (solve_board(board, true, true)) {
     cout << "The mystery1 board has a solution:" << '\n';
     display_board(board);
  } else {
     cout << "A solution cannot be found for mystery1." << '\n';
  } 
  cout << '\n';

  load_board("mystery2.dat", board);
  if (solve_board(board, true, true)) {
    cout << "The mystery2 board has a solution:" << '\n';
    display_board(board);
  } else {
	cout << "A solution cannot be found for mystery2." << '\n';
  }
  cout << '\n';

  load_board("mystery3.dat", board);
  if (solve_board(board, true, true)) {
    cout << "The mystery3 board has a solution:" << '\n';
    display_board(board);
  } else {
  	cout << "A solution cannot be found for mystery3." << '\n';
  }
  cout << '\n';

  return 0;
}
