#include "inverse.h"

void swap(int dim,int row1, int row2, double arr[SIZE][SIZE]){
    
    for ( int c = row1; c < 2*dim;c++){
        

        double temp = arr[row1][c];
        arr[row1][c] = arr[row2][c];
        arr[row2][c] = temp;
    }
}
void non_zero_pivot(int dim, int col, double arr[SIZE][SIZE]){
    int max_r = col;
    int non_zero_value = arr[col][col];
    
    for(int r = col ; r < dim ; r++){
        if(arr[r][col] != 0){
            non_zero_value = arr[r][col];
            max_r = r;
            if(max_r != col){
                swap(dim, col, max_r, arr);
            }
            return ;
            
        }
    }    
}
// **** By Gaussian Elinamation ****
void inverse(int dim, double arr[SIZE][SIZE],double inv[SIZE][SIZE]){
    double a[SIZE][SIZE];
    //printf("Original Matrix\n");
    for (int i = 0 ; i < dim ; i++){
        for (int j = 0 ; j < dim ; j++){
            a[i][j] = arr[i][j];
            //printf("\t%lf",a[i][j]);
        }
        //printf("\n");
    }
    for (int i = 0 ; i < dim ; i++){
        for (int j = dim ; j < 2*dim ; j++){
            if( i+dim == j){
                a[i][j] = 1.0;
            }else{
                a[i][j] = 0.0;
            }
        }   
    }
    for (int k = 0 ; k < dim ; k++){
        // get non-zero pivot
        non_zero_pivot(dim,k,a);
        double head = a[k][k];
        if(head == 0){
            printf("Not Invertible ! \n");
            return;
        }
        for ( int j = k ; j < 2*dim;j++){
            a[k][j] /= head;    
        }
        //printf("\t%lf\n",a[k][k]);
        for(int i = 0 ; i < dim ; i++){
            if(i == k ){
                continue;
            }else{
                double factor = a[i][k] / a[k][k];
                for ( int j = 0 ; j < 2*dim;j++){
                    a[i][j] -= factor * a[k][j];
                    //printf("\t%lf",a[i][j]);
                }
                //printf("\n");
            }
        }
    }
    printf("Inverse Matrix\n");
    for ( int i = 0 ; i < dim ; i++){
        for ( int j = dim ; j < 2*dim ; j++){
            inv[i][j-dim] = a[i][j];
            printf("\t%lf",a[i][j]);
        }
        printf("\n");
    }

}