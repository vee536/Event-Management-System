#ifndef EVENT_H
#define EVENT_H


struct Event
{
    int eventId;
    char eventName[50];
    char eventType[30];
    char date[15];
    char startTime[10];
    char endTime[10];
    char venue[30];
    int maxParticipants;
    float fee;
    char status[15];   
};


#define EVENT_FILE "events.dat"


void addEvent();
void displayEvents();
void searchEvent();
void updateEvent();
void deleteEvent();
void sortEvents();


int eventExists(int eventId);
int getEvent(int eventId, struct Event *e);


void eventMenu();

#endif
