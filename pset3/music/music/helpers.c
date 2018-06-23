// Helper functions for music

#include <cs50.h>
#include <string.h>
#include <math.h>
#include<stdio.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    double x = ((((double)fraction[0])-48)/(((double)fraction[2])-48)*8);
    //printf("%f", ((double)fraction[0]-48));
    //printf("%f", ((double)fraction[2]-48));
    //printf("%f", x);
    return x;
}

// Calculates frequency (in Hz) of a note
int frequency(string note){
    string allnotes[] = {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
    string allnotesv2[] = {"C","Db","D","Eb","E","F","Gb","G","Ab","A","Bb","B"};
    if(strlen(note) == 3){
        int completerotesv3 = (((int)note[2]) - 48)*12;
        int j = 0;
        int n3 = 0;
        for(j=0; n3<1; j++){
            if((note[0]== allnotes[j][0] && note[1] == allnotes[j][1]) || (note[0] == allnotesv2[j][0] && note[1] == allnotesv2[j][1])){
                n3 = j + 1 + completerotesv3;
            }
        }
        //distance from A; 58 is position of A4 n3 is position of the passed note
        double distfromA = n3 - 58;
        //frequency calculation in hz rounded
        int f = (int)round(pow(2,distfromA/12)*440);
        return f;
    }else if(strlen(note) == 2){
        /*Number of complete rotations of */
        int completerotes = (((int)note[1]) - 48)*12;
        int i = 0;
        int n = 0;
        for(i=0; n<1; i++){
            if(note[0] == allnotes[i][0]){
                n = i + 1 + completerotes;
            }
        }
        //distance from A; 58 is position of A4 n is position of the passed note
        double distfromAv2 = n - 58;
        //frequency calculation in hz rounded
        int f2 = (int)round(pow(2,distfromAv2/12)*440);
        return f2;
    }
    else
        return 0;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if(s[0] == '\0'){
        return true;
    }else{
        return false;
    }
}
