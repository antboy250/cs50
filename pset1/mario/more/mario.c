#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n = get_int("Height: ");
    while(n > 23 || n < 0)
    {
        n = get_int("Height: ");
    }
    for( int i = 0; i < n; i++){
        int x = 0;
        int y = 0;
        int z = 0;
        while(z < n - i - 1){
            printf(" ");
            z++;
        }
        while(x < i + 1){
            printf("#"); 
            x++;
            
        }
        printf("  ");
        while(y < i + 1){
            printf("#");
            y++;
            
        }
        printf("\n");
    }
}
