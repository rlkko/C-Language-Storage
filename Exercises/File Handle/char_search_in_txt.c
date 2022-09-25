// feof.c
// made by rikko
#include <stdio.h>
#include <stdlib.h>

// please be sure to add the file extension
int main(int argc, char **argv)
{
  FILE *fh;
  int ch;

  if ((fh = fopen("buffer.txt", "w+")) == NULL)
  {
    return 1;
  }

  if ((ch = fgetc(stdin)) != EOF)
  {
    fputc(ch, fh);
  }

  rewind(fh);

  while (!feof(fh))
  {
    ch = fgetc(fh);
    // printf added inside the loop to show eof char
    printf("char found in file: %c (%s)\n", ch, ch == EOF ? "EOF" : "NOT EOF");
  }
}