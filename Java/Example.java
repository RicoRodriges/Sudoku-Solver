import java.util.Calendar;
import com.RicoRodriges.SudSolver;

public class Example {

	static int table1[][] = {
		{5,3,0, 0,7,0, 0,0,0},
		{6,0,0, 1,9,5, 0,0,0},
		{0,9,8, 0,0,0, 0,6,0},

		{8,0,0, 0,6,0, 0,0,3},
		{4,0,0, 8,0,3, 0,0,1},
		{7,0,0, 0,2,0, 0,0,6},

		{0,6,0, 0,0,0, 2,8,0},
		{0,0,0, 4,1,9, 0,0,5},
		{0,0,0, 0,8,0, 0,7,9}
	};

	static int table2[][] = {
		{0,1,0, 9,0,0, 7,4,0},
		{0,0,0, 8,0,0, 0,0,3},
		{0,7,0, 3,2,0, 6,9,0},

		{0,0,4, 0,3,0, 2,0,0},
		{0,0,0, 6,0,2, 0,0,0},
		{0,0,8, 0,1,0, 3,0,0},

		{0,8,1, 0,7,0, 0,3,0},
		{3,0,0, 0,0,8, 0,0,0},
		{0,0,0, 0,0,0, 0,0,0}
	};

	static int table3[][] = {
		{0,0,1, 0,3,8, 0,7,0},
		{3,8,0, 0,0,6, 0,9,0},
		{0,0,7, 1,0,0, 0,8,0},

		{2,0,0, 0,6,0, 0,0,8},
		{8,0,0, 0,0,0, 7,0,5},
		{0,0,5, 7,0,1, 0,0,2},

		{0,2,6, 0,1,0, 0,0,0},
		{0,5,0, 2,9,0, 0,0,0},
		{0,0,0, 6,0,0, 8,2,0}
	};

	public static void main(String[] args) {
		boolean result;
		SudSolver solver = new SudSolver();
		long startTime, endTime;

		int sudoku[][] = table1;
		//int sudoku[][] = table2;
		//int sudoku[][] = table3;

		solver.loadTable(sudoku);
		
		startTime = Calendar.getInstance().getTimeInMillis();
		result = solver.Solve();
		endTime = Calendar.getInstance().getTimeInMillis();

		//solver.getSolution(sudoku);
		System.out.println("Time: " + (endTime-startTime) + " ms");
		System.out.println("Is solved: " + (result ? "yes" : "no"));
		System.out.println();
		System.out.print(solver);

	}

}
