#ifndef VENUE_H
#define VENUE_H

/* ---------- Venue structure ---------- */
struct Venue
{
    int venueId;
    char venueName[50];
    char location[50];
    int capacity;
    char venueType[30];
    char status[15];   /* "Available" or "Booked" */
};

/* ---------- File name ---------- */
#define VENUE_FILE "venues.dat"

/* ---------- Main modules ---------- */
void addVenue();
void displayVenues();
void searchVenue();

/* ---------- Helper functions (other members will call these) ---------- */
int venueExists(int venueId);
int getVenue(int venueId, struct Venue *v);

/* ---------- Menu for this module ---------- */
void venueMenu();

#endif
