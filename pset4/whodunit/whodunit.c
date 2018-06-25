#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char *argv[]){
    if(argc != 3){
        fprintf(stderr, "Usage: ./whodunit infile outfile\n");
        return 1;
    }
    char *in = argv[1];
    char *out = argv[2];
    FILE* infile = fopen(in, "r");
    if(infile == NULL){
        fprintf(stderr, "Infile could not be opened for reading\n");
        return 2;
    }
    FILE* outfile = fopen(out, "w");
    if(outfile == NULL){
        fprintf(stderr, "Outfile could not be opened for reading\n");
        return 3;
    }
    BITMAPFILEHEADER first14;
    fread(&first14, sizeof(BITMAPFILEHEADER), 1, infile);
    
    BITMAPINFOHEADER aftbf40;
    fread(&aftbf40, sizeof(BITMAPINFOHEADER), 1, infile);
    
    if (first14.bfType != 0x4d42 || first14.bfOffBits != 54 || aftbf40.biSize != 40 ||
        aftbf40.biBitCount != 24 || aftbf40.biCompression != 0)
    {
        fclose(infile);
        fclose(outfile);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    fwrite(&first14, sizeof(BITMAPFILEHEADER), 1, outfile);
    fwrite(&aftbf40, sizeof(BITMAPINFOHEADER), 1, outfile);
    
    int padding = (4 - (aftbf40.biWidth * 3)%4)%4;
    
    for(int i = 0, biheight = aftbf40.biHeight; i < biheight; i++ ){
        for(int j=0, biwidth = aftbf40.biWidth; j < biwidth; j++){
            BYTE one;
            BYTE two;
            BYTE three;
            fread(&one, sizeof(BYTE), 1, infile);
            fread(&two, sizeof(BYTE), 1, infile);
            fread(&three, sizeof(BYTE), 1, infile);
            
            fputc(0x88, outfile);
            fputc(0x88, outfile);
            fwrite(&three, sizeof(BYTE), 1, outfile);
            
        }
        fseek(infile, padding, SEEK_CUR);
        
        for(int k = 0; k<padding; k++){
            fputc(0x00, outfile);
        }
    }
    
    fclose(infile);
    
    fclose(outfile);
    
    return 0;
    
}