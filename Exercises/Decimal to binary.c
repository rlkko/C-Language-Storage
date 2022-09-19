#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char **argv)
{
  int a = 13;

  long long i, j;

  // create 2 for loops to get the byte and bit
  for (i = 0; i < sizeof(int); i++)
  {
    // create a variable to store the byte
    char byte = ((char *)&a)[i];
    for (j = 7; j >= 0; j--)
    {
      // create a variable and use the byte and bit shift to get the bit
      bool bit = (byte >> j) & 1;
      // print the variable content
      printf("%hhd", bit);
    }
    putc(' ', stdout);
  }
}