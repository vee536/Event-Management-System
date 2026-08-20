#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "participant.h"

void addParticipant()
{
    struct Participant p;
    FILE *fp;

    printf("\n---- ADD PARTICIPANT ----\n");

    printf("Enter Participant ID : ");
    scanf("%d", &p.participantId);

    if (participantExists(p.participantId))
    {
        printf("Participant ID already exists.\n");
        return;
    }

    printf("Enter Name           : ");
    scanf(" %[^\n]", p.name);

    printf("Enter Department     : ");
    scanf(" %[^\n]", p.department);

    printf("Enter Year           : ");
    scanf("%d", &p.year);

    printf("Enter Phone          : ");
    scanf(" %[^\n]", p.phone);

    printf("Enter Email          : ");
    scanf(" %[^\n]", p.email);

    fp = fopen(PARTICIPANT_FILE, "ab");

    if (fp == NULL)
    {
        printf("Error opening participant file.\n");
        return;
    }

    fwrite(&p, sizeof(struct Participant), 1, fp);
    fclose(fp);

    printf("Participant added successfully!\n");
}

void displayParticipants()
{
    struct Participant p;
    FILE *fp;
    int count = 0;

    fp = fopen(PARTICIPANT_FILE, "rb");

    if (fp == NULL)
    {
        printf("No participants found.\n");
        return;
    }

    printf("\n---------------------------------------------------------------\n");
    printf("%-8s%-20s%-18s%-8s\n",
           "ID", "NAME", "DEPARTMENT", "YEAR");
    printf("---------------------------------------------------------------\n");

    while (fread(&p, sizeof(struct Participant), 1, fp) == 1)
    {
        printf("%-8d%-20s%-18s%-8d\n",
               p.participantId,
               p.name,
               p.department,
               p.year);

        count++;
    }

    printf("---------------------------------------------------------------\n");

    if (count == 0)
        printf("No participants to display.\n");

    fclose(fp);
}

void searchParticipant()
{
    int choice;
    int found = 0;
    struct Participant p;
    FILE *fp;

    printf("\n---- SEARCH PARTICIPANT ----\n");
    printf("1. Participant ID\n");
    printf("2. Name\n");
    printf("3. Department\n");
    printf("4. Year\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    fp = fopen(PARTICIPANT_FILE, "rb");

    if (fp == NULL)
    {
        printf("No participants found.\n");
        return;
    }

    if (choice == 1)
    {
        int id;

        printf("Enter Participant ID: ");
        scanf("%d", &id);

        while (fread(&p, sizeof(struct Participant), 1, fp) == 1)
        {
            if (p.participantId == id)
            {
                found = 1;
                break;
            }
        }
    }
    else if (choice == 2 || choice == 3)
    {
        char key[100];

        printf("Enter search text: ");
        scanf(" %[^\n]", key);

        while (fread(&p, sizeof(struct Participant), 1, fp) == 1)
        {
            if (choice == 2 && strstr(p.name, key) != NULL)
            {
                found = 1;
                break;
            }

            if (choice == 3 && strstr(p.department, key) != NULL)
            {
                found = 1;
                break;
            }
        }
    }
    else if (choice == 4)
    {
        int year;

        printf("Enter Year: ");
        scanf("%d", &year);

        while (fread(&p, sizeof(struct Participant), 1, fp) == 1)
        {
            if (p.year == year)
            {
                found = 1;
                break;
            }
        }
    }
    else
    {
        printf("Invalid choice.\n");
        fclose(fp);
        return;
    }

    fclose(fp);

    if (found)
    {
        printf("\n---- PARTICIPANT FOUND ----\n");
        printf("Participant ID : %d\n", p.participantId);
        printf("Name           : %s\n", p.name);
        printf("Department     : %s\n", p.department);
        printf("Year           : %d\n", p.year);
        printf("Phone          : %s\n", p.phone);
        printf("Email          : %s\n", p.email);
    }
    else
    {
        printf("No matching participant found.\n");
    }
}

int participantExists(int participantId)
{
    struct Participant p;
    FILE *fp;

    fp = fopen(PARTICIPANT_FILE, "rb");

    if (fp == NULL)
        return 0;

    while (fread(&p, sizeof(struct Participant), 1, fp) == 1)
    {
        if (p.participantId == participantId)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

int getParticipant(int participantId, struct Participant *participant)
{
    struct Participant p;
    FILE *fp;

    fp = fopen(PARTICIPANT_FILE, "rb");

    if (fp == NULL)
        return 0;

    while (fread(&p, sizeof(struct Participant), 1, fp) == 1)
    {
        if (p.participantId == participantId)
        {
            *participant = p;
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}
