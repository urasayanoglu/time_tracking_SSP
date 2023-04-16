/*
 * File:        fileio.h
 * Authors:     Uras Ayanoglu, Jan-Krister Helenius, Sebastian Sopola
 * Description: Header file for fileio.c
 */
#ifndef TIME_TRACKING_SSP_FILEIO_H
#define TIME_TRACKING_SSP_FILEIO_H

#define NAME_LENGTH 30

struct User
{
    unsigned int ID;
    char firstName[NAME_LENGTH];
    char lastName[NAME_LENGTH];
};

struct Action
{
    unsigned int usedID;
    int actionType;
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

void writeDB(int numberOfUsers, int numberOfActions, char *filename, struct *users, struct *actions);



#endif //TIME_TRACKING_SSP_FILEIO_H
