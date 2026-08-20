#ifndef EVENT_H
#define EVENT_H

/* ---------- Event structure ---------- */
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
    char status[15];   /* "Open" or "Closed" or "Cancelled" */
};

/* ---------- File name ---------- */
#define EVENT_FILE "events.dat"

/* ---------- Main modules ---------- */
void addEvent();
void displayEvents();
void searchEvent();
void updateEvent();
void deleteEvent();
void sortEvents();

/* ---------- Helper functions (other members will call these) ---------- */
int eventExists(int eventId);
int getEvent(int eventId, struct Event *e);

/* ---------- Menu for this module ---------- */
void eventMenu();

#endif
