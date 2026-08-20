#ifndef REGISTRATION_H
#define REGISTRATION_H

#define REGISTRATION_FILE "registrations.dat"

struct Registration
{
    int registrationId;
    int participantId;
    int eventId;
    char registrationDate[15];
    int status;
};

void registerParticipant();
void cancelRegistration();
void searchRegistrations();

int registrationExists(int participantId, int eventId);
int getRegistration(int registrationId, struct Registration *registration);

#endif
