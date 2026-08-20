#ifndef RESULTS_H
#define RESULTS_H

#define RESULTS_FILE "results.dat"

struct EventResult
{
    int eventId;
    int participantId; /* -1 if it's a team or not registered directly as an individual participant */
    char nameOrTeam[100];
    int position;
    int score;
    char prize[50];
};

void recordResult();
void displayResults();
void searchResults();
void resultsMenu();

#endif
