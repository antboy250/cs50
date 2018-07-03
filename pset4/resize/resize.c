// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize <factor> infile outfile\n");
        return 1;
    }

    // remember filenames
    char *sizer = argv[1];
    char *infile = argv[2];
    char *outfile = argv[3];
    //resizer rate variable
    double multiplier = 0;
    //spplit the floating number doubleo whole and dec #'s!
    string leftofdec = strtok(sizer, ".");
    string rightofdec = strtok(NULL, ".");
    double whole =0;
    double dec = 0;
    for(int i=0; i< strlen(leftofdec); i++){
        if(leftofdec != NULL){
            whole = ((double)leftofdec[i]-48)*pow(10, i);
        }
        if(rightofdec != NULL){
            dec = ((double)rightofdec[i]-48)*pow(10, -(i+1));
        }
    }
    multiplier = whole + dec;

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    BITMAPFILEHEADER bfres;
    bfres = bf;

    BITMAPINFOHEADER bires;
    bires = bi;
    // bfres.bfSize = bf.bfSize*multiplier*multiplier;
    bires.biWidth = bi.biWidth*multiplier;
    bires.biHeight = bi.biHeight*multiplier;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    //get the biSizeImage correct then add 54 for the bfSize

    // determine padding for scanlines
    double padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    double paddingonnew = (4-((int)(bi.biWidth * sizeof(RGBTRIPLE) * (double)multiplier)) % 4) % 4;
    //bfres.bfSize = (bires.biWidth * bires.biHeight) + (paddingonnew * bires.biHeight);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfres, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bires, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (double i = 0, biresHeight = abs(bires.biHeight); i < biresHeight; i++)
    {
       for(double m = 0; m < multiplier; m++){
        // iterate over pixels in scanline
          for (double j = 0; j < bi.biWidth; j++)
          {
              // temporary storage
              RGBTRIPLE triple;

              // read RGB triple from infile
              fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
              //loop to multiply each pixel per row while writing
              for(double dupli = 0; dupli<multiplier; dupli++){
              // write RGB triple to outfile
                  fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
              }
          }
            // then add it back (to demonstrate how)
               for (double k = 0; k < paddingonnew; k++)
               {
                   fputc(0x00, outptr);
               }
            if(m<multiplier-1){
                fseek(inptr, -(bi.biWidth * sizeof(RGBTRIPLE)), SEEK_CUR);
            }
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);


    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
