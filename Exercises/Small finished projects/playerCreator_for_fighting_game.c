#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// this class is made for testing purposes ONLY
typedef struct playerData
{
  char *Name;
  unsigned int pDmg;

} playerData;

void createPlayer();
playerData *loadPlayer(char *profileName);
const char *file_extension = "bin";

// int main(int argc, char **argv)
// {
//   createPlayer();

//   return 0;
// }

// Now read the information from the file -- PLACE IN GAME CODE
playerData *loadPlayer(char *profileName)
{
  // i made this a ptr return type, since this is a local variable, prob bugs will happen
  const playerData p = {"", 0};
  FILE *fh;

  // add the file extension
  sprintf(profileName, "%s.%s", profileName, file_extension);
  fh = fopen(profileName, "r");

  if (fh == NULL)
  {
    fclose(fh);
    return NULL;
  }

  // check if you can read from the text file
  int elements_read = fread(&p, sizeof(playerData), 1, fh);

  if (elements_read <= 0)
  {
    fclose(fh);
    return NULL;
  }
  fclose(fh);

  return &p;
}

// Automatically adds the extension
void createPlayer()
{
  FILE *fh;
  playerData p;

  char file_name[30];

  // ask for player input
  puts("Player Name:");
  if (fgets(p.Name, 30, stdin) == NULL)
  {
    return;
  }

  p.Name[strcspn(p.Name, "\n")] = 0;

  puts("\nPlayer Damage:");
  scanf("%lu", &p.pDmg);

  if ((p.pDmg <= 0))
  {
    return;
  }

  // Saving the file name as the fighter
  sprintf(file_name, "%s.%s", p.Name, file_extension);

  if ((fh = fopen(file_name, "wb+")) == NULL)
  {
    fclose(fh);
    return;
  }

  // writes the data in binary and checks for errors
  size_t elements_written = fwrite(&p, sizeof(playerData), 1, fh);

  if (elements_written <= 0)
  {
    fclose(fh);
    return;
  }

  puts("Player Created Successfully!");
  fclose(fh);
}