 #include <stdio.h>
 #include <stdlib.h>

int main(int argc, char *argv[]) 
{
  int arr[] = {6,1,8,2,7};
  //each digit goes from 0-9
  int seen[10] = {0};
  int start,end;

  for(start = 0,end = (sizeof(arr) / sizeof(int)) ;start < end;start++,end--)
  {
    //if the number was seen before, leave the loop
    if(seen[arr[start]]++ || seen[arr[end]]++){
      printf("Yes \n");
      break;
    }  
  }

}
