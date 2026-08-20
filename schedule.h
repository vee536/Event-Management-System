#ifndef SCHEDULE_H
#define SCHEDULE_H



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


#define SCHEDULE_FILE "schedules.dat"


void scheduleEvent();
void displayFestSchedule();
void searchSchedule();


int isVenueAvailable(int venueId, char date[], char startTime[], char endTime[]);


void scheduleMenu();


void coordinatorVenueScheduleMenu();

#endif
