#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "results.h"
#include "event.h"
#include "participant.h"

void recordResult()
{
    struct EventResult r;
    struct Event e;
    struct Participant p;
    FILE *fp;

    printf("\n---- RECORD EVENT RESULT ----\n");

    printf("Enter Event ID: ");
    scanf("%d", &r.eventId);

    if (!eventExists(r.eventId))
    {
        printf("Event ID %d does not exist.\n", r.eventId);
        return;
    }

    getEvent(r.eventId, &e);
    printf("Event Name: %s (%s)\n", e.eventName, e.eventType);

    printf("Enter Participant ID (-1 if team or unregistered): ");
    scanf("%d", &r.participantId);

    if (r.participantId != -1)
    {
        if (!participantExists(r.participantId))
        {
            printf("Warning: Participant ID does not exist. Saving as unregistered/team.\n");
            r.participantId = -1;
            printf("Enter Team or Participant Name: ");
            scanf(" %[^\n]", r.nameOrTeam);
        }
        else
        {
            getParticipant(r.participantId, &p);
            printf("Participant Name: %s\n", p.name);
            strcpy(r.nameOrTeam, p.name);
        }
    }
    else
    {
        printf("Enter Team or Participant Name: ");
        scanf(" %[^\n]", r.nameOrTeam);
    }

    printf("Enter Position (e.g. 1 for 1st): ");
    scanf("%d", &r.position);

    printf("Enter Score: ");
    scanf("%d", &r.score);

    printf("Enter Prize (e.g. Gold, $100, etc.): ");
    scanf(" %[^\n]", r.prize);

    fp = fopen(RESULTS_FILE, "ab");
    if (fp == NULL)
    {
        printf("Error opening results file.\n");
        return;
    }

    fwrite(&r, sizeof(struct EventResult), 1, fp);
    fclose(fp);

    printf("Result recorded successfully!\n");
}

