#include "read_file.h"

int read_to_array(char* file_name,Point arr[SIZE]){
    FILE *fp;
    if((fp=fopen(file_name,"r")) == NULL){
        printf("open file error!!\n");
        system("PAUSE");
        exit(0);
    }    
    int i = -1, j = 0,n = 3;
    
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("Retrieved line of length %zu:\n", read);
        //printf("%s", line);
        char* pch = strtok (line," ");
        while (pch != NULL){
            //printf ("%s\n",pch);
            
            if (i < 0){
                sscanf(pch, "%d", &n);
                printf ("%d\n",n);
            }else{
                sscanf(pch, "%lf", &arr[i].x);
                printf ("%f\n",arr[i].x);
                pch = strtok (NULL, " ");
                sscanf(pch, "%lf", &arr[i].y);
                printf ("%f\n",arr[i].y);
            }
            pch = strtok (NULL, " ");
            
        }
        i++;
        
    }
    fclose(fp);
    return n;
}