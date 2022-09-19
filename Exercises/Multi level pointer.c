 #include <stdio.h>
 #include <stdlib.h>
 #include <locale.h>
 #include <string.h>

int main(int argc, char *argv[]) 
{
  setlocale(LC_ALL,"Portuguese");

  int x = 5;
  int* ptr_x = NULL; //pointer to x
  int** ptr_ptr_x = NULL; // pointer of pointer to x

  //Initialization of pointers
  ptr_x = &x;
  ptr_ptr_x = &ptr_x;

  printf("value of var = %d (int) \nptr_var -> %08x (int *)\n*ptr_var -> %d\nptr_ptr_var -> %08x(int**)\n*ptr_ptr_var -> %08x(int*)\n**ptr_ptr_var -> %d"
  ,x,ptr_x,*ptr_x,ptr_ptr_x,*ptr_ptr_x,**ptr_ptr_x);



}
