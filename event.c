#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"

#define MAX_EVENTS 100


   
  
void addEvent()
{
    struct Event e;
    FILE *fp;

    printf("\n---- ADD NEW EVENT ----\n");

    printf("Enter Event ID          : ");
    scanf("%d", &e.eventId);

    
    if (eventExists(e.eventId))
    {
        printf("An event with this ID already exists. Try again.\n");
        return;
    }

    printf("Enter Event Name        : ");
    scanf(" %[^\n]", e.eventName);

    printf("Enter Event Type        : ");
    scanf(" %[^\n]", e.eventType);

    printf("Enter Date (dd-mm-yyyy) : ");
    scanf(" %[^\n]", e.date);

    printf("Enter Start Time        : ");
    scanf(" %[^\n]", e.startTime);

    printf("Enter End Time          : ");
    scanf(" %[^\n]", e.endTime);

    printf("Enter Venue             : ");
    scanf(" %[^\n]", e.venue);

    printf("Enter Max Participants  : ");
    scanf("%d", &e.maxParticipants);

    printf("Enter Registration Fee  : ");
    scanf("%f", &e.fee);

    strcpy(e.status, "Open");

    fp = fopen(EVENT_FILE, "ab");
    if (fp == NULL)
    {
        printf("Error: could not open event file.\n");
        return;
    }

    fwrite(&e, sizeof(struct Event), 1, fp);
    fclose(fp);

    printf("Event added successfully!\n");
}


void displayEvents()
{
    struct Event e;
    FILE *fp;
    int count = 0;

    fp = fopen(EVENT_FILE, "rb");
    if (fp == NULL)
    {
        printf("No events found yet.\n");
        return;
    }

    printf("\n---------------------------------------------------------------\n");
    printf("%-6s%-20s%-12s%-12s%-15s\n", "ID", "EVENT NAME", "TYPE", "DATE", "VENUE");
    printf("---------------------------------------------------------------\n");

    while (fread(&e, sizeof(struct Event), 1, fp) == 1)
    {
        printf("%-6d%-20s%-12s%-12s%-15s\n",
               e.eventId, e.eventName, e.eventType, e.date, e.venue);
        count++;
    }

    printf("---------------------------------------------------------------\n");

    if (count == 0)
        printf("No events to show.\n");

    fclose(fp);
}

  
  
