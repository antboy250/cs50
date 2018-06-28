#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    if(argc != 2){
        printf("use well");
    }
    char *sizer = argv[1];
    double multiplier = 0;
    string leftofdec = strtok(sizer, ".");
    string rightofdec = strtok(NULL, ".");
    double whole =0;
    double dec = 0;
    for(int i=0; i< strlen(leftofdec); i++){
        whole = ((double)leftofdec[i]-48)*pow(10, i);
        dec = ((double)rightofdec[i]-48)*pow(10, -(i+1));
    }
    multiplier = whole + dec;
    printf("%f\n", multiplier);

}