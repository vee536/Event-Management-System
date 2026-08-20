#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registration.h"
#include "participant.h"
#include "event.h"

int getNextRegistrationId()
{
    struct Registration r;
    FILE *fp;
    int maxId = 0;

    fp = fopen(REGISTRATION_FILE, "rb");

    if (fp == NULL)
        return 1;

    while (fread(&r, sizeof(struct Registration), 1, fp) == 1)
    {
        if (r.registrationId > maxId)
            maxId = r.registrationId;
    }

    fclose(fp);

    return maxId + 1;
}

int countEventRegistrations(int eventId)
{
    struct Registration r;
    FILE *fp;
    int count = 0;

    fp = fopen(REGISTRATION_FILE, "rb");

    if (fp == NULL)
        return 0;

    while (fread(&r, sizeof(struct Registration), 1, fp) == 1)
    {
        if (r.eventId == eventId && r.status == 1)
            count++;
    }

    fclose(fp);

    return count;
}

int registrationExists(int participantId, int eventId)
{
    struct Registration r;
    FILE *fp;

    fp = fopen(REGISTRATION_FILE, "rb");

    if (fp == NULL)
        return 0;

    while (fread(&r, sizeof(struct Registration), 1, fp) == 1)
    {
        if (r.participantId == participantId &&
            r.eventId == eventId &&
            r.status == 1)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void registerParticipant()
{
    struct Registration r;
    struct Participant p;
    struct Event e;
    FILE *fp;
    int participantId;
    int eventId;
    int currentRegistrations;

    printf("\n---- REGISTER PARTICIPANT FOR EVENT ----\n");

    printf("Enter Participant ID: ");
    scanf("%d", &participantId);

    if (!participantExists(participantId))
    {
        printf("Participant does not exist.\n");
        return;
    }

    getParticipant(participantId, &p);

    printf("Participant: %s\n", p.name);

    printf("Enter Event ID: ");
    scanf("%d", &eventId);

    if (!eventExists(eventId))
    {
        printf("Event does not exist.\n");
        return;
    }

    getEvent(eventId, &e);

    if (strcmp(e.status, "Open") != 0)
    {
        printf("Registration is closed for this event.\n");
        return;
    }

    currentRegistrations = countEventRegistrations(eventId);

    if (currentRegistrations >= e.maxParticipants)
    {
        printf("Registration capacity is full.\n");
        return;
    }

    if (registrationExists(participantId, eventId))
    {
        printf("Participant is already registered for this event.\n");
        return;
    }

    r.registrationId = getNextRegistrationId();
    r.participantId = participantId;
    r.eventId = eventId;
    r.status = 1;

    printf("Enter Registration Date (dd-mm-yyyy): ");
    scanf(" %[^\n]", r.registrationDate);

    fp = fopen(REGISTRATION_FILE, "ab");

    if (fp == NULL)
    {
        printf("Error opening registration file.\n");
        return;
    }

    fwrite(&r, sizeof(struct Registration), 1, fp);
    fclose(fp);

    printf("\nRegistration successful!\n");
    printf("Registration ID : %d\n", r.registrationId);
    printf("Participant     : %s\n", p.name);
    printf("Event           : %s\n", e.eventName);
}

void cancelRegistration()
{
    struct Registration registrations[500];
    int count = 0;
    int registrationId;
    int participantId;
    int i;
    int found = 0;
    FILE *fp;

    printf("\n---- CANCEL REGISTRATION ----\n");

    printf("Enter Registration ID: ");
    scanf("%d", &registrationId);

    fp = fopen(REGISTRATION_FILE, "rb");

    if (fp == NULL)
    {
        printf("No registrations found.\n");
        return;
    }

    while (fread(&registrations[count],
                 sizeof(struct Registration),
                 1,
                 fp) == 1)
    {
        count++;
    }

    fclose(fp);

    for (i = 0; i < count; i++)
    {
        if (registrations[i].registrationId == registrationId)
        {
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Registration ID not found.\n");
        return;
    }

    printf("Enter Participant ID for verification: ");
    scanf("%d", &participantId);

    if (registrations[i].participantId != participantId)
    {
        printf("Participant verification failed.\n");
        return;
    }

    if (registrations[i].status == 0)
    {
        printf("Registration is already cancelled.\n");
        return;
    }

    registrations[i].status = 0;

    fp = fopen(REGISTRATION_FILE, "wb");

    if (fp == NULL)
    {
        printf("Error opening registration file.\n");
        return;
    }

    for (i = 0; i < count; i++)
    {
        fwrite(&registrations[i],
               sizeof(struct Registration),
               1,
               fp);
    }

    fclose(fp);

    printf("Registration cancelled successfully.\n");
}

int getRegistration(int registrationId,
                     struct Registration *registration)
{
    struct Registration r;
    FILE *fp;

    fp = fopen(REGISTRATION_FILE, "rb");

    if (fp == NULL)
        return 0;

    while (fread(&r, sizeof(struct Registration), 1, fp) == 1)
    {
        if (r.registrationId == registrationId)
        {
            *registration = r;
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void searchRegistrations()
{
    int choice;
    int id;
    int found = 0;
    struct Registration r;
    struct Participant p;
    struct Event e;
    FILE *fp;

    printf("\n---- SEARCH REGISTRATIONS ----\n");
    printf("1. Registrations for an Event\n");
    printf("2. Events registered by a Participant\n");
    printf("3. Search by Registration ID\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    fp = fopen(REGISTRATION_FILE, "rb");

    if (fp == NULL)
    {
        printf("No registrations found.\n");
        return;
    }

    if (choice == 1)
    {
        printf("Enter Event ID: ");
        scanf("%d", &id);

        while (fread(&r, sizeof(struct Registration), 1, fp) == 1)
        {
            if (r.eventId == id && r.status == 1)
            {
                found = 1;

                if (getParticipant(r.participantId, &p))
                {
                    printf("\nRegistration ID : %d\n", r.registrationId);
                    printf("Participant ID  : %d\n", r.participantId);
                    printf("Participant     : %s\n", p.name);
                    printf("Date            : %s\n", r.registrationDate);
                }
            }
        }
    }
    else if (choice == 2)
    {
        printf("Enter Participant ID: ");
        scanf("%d", &id);

        while (fread(&r, sizeof(struct Registration), 1, fp) == 1)
        {
            if (r.participantId == id && r.status == 1)
            {
                found = 1;

                if (getEvent(r.eventId, &e))
                {
                    printf("\nRegistration ID : %d\n", r.registrationId);
                    printf("Event ID        : %d\n", r.eventId);
                    printf("Event Name      : %s\n", e.eventName);
                    printf("Date            : %s\n", e.date);
                }
            }
        }
    }
    else if (choice == 3)
    {
        printf("Enter Registration ID: ");
        scanf("%d", &id);

        while (fread(&r, sizeof(struct Registration), 1, fp) == 1)
        {
            if (r.registrationId == id)
            {
                found = 1;

                printf("\nRegistration ID : %d\n", r.registrationId);
                printf("Participant ID  : %d\n", r.participantId);
                printf("Event ID        : %d\n", r.eventId);
                printf("Date            : %s\n", r.registrationDate);
                printf("Status          : %s\n",
                       r.status == 1 ? "Active" : "Cancelled");

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

    if (!found)
        printf("No matching registration found.\n");
}
