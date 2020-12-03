#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/array.h"

static inline int rndm(int n){
    
    srand(time(NULL));
    return rand()/((RAND_MAX/n) + 1);
}
    


static int write_pbm(char **matrix,int m,int n,char *outfile){
    
    FILE *fname;
    int i,j;
    fname=fopen(outfile,"w");
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            fputc((int)matrix[i][j],fname);
        }
        fputc(10,fname);
    }
    fclose(fname);

}

static char **make_random_matrix(int m,int n,double f){
    
    char **M;
    int i,j,k;
    M=make_cmatrix(m,n);
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
            M[i][j]='0';
    while(k<f*m*n){
        i=rndm(m);
        j=rndm(n);
        if(M[i][j]=='0'){
            M[i][j]='1';
            k++;
        }
    }
    return M;

}

static void show_usage(char *progname){
    
    printf("Error %s \n",progname);

}

int main(int argc, char **argv){

    int m,n,s; //image mxn,s seed
    double f; //fill ratio;
    char **M;
    char *outfile;
    char *endptr;
    int status;

    if(argc != 6){
        show_usage(argv[0]);
        return EXIT_FAILURE;
    }

    m=strtol(argv[1],&endptr,10);
    if(*endptr != '\0' || m<1){
        show_usage(argv[0]);
        return EXIT_FAILURE;
    }

    n=strtol(argv[2],&endptr,10);
    if(*endptr != '\0' || n<1){
        show_usage(argv[0]);
        return EXIT_FAILURE;
    }

    s=strtol(argv[3],&endptr,10);
    if(*endptr != '\0' || s<1){
        show_usage(argv[0]);
        return EXIT_FAILURE;
    }

    f=strtod(argv[4],&endptr);
    if(*endptr != '\0' || f>1.0 || f < 0){
        show_usage(argv[0]);
        return EXIT_FAILURE;
    }

    outfile=argv[5];
    M = make_random_matrix(m, n, f);
    if (write_pbm(M, m, n, outfile) == 1)
        status = EXIT_SUCCESS;
    free_cmatrix(M);
    return status;
}
