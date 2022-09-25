 #include <stdio.h>
 #include <stdlib.h>

int main(int argc, char *argv[]) 
{
  int seen[10];
  
  int N,rem;
  scanf("%i",&N);

  while(N > 0){
    rem = N%10;
    if(seen[rem] == 1){
      printf("%d is the Duplicate \n", rem);
      return 0;
    }
      
    seen[rem] = 1;
    N = N/10;
  }
  puts("No duplicate\n");
}
