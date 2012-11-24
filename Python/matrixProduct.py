#!/usr/bin/env
# -*- coding:utf-8 -*-

#	matrixProduct.py  --- uses 2D lists to create matrix objects demonstrating
#		how matrix multiplicaion works.
#	1.a 	Multiplication can be done by the naive algorithm - ijk iterations.
#	1.b 	With the beauty of python language, the triple loops can be replaced by a single line.
#	2.   	A better appraoch is to use numpy/scipy packages.
#
#									- Sam Sun <sunjunjian@gmail.com>, 2012


import numpy as np



def LoadFromFile(filename):
	matrix = []

	try:
		f = open(filename, 'r')
	except FileNotFoundError:
		print	'Oops! No such file or directory:', filename
		return	matrix
	else:
		lines = f.readlines()
		f.close()

	for line in lines:
		matrix.append(map(float, (line).split('\t')))

	return	matrix



def NaiveAlg(matrix_a, matrix_b):
	try:
		if len(matrix_a[0]) != len(matrix_b):
			raise	SizeMismatch
	except SizeMismatch:
		print	'Oops! Unable to multiply the matrices due to size mismatch.'
		matrix_c = []
		return	matrix_c


	rows = len(matrix_a)
	columns = len(matrix_b[0])

	matrix_c = [[0 for col in range(columns)] for row in range(rows)]

	for i in range(rows):
		for j in range(columns):
			for k in range(len(matrix_b)):
				matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j]

	return	matrix_c


def OneLineAlg(matrix_a, matrix_b):
	try:
		if len(matrix_a[0]) != len(matrix_b):
			raise	SizeMismatch
	except SizeMismatch:
		print	'Oops! Unable to multiply the matrices due to size mismatch.'
		matrix_c = []
		return	matrix_c
	else:
		# use zip to iterate over two lists in parallel
		return	[ [sum(a * b for a, b in zip(a, b)) for b in zip(*matrix_b)] for a in matrix_a ]





if __name__ == "__main__":
	file1 = '../inputFiles/a_8x8.in'
	file2 = '../inputFiles/b_8x8.in'

	a = LoadFromFile(file1)
	b = LoadFromFile(file2)
	
	# naive algorithm 
	# c = NaiveAlg(a, b)

	c = OneLineAlg(a, b)

	# numpy library
	# a = np.matrix(a)
	# b = np.matrix(a)
	# c = a * b

	for i in range(len(c)):
		print c[i]




