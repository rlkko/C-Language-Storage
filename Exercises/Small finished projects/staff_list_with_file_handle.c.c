// FILE_NAME.C
// made by rikko
#define NAME_MAX_LENGTH 30

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

typedef struct
{
  char name[NAME_MAX_LENGTH];
  uint16_t age;
  double wage;
  // deleted = '*' -> deleted
  char deleted;
} Person;

typedef struct Archive
{
  Person p[30];
  long counter;
} Archive;

// Global variable object
Archive list;

// vars to save time in case of rewritting
const char *FILE_NAME = "archive.bin";
const uint16_t MAX_LEADERBOARD_NUM = 5;

// regex script to clear the screen in powershell
#define clrscr() printf("\e[1;1H\e[2J")

enum deleted
{
  yes = 1,
  no = 0
};

// EXTRA FUNCTIONS

void read_name(char *message, Person *p)
{
  puts(message);
  fgets(p->name, 29, stdin);
}

void read_age(const char *message, Person *p)
{
  puts(message);
  scanf(" %hu", &(p->age));
}

void read_wage(const char *message, Person *p)
{
  puts(message);
  scanf(" %lf", &(p->wage));
}

FILE *create_fhandle(const char *fail_message)
{
  if ((fopen(FILE_NAME, "w+b")) == NULL)
    puts(fail_message);

  return fopen(FILE_NAME, "w+b");
}

FILE *create_load_fhandle(const char *fail_message)
{
  if ((fopen(FILE_NAME, "r+b")) == NULL)
    puts(fail_message);

  return fopen(FILE_NAME, "r+b");
}

void Insert(Person p)
{
  list.p[list.counter++] = p;
};

static inline void Inic()
{
  list.counter = -1;
}

void search_name()
{
  char user_input[30];
  puts("Input your search term:");
  fgets(user_input, 30, stdin);

  int i;
  for (i = 0; i <= list.counter; i++)
    if (memcmp(user_input, list.p[i].name, NAME_MAX_LENGTH) == 0)
    {
      printf("%s was found and has %hu years old!", user_input, list.p[i].age);
      break;
    }
}

void show_leaderboard(const char *message)
{
  puts(message);

  int32_t i;

  for (i = 0; i < list.counter; i++)
    if (i < MAX_LEADERBOARD_NUM && !list.p[i].deleted)
      printf("%d | %s", i, list.p[i].name, list.p[i].age);
}

// Displays the full reg content
void show_full_list()
{
  long i;
  Person *ptr;

  if (list.counter == 0)
    puts("The list is empty!");

  // read and print the whole group of people
  for (ptr = list.p, i = 0; i < list.counter; ptr++, i++)
    printf("%ld - %15s [ %3hu y.o | makes %6.2lf | Banned:%d ]\n", i, list.p[i].name, list.p[i].age, list.p[i].wage, list.p[i].deleted);
}

// reads data from file
void data_Load(const char *fail_message)
{
  Person p;

  FILE *file_stream = create_load_fhandle(fail_message);

  while ((fread(&p, sizeof(Person), 1, file_stream)))
    Insert(p);

  fclose(file_stream);
  // printf("Data read: %zu \n", read_data);
}

// writes data back to the file
void data_Save(const char *fail_message)
{
  FILE *file_stream = create_fhandle(fail_message);

  int i;
  for (i = 0; i <= list.counter; i++)
    if ((fwrite(&list.p[i], sizeof(Person), 1, file_stream)) == 0)
      puts("wrote zero");

  fclose(file_stream);

  // printf("Data written: %zu \n", written_data);
}

void register_insert()
{
  Person p;

  read_name("Name: ", &p);

  read_age("Age: ", &p);

  read_wage("Wage: ", &p);

  p.deleted = no;

  Insert(p);
}

// MAIN MENU
void register_change(const char *message_fail)
{
  long id;
  // In order to reference the user
  show_full_list(list);

  if (list.counter == 0)
  {
    puts(message_fail);
    return;
  }

  puts("\nwhich one you want to Edit? 0 - Back");
  scanf(" %lu", &id);
  Person *p = &(list.p[id]);

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
    read_name("New Name:", p);
    break;
  case '2':
    read_age("New Age:", p);
    break;
  case '3':
    read_wage("New Wage: ", p);
    break;
  case '4':
    // User delete / recover
    p->deleted = yes ? no : yes;
    break;
  default:
    return;
  }
  data_Save("DATA SAVE FAILED");
  // retrieve back the data
};

void register_delete(const char *fail_message)
{
  // loads player board
  show_full_list("\nTop most cute:");

  long id;
  if ((scanf(" %ld", &id)) == 0)
    puts(fail_message);

  list.p[id].deleted = yes;
};

void register_search(const Archive *archive)
{
  while (true)
  {
    char escolha = -1;

    puts("1. Search by age interval");
    puts("2. Search by name");
    puts("0. Go back");

    scanf(" %c%*c", &escolha);
    getchar();

    switch (escolha)
    {
    case '1':
      // Ask the data to the user brother, not 0 0
      // search_age_interval(0, 0, file_stream);
      break;
    case '2':
      search_name(archive);
      break;
    case '0':
      break;
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

int main()
{
  Inic();
  data_Load("Failed to load");

  char escolha = -1;
  clrscr();

  while (true)
  {
    show_leaderboard("Welcome!");
    printf("\nTheres %ld registers in the list\n", list.counter);
    puts("\n1. Insert Register");
    puts("2. Change Register");
    puts("3. Delete Register");
    puts("4. Full Reg. list ");
    puts("5. Search");
    puts("0. Exit\n");

    scanf(" %c%*c", &escolha);
    printf("How many in the list %ld\n", list.counter);
    switch (escolha)
    {
    case '1':
      register_insert();
      break;
    case '2':
      register_change("Failed trying to change data!");
      break;
    case '3':
      register_delete("Failed trying to delete data!");
      break;
    case '4':
      show_full_list();
      break;
    case '5':
      // void search_register(FILE *list)
      break;
    case '0':
      data_Save("DATA SAVE FAILED");
      return 0;
    default:
      puts("Invalid input");
    }
  }
}
