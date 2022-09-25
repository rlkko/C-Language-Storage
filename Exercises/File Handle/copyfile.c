// copyfile.c
// made by rikko
#include <stdio.h>
#include <stdlib.h>

// please be sure to add the extension
int main(int argc, char **argv)
{
  const char *src = argv[1], *dest = argv[2];
  int ch;

  if (argc != 3)
  {
    printf("syntax:\nsrc:%s\ndest:%s\n", src, dest);
    return 1;
  }

  FILE *fh_in, *fh_out;

  if ((fh_in = fopen(src, "rb")) == NULL)
  {
    printf("Couldnt open the file: %s", src);
    return 2;
  }

  if ((fh_out = fopen(dest, "wb")) == NULL)
  {
    printf("Couldnt open the file: %s", dest);
    return 3;
  }

  while ((ch = fgetc(fh_in)) != EOF)
    fputc(ch, fh_out);

  fclose(fh_in);
  fclose(fh_out);
}