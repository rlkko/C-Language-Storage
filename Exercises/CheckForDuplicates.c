 #include <stdio.h>
 #include <stdlib.h>

int main(int argc, char *argv[]) 
{
  //Array and variables
  int arr[] = {6,7,8,2,7};
  //each digit goes from 0-9
  int seen[10] = {0};
  int i,j;

  for(i = 0,j = (sizeof(arr) / sizeof(int)) ;i < j;i++,j--)
  {
    if(++seen[arr[i]] >= 2 || ++seen[arr[j]] >= 2){
      printf("Yes \n");
      break;
    }  
  }

}
