#include <stdio.h>
#define SIZE 100

void swap(int dim,int row1, int row2, double arr[SIZE][SIZE]);
void non_zero_pivot(int dim, int col, double arr[SIZE][SIZE]);
// **** By Gaussian Elinamation ****
void inverse(int dim, double arr[SIZE][SIZE],double inv[SIZE][SIZE]);
