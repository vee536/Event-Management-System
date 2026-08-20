#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reports.h"
#include "event.h"
#include "participant.h"
#include "registration.h"
#include "coordinator.h"
#include "venue.h"
#include "schedule.h"
#include "results.h"


static int containsIgnoreCase(const char *str, const char *sub)
{
    if (!str || !sub) return 0;
    int lenStr = (int)strlen(str);
    int lenSub = (int)strlen(sub);
    if (lenSub > lenStr) return 0;
    for (int i = 0; i <= lenStr - lenSub; i++)
    {
        int match = 1;
        for (int j = 0; j < lenSub; j++)
        {
            char c1 = str[i + j];
            char c2 = sub[j];
            if (c1 >= 'A' && c1 <= 'Z') c1 = c1 - 'A' + 'a';
            if (c2 >= 'A' && c2 <= 'Z') c2 = c2 - 'A' + 'a';
            if (c1 != c2)
            {
                match = 0;
                break;
            }
        }
        if (match) return 1;
    }
    return 0;
}

void displayFestStatistics()
{
    FILE *fp;
    int totalEvents = 0, techEvents = 0, cultEvents = 0, sportsEvents = 0, litEvents = 0;
    int totalParticipants = 0;
    int totalRegistrations = 0;
    int totalVenues = 0;
    int totalCoordinators = 0;

    struct Event e;
    struct Participant p;
    struct Registration r;
    struct Venue v;
    struct Coordinator c;

    
    fp = fopen(EVENT_FILE, "rb");
    if (fp != NULL)
    {
        while (fread(&e, sizeof(struct Event), 1, fp) == 1)
        {
            totalEvents++;
            if (containsIgnoreCase(e.eventType, "tech")) techEvents++;
            else if (containsIgnoreCase(e.eventType, "cult")) cultEvents++;
            else if (containsIgnoreCase(e.eventType, "sport") || containsIgnoreCase(e.eventType, "game")) sportsEvents++;
            else if (containsIgnoreCase(e.eventType, "lit")) litEvents++;
        }
        fclose(fp);
    }

    
    fp = fopen(PARTICIPANT_FILE, "rb");
    if (fp != NULL)
    {
        while (fread(&p, sizeof(struct Participant), 1, fp) == 1)
        {
            totalParticipants++;
        }
        fclose(fp);
    }

    
    fp = fopen(REGISTRATION_FILE, "rb");
    if (fp != NULL)
    {
        while (fread(&r, sizeof(struct Registration), 1, fp) == 1)
        {
            if (r.status == 1)
            {
                totalRegistrations++;
            }
        }
        fclose(fp);
    }

    
    fp = fopen(VENUE_FILE, "rb");
    if (fp != NULL)
    {
        while (fread(&v, sizeof(struct Venue), 1, fp) == 1)
        {
            totalVenues++;
        }
        fclose(fp);
    }

    
    fp = fopen(COORD_FILE, "rb");
    if (fp != NULL)
    {
        while (fread(&c, sizeof(struct Coordinator), 1, fp) == 1)
        {
            totalCoordinators++;
        }
        fclose(fp);
    }

    
    
    int eventIds[1000];
    int eventCounts[1000];
    int uniqueEvents = 0;
    memset(eventIds, 0, sizeof(eventIds));
    memset(eventCounts, 0, sizeof(eventCounts));

    fp = fopen(REGISTRATION_FILE, "rb");
    if (fp != NULL)
    {
        while (fread(&r, sizeof(struct Registration), 1, fp) == 1)
        {
            if (r.status == 1)
            {
                int found = -1;
                for (int i = 0; i < uniqueEvents; i++)
                {
                    if (eventIds[i] == r.eventId)
                    {
                        found = i;
                        break;
                    }
                }
                if (found != -1)
                {
                    eventCounts[found]++;
                }
                else if (uniqueEvents < 1000)
                {
                    eventIds[uniqueEvents] = r.eventId;
                    eventCounts[uniqueEvents] = 1;
                    uniqueEvents++;
                }
            }
        }
        fclose(fp);
    }

    int maxCount = 0;
    int popularEventId = -1;
    for (int i = 0; i < uniqueEvents; i++)
    {
        if (eventCounts[i] > maxCount)
        {
            maxCount = eventCounts[i];
            popularEventId = eventIds[i];
        }
    }

    char popularEventName[50] = "None";
    if (popularEventId != -1)
    {
        if (getEvent(popularEventId, &e))
        {
            strcpy(popularEventName, e.eventName);
        }
    }

    printf("\n================================================\n");
    printf("              FEST STATISTICS\n");
    printf("================================================\n");
    printf("Total Events             : %d\n", totalEvents);
    printf("Technical Events         : %d\n", techEvents);
    printf("Cultural Events          : %d\n", cultEvents);
    printf("Sports Events            : %d\n", sportsEvents);
    if (litEvents > 0)
    {
        printf("Literary Events          : %d\n", litEvents);
    }
    printf("\n");
    printf("Total Participants       : %d\n", totalParticipants);
    printf("Total Registrations      : %d\n", totalRegistrations);
    printf("\n");
    printf("Available Venues         : %d\n", totalVenues);
    printf("Total Coordinators       : %d\n", totalCoordinators);
    printf("\n");
    printf("Most Popular Event       : %s\n", popularEventName);
    printf("Highest Registrations    : %d\n", maxCount);
    printf("================================================\n");
}

