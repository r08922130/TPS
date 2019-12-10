
#include "read_file.h"
#include "tps.h"

int main(int argc, char** argv){
    Point source[SIZE];

    //******************************  
    //****** read source file ******
    //****************************** 
    int i = 0 , n = 0;
    n = read_to_array(argv[1], source);
    Point target[SIZE];

    //******************************  
    //****** read target file ******
    //******************************
    n = read_to_array(argv[2], target);


    double w[2][SIZE];
    // ***** get the weight of TPS model *****
    getTPS(n,source,target,w);
    Point points[IMG_WIDTH*IMG_HEIGHT];
    Point o_points[IMG_WIDTH*IMG_HEIGHT];
    for (int r = 0 ; r <IMG_HEIGHT ; r++) {
        for (int c = 0 ; c < IMG_WIDTH ; c++){
            //printf("%lf\n",c - floor(IMG_WIDTH/2));
            points[r*IMG_WIDTH +c].x = c - floor(IMG_WIDTH/2);
            points[r*IMG_WIDTH +c].y = r - floor(IMG_WIDTH/2);
            o_points[r*IMG_WIDTH +c].x =points[r*IMG_WIDTH +c].x;
            o_points[r*IMG_WIDTH +c].y =points[r*IMG_WIDTH +c].y;
        }
        
    } 


    // *** TPS mapping ***
    TPS(n,w,points,source);
    
    // ******************
    // ****** plot ******
    // ******************
    {
        char * commandsForGnuplot_2[] = {"set title \"Original\"", "plot 'o_data.temp'"};
        char * commandsForGnuplot[] = {"set title \"Mapped\"", "plot 'data.temp'"};

        FILE * temp = fopen("data.temp", "w");
        /*Opens an interface that one can use to send commands as if they were typing into the
        *     gnuplot command line.  "The -persistent" keeps the plot open even after your
        *     C program terminates.
        */
        
        FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
        
        for (i=0; i < IMG_WIDTH*IMG_HEIGHT; i++){
            fprintf(temp, "%lf %lf \n", points[i].x, points[i].y); //Write the data to a temporary file
        }

        for (i=0; i < NUM_COMMANDS; i++){
            
            fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
        }
        temp = fopen("o_data.temp", "w");
        gnuplotPipe = popen ("gnuplot -persistent", "w");
        
        for (i=0; i < IMG_WIDTH*IMG_HEIGHT; i++){
            fprintf(temp, "%lf %lf \n", o_points[i].x, o_points[i].y); //Write the data to a temporary file
        }

        for (i=0; i < NUM_COMMANDS; i++){    
            fprintf(gnuplotPipe, "%s \n", commandsForGnuplot_2[i]); //Send commands to gnuplot one by one.
        }
    }
    return 0;
}