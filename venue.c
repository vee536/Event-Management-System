#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "venue.h"

#define MAX_VENUES 100


void addVenue()
{
    struct Venue v;
    FILE *fp;

    printf("\n---- ADD NEW VENUE ----\n");

    printf("Enter Venue ID           : ");
    scanf("%d", &v.venueId);


    if (venueExists(v.venueId))
    {
        printf("A venue with this ID already exists. Try again.\n");
        return;
    }

    printf("Enter Venue Name         : ");
    scanf(" %[^\n]", v.venueName);

    printf("Enter Location           : ");
    scanf(" %[^\n]", v.location);

    printf("Enter Capacity           : ");
    scanf("%d", &v.capacity);

    printf("Enter Venue Type         : ");
    scanf(" %[^\n]", v.venueType);

    strcpy(v.status, "Available");

    fp = fopen(VENUE_FILE, "ab");
    if (fp == NULL)
    {
        printf("Error: could not open venue file.\n");
        return;
    }

    fwrite(&v, sizeof(struct Venue), 1, fp);
    fclose(fp);

    printf("Venue added successfully!\n");
}



void displayVenues()
{
    struct Venue v;
    FILE *fp;
    int count = 0;

    fp = fopen(VENUE_FILE, "rb");
    if (fp == NULL)
    {
        printf("No venues found yet.\n");
        return;
    }

    printf("\n---------------------------------------------------------------\n");
    printf("%-6s%-20s%-15s%-10s%-15s%-12s\n", "ID", "NAME", "LOCATION", "CAP.", "TYPE", "STATUS");
    printf("---------------------------------------------------------------\n");

    while (fread(&v, sizeof(struct Venue), 1, fp) == 1)
    {
        printf("%-6d%-20s%-15s%-10d%-15s%-12s\n",
               v.venueId, v.venueName, v.location, v.capacity, v.venueType, v.status);
        count++;
    }

    printf("---------------------------------------------------------------\n");

    if (count == 0)
        printf("No venues to show.\n");

    fclose(fp);
}


void searchVenue()
{
    int choice;
    struct Venue v;
    FILE *fp;
    int found = 0;

    printf("\n---- SEARCH VENUE ----\n");
    printf("1. Search by Venue ID\n");
    printf("2. Search by Venue Name\n");
    printf("3. Search by Capacity (minimum)\n");
    printf("4. Search by Venue Type\n");
    printf("5. Search by Availability Status\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    fp = fopen(VENUE_FILE, "rb");
    if (fp == NULL)
    {
        printf("No venues found yet.\n");
        return;
    }

    if (choice == 1)
    {
        int id;
        printf("Enter Venue ID to search: ");
        scanf("%d", &id);

        while (fread(&v, sizeof(struct Venue), 1, fp) == 1)
        {
            if (v.venueId == id)
            {
                found = 1;
                break;
            }
        }
    }
    else if (choice == 3)
    {
        int cap;
        printf("Enter minimum capacity: ");
        scanf("%d", &cap);

        while (fread(&v, sizeof(struct Venue), 1, fp) == 1)
        {
            if (v.capacity >= cap)
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

        while (fread(&v, sizeof(struct Venue), 1, fp) == 1)
        {
            if (choice == 2 && strstr(v.venueName, key) != NULL)
            {
                found = 1;
                break;
            }
            if (choice == 4 && strstr(v.venueType, key) != NULL)
            {
                found = 1;
                break;
            }
            if (choice == 5 && strstr(v.status, key) != NULL)
            {
                found = 1;
                break;
            }
        }
    }

    fclose(fp);

    if (found)
    {
        printf("\n---- VENUE FOUND ----\n");
        printf("Venue ID     : %d\n", v.venueId);
        printf("Venue Name   : %s\n", v.venueName);
        printf("Location     : %s\n", v.location);
        printf("Capacity     : %d\n", v.capacity);
        printf("Venue Type   : %s\n", v.venueType);
        printf("Status       : %s\n", v.status);
    }
    else
    {
        printf("No matching venue found.\n");
    }
}


int venueExists(int venueId)
{
    struct Venue v;
    FILE *fp;

    fp = fopen(VENUE_FILE, "rb");
    if (fp == NULL)
        return 0;

    while (fread(&v, sizeof(struct Venue), 1, fp) == 1)
    {
        if (v.venueId == venueId)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

int getVenue(int venueId, struct Venue *v)
{
    struct Venue temp;
    FILE *fp;

    fp = fopen(VENUE_FILE, "rb");
    if (fp == NULL)
        return 0;

    while (fread(&temp, sizeof(struct Venue), 1, fp) == 1)
    {
        if (temp.venueId == venueId)
        {
            *v = temp;
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}


 

void venueMenu()
{
    int choice;

    do
    {
        printf("\n===== VENUE MANAGEMENT =====\n");
        printf("1. Add Venue\n");
        printf("2. Display Venues\n");
        printf("3. Search Venue\n");
        printf("0. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1: addVenue(); break;
            case 2: displayVenues(); break;
            case 3: searchVenue(); break;
            case 0: printf("Returning...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }

    } while (choice != 0);
}