void displayResults()
{
    int choice;
    printf("\n---- DISPLAY RESULTS ----\n");
    printf("1. Results of a particular event\n");
    printf("2. Results of all events\n");
    printf("3. Participant achievements\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    FILE *fp = fopen(RESULTS_FILE, "rb");
    if (fp == NULL)
    {
        printf("No results recorded yet.\n");
        return;
    }

    struct EventResult r;
    struct Event e;
    int found = 0;

    if (choice == 1)
    {
        int searchId;
        printf("Enter Event ID: ");
        scanf("%d", &searchId);

        if (getEvent(searchId, &e))
        {
            printf("\n================================================\n");
            printf("             %s RESULTS\n", e.eventName);
            printf("================================================\n");
            printf("%-12s%-20s%-10s%-15s\n", "Position", "Team/Participant", "Score", "Prize");
            printf("------------------------------------------------\n");
            while (fread(&r, sizeof(struct EventResult), 1, fp) == 1)
            {
                if (r.eventId == searchId)
                {
                    printf("%-12d%-20s%-10d%-15s\n", r.position, r.nameOrTeam, r.score, r.prize);
                    found = 1;
                }
            }
            printf("================================================\n");
        }
        else
        {
            printf("Event not found.\n");
        }
    }
    else if (choice == 2)
    {
        printf("\n======================================================================\n");
        printf("                          ALL EVENT RESULTS\n");
        printf("======================================================================\n");
        printf("%-6s%-20s%-20s%-10s%-8s%-15s\n", "Evt ID", "Event Name", "Team/Participant", "Position", "Score", "Prize");
        printf("----------------------------------------------------------------------\n");
        while (fread(&r, sizeof(struct EventResult), 1, fp) == 1)
        {
            char evName[50] = "Unknown";
            if (getEvent(r.eventId, &e))
            {
                strcpy(evName, e.eventName);
            }
            printf("%-6d%-20s%-20s%-10d%-8d%-15s\n", r.eventId, evName, r.nameOrTeam, r.position, r.score, r.prize);
            found = 1;
        }
        printf("======================================================================\n");
    }
    else if (choice == 3)
    {
        char searchName[100];
        printf("Enter Participant/Team Name: ");
        scanf(" %[^\n]", searchName);

        printf("\n======================================================================\n");
        printf("             ACHIEVEMENTS FOR: %s\n", searchName);
        printf("======================================================================\n");
        printf("%-6s%-20s%-10s%-8s%-15s\n", "Evt ID", "Event Name", "Position", "Score", "Prize");
        printf("----------------------------------------------------------------------\n");
        while (fread(&r, sizeof(struct EventResult), 1, fp) == 1)
        {
            if (strstr(r.nameOrTeam, searchName) != NULL)
            {
                char evName[50] = "Unknown";
                if (getEvent(r.eventId, &e))
                {
                    strcpy(evName, e.eventName);
                }
                printf("%-6d%-20s%-10d%-8d%-15s\n", r.eventId, evName, r.position, r.score, r.prize);
                found = 1;
            }
        }
        printf("======================================================================\n");
    }
    else
    {
        printf("Invalid choice.\n");
    }

    fclose(fp);

    if (choice >= 1 && choice <= 3 && !found)
    {
        printf("No results matching query found.\n");
    }
}

void searchResults()
{
    int choice;
    printf("\n---- SEARCH RESULTS ----\n");
    printf("1. Search by Event ID\n");
    printf("2. Search by Participant/Team Name\n");
    printf("3. Search by Position\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    FILE *fp = fopen(RESULTS_FILE, "rb");
    if (fp == NULL)
    {
        printf("No results recorded yet.\n");
        return;
    }

    struct EventResult r;
    struct Event e;
    int found = 0;

    if (choice == 1)
    {
        int searchId;
        printf("Enter Event ID: ");
        scanf("%d", &searchId);

        printf("\n%-12s%-20s%-10s%-15s\n", "Position", "Team/Participant", "Score", "Prize");
        printf("------------------------------------------------\n");
        while (fread(&r, sizeof(struct EventResult), 1, fp) == 1)
        {
            if (r.eventId == searchId)
            {
                printf("%-12d%-20s%-10d%-15s\n", r.position, r.nameOrTeam, r.score, r.prize);
                found = 1;
            }
        }
    }
    else if (choice == 2)
    {
        char searchName[100];
        printf("Enter Participant/Team Name: ");
        scanf(" %[^\n]", searchName);

        printf("\n%-6s%-20s%-10s%-8s%-15s\n", "Evt ID", "Team/Participant", "Position", "Score", "Prize");
        printf("----------------------------------------------------------------------\n");
        while (fread(&r, sizeof(struct EventResult), 1, fp) == 1)
        {
            if (strstr(r.nameOrTeam, searchName) != NULL)
            {
                printf("%-6d%-20s%-10d%-8d%-15s\n", r.eventId, r.nameOrTeam, r.position, r.score, r.prize);
                found = 1;
            }
        }
    }
    else if (choice == 3)
    {
        int searchPos;
        printf("Enter Position: ");
        scanf("%d", &searchPos);

        printf("\n%-6s%-20s%-20s%-8s%-15s\n", "Evt ID", "Event Name", "Team/Participant", "Score", "Prize");
        printf("----------------------------------------------------------------------\n");
        while (fread(&r, sizeof(struct EventResult), 1, fp) == 1)
        {
            if (r.position == searchPos)
            {
                char evName[50] = "Unknown";
                if (getEvent(r.eventId, &e))
                {
                    strcpy(evName, e.eventName);
                }
                printf("%-6d%-20s%-20s%-8d%-15s\n", r.eventId, evName, r.nameOrTeam, r.score, r.prize);
                found = 1;
            }
        }
    }
    else
    {
        printf("Invalid choice.\n");
    }

    fclose(fp);

    if (choice >= 1 && choice <= 3 && !found)
    {
        printf("No results matching search query found.\n");
    }
}

void resultsMenu()
{
    int choice;
    do
    {
        printf("\n===== RESULTS MANAGEMENT =====\n");
        printf("1. Record Event Result\n");
        printf("2. Display Results\n");
        printf("3. Search Results\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                recordResult();
                break;
            case 2:
                displayResults();
                break;
            case 3:
                searchResults();
                break;
            case 0:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);
}
