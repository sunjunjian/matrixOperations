public class matrixProduct {
	public static void main(String[] args) {
		String fileNameA = "resource/a_8x8.in";
		jMatrix	matrixA = new	jMatrix(fileNameA);
		
		String fileNameB = "resource/b_8x8.in";
		jMatrix	matrixB = new	jMatrix(fileNameB);
		
		
		System.out.println();
		//System.out.println(System.getProperty("user.dir"));
		
		jMatrix	matrixC = new jMatrix();
		matrixC = matrixA.multiply(matrixB);
		matrixC.output();
		System.out.println();				
	}
}