void displayCategoryReport()
{
    FILE *fp;
    int techEvents = 0, cultEvents = 0, sportsEvents = 0, litEvents = 0, otherEvents = 0;
    struct Event e;

    fp = fopen(EVENT_FILE, "rb");
    if (fp != NULL)
    {
        while (fread(&e, sizeof(struct Event), 1, fp) == 1)
        {
            if (containsIgnoreCase(e.eventType, "tech")) techEvents++;
            else if (containsIgnoreCase(e.eventType, "cult")) cultEvents++;
            else if (containsIgnoreCase(e.eventType, "sport") || containsIgnoreCase(e.eventType, "game")) sportsEvents++;
            else if (containsIgnoreCase(e.eventType, "lit")) litEvents++;
            else otherEvents++;
        }
        fclose(fp);
    }

    printf("\n================================================\n");
    printf("              CATEGORY-WISE EVENT REPORT\n");
    printf("================================================\n");
    printf("Technical     : %d\n", techEvents);
    printf("Cultural      : %d\n", cultEvents);
    printf("Sports        : %d\n", sportsEvents);
    printf("Literary      : %d\n", litEvents);
    if (otherEvents > 0)
    {
        printf("Others        : %d\n", otherEvents);
    }
    printf("------------------------------------------------\n");
    printf("%-25s%-15s\n", "Event Name", "Registrations");
    printf("------------------------------------------------\n");

    fp = fopen(EVENT_FILE, "rb");
    if (fp != NULL)
    {
        while (fread(&e, sizeof(struct Event), 1, fp) == 1)
        {
            int regCount = countEventRegistrations(e.eventId);
            printf("%-25s%-15d\n", e.eventName, regCount);
        }
        fclose(fp);
    }
    printf("================================================\n");
}

void displayParticipantActivityReport()
{
    int participantId;
    struct Participant p;
    struct Registration r;
    struct Event e;
    FILE *fp;
    int count = 0;

    printf("\n---- PARTICIPATION REPORT ----\n");
    printf("Enter Participant ID: ");
    scanf("%d", &participantId);

    if (!participantExists(participantId))
    {
        printf("Participant ID %d not found.\n", participantId);
        return;
    }

    getParticipant(participantId, &p);

    printf("\n================================================\n");
    printf("              PARTICIPANT ACTIVITY REPORT\n");
    printf("================================================\n");
    printf("Participant: %d\n", p.participantId);
    printf("Name       : %s\n", p.name);
    printf("Department : %s\n", p.department);
    printf("Email      : %s\n", p.email);
    printf("------------------------------------------------\n");
    printf("Events Registered:\n");

    fp = fopen(REGISTRATION_FILE, "rb");
    if (fp != NULL)
    {
        while (fread(&r, sizeof(struct Registration), 1, fp) == 1)
        {
            if (r.participantId == participantId && r.status == 1)
            {
                if (getEvent(r.eventId, &e))
                {
                    count++;
                    printf("%d. %s (%s)\n", count, e.eventName, e.eventType);
                }
            }
        }
        fclose(fp);
    }

    printf("------------------------------------------------\n");
    printf("Total Events: %d\n", count);
    printf("================================================\n");
}

static int copyFile(const char *src, const char *dest)
{
    FILE *fsrc = fopen(src, "rb");
    if (fsrc == NULL)
    {
        return 0; 
    }
    FILE *fdest = fopen(dest, "wb");
    if (fdest == NULL)
    {
        fclose(fsrc);
        return 0;
    }
    char buf[4096];
    size_t bytes;
    while ((bytes = fread(buf, 1, sizeof(buf), fsrc)) > 0)
    {
        fwrite(buf, 1, bytes, fdest);
    }
    fclose(fsrc);
    fclose(fdest);
    return 1;
}

void backupData()
{
    printf("\n---- BACKING UP SYSTEM DATA ----\n");
    
    const char* files[] = {
        EVENT_FILE,
        PARTICIPANT_FILE,
        REGISTRATION_FILE,
        COORD_FILE,
        VENUE_FILE,
        SCHEDULE_FILE,
        RESULTS_FILE
    };
    
    int backedUpCount = 0;
    int attemptedCount = 7;

    for (int i = 0; i < attemptedCount; i++)
    {
        char backupName[100];
        sprintf(backupName, "%s.bak", files[i]);
        if (copyFile(files[i], backupName))
        {
            printf("Backed up %s to %s\n", files[i], backupName);
            backedUpCount++;
        }
        else
        {
            printf("Notice: File %s could not be backed up (might not exist yet).\n", files[i]);
        }
    }
    
    printf("Backup process complete. Total files backed up successfully: %d/%d\n", backedUpCount, attemptedCount);
}

void restoreData()
{
    printf("\n---- RESTORING SYSTEM DATA FROM BACKUP ----\n");
    
    const char* files[] = {
        EVENT_FILE,
        PARTICIPANT_FILE,
        REGISTRATION_FILE,
        COORD_FILE,
        VENUE_FILE,
        SCHEDULE_FILE,
        RESULTS_FILE
    };
    
    int restoredCount = 0;
    int attemptedCount = 7;

    for (int i = 0; i < attemptedCount; i++)
    {
        char backupName[100];
        sprintf(backupName, "%s.bak", files[i]);
        if (copyFile(backupName, files[i]))
        {
            printf("Restored %s from %s\n", files[i], backupName);
            restoredCount++;
        }
        else
        {
            printf("Notice: Backup file %s does not exist. Restoration skipped for this file.\n", backupName);
        }
    }
    
    printf("Restore process complete. Total files restored successfully: %d/%d\n", restoredCount, attemptedCount);
}
