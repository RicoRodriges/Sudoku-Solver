#pragma once
#define MIN_DIGITS_IN_TABLE 12

class SudSolver {
public:
	SudSolver();

	// Initialize sudoku table.
	// Grid is array[9][9] or array[9*9] with sudoku digits. Blank cells are indicated
	// by zero.
	void loadTable(int const (&grid)[9][9]);
	void loadTable(int const * const * grid);
	void loadTable(int const *grid);

	// Clear sudoku table
	void Reset();

	// Checks the uniqueness of numbers in row, column and block
	bool isTableCorrect();

	// Solve sudoku
	// Return true, if sudoku has been solved, else it has no solutions.
	bool Solve();

	// Return modified sudoku table.
	// Result is pointer to array[9][9] or array[9*9].
	// If Solve() return true then it is answer.
	// If Solve() return false then it is table with all unambiguous digits.
	void getSolution(int (*result)[9][9]);
	void getSolution(int ***result);
	void getSolution(int **result);

private:
	struct {
		char value;
		bool isCandidate[9];
	} cell[9][9];

	// Pushes digit in the cell when the row, column and block
	// have all the numbers from 1 to 9, except for the current one.
	// Return true if sudoku has been solved.
	bool Step1();

	// Pushes digit in the cell, if it can be written
	// only in current row, column or block.
	// Return true if one cell has been changed.
	bool Step2();

	// Every row, column and block must have all digits 1-9.
	bool isSolvable();

	// Checks the uniqueness of number in row, column and block.
	bool isCellCorrect(const int celly, const int cellx);
	
	// Recursive function.
	// Index = -1 for first step.
	// Return true, if sudoku has been solved, else it has no solutions.
	bool Bruteforce(int index);
};
