#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "coordinator.h"

#define MAX_COORDINATORS 100


  // 1. ADD COORDINATOR

void addCoordinator()
{
    struct Coordinator c;
    FILE *fp;

    printf("\n---- ADD NEW COORDINATOR ----\n");

    printf("Enter Coordinator ID    : ");
    scanf("%d", &c.coordId);

    /* check if this ID is already used */
    if (coordinatorExists(c.coordId))
    {
        printf("A coordinator with this ID already exists. Try again.\n");
        return;
    }

    printf("Enter Name              : ");
    scanf(" %[^\n]", c.name);

    printf("Enter Department         : ");
    scanf(" %[^\n]", c.department);

    printf("Enter Phone              : ");
    scanf(" %[^\n]", c.phone);

    printf("Enter Email              : ");
    scanf(" %[^\n]", c.email);

    printf("Enter Assigned Event     : ");
    scanf(" %[^\n]", c.assignedEvent);

    fp = fopen(COORD_FILE, "ab");
    if (fp == NULL)
    {
        printf("Error: could not open coordinator file.\n");
        return;
    }

    fwrite(&c, sizeof(struct Coordinator), 1, fp);
    fclose(fp);

    printf("Coordinator added successfully!\n");
}


  // 2. DISPLAY ALL COORDINATORS

void displayCoordinators()
{
    struct Coordinator c;
    FILE *fp;
    int count = 0;

    fp = fopen(COORD_FILE, "rb");
    if (fp == NULL)
    {
        printf("No coordinators found yet.\n");
        return;
    }

    printf("\n---------------------------------------------------------------\n");
    printf("%-8s%-18s%-16s%-12s%-20s\n", "ID", "NAME", "DEPARTMENT", "PHONE", "ASSIGNED EVENT");
    printf("---------------------------------------------------------------\n");

    while (fread(&c, sizeof(struct Coordinator), 1, fp) == 1)
    {
        printf("%-8d%-18s%-16s%-12s%-20s\n",
               c.coordId, c.name, c.department, c.phone, c.assignedEvent);
        count++;
    }

    printf("---------------------------------------------------------------\n");

    if (count == 0)
        printf("No coordinators to show.\n");

    fclose(fp);
}


  // 3. SEARCH COORDINATOR

void searchCoordinator()
{
    int choice;
    struct Coordinator c;
    FILE *fp;
    int found = 0;

    printf("\n---- SEARCH COORDINATOR ----\n");
    printf("1. Search by Coordinator ID\n");
    printf("2. Search by Name\n");
    printf("3. Search by Department\n");
    printf("4. Search by Assigned Event\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    fp = fopen(COORD_FILE, "rb");
    if (fp == NULL)
    {
        printf("No coordinators found yet.\n");
        return;
    }

    if (choice == 1)
    {
        int id;
        printf("Enter Coordinator ID to search: ");
        scanf("%d", &id);

        while (fread(&c, sizeof(struct Coordinator), 1, fp) == 1)
        {
            if (c.coordId == id)
            {
                found = 1;
                break;
            }
        }
    }
    else
    {
        char key[50];
        printf("Enter text to search: ");
        scanf(" %[^\n]", key);

        while (fread(&c, sizeof(struct Coordinator), 1, fp) == 1)
        {
            if (choice == 2 && strstr(c.name, key) != NULL)
            {
                found = 1;
                break;
            }
            if (choice == 3 && strstr(c.department, key) != NULL)
            {
                found = 1;
                break;
            }
            if (choice == 4 && strstr(c.assignedEvent, key) != NULL)
            {
                found = 1;
                break;
            }
        }
    }

    fclose(fp);

    if (found)
    {
        printf("\n---- COORDINATOR FOUND ----\n");
        printf("Coordinator ID   : %d\n", c.coordId);
        printf("Name             : %s\n", c.name);
        printf("Department       : %s\n", c.department);
        printf("Phone            : %s\n", c.phone);
        printf("Email            : %s\n", c.email);
        printf("Assigned Event   : %s\n", c.assignedEvent);
    }
    else
    {
        printf("No matching coordinator found.\n");
    }
}


  // HELPER FUNCTIONS (used by other modules too, e.g. schedule.c)

/* returns 1 if coordinator exists, 0 if not */
int coordinatorExists(int coordId)
{
    struct Coordinator c;
    FILE *fp;

    fp = fopen(COORD_FILE, "rb");
    if (fp == NULL)
        return 0;

    while (fread(&c, sizeof(struct Coordinator), 1, fp) == 1)
    {
        if (c.coordId == coordId)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

/* copies the coordinator data into *c, returns 1 if found, 0 if not */
int getCoordinator(int coordId, struct Coordinator *c)
{
    struct Coordinator temp;
    FILE *fp;

    fp = fopen(COORD_FILE, "rb");
    if (fp == NULL)
        return 0;

    while (fread(&temp, sizeof(struct Coordinator), 1, fp) == 1)
    {
        if (temp.coordId == coordId)
        {
            *c = temp;
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}


  // MODULE MENU

void coordinatorMenu()
{
    int choice;

    do
    {
        printf("\n===== COORDINATOR MANAGEMENT =====\n");
        printf("1. Add Coordinator\n");
        printf("2. Display Coordinators\n");
        printf("3. Search Coordinator\n");
        printf("0. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1: addCoordinator(); break;
            case 2: displayCoordinators(); break;
            case 3: searchCoordinator(); break;
            case 0: printf("Returning...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }

    } while (choice != 0);
}
