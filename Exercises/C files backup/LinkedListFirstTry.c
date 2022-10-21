// FILE_NAME.C
// made by rikko
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  // Data pointer
  int value;
  /// Next field
  struct node *next;
} Node;

void printlist(Node *head)
{
  // Runs through while theres no null 'next' attribute
  for (Node *tmp = head; tmp->next != NULL; tmp = tmp->next)
    printf("%d - ", tmp->value);
}

void insert_end(Node **head, int value)
{
  // Creates node template
  Node *tmp = NULL;

  if (tmp = (Node *)malloc(sizeof(Node)) == NULL)
    exit(1);

  // Fill the default data to it
  tmp->value = value;
  tmp->next = NULL;

  // Checks if the list is empty and inserts
  if (*head == NULL)
  {
    *head = tmp;
    return;
  }

  // If not, go through until you find an empty slot
  Node *curr = *head;
  while (curr->next != NULL)
    curr = curr->next;

  // Place the template object into the last position
  curr->next = tmp;
}

int main()
{
  // Where the linked list starts
  Node *head = NULL;

  // Inserts numbers from 1 to 10
  for (int i = 1; i < 10; i++)
    insert_end(&head, i);

  // Prints The inserted numbers
  printlist(head);

  return 0;
}
