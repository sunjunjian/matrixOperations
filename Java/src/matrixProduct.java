/*
 *	Matrix operations
 *
 *		- Sam Sun <sunjunjian@gmail.com>, 2012
 */

public class matrixProduct {
	public static void main(String[] args) {
		final static String FILE_NAME_A = "resource/a_8x8.in";
		jMatrix	matrixA = new	jMatrix(FILE_NAME_A);
		
		final static String FILE_NAME_B = "resource/b_8x8.in";
		jMatrix	matrixB = new	jMatrix(FILE_NAME_B);
		
		
		System.out.println();
		//System.out.println(System.getProperty("user.dir"));
		
		jMatrix	matrixC = new jMatrix();
		matrixC = matrixA.multiply(matrixB);
		matrixC.output();
		System.out.println();				
	}
}