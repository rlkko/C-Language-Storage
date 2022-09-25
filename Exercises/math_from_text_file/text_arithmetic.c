// math_from_text.c
// made by rikko
// the syntax is %program% -t dados.dat
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char **argv)
{
  FILE *fh;
  const char *operation_format = "%d %c %d = %d\n";
  int element_1, element_2, operation, res = 0;
  char operator, show_operations = 0;

  if (argv[1][0] == '-')
  {
    switch (argv[1][1])
    {
    case 't':
      show_operations = 1;
      break;
    }

    fh = fopen(argv[2], "r+b");
  }
  else
  {
    fh = fopen(argv[1], "r+b");
  }

  if (fh == NULL)
    return 1;

  while ((fscanf(fh, "%d%c%d", &element_1, &operator, & element_2)) != EOF)
  {

    switch (operator)
    {
    case '+':
      operation = element_1 + element_2;
      break;
    case '-':
      operation = element_1 - element_2;
      break;
    case '*':
      operation = element_1 * element_2;
      break;
    case '/':
      operation = element_1 / element_2;
      break;
    }
    res += operation;
    if (show_operations)
      printf(operation_format, element_1, operator, element_2, operation);
  }
  printf("%d", res);
}
