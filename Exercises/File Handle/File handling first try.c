#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int main(int argc, char **argv)
{
  FILE *fh_output;
  fh_output = fopen("text.txt", "w");
  int input = 0;

  if (fh_output == NULL)
  {
    fclose(fh_output);
    return 1;
  }

  fputs("Enter # ( -1 EXIT )\n", stdout);
  while (true)
  {
    scanf("%d", &input);

    if (input == -1)
      break;
    else
      fprintf(fh_output, "%d \n", input);
  }
  fclose(fh_output);

  // taking Input

  FILE *fh_input;
  fh_input = fopen("text.txt", "r");

  if (fh_input == NULL)
  {
    fclose(fh_input);
    return 1;
  }

  int foutput = 0;
  int findex = 0;
  int farray[100];

  while (fscanf(fh_input, "%d", &foutput) != EOF)
  {
    farray[findex] = foutput;
    findex++;
  }

  fclose(fh_input);

  int i, average;
  for (i = 0, average = 0; i < findex; i++)
  {
    average += farray[i];
    fprintf(stdout, "%d line : %d\n", i + 1, farray[i]);
  }
  printf("The average is %d\n", average / findex);
}