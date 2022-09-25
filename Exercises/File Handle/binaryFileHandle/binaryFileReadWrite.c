// copyfile.c
// made by rikko
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct cliente
{
  int numero;
  char nome[20];
} cliente;

int main(int argc, char **argv)
{
  FILE *fh;
  cliente c;

  if ((fh = fopen("clientes.bin", "r+b")) == NULL)
    return 1;

  while (true)
  {
    size_t elements_read = fread(&c, sizeof(cliente), 1, fh);

    if (feof(fh))
      break;

    printf("[%d] Nome: %s\n", c.numero, c.nome);
  }

  fclose(fh);

  // printf("Elements read: %lu\n", elements_read);
}

// CODE USED TO CREATE THE .BIN FILE

// FILE *fh_in;
// FILE *fh_out;
// cliente c;

// if ((fh_in = fopen("yolo.txt", "r+b")) == NULL)
//   return 1;

// if ((fh_out = fopen("yolo.bin", "w+b")) == NULL)
// {
//   return 2;
// }

// while ((fscanf(fh_in, "%d %s", &c.numero, c.nome)) != EOF)
//   fwrite(&c, sizeof(cliente), 1, fh_out);
// fclose(fh_in);
// fclose(fh_out);