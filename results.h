#ifndef RESULTS_H
#define RESULTS_H

#define RESULTS_FILE "results.dat"

struct EventResult
{
    int eventId;
    int participantId; 
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
