#ifndef VENUE_H
#define VENUE_H


struct Venue
{
    int venueId;
    char venueName[50];
    char location[50];
    int capacity;
    char venueType[30];
    char status[15];   
};


#define VENUE_FILE "venues.dat"


void addVenue();
void displayVenues();
void searchVenue();


int venueExists(int venueId);
int getVenue(int venueId, struct Venue *v);


void venueMenu();

#endif
