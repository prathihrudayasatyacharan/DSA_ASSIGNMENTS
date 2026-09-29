#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

struct Node
{
    char page[SIZE];
    struct Node *prev;
    struct Node *next;
};

struct Node *head = NULL;
struct Node *tail = NULL;
struct Node *current = NULL;

void visitPage(char page[])
{
    struct Node *newNode;
    struct Node *temp;

    newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    strcpy(newNode->page, page);
    newNode->prev = NULL;
    newNode->next = NULL;

    /*
     * If the user visits a new page while not at the last page,
     * remove the forward history.
     */
    if (current != NULL && current != tail)
    {
        temp = current->next;

        while (temp != NULL)
        {
            struct Node *nextNode = temp->next;
            free(temp);
            temp = nextNode;
        }

        current->next = NULL;
        tail = current;
    }

    if (head == NULL)
    {
        head = tail = current = newNode;
    }
    else
    {
        newNode->prev = current;
        current->next = newNode;
        tail = newNode;
        current = newNode;
    }

    printf("Visited: %s\n", page);
}

void moveForward()
{
    if (current == NULL)
    {
        printf("No pages available.\n");
        return;
    }

    if (current->next == NULL)
    {
        printf("Already at the last page.\n");
        return;
    }

    current = current->next;

    printf("Current page: %s\n", current->page);
}

void moveBackward()
{
    if (current == NULL)
    {
        printf("No pages available.\n");
        return;
    }

    if (current->prev == NULL)
    {
        printf("Already at the first page.\n");
        return;
    }

    current = current->prev;

    printf("Current page: %s\n", current->page);
}

void deletePage(char page[])
{
    struct Node *temp = head;

    while (temp != NULL)
    {
        if (strcmp(temp->page, page) == 0)
        {
            if (temp->prev != NULL)
                temp->prev->next = temp->next;
            else
                head = temp->next;

            if (temp->next != NULL)
                temp->next->prev = temp->prev;
            else
                tail = temp->prev;

            if (current == temp)
            {
                if (temp->next != NULL)
                    current = temp->next;
                else
                    current = temp->prev;
            }

            free(temp);

            printf("Page '%s' deleted.\n", page);
            return;
        }

        temp = temp->next;
    }

    printf("Page '%s' not found.\n", page);
}

void displayForward()
{
    struct Node *temp = head;

    if (head == NULL)
    {
        printf("History is empty.\n");
        return;
    }

    printf("\nFirst to Last:\n");

    while (temp != NULL)
    {
        if (temp == current)
            printf("[%s] <-> ", temp->page);
        else
            printf("%s <-> ", temp->page);

        temp = temp->next;
    }

    printf("NULL\n");
}

void displayBackward()
{
    struct Node *temp = tail;

    if (tail == NULL)
    {
        printf("History is empty.\n");
        return;
    }

    printf("\nLast to First:\n");

    while (temp != NULL)
    {
        if (temp == current)
            printf("[%s] <-> ", temp->page);
        else
            printf("%s <-> ", temp->page);

        temp = temp->prev;
    }

    printf("NULL\n");
}

int main()
{
    int choice;
    char page[SIZE];

    while (1)
    {
        printf("\n--- WEB PAGE HISTORY ---\n");
        printf("1. Visit new page\n");
        printf("2. Move forward\n");
        printf("3. Move backward\n");
        printf("4. Delete page\n");
        printf("5. Display first to last\n");
        printf("6. Display last to first\n");
        printf("7. Display current page\n");
        printf("8. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter page name/URL: ");
                scanf("%99s", page);
                visitPage(page);
                break;

            case 2:
                moveForward();
                break;

            case 3:
                moveBackward();
                break;

            case 4:
                printf("Enter page to delete: ");
                scanf("%99s", page);
                deletePage(page);
                break;

            case 5:
                displayForward();
                break;

            case 6:
                displayBackward();
                break;

            case 7:
                if (current != NULL)
                    printf("Current page: %s\n", current->page);
                else
                    printf("No current page.\n");
                break;

            case 8:
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
