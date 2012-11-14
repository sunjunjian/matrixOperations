/**		jMatrix.h  ---  create a matrix class to demonstrate how matrix operation works, for instance,
			A+=3, A+B, A-B, A*B, A(i, j), etc. 

			_____ @ Junjian Sun _______

 **/



#ifndef		_JMATRIXCLASS_H
#define 	_JMATRIXCLASS_H

#include 	<iostream>

using namespace std;


class 	sizeError {
public:
		void 	display() {
				cout << "Oops! Matrices size mismatch, unable to proceed." << endl;
		}
};



template 	<class 	T>
class		jMatrix
{
	public:
			jMatrix( int	rows, int	columns );									// constructor
			jMatrix( const	jMatrix<T> 	& );										// copy constructor
			~jMatrix() {
					delete	[]_element;
			};


			int 	rows() 		const { return 	_rows; }							// get matrix row size
			int 	columns() 	const { return 	_columns; }							// get matrix column size
			T		trace()		const {												// trace
					if ( _rows == _columns && _rows > 0 ) {
							T 		sum = 0;
							for ( int i = 0; i < _rows; i++ )
									sum += _element[i*_columns + i];

							return	sum;
					}
					else
							return	0;
			}


			/**
					special matrices
			 **/

			bool	isUpperTriangular();
			bool	isSymmetric();


			/**	
					operations, including get (i,j) element, transpose, addition, multiplication, etc.
			 **/

			T 	&operator()( int	i, int	j )	const	{							// get (i,j) element 
					return	_element[ (i-1)*_columns + (j-1) ];						// No i,j offset 
			}				


			jMatrix<T>	&operator=(const   jMatrix <T>	&);							// matrix assignment

			jMatrix<T>	transpose() const;											// matrix transpose		


			jMatrix<T> 	&operator+=(const  T	&);									// arithmetic operation
			jMatrix<T> 	operator+(const   jMatrix <T>	&)  const;
			jMatrix<T> 	operator-(const   jMatrix <T>	&)  const;
			jMatrix<T> 	operator*(const   jMatrix <T>	&)  const;


	private:
			int		_rows;
			int 	_columns;
			T 		*_element;

	template 	<class 	Y>
	friend	ostream		&	operator<<( ostream 	&, const jMatrix<Y>		& );	// stream output override
};






/**	    
		--------------- Impletementation  ----------------------------------
 **/
 

// constructor --- returns a matrix of specified row szie and column size with elements equal to sezo.
template 	<class 	T>
jMatrix<T>::jMatrix( int	rows, int	columns ) {
		sizeError	err;
		if ( rows <= 0 || columns <= 0 )
				throw	err;

		_rows	 = rows;
		_columns = columns;
		_element = new T[ _rows * _columns ];

		for ( int i = 0; i < _rows * _columns; i++ )
		 	_element[i] = 0;
}



// copy constructor --- returns a new matrix equals to the given matrix
template 	<class 	T>
jMatrix<T>::jMatrix( const	jMatrix<T> 	&rhs ) {
		_rows 		= rhs._rows;
		_columns 	= rhs._columns;
		_element	= new T[ _rows * _columns ];

		for ( int i = 0; i < _rows * _columns; i++  )
				_element[i] = rhs._element[i];
}



// isTriangular() --- returns if the matrix is triangular
template 	<class 	T>
bool	jMatrix<T>::isUpperTriangular() {
		if ( _rows && ( _rows == _columns ) ) {
				for ( int i = 0; i < ( _rows - 1 ); i++ )
						for (int j = 0; j > i; ++j)
								if ( _element[i*_columns + j] != 0 )
										return 	false;

				return 	true;
		}
		else
				return 	false;
}



// isSymmetric() --- returns if the matrix is symmetric
template 	<class 	T>
bool	jMatrix<T>::isSymmetric() {
		if ( _rows && ( _rows == _columns ) ) {
				for ( int i = 0; i < ( _rows - 1 ); i++ )
						for (int j = 0; j > i; ++j)
								if ( _element[i*_columns + j] != _element[j*_columns + i] )
										return 	false;

				return 	true;
		}
		else
				return 	false;
}



/**		Matrix assignment:
			jMatrix<int> 	a(10, 10), b(5, 5);
			a = b;
 **/
template 	<class 	T>
jMatrix <T>		&jMatrix<T>::operator=( const   jMatrix<T>	&rhs ) {
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
jMatrix <T>		jMatrix<T>::transpose( )  const 
{
	    jMatrix<T> 	result( _columns, _rows );

		for ( int i = 0; i < result._rows; i++  )
				for ( int j = 0; j < result._columns; j++ ) {
						result._element[i*result._columns + j] = _element[j*_columns + i];
				}

		return	result;
}



/**		Add a constant to every element of the matrix:
			jMatrix<int> 	a(10, 10);
			a = a + 3;
 **/
template 	<class 	T>
jMatrix<T>	&jMatrix<T>::operator+=( const	T 	&rhs )  
{  
	    for ( int i = 0; i < _rows * _columns; i++ )  
	      		_element[i] += rhs;  

	    return  *this;  
} 



/**		Matrix addition:
			jMatrix<int> 	a(10, 10), b(10, 10), c(10, 10);
			c = a + b;
 **/
template 	<class 	T>
jMatrix<T>	jMatrix<T>::operator+( const	jMatrix<T>  &rhs )  const  
{  
		sizeError	err;
	    if ( _rows != rhs._rows || _columns != rhs._columns )  
	      		throw err;  

	    jMatrix<T> 	result( _rows, _columns ); 

	    for ( int i = 0; i < _rows * _columns; i++ )  
	    		result._element[i] = _element[i] + rhs._element[i];  

	    return result;  
}



/**		Matrix subtraction:
			jMatrix<int> 	a(10, 10), b(10, 10), c(10, 10);
			c = a - b;
 **/
template 	<class 	T>
jMatrix<T>	jMatrix<T>::operator-( const	jMatrix<T>  &rhs )  const  
{  
		sizeError	err;	    
	    if ( _rows != rhs._rows || _columns != rhs._columns )  
	      		throw err;  

	    jMatrix<T> 	result( _rows, _columns ); 

	    for ( int i = 0; i < _rows * _columns; i++ )  
	    		result._element[i] = _element[i] - rhs._element[i];  

	    return result;  
}



/**		Matrix multiplication:
			jMatrix<int> 	a(10, 10), b(10, 10), c(10, 10);
			c = a * b;
 **/
template 	<class 	T> 
jMatrix<T>	jMatrix<T>::operator*(const		jMatrix<T>  &rhs )  const  
{
		sizeError	err;	    
	    if ( _columns != rhs._rows )  
	      		throw err;  

	    jMatrix<T> 	result( _rows, rhs._columns ); 

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
ostream		&operator<<( ostream	&out, const		jMatrix<T>  &rhs )  
{   
	    for ( int i = 0, k = 0; i < rhs._rows; i++ ) { 
		        for ( int j = 0; j < rhs._columns; j++ )  
		        		out << rhs._element[k++] << "\t";  
		        out << endl;  
	    };  

	    return out;  
}




#endif