#ifndef COORDINATOR_H
#define COORDINATOR_H

/* ---------- Coordinator structure ---------- */
struct Coordinator
{
    int coordId;
    char name[50];
    char department[30];
    char phone[15];
    char email[50];
    char assignedEvent[50];
};

/* ---------- File name ---------- */
#define COORD_FILE "coordinators.dat"

/* ---------- Main modules ---------- */
void addCoordinator();
void displayCoordinators();
void searchCoordinator();

/* ---------- Helper functions (other members will call these) ---------- */
int coordinatorExists(int coordId);
int getCoordinator(int coordId, struct Coordinator *c);

/* ---------- Menu for this module ---------- */
void coordinatorMenu();

#endif
