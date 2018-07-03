#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image");
        return 1;
    }

    FILE *infile = fopen(argv[1], "r");
    if(infile == NULL)
    {
        fprintf(stderr, "File was not opened for reading.");
        return 2;
    }
    // int counter = 0;
    char outer[8] = "000.jpg";
    FILE *outfile = fopen(outer, "w");
    if(outfile == NULL)
    {
        fprintf(stderr, "Outfile was not opened for writing.");
        return 3;
    }
    fseek(infile, 0, SEEK_SET);
    typedef uint8_t  BYTE;
    BYTE buffer[512];
    fread(buffer, sizeof(buffer), 1, infile);
    //for loop to iterate over 50 pictures this is the lazy way, I should have done a better check to keep searching for JPEG sigs until EOF with jtell
    //this will write the signatures found after first iteration
    if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
    {
        fwrite(buffer, sizeof(buffer), 1, outfile);
    }
    //this read 512 bytes until it notices that the first four bytes look like a jpeg signature
    while(buffer[0] != 0xff || buffer[1] != 0xd8 || buffer[2] != 0xff)
    {
        fread(buffer, sizeof(buffer), 1, infile);
        if(feof(infile))
        {
            break;
        }
        //when the first four bytes pass JPEG signature check it will write one 512 byte block and read the next 512 block byte
        while(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            fwrite(buffer, sizeof(buffer), 1, outfile);
            fread(buffer, sizeof(buffer), 1, infile);
            //After writing the first 512 byte block after detecting the JPEG signatures continue
            //reading and writing 512 byte blocks until next JPEG signature detected
            while(buffer[0] != 0xff || buffer[1] != 0xd8 || buffer[2] != 0xff )
            {
                fwrite(buffer, sizeof(buffer), 1, outfile);
                fread(buffer, sizeof(buffer), 1, infile);
                if(feof(infile))
                {
                    break;
                }
            }
            fclose(outfile);
            if(feof(infile))
            {
                break;
            }
            // sprintf(outer, "%.3d.jpg", counter++);
            // this rotates through which JPEG files we should write to
            outer[2] = outer[2] + 1;
            if(outer[2] > '9'){
                outer[2] = '0';
                outer[1] = outer[1] + 1;
            }
            // if(outer[1] == '5' && outer[2] == '1')
            // {
            //     break;
            // }
            outfile = fopen(outer, "w");
            if(outfile == NULL)
            {
                fprintf(stderr, "Outfile was not opened for writing.");
                return 3;
            }
        }
    }
    fclose(infile);
    return 0;
}