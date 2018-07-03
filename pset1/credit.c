#include <cs50.h>
#include <stdio.h>
#include <math.h>


int main(void){
    long long x = get_long_long("number: ");//prompts user for number
    long long copy = x;
    long long numDigits = 0;
    //do while loop that gets the length of the cc#
    do{
        ++numDigits;
        copy = copy / 10;
    } while ( copy );
    long long digits[numDigits];//creates array
    //while loop below puts each digit of the number in an array starting from the 1's place digit
    while( x >= 10 ){
        for(long long i=0; i<numDigits; i++){
            digits[i] = x % 10;
            x = x / 10;
        }
    }
    //for loop below prints item in the array

    //prints the length of the card number
    long long sumtwos[numDigits/2];
    long long k = 1;

    //while loop that puts the addition of each digit of everyother number*2 starting with second to last to an array
        for(long long sumtwosarray = 0; sumtwosarray<numDigits/2; sumtwosarray++){
            if(k< numDigits){
            int twos = 2*digits[k];
            if(twos>=10){
                sumtwos[sumtwosarray] = twos%10 + 1;
            }
            else {
                sumtwos[sumtwosarray] = twos;
            }
            k = k+2;
            }
        }
    long long fintwos = 0;
    //for loop that adds last array
    for( long long count = 0; count<numDigits/2; count++){
        fintwos = fintwos + sumtwos[count];
    }

    long long finregs = 0;
    //for loop that adds everyother number starting with last
    for(long long ones = 0; ones<=numDigits-1; ones= ones+2){
        finregs = finregs + digits[ones];
    }

    if(numDigits == 16){
        if((fintwos+finregs)%10 == 0){
            if(digits[numDigits-1]*10 + digits[numDigits - 2] == 51 || digits[numDigits-1]*10 + digits[numDigits - 2] == 52 || digits[numDigits-1]*10 + digits[numDigits - 2] == 53 || digits[numDigits-1]*10 + digits[numDigits - 2] == 54 || digits[numDigits-1]*10 + digits[numDigits - 2] == 55){
                printf("MASTERCARD\n");}
            else if(digits[numDigits-1] == 4){
                printf("VISA\n");
            }
            else printf("INVALID\n");
        }
        else printf("INVALID\n");
    }
    else if(numDigits == 13){
        if((fintwos+finregs)%10 == 0){
            if(digits[numDigits-1] == 4){
                printf("VISA\n");
            }
            else printf("INVALID\n");
        }
        else printf("INVALID\n");
    }
    else if(numDigits == 15){
        if((fintwos+finregs)%10 == 0){
            if(digits[numDigits-1]*10 + digits[numDigits - 2] == 34 || digits[numDigits-1]*10 + digits[numDigits - 2] == 37){
                printf("AMEX\n");
            }
            else printf("INVALID\n");
        }
        else printf("INVALID\n");
    }
    else printf("INVALID\n");
}






