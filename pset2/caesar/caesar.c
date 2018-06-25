#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(int argc, string argv[]){
    
    if(argc != 2){
        printf("Did not enter 1 and only 1 command-line argument!!\n");
        return 1;
    }
    else{
        string word = get_string("plaintext: ");
        int counter = 0;
        while(word[counter] != '\0'){
            counter++;
        }
        int counter2 = 0;
        int numtolet = 0;
        int length = strlen(argv[1]);
        while(argv[1][counter2] != '\0'){
            numtolet = numtolet + (((int) argv[1][counter2])-48) * pow(10,length-1);
            length--;
            counter2++;
        }
        int i = 0;
        int newword[counter];
        for(i=0; i<counter;i++){
            if((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z')){
                newword[i] = (int) word[i] + numtolet%26;
                if(newword[i] > 'z' || (newword[i] > 'Z' && ((int) word[i] < 'a'))){
                    newword[i] = newword[i] - ('z' - 'a' +1);
                }
            }
            else{
                newword[i] = (int) word[i];
            }
        }
        int counter3 = 0;
        printf("ciphertext: ");
        for(counter3 = 0; counter3<counter; counter3++){
            printf("%c", newword[counter3]);
            if(counter3 == counter-1){
                printf("\n");
            }
        }
        return 0;
    }
}