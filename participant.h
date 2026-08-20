#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#define PARTICIPANT_FILE "participants.dat"

struct Participant
{
    int participantId;
    char name[100];
    char department[50];
    int year;
    char phone[20];
    char email[100];
};

void addParticipant();
void displayParticipants();
void searchParticipant();

int participantExists(int participantId);
int getParticipant(int participantId, struct Participant *participant);

#endif
