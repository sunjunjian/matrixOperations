#ifndef 	_LOADMATRIX_H
#define 	_LOADMATRIX_H



#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include "jMatrix.h"


using namespace std;


struct sizeofMatrix {
		int 	rows;
		int 	columns;
};



inline void movetoFileBeginning( ifstream	&infile ) {
		if ( infile.eof() ) 		infile.clear();
		infile.seekg( 0, ios::beg);	
}




template 	<class 	T>
sizeofMatrix getMatrixSize( ifstream	&infile, T 	 &typeRef ) {
		sizeofMatrix 	size;
		size.rows = 0;
		size.columns = 0;

		int 			i = 0;
		string 			str;

		movetoFileBeginning( infile );		

		while ( ! infile.eof() ) {
				getline( infile, str );
				++i;
		}

		size.rows = i - 1;

		movetoFileBeginning( infile );

		if ( size.rows > 0 ) {
				int 			j = 0;

				getline( infile, str );

				istringstream 	ss(str);

				while ( ss >> typeRef ) 
						++j;

				size.columns = j;
		}

		movetoFileBeginning( infile );		

		return size;
}





template 	<class 	T>
void loadMatrix( 	vector< vector <T> > &matrix, 
					ifstream	&infile  ) 
{
		int 		i = 0, j;
		string 		str;
		T			element;

		movetoFileBeginning( infile );

		while ( ! infile.eof() ) {
				getline( infile, str );
				istringstream 	ss(str);
				j = 0;

				while ( ss >> element ) 
						matrix[i][j++] = element;
				
				++i;
		}

		movetoFileBeginning( infile );
}



template 	<class 	T>
void loadMatrix( 	jMatrix<T>	 	&matrix, 
					ifstream		&infile  ) 
{
		int 		i = 1, j;
		string 		str;
		T			element;

		movetoFileBeginning( infile );

		while ( ! infile.eof() ) {
				getline( infile, str );
				istringstream 	ss(str);
				j = 1;

				while ( ss >> element ) 
						matrix( i, j++ ) = element;				// NO i, j OFFSET !!!
				
				++i;
		}

		movetoFileBeginning( infile );
}






template 	<class 	T>
void printMatrix( const vector< vector <T> > &matrix, 
					int rows,
					int columns ) 
{
		for ( int i = 0; i < rows; i++ ) {
				for ( int j = 0; j < columns; j++ ) 
						cout << matrix[i][j] << "\t";
				
				cout << endl;
		}
}


#endif