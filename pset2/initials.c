#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void){
  string s = get_string();
  
  if( s[0] != ' '){
      printf("%c", toupper(s[0]));
    }

  for( int i = 1, n = strlen(s); i < n; i++){
    
    if( s[i-1] == ' ' && s[i] != ' '){

      printf("%c", toupper(s[i]));

    }
  }
  printf("\n");
}