#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inverse.h"
#define IMG_WIDTH 41
#define IMG_HEIGHT 41
#define NUM_COMMANDS 2
#ifndef P
#define P
typedef struct{
    double x;
    double y;
}Point;
#endif
//extern struct Point entity;


void getTPS(int n ,Point * source,Point * target,double w[2][SIZE]);

//void inverse_arr(int n ,double arr[SIZE][SIZE],double inv[SIZE][SIZE]);

double U(double r);

double square_distance(Point p1, Point p2);

void TPS(int n,double w[2][SIZE], Point points[1681], Point source[SIZE]);

double determinant(double a[SIZE][SIZE], int k);

void cofactor(double num[SIZE][SIZE], double f,double inv[SIZE][SIZE]);

void transpose(double num[SIZE][SIZE], double fac[SIZE][SIZE], double r,double inv[SIZE][SIZE]);

