#include "loadMatrix.h"
#include "multiplicationAlg.h"
#include "jMatrix.h"
#include "zMatrix.h"


using namespace std;



template 	<class 	T>
void	test1( 	ifstream		&infileA,
				ifstream		&infileB,
				T 				&typeRef
 ) 
{
		sizeofMatrix 	sizeA, sizeB;
		sizeA = getMatrixSize( infileA, typeRef );
		sizeB = getMatrixSize( infileB, typeRef );

		if ( ! (sizeA.rows && sizeA.columns && sizeB.rows && sizeB.columns) ) {
				cout << "Oops! At least one of the matrices is of size zero.\n" << endl;
				return;
		}

		vector< vector<T> >	matrixA(sizeA.rows, vector<T>(sizeA.columns));
		vector< vector<T> >	matrixB(sizeB.rows, vector<T>(sizeB.columns));

		loadMatrix( matrixA, infileA );
		loadMatrix( matrixB, infileB );

		if ( sizeA.columns == sizeB.rows ) {
				vector<T> 	vec( sizeB.columns, 0 );
				vector< vector<T> >	matrixC(sizeA.rows, vec);

				naiveMultiplication( matrixA, matrixB, sizeA.rows, sizeA.columns, sizeB.columns, matrixC );

				printMatrix( matrixC, sizeA.rows, sizeB.columns );
		}
}



template 	<class 	T>
void	test2( 	ifstream		&infileA,
				ifstream		&infileB,
				T 				&typeRef
 ) 
{
		sizeofMatrix 	sizeA, sizeB;
		sizeA = getMatrixSize( infileA, typeRef );
		sizeB = getMatrixSize( infileB, typeRef );

		if ( ! (sizeA.rows && sizeA.columns && sizeB.rows && sizeB.columns) ) {
				cout << "Oops! At least one of the matrices is of size zero.\n" << endl;
				return;
		}

		jMatrix<T>		matrixA( sizeA.rows, sizeA.columns );
		jMatrix<T>		matrixB( sizeB.rows, sizeB.columns );

		loadMatrix( matrixA, infileA );
		loadMatrix( matrixB, infileB );

		try {
				jMatrix<T>		matrixC( sizeA.rows, sizeB.columns );
				matrixC = matrixA * matrixB;
				cout << matrixC << endl;
		}
		catch ( sizeError &err ) {
				err.display();
		}
		
}




int main (int argc, char* argv[]) {

		string	matrixFileA = "..//inputFiles//a_8x8.in";
		string	matrixFileB = "..//inputFiles//b_8x8.in";

		ifstream	infileA(matrixFileA.c_str(),	ios_base::in);
		ifstream	infileB(matrixFileB.c_str(),	ios_base::in);

		if 	( ! infileA ) {
				cerr << "Oops! Unable to open file A!\n";
				infileB.close();
				return	0;
		}
		else   if 	( ! infileB ) {
				cerr << "Oops! Unable to open file B!\n";
				infileA.close();
				return	0;
		}			
		else {
				double		typeRef;
				test1( infileA, infileB, typeRef );
				cout << "\n\n" << endl;
				test2( infileA, infileB, typeRef );			
		}


		infileA.close();
		infileB.close();

		return 0;
}