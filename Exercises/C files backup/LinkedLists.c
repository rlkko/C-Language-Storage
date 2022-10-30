// FILE_NAME.C
// http://cslibrary.stanford.edu/103/LinkedListBasics.pdf
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

Node *DummyList()
{
  Node dummy;          // Dummy is temporarely the first node
  Node *tail = &dummy; // Start the node at dummy
                       // build the list on dummy.next (tail->next)

  dummy.next = NULL;

  for (int i = 0; i < 6; i++)
  {
    Push(&(tail->next), i);
    tail = tail->next;
  }
  // 1 - 2 - 3 - 4 - 5 - Counter: 5
  printf("The last node num is %d\n", tail->value);
}

void Push(Node **head, int value)
{
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->value = value;

  // point the next node to head
  newNode->next = *head;

  // Change the head from the old to the new start
  *head = newNode;
}

void insert_after(Node* previous_node,int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));

    if (new_node == NULL)
        return;
    
    new_node->value = value;
    //change the next node to the sucessor
    new_node->next = previous_node->next;
    //change the predecessor's node to the new node
    previous_node->next = new_node;
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

void Deallocate(Node **head)
{
  Node *curr = *head;
  while (curr != NULL)
  {
    // get handle
    Node *nod = curr;
    // move curr
    curr = curr->next;
    //  deallocate using nod
    free(nod);
  }
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
  Node *tail = NULL;
  // Inserts numbers from 1 to 10
  for (int i = 1; i < 10; i++)
    insert_end(&head, &tail, i);

  // Prints The inserted numbers
  printlist(head);

  // Deallocate list
  Deallocate(head);
  return 0;
}
