#ifndef SCHEDULE_H
#define SCHEDULE_H

/* ---------- Schedule structure ---------- */
/* Connects an Event + a Coordinator + a Venue at a Date/Time */
struct Schedule
{
    int scheduleId;
    int eventId;
    int coordId;
    int venueId;
    char date[15];
    char startTime[10];
    char endTime[10];
};

/* ---------- File name ---------- */
#define SCHEDULE_FILE "schedules.dat"

/* ---------- Main modules ---------- */
void scheduleEvent();
void displayFestSchedule();
void searchSchedule();

/* ---------- Helper function ---------- */
int isVenueAvailable(int venueId, char date[], char startTime[], char endTime[]);

/* ---------- Menu for this module ---------- */
void scheduleMenu();

/* ---------- Combined menu for Member 3 (Coordinators + Venues + Schedule) ---------- */
void coordinatorVenueScheduleMenu();

#endif
