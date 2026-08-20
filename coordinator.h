#ifndef COORDINATOR_H
#define COORDINATOR_H


struct Coordinator
{
    int coordId;
    char name[50];
    char department[30];
    char phone[15];
    char email[50];
    char assignedEvent[50];
};


#define COORD_FILE "coordinators.dat"


void addCoordinator();
void displayCoordinators();
void searchCoordinator();


int coordinatorExists(int coordId);
int getCoordinator(int coordId, struct Coordinator *c);


void coordinatorMenu();

#endif
