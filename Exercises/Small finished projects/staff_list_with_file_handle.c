// FILE_NAME.C
// made by rikko
#define NAME_MAX_LENGTH 30

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

// regex script to clear the screen in powershell
#define clrscr() printf("\e[1;1H\e[2J")

// vars to save time in case of rewritting
const uint16_t MAX_LEADERBOARD_NUM = 5;
const char CHAR_DELETED_STATUS = '*';
const char *FILE_NAME = "persons.bin";

typedef struct person
{
  char name[NAME_MAX_LENGTH];
  uint16_t age;
  double wage;
  // status = '*' -> deleted
  char status;
} Person;

typedef struct Archive
{
  Person p[30];
  long counter;
} Archive;

void Start(Archive *);

// Main menu
void Insert_input(Archive *);
void change_register(Archive *);
void delete_register(Archive *);
void show_full_list(const Archive *);
void search_name(const Archive *);
// void search_age_interval(const int, const int, Archive*);

// Extra functions
void Inic(Archive *);
void Insert(Archive *, Person);
void show_data_leaderboard(const Archive *);
void data_Load(Archive *);
void data_Save(Archive *);
FILE *create_fhandle();

int main()
{
  // File handler to be used in all func
  Archive list;
  Inic(&list);

  Start(&list);
  return 0;
}

void Start(Archive *person_list)
{
  char escolha = -1;
  clrscr();
  data_Load(person_list);
  while (true)
  {
    show_data_leaderboard(person_list);
    printf("\nTheres %ld registers in the list\n", person_list->counter);
    puts("\n1. Add Register");
    puts("2. Change Register");
    puts("3. Delete Register");
    puts("4. Full Reg. list ");
    puts("5. Search");
    puts("0. Exit\n");

    //* in the scanf Supresses assignement
    scanf(" %c%*c", &escolha);

    switch (escolha)
    {
    case '1':
      Insert_input(person_list);
      break;
    case '2':
      change_register(person_list);
      break;
    case '3':
      delete_register(person_list);
      break;
    case '4':
      show_full_list(person_list);
      break;
    case '5':
      // void search_register(FILE *person_list)
      break;
    case '0':
      data_Save(person_list);
      return;
    default:
      puts("ERROR\n");
    }
  }
  data_Save(person_list);
}

void Insert_input(Archive *arc)
{
  Person p;

  printf("Name: ");
  fgets(p.name, NAME_MAX_LENGTH, stdin);

  printf("Age: ");
  if ((scanf(" %hu", &p.age)) == 0)
  {
    fputs("Error while adding the age!", stderr);
    return;
  }

  printf("Wage: ");
  if ((scanf(" %lf", &p.wage)) == 0)
  {
    puts("Error while adding the register!");
    return;
  }
  Insert(arc, p);
}

// MAIN MENU
void change_register(Archive *arc)
{
  long id;
  Person p;

  // In order to reference the user
  show_full_list(arc);

  puts("\nwhich one you want to Edit? 0 - Back");
  scanf(" %lu", &id);
  p = arc->p[id];

  // Create a copy of the register
  char option = -1;

  puts("1. Nome");
  puts("2. Age");
  puts("3. Wage");
  puts("4. Status\n");

  option = fgetc(stdin);

  // Edit the created copy
  switch (option)
  {
  case '1':
    getchar();
    puts("New Name:");
    fgets(p.name, 29, stdin);
    break;
  case '2':
    puts("New Age:");
    scanf("%hu", &p.age);
    break;
  case '3':
    puts("New Wage:\n");
    scanf("%lf", &p.wage);
    break;
  case '4':
    p.status = '0';
    break;
  default:
    puts("ERROR");
    return;
  }

  // retrieve back the data
};

void delete_register(Archive *archive)
{
  // loads player board
  show_full_list(archive);

  // asks for who to delete
  long id;
  puts("\nwhich one you want to delete? 0 - Back\nTo recover just change the status.");
  scanf(" %ld", &id);

  // store the data
  archive->p[id].status = '*';
};

void search_register(Archive *arc)
{
  while (true)
  {
    char escolha = -1;

    puts("1. Search by age interval");
    puts("2. Search by name");
    puts("0. Go back");

    scanf(" %c", &escolha);

    switch (escolha)
    {
    case '1':
      // Ask the data to the user brother, not 0 0 :bruh:
      // search_age_interval(0, 0, file_stream);
      break;
    case '2':
      search_name(arc);
      break;
    case '0':
      Start(arc);
    default:
      puts("input invalido");
    }
  }
}

// MENU 5
// void search_age_interval(const int from, const int to, FILE *file_stream)
// {
//   puts("listar registo!");
// }

// EXTRA FUNCTIONS

void search_name(const Archive *archive)
{
  char user_input[30];
  puts("Input your search term:");
  fgets(user_input, 30, stdin);

  int i;
  for (i = 0; i <= archive->counter; i++)
    if (memcmp(user_input, archive->p[i].name, NAME_MAX_LENGTH) == 0)
    {
      printf("%s was found and has %hu years old!", user_input, archive->p[i].age);
      break;
    }
}
void show_data_leaderboard(const Archive *arc)
{
  int32_t i = 0;
  Person p;

  puts("\nTop most cute:");
  for (i = 0; i < arc->counter; i++)
  {
    p = arc->p[i];
    if (i < MAX_LEADERBOARD_NUM && p.status != CHAR_DELETED_STATUS)
      printf("%d | %s", i, p.name, p.age);
  }
}

// Displays the full reg content
void show_full_list(const Archive *arc)
{
  Person p;
  int32_t i;

  // read and print the whole group of people
  for (i = 0; i < arc->counter; i++)
  {
    p = arc->p[i];
    printf("%ld - %15s [ %3hu y.o | makes %6.2lf | Banned:%c ]\n", i, p.name, p.age, p.wage, p.status == '*' ? 'X' : ' ');
  }
}

// reads data from file
void data_Load(Archive *arc)
{
  Person p;

  FILE *file_stream;
  if ((file_stream = fopen(FILE_NAME, "r+b")) == NULL)
  {
    fputs("Couldnt read the data!", stderr);
    return;
  }

  while (true)
  {
    fread(&p, sizeof(Person), 1, file_stream);
    if (feof(file_stream))
      break;
    Insert(arc, p);
  }
  fclose(file_stream);
  // printf("Data read: %zu \n", read_data);
}

// writes data back to the file
void data_Save(Archive *arc)
{
  FILE *file_stream;
  if ((file_stream = create_fhandle()) == NULL)
  {
    fputs("couldnt put the data!", stderr);
    return;
  }

  int i;
  Person p;

  for (i = 0; i < arc->counter; i++)
  {
    p = arc->p[i];
    fwrite(&p, sizeof(Person), 1, file_stream);
  }
  fclose(file_stream);

  // printf("Data written: %zu \n", written_data);
}

FILE *create_fhandle()
{
  return fopen(FILE_NAME, "w+b");
}

void Insert(Archive *a, Person p)
{
  a->p[a->counter++] = p;
};

void Inic(Archive *arc)
{
  arc->counter = 0;
}
