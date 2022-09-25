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

  FILE *fh_input;
  fh_input = fopen("text.txt", "r");

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

  // FILE *fh_input;

  // fh_input = fopen("text.txt", "r");
  // char buffer[256];

  // fgets(buffer, 256, fh_input);

  // puts(buffer);

  // fclose(fh_input);
}