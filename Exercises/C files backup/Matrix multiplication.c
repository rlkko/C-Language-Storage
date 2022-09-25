 #include <stdio.h>
 #include <stdlib.h>
 #define MAX 9

int main(int argc, char *argv[]) 
{
  //General variable initialization
  int sum = 0, a_arr_row= 0, a_arr_col = 0, b_arr_row= 0, b_arr_col = 0;
  int array_a[MAX][MAX],array_b[MAX][MAX];

  //Ask the user for the elements matrix a 
  puts("Enter the rows and columns of matrix a: ");
  scanf("%d %d",&a_arr_col,&a_arr_row);

  // iterate through the array to save the input
  puts("Enter elements of matrix a: ");
  
  int i,j,k;
  for(i = 0; i< a_arr_col; i++)
    for(j = 0; j < a_arr_row; j++)
      scanf(" %d",&array_a[i][j]);

  //B Matrix
  puts("Enter the rows and columns of matrix b: ");
  scanf("%d %d",&b_arr_col,&b_arr_row);

  puts("Enter elements of matrix b: ");

  for(i = 0; i< b_arr_col; i++)
    for(j = 0; j < b_arr_row; j++)
      scanf(" %d",&array_b[i][j]);
  
  //The if to avoid the incompatible number of elements
  if(a_arr_col != b_arr_row)
  {
    puts("rows must be equal to columns!");
    return 0;
  }

  //declare the matrix to save the result
  puts("Resultant matrix: ");
  int result[a_arr_col][b_arr_row];

  // do the product of each element on array b with array a
  for( i = 0; i < a_arr_row; i++)
    for( j = 0; j < b_arr_row; j++)
    {
      for(k = 0; k < b_arr_col; k++)
        sum += array_a[i][k] * array_b[k][j];

      result[i][j] = sum;
      sum = 0;
    }
  
  //print the result array
  for(i = 0; i < a_arr_col; i++){
    for(j = 0; j < b_arr_row;j++)
      printf("%d ", result[i][j]);

    putchar('\n');
  }
}
