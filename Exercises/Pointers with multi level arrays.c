 #include <stdio.h>
 #include <stdlib.h>
 #include <locale.h>
 #include <string.h>  

void print(char* C){
  while(*C){
    putchar(*C++);
  }
  putchar('\n');

}

int main(int argc, char *argv[]) 
{
  char words[2][20] = {"America","Portugal"};

  // p = words[0]
  //*p = words[0][0]
  //p+1 = words[1]
  //*p = words[1][0]
  char (*p)[20] = words;

  char* ptr = *p;
  
  printf("%c",*(*(p+1)+2));
  
  printf("%c",*(p[1]+2));
  
  return 0;
}
