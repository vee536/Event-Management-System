#include <stdio.h>
#include "event.h"
#include "participant.h"
#include "registration.h"
#include "coordinator.h"
#include "venue.h"
#include "schedule.h"

void participantMenu()
{
    int choice;

    do
    {
        printf("\n===== PARTICIPANT & REGISTRATION MANAGEMENT =====\n");
        printf("1. Add Participant\n");
        printf("2. Display Participants\n");
        printf("3. Search Participant\n");
        printf("4. Register Participant for Event\n");
        printf("5. Cancel Registration\n");
        printf("6. Search Registrations\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addParticipant();
                break;

            case 2:
                displayParticipants();
                break;

            case 3:
                searchParticipant();
                break;

            case 4:
                registerParticipant();
                break;

            case 5:
                cancelRegistration();
                break;

            case 6:
                searchRegistrations();
                break;

            case 0:
                printf("Returning to main menu...\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 0);
}

int main()
{
    int choice;

    do
    {
        printf("\n========== EVENT MANAGEMENT SYSTEM ==========\n");
        printf("1. Event Management\n");
        printf("2. Participant & Registration Management\n");
        printf("3. Coordinators, Venues & Schedule\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                eventMenu();
                break;

            case 2:
                participantMenu();
                break;

            case 3:
                coordinatorVenueScheduleMenu();
                break;

            case 0:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 0);

    return 0;
}