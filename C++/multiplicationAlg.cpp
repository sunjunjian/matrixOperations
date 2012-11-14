#include "multiplicationAlg.h"

using namespace std;

void  naiveMultiplication( 	const vector< vector <double> > &matrixA,
							const vector< vector <double> > &matrixB,
							int 	rows,
							int 	innerLoop,
							int 	columns,
							vector< vector <double> > &matrixC ) 
{
		for ( int i = 0; i < rows; i++ ) {
			for ( int j = 0; j < columns; j++ ) {
				for ( int k = 0; k < innerLoop; k++ ) {
						matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
				}
			}
		}
}




