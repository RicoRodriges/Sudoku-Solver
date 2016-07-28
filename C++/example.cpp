#include <iostream>
#include <time.h>
#include "SudSolver.h"

using namespace std;

static int table1[9][9] = {
	5,3,0, 0,7,0, 0,0,0,
	6,0,0, 1,9,5, 0,0,0,
	0,9,8, 0,0,0, 0,6,0,

	8,0,0, 0,6,0, 0,0,3,
	4,0,0, 8,0,3, 0,0,1,
	7,0,0, 0,2,0, 0,0,6,

	0,6,0, 0,0,0, 2,8,0,
	0,0,0, 4,1,9, 0,0,5,
	0,0,0, 0,8,0, 0,7,9
};

static int table2[9][9] = {
	0,1,0, 9,0,0, 7,4,0,
	0,0,0, 8,0,0, 0,0,3,
	0,7,0, 3,2,0, 6,9,0,

	0,0,4, 0,3,0, 2,0,0,
	0,0,0, 6,0,2, 0,0,0,
	0,0,8, 0,1,0, 3,0,0,

	0,8,1, 0,7,0, 0,3,0,
	3,0,0, 0,0,8, 0,0,0,
	0,0,0, 0,0,0, 0,0,0
};

static int table3[9][9] = {
	0,0,1, 0,3,8, 0,7,0,
	3,8,0, 0,0,6, 0,9,0,
	0,0,7, 1,0,0, 0,8,0,

	2,0,0, 0,6,0, 0,0,8,
	8,0,0, 0,0,0, 7,0,5,
	0,0,5, 7,0,1, 0,0,2,

	0,2,6, 0,1,0, 0,0,0,
	0,5,0, 2,9,0, 0,0,0,
	0,0,0, 6,0,0, 8,2,0
};

int main() {
	bool result;
	time_t startTime, endTime;
	SudSolver solver;

	// First example
	// int (&sudoku)[9][9] = table1;
	
	// Second example
	int **sudoku = new int*[9];
	for (int i = 0; i < 9; i++) {
		sudoku[i] = new int[9];
		for (int j = 0; j < 9; j++)
			sudoku[i][j] = table2[i][j];
	}

	// Third example
	//int *sudoku = new int[9*9];
	//for (int y = 0; y < 9; y++)
	//	for (int x = 0; x < 9; x++)
	//		sudoku[y*9 + x] = table3[y][x];

	solver.loadTable(sudoku);
	
	startTime = time(nullptr);
	result = solver.Solve();
	endTime = time(nullptr);

	solver.getSolution(&sudoku);
	cout << "Time: " << endTime-startTime << " ms" << endl;
	cout << "Is solved: " << (result ? "yes" : "no") << endl;

	for (int y = 0; y < 9; y++) {
		if (y % 3 == 0)
			cout << endl;
		for (int x = 0; x < 9; x++) {
			if (x % 3 == 0)
				cout << " ";
			cout << sudoku[y][x] << " ";
			// For third example
			//cout << sudoku[y*9 + x] << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < 9; i++)
		delete[] sudoku[i];
	delete[] sudoku;
	return 0;
}