void searchEvent()
{
    int choice;
    struct Event e;
    FILE *fp;
    int found = 0;

    printf("\n---- SEARCH EVENT ----\n");
    printf("1. Search by Event ID\n");
    printf("2. Search by Event Name\n");
    printf("3. Search by Event Type\n");
    printf("4. Search by Date\n");
    printf("5. Search by Venue\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    fp = fopen(EVENT_FILE, "rb");
    if (fp == NULL)
    {
        printf("No events found yet.\n");
        return;
    }

    if (choice == 1)
    {
        int id;
        printf("Enter Event ID to search: ");
        scanf("%d", &id);

        while (fread(&e, sizeof(struct Event), 1, fp) == 1)
        {
            if (e.eventId == id)
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

        while (fread(&e, sizeof(struct Event), 1, fp) == 1)
        {
            if (choice == 2 && strstr(e.eventName, key) != NULL)
            {
                found = 1;
                break;
            }
            if (choice == 3 && strstr(e.eventType, key) != NULL)
            {
                found = 1;
                break;
            }
            if (choice == 4 && strstr(e.date, key) != NULL)
            {
                found = 1;
                break;
            }
            if (choice == 5 && strstr(e.venue, key) != NULL)
            {
                found = 1;
                break;
            }
        }
    }

    fclose(fp);

    if (found)
    {
        printf("\n---- EVENT FOUND ----\n");
        printf("Event ID       : %d\n", e.eventId);
        printf("Event Name     : %s\n", e.eventName);
        printf("Event Type     : %s\n", e.eventType);
        printf("Date           : %s\n", e.date);
        printf("Start Time     : %s\n", e.startTime);
        printf("End Time       : %s\n", e.endTime);
        printf("Venue          : %s\n", e.venue);
        printf("Max Participants: %d\n", e.maxParticipants);
        printf("Fee            : %.2f\n", e.fee);
        printf("Status         : %s\n", e.status);
    }
    else
    {
        printf("No matching event found.\n");
    }
}


  
  
void updateEvent()
{
    struct Event events[MAX_EVENTS];
    int count = 0;
    int id, i, found = 0;
    FILE *fp;

    printf("\n---- UPDATE EVENT ----\n");
    printf("Enter Event ID to update: ");
    scanf("%d", &id);

    fp = fopen(EVENT_FILE, "rb");
    if (fp == NULL)
    {
        printf("No events found yet.\n");
        return;
    }

    
    while (fread(&events[count], sizeof(struct Event), 1, fp) == 1)
    {
        count++;
    }
    fclose(fp);

    for (i = 0; i < count; i++)
    {
        if (events[i].eventId == id)
        {
            found = 1;

            printf("Enter new Event Name        : ");
            scanf(" %[^\n]", events[i].eventName);

            printf("Enter new Date              : ");
            scanf(" %[^\n]", events[i].date);

            printf("Enter new Start Time        : ");
            scanf(" %[^\n]", events[i].startTime);

            printf("Enter new End Time          : ");
            scanf(" %[^\n]", events[i].endTime);

            printf("Enter new Venue             : ");
            scanf(" %[^\n]", events[i].venue);

            printf("Enter new Max Participants  : ");
            scanf("%d", &events[i].maxParticipants);

            printf("Enter new Fee               : ");
            scanf("%f", &events[i].fee);

            printf("Enter new Status (Open/Closed/Cancelled): ");
            scanf(" %[^\n]", events[i].status);

            break;
        }
    }

    if (!found)
    {
        printf("Event ID not found.\n");
        return;
    }

    
    fp = fopen(EVENT_FILE, "wb");
    for (i = 0; i < count; i++)
    {
        fwrite(&events[i], sizeof(struct Event), 1, fp);
    }
    fclose(fp);

    printf("Event updated successfully!\n");
}


  
  
void deleteEvent()
{
    struct Event events[MAX_EVENTS];
    int count = 0;
    int id, i, found = 0;
    int choice;
    FILE *fp;

    printf("\n---- DELETE / CANCEL EVENT ----\n");
    printf("Enter Event ID to delete: ");
    scanf("%d", &id);

    fp = fopen(EVENT_FILE, "rb");
    if (fp == NULL)
    {
        printf("No events found yet.\n");
        return;
    }

    while (fread(&events[count], sizeof(struct Event), 1, fp) == 1)
    {
        count++;
    }
    fclose(fp);

    for (i = 0; i < count; i++)
    {
        if (events[i].eventId == id)
        {
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Event ID not found.\n");
        return;
    }

    printf("Are you sure you want to delete \"%s\"?\n", events[i].eventName);
    printf("1. Yes\n2. No\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice != 1)
    {
        printf("Delete cancelled.\n");
        return;
    }

    
    for (; i < count - 1; i++)
    {
        events[i] = events[i + 1];
    }
    count--;

    fp = fopen(EVENT_FILE, "wb");
    for (i = 0; i < count; i++)
    {
        fwrite(&events[i], sizeof(struct Event), 1, fp);
    }
    fclose(fp);

    printf("Event deleted successfully!\n");
}


  
 
void sortEvents()
{
    struct Event events[MAX_EVENTS];
    struct Event temp;
    int count = 0;
    int i, j, choice;
    FILE *fp;

    fp = fopen(EVENT_FILE, "rb");
    if (fp == NULL)
    {
        printf("No events found yet.\n");
        return;
    }

    while (fread(&events[count], sizeof(struct Event), 1, fp) == 1)
    {
        count++;
    }
    fclose(fp);

    if (count == 0)
    {
        printf("No events to sort.\n");
        return;
    }

    printf("\n---- SORT EVENTS ----\n");
    printf("1. Sort by Event Name\n");
    printf("2. Sort by Date\n");
    printf("3. Sort by Event Type\n");
    printf("4. Sort by Fee\n");
    printf("5. Sort by Max Participants\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    
    for (i = 0; i < count - 1; i++)
    {
        for (j = 0; j < count - 1 - i; j++)
        {
            int swapNeeded = 0;

            if (choice == 1 && strcmp(events[j].eventName, events[j + 1].eventName) > 0)
                swapNeeded = 1;
            else if (choice == 2 && strcmp(events[j].date, events[j + 1].date) > 0)
                swapNeeded = 1;
            else if (choice == 3 && strcmp(events[j].eventType, events[j + 1].eventType) > 0)
                swapNeeded = 1;
            else if (choice == 4 && events[j].fee > events[j + 1].fee)
                swapNeeded = 1;
            else if (choice == 5 && events[j].maxParticipants > events[j + 1].maxParticipants)
                swapNeeded = 1;

            if (swapNeeded)
            {
                temp = events[j];
                events[j] = events[j + 1];
                events[j + 1] = temp;
            }
        }
    }

    printf("\n---- SORTED EVENT LIST ----\n");
    printf("---------------------------------------------------------------\n");
    printf("%-6s%-20s%-12s%-12s%-10s\n", "ID", "EVENT NAME", "TYPE", "DATE", "FEE");
    printf("---------------------------------------------------------------\n");
    for (i = 0; i < count; i++)
    {
        printf("%-6d%-20s%-12s%-12s%-10.2f\n",
               events[i].eventId, events[i].eventName,
               events[i].eventType, events[i].date, events[i].fee);
    }
    printf("---------------------------------------------------------------\n");
}


  
  


int eventExists(int eventId)
{
    struct Event e;
    FILE *fp;

    fp = fopen(EVENT_FILE, "rb");
    if (fp == NULL)
        return 0;

    while (fread(&e, sizeof(struct Event), 1, fp) == 1)
    {
        if (e.eventId == eventId)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}


int getEvent(int eventId, struct Event *event)
{
    struct Event e;
    FILE *fp;

    fp = fopen(EVENT_FILE, "rb");
    if (fp == NULL)
        return 0;

    while (fread(&e, sizeof(struct Event), 1, fp) == 1)
    {
        if (e.eventId == eventId)
        {
            *event = e;
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}


  
  
void eventMenu()
{
    int choice;

    do
    {
        printf("\n===== EVENT MANAGEMENT =====\n");
        printf("1. Add Event\n");
        printf("2. Display All Events\n");
        printf("3. Search Event\n");
        printf("4. Update Event\n");
        printf("5. Delete/Cancel Event\n");
        printf("6. Sort Events\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1: addEvent(); break;
            case 2: displayEvents(); break;
            case 3: searchEvent(); break;
            case 4: updateEvent(); break;
            case 5: deleteEvent(); break;
            case 6: sortEvents(); break;
            case 0: printf("Returning to main menu...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }

    } while (choice != 0);
}