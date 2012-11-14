#	matrixProduct.py  --- uses 2D lists to create matrix objects demonstrating
#		how matrix multiplicaion works.

#	1.a 	Multiplication can be done by the naive algorithm - ijk iterations.
#	1.b 	With the beauty of python language, the triple loops can be replaced by a single line.
#	2.   	A better appraoch is to use numpy/scipy packages.


import numpy as np



def loadFromFile(fileName):
	matrix = []

	try:
		f = open(fileName, 'r')
	except FileNotFoundError:
		print	'Oops! No such file or directory:', fileName
		return	matrix
	else:
		lines = f.readlines()
		f.close()

	for line in lines:
		matrix.append(map(float, (line).split('\t')))

	return	matrix



def naiveAlg(matrixA, matrixB):
	try:
		if len(matrixA[0]) != len(matrixB):
			raise	SizeMismatch
	except SizeMismatch:
		print	'Oops! Unable to multiply the matrices due to size mismatch.'
		matrixC = []
		return	matrixC


	rows = len(matrixA)
	columns = len(matrixB[0])

	matrixC = [[0 for col in range(columns)] for row in range(rows)]

	for i in range(rows):
		for j in range(columns):
			for k in range(len(matrixB)):
				matrixC[i][j] += matrixA[i][k] * matrixB[k][j]

	return	matrixC


def oneLineAlg(matrixA, matrixB):
	try:
		if len(matrixA[0]) != len(matrixB):
			raise	SizeMismatch
	except SizeMismatch:
		print	'Oops! Unable to multiply the matrices due to size mismatch.'
		matrixC = []
		return	matrixC
	else:
		# use zip to iterate over two lists in parallel
		return	[ [sum(a * b for a, b in zip(a, b)) for b in zip(*matrixB)] for a in matrixA ]





if __name__ == "__main__":
	file1 = '../inputFiles/a_8x8.in'
	file2 = '../inputFiles/b_8x8.in'

	A = loadFromFile(file1)
	B = loadFromFile(file2)
	
	#C = naiveAlg(A, B)

	C = oneLineAlg(A, B)

	#A = np.matrix(A)
	#B = np.matrix(B)
	#C = A * B

	for i in range(len(C)):
		print C[i]




