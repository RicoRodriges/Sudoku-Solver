package com.RicoRodriges;

public class SudSolver {
	private class Cells {
		public int value;
		public boolean isCandidate[] = new boolean[9];
	};

	private Cells[][] cell = new Cells[9][9];
	private final int MIN_DIGITS_IN_TABLE = 12;

	public SudSolver() {
		for (int y = 0; y < 9; y++) {
			for (int x = 0; x < 9; x++) {
				cell[y][x] = new Cells();
				for (int k = 0; k < 9; k++)
					cell[y][x].isCandidate[k] = true;
				cell[y][x].value = 0;
			}
		}
	}

	/**
	 * Initialize sudoku table.
	 * 
	 * @param grid
	 *            is array[9][9] with sudoku digits. Blank cells are indicated
	 *            by zero.
	 */
	public void loadTable(int[][] grid) {
		for (int y = 0; y < 9; y++) {
			for (int x = 0; x < 9; x++) {
				for (int k = 0; k < 9; k++)
					cell[y][x].isCandidate[k] = true;
				cell[y][x].value = grid[y][x];
			}
		}
	}

	/** Clear sudoku table */
	public void Reset() {
		for (int y = 0; y < 9; y++) {
			for (int x = 0; x < 9; x++) {
				for (int k = 0; k < 9; k++)
					cell[y][x].isCandidate[k] = true;
				cell[y][x].value = 0;
			}
		}
	}

	/** Checks the uniqueness of numbers in row, column and block */
	public boolean isTableCorrect() {
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

	/**
	 * Solve sudoku.
	 * 
	 * @return true, if sudoku has been solved, else it has no solutions.
	 */
	public boolean Solve() {

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

	/**
	 * Return modified sudoku table.
	 * 
	 * @param result
	 *            is array[9][9]. If Solve() return true then it is answer. If
	 *            Solve() return false then it is table with all unambiguous
	 *            digits.
	 */
	public void getSolution(int[][] result) {
		for (int x = 0; x < 9; x++)
			for (int y = 0; y < 9; y++)
				result[y][x] = cell[y][x].value;
	}

	public String toString() {
		String str = "";
		for (int y = 0; y < 9; y++) {
			if (y != 0 && y % 3 == 0)
				str += "\r\n";
			for (int x = 0; x < 9; x++) {
				if (x % 3 == 0)
					str += " ";
				str += cell[y][x].value + " ";
			}
			str += "\r\n";
		}
		return str;
	}

	/**
	 * Pushes digit in the cell when the row, column and block have all the
	 * numbers from 1 to 9, except for the current one.
	 * 
	 * @return true if sudoku has been solved.
	 */
	private boolean Step1() {
		boolean isFoundSingleCandidate, isSolved;
		int candidateCount, candidateValue;

		do {
			isFoundSingleCandidate = false;
			isSolved = true;

			for (int y = 0; y < 9; y++) {
				for (int x = 0; x < 9; x++) {
					if (cell[y][x].value == 0) {
						candidateValue = candidateCount = 0;
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

	/**
	 * Pushes digit in the cell, if it can be written only in current row,
	 * column or block.
	 * 
	 * @return true if one cell has been changed.
	 */
	private boolean Step2() {
		int count = 0, indexx = 0, indexy = 0;

		for (int candidate = 0; candidate < 9; candidate++) {

			for (int y = 0; y < 9; y++) {
				count = 0;
				for (int x = 0; x < 9; x++) {
					if (cell[y][x].value == 0
							&& cell[y][x].isCandidate[candidate] == true) {
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
					if (cell[y][x].value == 0
							&& cell[y][x].isCandidate[candidate] == true) {
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
					for (int y = dy * 3; y < dy * 3 + 3; y++) {
						for (int x = dx * 3; x < dx * 3 + 3; x++) {
							if (cell[y][x].value == 0
									&& cell[y][x].isCandidate[candidate] == true) {
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

	/** Every row, column and block must have all digits 1-9. */
	private boolean isSolvable() {
		boolean isFound;

		for (int value = 0; value < 9; value++) {

			for (int y = 0; y < 9; y++) {
				isFound = false;
				for (int x = 0; x < 9; x++) {
					if ((cell[y][x].value == value + 1)
							|| (cell[y][x].value == 0 && cell[y][x].isCandidate[value] == true)) {
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
					if ((cell[y][x].value == value + 1)
							|| (cell[y][x].value == 0 && cell[y][x].isCandidate[value] == true)) {
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
					for (int y = dy * 3; y < dy * 3 + 3 && !isFound; y++) {
						for (int x = dx * 3; x < dx * 3 + 3; x++) {
							if ((cell[y][x].value == value + 1)
									|| (cell[y][x].value == 0 && cell[y][x].isCandidate[value] == true)) {
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

	/** Checks the uniqueness of number in row, column and block. */
	private boolean isCellCorrect(int celly, int cellx) {
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
		int starty = (int) (celly / 3) * 3;
		int startx = (int) (cellx / 3) * 3;
		for (int y = starty; y < starty + 3; y++)
			for (int x = startx; x < startx + 3; x++)
				if (cell[y][x].value == value && x != cellx && y != celly)
					return false;

		return true;
	}

	/**
	 * Recursive function.
	 * 
	 * @param index
	 *            = -1 for first step.
	 * @return true, if sudoku has been solved, else it has no solutions.
	 */
	private boolean Bruteforce(int index) {
		index++;
		if (index == 9 * 9)
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
}
