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
  // Run through the list, prints counter
  int counter;

  // tmp and head ptr share the same list structure, tmp gets deallocated
  Node *tmp;
  for (counter = 0, tmp = head; tmp != NULL; counter++, tmp = tmp->next)
    printf("%d - ", tmp->value);

  printf("%d items\n", counter);
}

void insert_start(Node **head, int value)
{
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->value = value;

  // point the next node to head
  newNode->next = *head;

  // Change the head from the old to the new start
  *head = newNode;
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

Node *BuildTwoThree()
{
  Node *head = (Node *)malloc(sizeof(Node)); // Allocate 2 nodes in the heap
  Node *three = (Node *)malloc(sizeof(Node));

  // Setup the nodes
  head->next = three;
  head->value = 2;
  three->next = NULL;
  three->value = 3;

  // At this point the linked list is referenced by head
  return head;
}

int main()
{
  // Node *head = BuildTwoThree();
  // Where the linked list starts
  Node *head = NULL;

  // Inserts numbers from 1 to 10
  for (int i = 1; i < 10; i++)
    insert_end(&head, i);

  // Prints The inserted numbers
  printlist(head);

  return 0;
}
