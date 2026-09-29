#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int roll;
    struct Node *next;
};

struct Node *head = NULL;

void insertBeginning(int roll)
{
    struct Node *newNode;

    newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    newNode->roll = roll;
    newNode->next = head;
    head = newNode;

    printf("Roll number %d inserted.\n", roll);
}

void search(int roll)
{
    struct Node *temp = head;
    int position = 1;

    while (temp != NULL)
    {
        if (temp->roll == roll)
        {
            printf("Roll number %d found at position %d.\n",
                   roll, position);
            return;
        }

        temp = temp->next;
        position++;
    }

    printf("Roll number %d is not available.\n", roll);
}

void deleteNode(int roll)
{
    struct Node *temp = head;
    struct Node *prev = NULL;

    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    if (head->roll == roll)
    {
        head = head->next;
        free(temp);

        printf("Roll number %d deleted.\n", roll);
        return;
    }

    while (temp != NULL && temp->roll != roll)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Roll number %d is not available.\n", roll);
        return;
    }

    prev->next = temp->next;
    free(temp);

    printf("Roll number %d deleted.\n", roll);
}

void display()
{
    struct Node *temp = head;

    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    printf("Student roll numbers: ");

    while (temp != NULL)
    {
        printf("%d -> ", temp->roll);
        temp = temp->next;
    }

    printf("NULL\n");
}

int main()
{
    int choice, roll;

    while (1)
    {
        printf("\n--- SINGLY LINKED LIST ---\n");
        printf("1. Insert at beginning\n");
        printf("2. Search roll number\n");
        printf("3. Delete roll number\n");
        printf("4. Display\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter roll number: ");
                scanf("%d", &roll);
                insertBeginning(roll);
                display();
                break;

            case 2:
                printf("Enter roll number to search: ");
                scanf("%d", &roll);
                search(roll);
                break;

            case 3:
                printf("Enter roll number to delete: ");
                scanf("%d", &roll);
                deleteNode(roll);
                display();
                break;

            case 4:
                display();
                break;

            case 5:
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
