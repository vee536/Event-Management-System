#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schedule.h"
#include "event.h"
#include "coordinator.h"
#include "venue.h"

#define MAX_SCHEDULES 100



int timeToMinutes(char t[])
{
    int hh = 0, mm = 0;
    sscanf(t, "%d:%d", &hh, &mm);
    return (hh * 60) + mm;
}


 

int scheduleExists(int scheduleId)
{
    struct Schedule s;
    FILE *fp;

    fp = fopen(SCHEDULE_FILE, "rb");
    if (fp == NULL)
        return 0;

    while (fread(&s, sizeof(struct Schedule), 1, fp) == 1)
    {
        if (s.scheduleId == scheduleId)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}


  
int isVenueAvailable(int venueId, char date[], char startTime[], char endTime[])
{
    struct Schedule s;
    FILE *fp;
    int newStart, newEnd, oldStart, oldEnd;

    newStart = timeToMinutes(startTime);
    newEnd = timeToMinutes(endTime);

    fp = fopen(SCHEDULE_FILE, "rb");
    if (fp == NULL)
        return 1;   

    while (fread(&s, sizeof(struct Schedule), 1, fp) == 1)
    {
        if (s.venueId == venueId && strcmp(s.date, date) == 0)
        {
            oldStart = timeToMinutes(s.startTime);
            oldEnd = timeToMinutes(s.endTime);

            if (newStart < oldEnd && oldStart < newEnd)
            {
                fclose(fp);
                return 0;   
            }
        }
    }

    fclose(fp);
    return 1;  
}



void scheduleEvent()
{
    struct Schedule s;
    struct Event e;
    struct Coordinator c;
    struct Venue v;
    FILE *fp;

    printf("\n---- SCHEDULE EVENT ----\n");

    printf("Enter Schedule ID        : ");
    scanf("%d", &s.scheduleId);

    if (scheduleExists(s.scheduleId))
    {
        printf("A schedule with this ID already exists. Try again.\n");
        return;
    }

 
    printf("Enter Event ID           : ");
    scanf("%d", &s.eventId);

    if (!getEvent(s.eventId, &e))
    {
        printf("No event found with this ID. Please add the event first.\n");
        return;
    }


    printf("Enter Coordinator ID     : ");
    scanf("%d", &s.coordId);

    if (!getCoordinator(s.coordId, &c))
    {
        printf("No coordinator found with this ID. Please add the coordinator first.\n");
        return;
    }


    printf("Enter Venue ID           : ");
    scanf("%d", &s.venueId);

    if (!getVenue(s.venueId, &v))
    {
        printf("No venue found with this ID. Please add the venue first.\n");
        return;
    }


    printf("Enter Date (dd-mm-yyyy)  : ");
    scanf(" %[^\n]", s.date);

    printf("Enter Start Time (HH:MM) : ");
    scanf(" %[^\n]", s.startTime);

    printf("Enter End Time (HH:MM)   : ");
    scanf(" %[^\n]", s.endTime);

    
    if (!isVenueAvailable(s.venueId, s.date, s.startTime, s.endTime))
    {
        printf("\nConflict! Venue \"%s\" is already booked on %s during that time.\n",
               v.venueName, s.date);
        printf("Please choose a different time or venue.\n");
        return;
    }


    fp = fopen(SCHEDULE_FILE, "ab");
    if (fp == NULL)
    {
        printf("Error: could not open schedule file.\n");
        return;
    }

    fwrite(&s, sizeof(struct Schedule), 1, fp);
    fclose(fp);

    printf("\nEvent \"%s\" scheduled successfully!\n", e.eventName);
    printf("Coordinator : %s\n", c.name);
    printf("Venue       : %s\n", v.venueName);
    printf("Date        : %s\n", s.date);
    printf("Time        : %s - %s\n", s.startTime, s.endTime);
}


void displayFestSchedule()
{
    struct Schedule s;
    struct Event e;
    struct Venue v;
    FILE *fp;
    int count = 0;

    fp = fopen(SCHEDULE_FILE, "rb");
    if (fp == NULL)
    {
        printf("No schedule created yet.\n");
        return;
    }

    printf("\n==============================================================\n");
    printf("                     FEST SCHEDULE\n");
    printf("==============================================================\n");
    printf("%-12s%-14s%-20s%-15s\n", "DATE", "TIME", "EVENT", "VENUE");
    printf("--------------------------------------------------------------\n");

    while (fread(&s, sizeof(struct Schedule), 1, fp) == 1)
    {
        char timeRange[25];
        char eventName[50] = "Unknown";
        char venueName[50] = "Unknown";

        if (getEvent(s.eventId, &e))
            strcpy(eventName, e.eventName);

        if (getVenue(s.venueId, &v))
            strcpy(venueName, v.venueName);

        sprintf(timeRange, "%s-%s", s.startTime, s.endTime);

        printf("%-12s%-14s%-20s%-15s\n", s.date, timeRange, eventName, venueName);
        count++;
    }

    printf("==============================================================\n");

    if (count == 0)
        printf("No schedule entries to show.\n");

    fclose(fp);
}


void searchSchedule()
{
    int choice;
    struct Schedule s;
    struct Event e;
    struct Venue v;
    FILE *fp;
    int found = 0;

    printf("\n---- SEARCH SCHEDULE ----\n");
    printf("1. Events on a particular date\n");
    printf("2. Events in a particular venue\n");
    printf("3. Events handled by a coordinator\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    fp = fopen(SCHEDULE_FILE, "rb");
    if (fp == NULL)
    {
        printf("No schedule created yet.\n");
        return;
    }

    if (choice == 1)
    {
        char date[15];
        printf("Enter Date (dd-mm-yyyy): ");
        scanf(" %[^\n]", date);

        while (fread(&s, sizeof(struct Schedule), 1, fp) == 1)
        {
            if (strcmp(s.date, date) == 0)
            {
                found = 1;
                getEvent(s.eventId, &e);
                getVenue(s.venueId, &v);
                printf("%-12s%-14s%-20s%-15s\n", s.date, s.startTime, e.eventName, v.venueName);
            }
        }
    }
    else if (choice == 2)
    {
        int venueId;
        printf("Enter Venue ID: ");
        scanf("%d", &venueId);

        while (fread(&s, sizeof(struct Schedule), 1, fp) == 1)
        {
            if (s.venueId == venueId)
            {
                found = 1;
                getEvent(s.eventId, &e);
                printf("%-12s%-14s%-20s\n", s.date, s.startTime, e.eventName);
            }
        }
    }
    else if (choice == 3)
    {
        int coordId;
        printf("Enter Coordinator ID: ");
        scanf("%d", &coordId);

        while (fread(&s, sizeof(struct Schedule), 1, fp) == 1)
        {
            if (s.coordId == coordId)
            {
                found = 1;
                getEvent(s.eventId, &e);
                getVenue(s.venueId, &v);
                printf("%-12s%-14s%-20s%-15s\n", s.date, s.startTime, e.eventName, v.venueName);
            }
        }
    }
    else
    {
        printf("Invalid choice.\n");
    }

    fclose(fp);

    if (!found && (choice == 1 || choice == 2 || choice == 3))
        printf("No matching schedule found.\n");
}


void scheduleMenu()
{
    int choice;

    do
    {
        printf("\n===== EVENT SCHEDULING =====\n");
        printf("1. Schedule Event\n");
        printf("2. Display Fest Schedule\n");
        printf("3. Search Schedule\n");
        printf("0. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1: scheduleEvent(); break;
            case 2: displayFestSchedule(); break;
            case 3: searchSchedule(); break;
            case 0: printf("Returning...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }

    } while (choice != 0);
}


 
void coordinatorVenueScheduleMenu()
{
    int choice;

    do
    {
        printf("\n===== COORDINATORS, VENUES & SCHEDULE =====\n");
        printf("1. Coordinator Management\n");
        printf("2. Venue Management\n");
        printf("3. Event Scheduling\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1: coordinatorMenu(); break;
            case 2: venueMenu(); break;
            case 3: scheduleMenu(); break;
            case 0: printf("Returning to main menu...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }

    } while (choice != 0);
}
