/**		zMatrix.h  ---  create a matrix class to demonstrate how matrix operation works, for instance,
			A+=3, A+B, A-B, A*B, A[i][j], etc. The difference between zMatrix and jMatrix is that
			it replaces A(i, j) with the naive matrix operator A[i][j]. 

			_____ @ Junjian Sun _______

		************************************
		However, the use of [][] is claimed to be slow and hard to maintain due to the difficulty of
			encapsulation and/or parameter checking. 
		
			C++ FAQ [13.12] by Marshall Cline.
		************************************
 **/


#ifndef		_ZMATRIXCLASS_H
#define 	_ZMATRIXCLASS_H

#include 	<iostream>

using namespace std;

template 	<class 	T>
class		zMatrix
{
	public:
			zMatrix( int	rows, int	columns );									// constructor
			zMatrix( const	zMatrix<T> 	& );										// copy constructor
			~zMatrix() {
					delete	[]_element;
			};


			int 	rows() 		const { return 	_rows; }							// get matrix row size
			int 	columns() 	const { return 	_columns; }							// get matrix column size
			T		trace()		const {												// trace
					if ( _rows == _columns && _rows > 0 ) {
							T 		sum = 0;
							for ( int i = 0; i < _rows; i++ )
									sum += _element[i][i];

							return	sum;
					}
					else
							return	0;
			}


			/**	
					operations, including, transpose, addition, multiplication, etc.
			 **/			
			int 	*operator[](int 	pos);

			zMatrix<T>	&operator=(const   zMatrix <T>	&);							// matrix assignment

			zMatrix<T>	transpose() const;											// matrix transpose		


			zMatrix<T> 	&operator+=(const  T	&);									// arithmetic operation
			zMatrix<T> 	operator+(const   zMatrix <T>	&)  const;
			zMatrix<T> 	operator-(const   zMatrix <T>	&)  const;
			zMatrix<T> 	operator*(const   zMatrix <T>	&)  const;


	private:
			int		_rows;
			int 	_columns;
			T 		*_element;

	template 	<class 	Y>
	friend	ostream		&	operator<<( ostream 	&, const zMatrix<Y>		& );	// stream output override
};






/**	    
		--------------- Impletementation  ----------------------------------
 **/
 

// constructor --- returns a matrix of specified row szie and column size with elements equal to sezo.
template 	<class 	T>
zMatrix<T>::zMatrix( int	rows, int	columns ) {
		if ( rows <= 0 || columns <= 0 )
				throw	"Oops! Invalid matrix size detercted.\n";

		_rows	 = rows;
		_columns = columns;
		_element = new T[ _rows * _columns ];

		for ( int i = 0; i < _rows * _columns; i++ )
		 	_element[i] = 0;
}



// copy constructor --- returns a new matrix equals to the given matrix
template 	<class 	T>
zMatrix<T>::zMatrix( const	zMatrix<T> 	&rhs ) {
		_rows 		= rhs._rows;
		_columns 	= rhs._columns;
		_element	= new T[ _rows * _columns ];

		for ( int i = 0; i < _rows * _columns; i++  )
				_element[i] = rhs._element[i];
}



// implement matrix[][] operator 
template 	<class 	T>
int 	*zMatrix<T>::operator[](int 	pos) {
		return 	&_element[pos];
}




//	Matrix assignment:
template 	<class 	T>
zMatrix <T>		&zMatrix<T>::operator=( const   zMatrix<T>	&rhs ) {
		if ( this != &rhs ) {
				delete	[]_element;

				_rows		= rhs._rows;
				_columns	= rhs._columns;
				_element	= new T[ _rows * _columns ];

				for ( int i = 0; i < _rows * _columns; i++  )
						_element[i] = rhs._element[i];
		}

		return	*this;
}



// transpose() --- returns if a transpose matrix
template 	<class 	T>
zMatrix <T>		zMatrix<T>::transpose( )  const 
{
	    zMatrix<T> 	result( _columns, _rows );

		for ( int i = 0; i < result._rows; i++  )
				for ( int j = 0; j < result._columns; j++ ) {
						result._element[i*result._columns + j] = _element[j*_columns + i];
				}

		return	result;
}



/**		Add a constant to every element of the matrix:
			zMatrix<int> 	a(10, 10);
			a = a + 3;
 **/
template 	<class 	T>
zMatrix<T>	&zMatrix<T>::operator+=( const	T 	&rhs )  
{  
	    for ( int i = 0; i < _rows * _columns; i++ )  
	      		_element[i] += rhs;  

	    return  *this;  
} 



/**		Matrix addition:
 **/
template 	<class 	T>
zMatrix<T>	zMatrix<T>::operator+( const	zMatrix<T>  &rhs )  const  
{  
	    if ( _rows != rhs._rows || _columns != rhs._columns )  
	      		throw "Oops! Matrices size mismatch, unable to add.\n";  

	    zMatrix<T> 	result( _rows, _columns ); 

	    for ( int i = 0; i < _rows * _columns; i++ )  
	    		result._element[i] = _element[i] + rhs._element[i];  

	    return result;  
}



/**		Matrix subtraction:
 **/
template 	<class 	T>
zMatrix<T>	zMatrix<T>::operator-( const	zMatrix<T>  &rhs )  const  
{  
	    if ( _rows != rhs._rows || _columns != rhs._columns )  
	      		throw "Oops! Matrices size mismatch, unable to subtract.\n";  

	    zMatrix<T> 	result( _rows, _columns ); 

	    for ( int i = 0; i < _rows * _columns; i++ )  
	    		result._element[i] = _element[i] - rhs._element[i];  

	    return result;  
}



/**		Matrix multiplication:
 **/
template 	<class 	T> 
zMatrix<T>	zMatrix<T>::operator*(const		zMatrix<T>  &rhs )  const  
{
	    if ( _columns != rhs._rows )  
	      		throw "Oops! Matrices size mismatch, unable to multiply.\n";  

	    zMatrix<T> 	result( _rows, rhs._columns ); 

		int offset = 0;
	    for ( int i = 0; i < _rows; i++ )  {
	    		offset = i * _columns;
	    		for ( int j = 0; j < rhs._columns; j++ )
	    				for ( int k = 0; k < _columns; k++ ) {
	    						result._element[offset + j] += _element[offset + k] * rhs._element[k*rhs._columns + j];
	    				}	    		
	    }

	    return result;
}



// overide stream output operator <<
template 	<class 	T>  
ostream		&operator<<( ostream	&out, const		zMatrix<T>  &rhs )  
{   
	    for ( int i = 0, k = 0; i < rhs._rows; i++ ) { 
		        for ( int j = 0; j < rhs._columns; j++ )  
		        		out << rhs._element[k++] << "\t";  
		        out << endl;  
	    };  

	    return out;  
}




#endif