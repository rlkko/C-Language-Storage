// binary_convert.c
// made by rikko
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char **argv)
{
  if (argc != 2)
    printf("Syntax: binary_convert.exe Num\ninvalid input");

  const int const num = atoi(argv[1]);
  int i, j;

  // create 2 for loops to get the byte and bit
  for (i = 0; i < sizeof(int); i++)
  {
    // create a variable to store the byte
    char byte = ((char *)&num)[i];
    for (j = 7; j >= 0; j--)
    {
      // get bit by bit shifting to nth bit and comparing to 1
      char bit = (byte >> j) & 1;
      // print bit
      printf("%hhd", bit);
    }
    putchar(' ');
  }
}
