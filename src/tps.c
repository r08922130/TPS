#include "tps.h"

void getTPS( int n ,Point source[SIZE],  Point target[SIZE], double w[2][SIZE]){
    // **********************
    // *** get TPS weight ***
    // **********************

    int L_size = n+3;
    double L[SIZE][SIZE];

    //**** K ****
    for ( int i = 0 ; i < n;i++){
        for (int j = 0; j < i ; j++){
            L[i][j] = U(square_distance(source[i],source[j]));
            L[j][i] = L[i][j];
        }
    }
    //**** P ****
    for(int j = 0 ; j < n;j++){
        L[n][j] = 1;
        L[n+1][j] = source[j].x;
        L[n+2][j] = source[j].y;
        L[j][n] = L[n][j];
        L[j][n+1] = L[n+1][j];
        L[j][n+2] = L[n+2][j];
    }
    printf("\n\n\nThe L matrix is : \n");
    for (int i = 0;i < L_size; i++){
        for (int j = 0;j < L_size; j++){
            
            printf("\t%f", L[i][j]);
        }
    printf("\n");
        }
    double inv[SIZE][SIZE];

    // *** get inverse of L by adjoint matrix ***

    /*float d = determinant(L, L_size);
    if (d == 0)
        printf("\nInverse of Entered Matrix is not possible\n");
    else
        cofactor(L, L_size,inv);*/

    

    //*** get inverse of L by Gaussian-Jordan ***
    inverse(L_size, L, inv);
    
    printf("\n\n\nW a1 ax ay is : \n");
    // *** inverse of L dot target point ***
    for(int i = 0 ; i < L_size; i++){
        double sum_x = 0;
        double sum_y = 0;
        for(int j = 0 ; j < n; j++){
            sum_x += inv[i][j] * target[j].x;
            sum_y += inv[i][j] * target[j].y;
        }
        w[0][i] = sum_x;
        w[1][i] = sum_y;
        printf("\t%lf\t%lf\n", sum_x,sum_y);
    }
}
// the function for inverse matrix by using adjoint matrix   
double determinant(double a[SIZE][SIZE], int k){
    double s = 1, det = 0, b[SIZE][SIZE];
    int i, j, m, n, c;
    
    
    
    if (k == 1){
        return (a[0][0]);
    }else{
        det = 0;
        for (c = 0; c < k; c++){
            m = 0;
            n = 0;
            for (i = 0;i < k; i++){
                for (j = 0 ;j < k; j++){
                    b[i][j] = 0;
                    if (i != 0 && j != c){
                        b[m][n] = a[i][j];
                        if (n < (k - 2))
                            n++;
                        else{
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            det = det + s * (a[0][c] * determinant(b, k - 1));
            s = -1 * s;
        }
    }

    return (det);
}
// the function for inverse matrix by using adjoint matrix   
void cofactor(double num[SIZE][SIZE], double f,double inv[SIZE][SIZE]){
    double b[SIZE][SIZE], fac[SIZE][SIZE];
    int p, q, m, n, i, j;
    for (q = 0;q < f; q++){
        for (p = 0;p < f; p++){
            m = 0;
            n = 0;
            for (i = 0;i < f; i++){
                for (j = 0;j < f; j++){
                    if (i != q && j != p){
                        b[m][n] = num[i][j];
                        if (n < (f - 2))
                            n++;
                        else
                        {
                        n = 0;
                        m++;
                        }
                    }
                }
            }
            fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);
        }
    }
    transpose(num, fac, f,inv);
}
// the function for inverse matrix by using adjoint matrix   
/*Finding transpose of matrix*/ 
void transpose(double num[SIZE][SIZE], double fac[SIZE][SIZE], double r,double inv[SIZE][SIZE]){
    int i, j;
    double b[SIZE][SIZE], inverse[SIZE][SIZE], d;

    for (i = 0;i < r; i++){
        for (j = 0;j < r; j++){
            b[i][j] = fac[j][i];
        }
    }
    d = determinant(num, r);
    for (i = 0;i < r; i++){
        for (j = 0;j < r; j++){
            inverse[i][j] = b[i][j] / d;
        }
    }
    //printf("\n\n\nThe inverse of matrix is : \n");

    for (i = 0;i < r; i++){
        for (j = 0;j < r; j++){
            inv[i][j] = inverse[i][j];
            //printf("\t%f", inverse[i][j]);
        }
        //printf("\n");
    }
}

double U(double r){
    if (r == 0){
        return 0;
    }
    return r * log(r);

}

double square_distance(Point p1, Point p2){
    return pow(p1.x-p2.x,2)+ pow(p1.y-p2.y,2);
}

void TPS(int n,double w[2][SIZE], Point points[IMG_WIDTH*IMG_HEIGHT], Point source[SIZE]){
    // *******************
    // *** TPS mapping ***
    // *******************

    for(int i = 0; i < IMG_WIDTH*IMG_HEIGHT; i++){
        double f_x = 0, f_y=0;
        for ( int j = 0; j < n ; j++){
            f_x += w[0][j] * U(square_distance( points[i], source[j]) );
            f_y += w[1][j] * U(square_distance( points[i], source[j]) );    
        }
        double temp_x = points[i].x;
        double temp_y = points[i].y;
        points[i].x = f_x + w[0][n] + w[0][n+1] * temp_x + w[0][n+2]  * temp_y;
        points[i].y = f_x + w[1][n] + w[1][n+1] * temp_x + w[1][n+2]  * temp_y;
    }
    
}
