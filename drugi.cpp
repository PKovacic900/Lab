#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50
#define EXIT_SUCCESS 0
#define MALLOC_ERROR -2
#define SCANF_ERROR -3

struct _person;
typedef struct _person *Position;

typedef struct _person
{
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    int birthYear;
    Position next;
} Person;

Position createPerson();
int addToFrontOfTheList(Position);
int addToEndOfTheList(Position);
int printPerson(Position);
int printList(Position);
Position findPerson(Position, char *);
int deletePerson(Position, char *);
int deleteList(Position);

int main()
{
    char in = 0;
    char surname[MAX_SIZE];
    Person head = {.next = NULL, .name = {0}, .surname = {0}, .birthYear = 0};

    printf("f - add person to front of the list\ne - add person to end of the list\np - print list\ns - find person with surname\nd - delete person with surname\n");

    do
    {
        printf("\nChoose action: ");
        if (scanf(" %c", &in) != 1)
            return SCANF_ERROR;

        switch (in)
        {
        case 'f':
            printf("Add to front of the list\n");
            addToFrontOfTheList(&head);
            break;
        case 'e':
            printf("Add to end of the list\n");
            addToEndOfTheList(&head);
            break;
        case 'p':
            printf("Printing list:\n");
            printList(head.next);
            break;
        case 's':
            printf("Find person with surname: ");
            if (scanf(" %s", surname) != 1)
                return SCANF_ERROR;
            Position person = findPerson(head.next, surname);
            if (person)
            {
                printPerson(person);
            }
            else
            {
                printf("\tPerson with surname '%s' was not found.\n", surname);
            }
            break;
        case 'd':
            printf("Delete person with surname: ");
            if (scanf(" %s", surname) != 1)
                return SCANF_ERROR;
            deletePerson(&head, surname);
            break;
        case '0':
            // End program
            break;
        default:
            printf("\tInvalid input. Try again.\n");
            break;
        }
    } while (in != '0');

    deleteList(&head);

    return EXIT_SUCCESS;
}

Position createPerson()
{
    Position person = (Position)malloc(sizeof(Person));
    if (!person)
    {
        printf("Malloc error!\n");
        return NULL;
    }

    printf("\tName: ");
    if (scanf(" %s", person->name) != 1)
    {
        free(person);
        return NULL;
    }

    printf("\tSurname: ");
    if (scanf(" %s", person->surname) != 1)
    {
        free(person);
        return NULL;
    }

    printf("\tBirth year: ");
    if (scanf(" %d", &person->birthYear) != 1)
    {
        free(person);
        return NULL;
    }

    person->next = NULL;
    return person;
}

int addToFrontOfTheList(Position head)
{
    Position newPerson = createPerson();
    if (!newPerson)
        return MALLOC_ERROR;

    newPerson->next = head->next;
    head->next = newPerson;

    return EXIT_SUCCESS;
}

int addToEndOfTheList(Position head)
{
    Position newPerson = createPerson();
    if (!newPerson)
        return MALLOC_ERROR;

    while (head->next != NULL)
        head = head->next;

    head->next = newPerson;

    return EXIT_SUCCESS;
}

int printPerson(Position person)
{
    if (person)
    {
        printf("\t%s %s, roden(a) %d. godine\n", person->name, person->surname, person->birthYear);
        return EXIT_SUCCESS;
    }
    return -1;
}

int printList(Position current)
{
    if (current == NULL)
    {
        printf("\tEmpty list!\n");
        return EXIT_SUCCESS;
    }

    while (current != NULL)
    {
        printPerson(current);
        current = current->next;
    }

    return EXIT_SUCCESS;
}

Position findPerson(Position current, char *sur)
{
    while (current != NULL && strcmp(current->surname, sur) != 0)
        current = current->next;

    return current;
}

Position findPersonPrev(Position current, char *sur)
{
    while (current->next != NULL && strcmp(current->next->surname, sur) != 0)
        current = current->next;

    if (current->next == NULL)
        return NULL;

    return current;
}

int deletePerson(Position head, char *sur)
{
    Position temp = NULL, prev = NULL;

    prev = findPersonPrev(head, sur);

    if (prev != NULL)
    {
        temp = prev->next;
        prev->next = temp->next;
        free(temp);

        printf("\tPerson deleted.\n");
    }
    else
    {
        printf("\tPerson with surname '%s' was not found.\n", sur);
    }

    return EXIT_SUCCESS;
}

int deleteList(Position head)
{
    Position temp = NULL;

    while (head->next != NULL)
    {
        temp = head->next;
        head->next = head->next->next;
        free(temp);
    }

    return EXIT_SUCCESS;
}
