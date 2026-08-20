#include <stdio.h>
#include "event.h"
#include "participant.h"
#include "registration.h"
#include "coordinator.h"
#include "venue.h"
#include "schedule.h"
#include "results.h"
#include "reports.h"

void participantMenu()
{
    int choice;

    do
    {
        printf("\n===== PARTICIPANT MANAGEMENT =====\n");
        printf("1. Add Participant\n");
        printf("2. Display Participants\n");
        printf("3. Search Participant\n");
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

            case 0:
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 0);
}

void registrationMenu()
{
    int choice;

    do
    {
        printf("\n===== REGISTRATION MANAGEMENT =====\n");
        printf("1. Register Participant for Event\n");
        printf("2. Cancel Registration\n");
        printf("3. Search Registrations\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                registerParticipant();
                break;

            case 2:
                cancelRegistration();
                break;

            case 3:
                searchRegistrations();
                break;

            case 0:
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 0);
}

void reportsMenu()
{
    int choice;

    do
    {
        printf("\n===== REPORTS =====\n");
        printf("1. Event Category Report\n");
        printf("2. Participant Activity Report\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                displayCategoryReport();
                break;

            case 2:
                displayParticipantActivityReport();
                break;

            case 0:
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 0);
}

void backupRestoreMenu()
{
    int choice;

    do
    {
        printf("\n===== BACKUP / RESTORE =====\n");
        printf("1. Backup Data\n");
        printf("2. Restore Data\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                backupData();
                break;

            case 2:
                restoreData();
                break;

            case 0:
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
        printf("\n");
        printf("\xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf\n");
        printf("\xb3       COLLEGE FEST MANAGEMENT SYSTEM       \xb3\n");
        printf("\xc5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xcb\n");
        printf("\xb3                                            \xb3\n");
        printf("\xb3  1. Event Management                       \xb3\n");
        printf("\xb3  2. Participant Management                 \xb3\n");
        printf("\xb3  3. Registration Management                \xb3\n");
        printf("\xb3  4. Coordinator Management                 \xb3\n");
        printf("\xb3  5. Venue Management                       \xb3\n");
        printf("\xb3  6. Schedule Management                    \xb3\n");
        printf("\xb3  7. Results Management                     \xb3\n");
        printf("\xb3  8. Fest Statistics                        \xb3\n");
        printf("\xb3  9. Reports                                \xb3\n");
        printf("\xb3 10. Backup / Restore                       \xb3\n");
        printf("\xb3 11. Exit                                   \xb3\n");
        printf("\xb3                                            \xb3\n");
        printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9\n");
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
                registrationMenu();
                break;

            case 4:
                coordinatorMenu();
                break;

            case 5:
                venueMenu();
                break;

            case 6:
                scheduleMenu();
                break;

            case 7:
                resultsMenu();
                break;

            case 8:
                displayFestStatistics();
                break;

            case 9:
                reportsMenu();
                break;

            case 10:
                backupRestoreMenu();
                break;

            case 11:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 11);

    return 0;
}