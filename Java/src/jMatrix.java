/**  	jMatrix.java --- uses 2-D arrays to create matrix objects
 *		demonstrating how matrix arithmetic operations work.
 *
 *			- Sam Sun <sunjunjian@gmail.com>, 2012
 */


//import java.util.Arrays;
import java.util.ArrayList;
//import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;


public class jMatrix {

	private	int			row;
	private	int			column;
	private	double[][]	elements;
	
	/**    -------- constructor ---------
	 */
	public	jMatrix(int row, int column, double value) {
		this.row = row;
		this.column = column;
		elements = new double[row][column];
		
		for (int i = 0; i < row; i++)
			for (int j = 0; j < column; j++)
				elements[i][j] = value;
	}
	
	public	jMatrix() {
		this(0, 0, 0);
	}
	
	public	jMatrix(int row) {
		this(row, row, 0);
	}
	
	public	jMatrix(int row, int column) {
		this(row, column, 0);
	}
	
	public	jMatrix(double[][] elements) {
		this.elements = elements;
		row = elements.length;
		column = elements[0].length;
	}

	
	public	jMatrix(String fileName) {
		
		try {
			BufferedReader	reader = 
					new BufferedReader(new FileReader(fileName));
			ArrayList<ArrayList<Double>> a2DList = 
					new ArrayList<ArrayList<Double>>();
			
			String	currentLine;
			int		rowCount = 0, columnCount = 0;
			
			// Read a line from the input file, and parse it into a list of doubles,
			// 	then append the list to a 2-D list.
			while ((currentLine = reader.readLine()) != null ) {
				if (currentLine.trim().equals(("")))
						break;
				
				String[]	currentLineElements = currentLine.split("\t");
				columnCount = currentLineElements.length;
				ArrayList<Double> a1DList = new ArrayList<Double>();
								
				for (String anElement : currentLineElements)
					a1DList.add(Double.parseDouble(anElement));
				
				a2DList.add(a1DList);
				
				rowCount++;
			}
			
			row = rowCount;
			column = columnCount;
			
			
			elements = new double[row][column];
			
			for (int i = 0; i < row; i++)
				for (int j = 0; j < column; j++)
					elements[i][j] = a2DList.get(i).get(j);
			
			reader.close();
		} catch (IOException e) {
			e.printStackTrace();
		}	
	}
	
	
	
	
	
	/**    -------- size/trace/special cases ---------
	 */	
	public	int		rows() { return		row; }
	public	int		columns() { return		column; }
	public	double	trace() {
		if ( row == column && row > 0 ) {
			double 		sum = 0;
			for ( int i = 0; i < row; i++ )
					sum += elements[i][i];
			return	sum;
		}
		else
			return	0;
	}
	
	public	boolean		isUpperTriangular() {
		if ( (row > 0) && ( row == column ) ) {
			for ( int i = 0; i < ( row - 1 ); i++ )
					for (int j = 0; j > i; ++j)
							if ( elements[i][j] != 0 )
									return 	false;
			return 	true;
		}
		else
			return 	false;		
	}
	
	public	boolean		isSymmetric() {
		if ( (row > 0) && ( row == column ) ) {
			for ( int i = 0; i < ( row - 1 ); i++ )
					for (int j = 0; j > i; ++j)
							if ( elements[i][j] != 0 )
									return 	false;
			return 	true;
		}
		else
			return 	false;		
	}
	
	
	/**    -------- get (i,j) element/transpose ---------
	 */	
	public	double	getElement(int i, int j) {
		return	elements[i][j];
	}
	
	public	jMatrix	transpose() {
		int			row = this.column;
		int 		column = this.row;
		jMatrix		result = new jMatrix(row, column);
		
		for (int i = 0; i < row; i++)
			for (int j = 0; j < column; j++)
				result.elements[i][j] = elements[j][i];
		
		return	result;
	}
	
	
	/**    -------- addition/subtraction/multiplication ---------
	 */	
	public	void	add(jMatrix m) {
		try {
			if (row != m.rows() || column != m.columns())
				throw new Exception("Oops! Matrices size mismatch, unable to add.\n");		
		} catch (Exception e) {
			e.printStackTrace();
			return;
		}
		
		for (int i = 0; i < row; i++)
			for (int j = 0; j < column; j++)
				elements[i][j] += m.elements[i][j];
	}

	
	public	void	subtract(jMatrix m) {
		try {
			if (row != m.rows() || column != m.columns())
				throw new Exception("Oops! Matrices size mismatch, unable to subtract.\n");		
		} catch (Exception e) {
			e.printStackTrace();
			return;
		}
		
		for (int i = 0; i < row; i++)
			for (int j = 0; j < column; j++)
				elements[i][j] += m.elements[i][j];
	}
	
	
	public	jMatrix		multiply(jMatrix m) {

		try {
			if (row != m.rows() || column != m.columns())
				throw new Exception("Oops! Matrices size mismatch, unable to multiply.\n");		
		} catch (Exception e) {
			e.printStackTrace();
			return	new jMatrix();
		}
		
		jMatrix	result = new jMatrix(row, m.column);
				
		for (int i = 0; i < row; i++)
			for (int j = 0; j < m.column; j++)
				for (int k = 0; k < column; k++)
					result.elements[i][j] += elements[i][k] * m.elements[k][j];
		
		return	result;
	}	
	
	
	/**    -------- I/O ---------
	 */
	public	void	output() {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++)
				System.out.print(elements[i][j] + "\t");
			System.out.println();
		}
	}
	
	
		
		
			
}
