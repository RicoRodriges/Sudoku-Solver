#include "SudSolver.h"


SudSolver::SudSolver() {
	Reset();
}

void SudSolver::loadTable(int const (&grid)[9][9]) {
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			for (int k = 0; k < 9; k++)
				cell[y][x].isCandidate[k] = true;
			cell[y][x].value = grid[y][x];
		}
	}
}

void SudSolver::loadTable(int const * const *grid) {
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			for (int k = 0; k < 9; k++)
				cell[y][x].isCandidate[k] = true;
			cell[y][x].value = grid[y][x];
		}
	}
}

void SudSolver::loadTable(int const *grid) {
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			for (int k = 0; k < 9; k++)
				cell[y][x].isCandidate[k] = true;
			cell[y][x].value = grid[y*9 + x];
		}
	}
}

void SudSolver::Reset() {
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			for (int k = 0; k < 9; k++)
				cell[y][x].isCandidate[k] = true;
			cell[y][x].value = 0;
		}
	}
}

bool SudSolver::isTableCorrect() {
	int countCells = 0;
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			if (cell[y][x].value != 0) {
				if (!isCellCorrect(y, x))
					return false;
				countCells++;
			}
		}
	}
	if (countCells >= MIN_DIGITS_IN_TABLE)
		return true;
	else
		return false;
}

bool SudSolver::Solve() {

	if (!isTableCorrect())
		return false;

	// Search unambiguous cells
	do {
		if (Step1())
			return true;
	} while (Step2());

	if (!isSolvable())
		return false;

	// All unambiguous digits were found, but there is no solution
	// Begin brute-force method
	return Bruteforce(-1);
}

bool SudSolver::Step1() {
	bool isFoundSingleCandidate, isSolved;
	int candidateCount, candidateValue;

	do {
		isFoundSingleCandidate = false;
		isSolved = true;

		for (int y = 0; y < 9; y++) {
			for (int x = 0; x < 9; x++) {
				if (cell[y][x].value == 0) {
					candidateCount = 0;
					for (int candidate = 0; candidate < 9; candidate++) {
						if (cell[y][x].isCandidate[candidate] == true) {
							cell[y][x].value = candidate + 1;
							if (isCellCorrect(y, x)) {
								candidateCount++;
								candidateValue = candidate + 1;
							} else
								cell[y][x].isCandidate[candidate] = false;
						}
					}
					if (candidateCount == 1) {
						cell[y][x].value = candidateValue;
						isFoundSingleCandidate = true;
					} else {
						cell[y][x].value = 0;
						isSolved = false;
					}
				}
			}
		}
	} while (isFoundSingleCandidate);

	return isSolved;
}

bool SudSolver::Step2() {
	int count, indexx, indexy;

	for (int candidate = 0; candidate < 9; candidate++) {

		for (int y = 0; y < 9; y++) {
			count = 0;
			for (int x = 0; x < 9; x++) {
				if (cell[y][x].value == 0 && cell[y][x].isCandidate[candidate] == true) {
					count++;
					indexx = x;
				}
			}
			if (count == 1) {
				cell[y][indexx].value = candidate + 1;
				return true;
			}
		}

		for (int x = 0; x < 9; x++) {
			count = 0;
			for (int y = 0; y < 9; y++) {
				if (cell[y][x].value == 0 && cell[y][x].isCandidate[candidate] == true) {
					count++;
					indexy = y;
				}
			}
			if (count == 1) {
				cell[indexy][x].value = candidate + 1;
				return true;
			}
		}

		for (int dy = 0; dy < 3; dy++) {
			for (int dx = 0; dx < 3; dx++) {
				count = 0;
				for (int y = dy*3; y < dy*3+3; y++) {
					for (int x = dx*3; x < dx*3+3; x++) {
						if (cell[y][x].value == 0 && cell[y][x].isCandidate[candidate] == true) {
							count++;
							indexx = x;
							indexy = y;
						}
					}
				}
				if (count == 1) {
					cell[indexy][indexx].value = candidate + 1;
					return true;
				}
			}
		}

	}
	return false;
}

bool SudSolver::isSolvable() {
	bool isFound;

	for (int value = 0; value < 9; value++) {

		for (int y = 0; y < 9; y++) {
			isFound = false;
			for (int x = 0; x < 9; x++) {
				if ((cell[y][x].value == value+1) || (cell[y][x].value == 0 && cell[y][x].isCandidate[value] == true)) {
					isFound = true;
					break;
				}
			}
			if (!isFound)
				return false;
		}

		for (int x = 0; x < 9; x++) {
			isFound = false;
			for (int y = 0; y < 9; y++) {
				if ((cell[y][x].value == value+1) || (cell[y][x].value == 0 && cell[y][x].isCandidate[value] == true)) {
					isFound = true;
					break;
				}
			}
			if (isFound == false)
				return false;
		}

		for (int dy = 0; dy < 3; dy++) {
			for (int dx = 0; dx < 3; dx++) {
				isFound = false;
				for (int y = dy*3; y < dy*3+3 && !isFound; y++) {
					for (int x = dx*3; x < dx*3+3; x++) {
						if ((cell[y][x].value == value+1) || (cell[y][x].value == 0 && cell[y][x].isCandidate[value] == true)) {
							isFound = true;
							break;
						}
					}
				}
				if (isFound == false)
					return false;
			}
		}
	}
	return true;
}

bool SudSolver::isCellCorrect(const int celly, const int cellx) {	
	int value = cell[celly][cellx].value;

	// row
	for (int x = 0; x < 9; x++)
		if (cell[celly][x].value == value && x != cellx)
			return false;

	// column
	for (int y = 0; y < 9; y++)
		if (cell[y][cellx].value == value && y != celly)
			return false;

	// 3x3 block
	int starty = int(celly/3)*3;
	int startx = int(cellx/3)*3;
	for (int y = starty; y < starty+3; y++)
		for (int x = startx; x < startx+3; x++)
			if (cell[y][x].value == value && x != cellx && y != celly)
				return false;

	return true;
}

void SudSolver::getSolution(int (*result)[9][9]) {
	for (int x = 0; x < 9; x++)
		for (int y = 0; y < 9; y++)
			(*result)[y][x] = cell[y][x].value;
}

void SudSolver::getSolution(int ***result) {
	for (int x = 0; x < 9; x++)
		for (int y = 0; y < 9; y++)
			(*result)[y][x] = cell[y][x].value;
}

void SudSolver::getSolution(int **result) {
	for (int x = 0; x < 9; x++)
		for (int y = 0; y < 9; y++)
			(*result)[y*9 + x] = cell[y][x].value;
}

bool SudSolver::Bruteforce(int index) {
	index++;
	if (index == 9*9)
		return true;

	int x = index % 9;
	int y = index / 9;

	if (cell[y][x].value != 0) {
		return Bruteforce(index);
	} else {
		for (int candidate = 0; candidate < 9; candidate++) {
			if (cell[y][x].isCandidate[candidate] == false)
				continue;
			cell[y][x].value = candidate + 1;
			if (isCellCorrect(y, x))
				if (Bruteforce(index))
					return true;
		}
		cell[y][x].value = 0;
	}
	return false;
}