/*
 * File:        TestFileio.c
 * Authors:     Uras Ayanoglu, Jan-Krister Helenius, Sebastian Sopola
 * Description: Unit tests for fileio.c
 */

#include <stdio.h>
#include "Fileio.h"
#include "Fileio.h"

int main()
{
    // Create user struct
    struct User users[3];
    users[0].ID = 1111;
    users[1].ID = 1221;
    users[2].ID = 3;
    users[0].type = 0;
    users[1].type = 1;
    users[2].type = 2;
    users[0].status = 0;
    users[1].status = 1;
    users[2].status = 0;
    users[0].firstName = "Uras";
    users[1].firstName = "Carl Magnus";
    users[2].firstName = "Sebastian"
    users[0].lastName = "Ayanoglu";
    users[1].lastName = "von Anckarswert";
    users[2].lastName = "Sopola";

    // action struct, copypaste from Testaction
    struct Action testActions[3];
    testActions[0].usedID=1;
    testActions[0].actionType = 0;
    testActions[0].day=2;
    testActions[0].hour=11;
    testActions[0].minute=33;
    testActions[0].month=8;
    testActions[0].second=22;
    testActions[0].year=2011;
    testActions[1].usedID=6;
    testActions[1].actionType = 1;
    testActions[1].day=7;
    testActions[1].hour=16;
    testActions[1].minute=25;
    testActions[1].month=5;
    testActions[1].second=34;
    testActions[1].year=2011;
    testActions[2].usedID=0;
    testActions[2].actionType = 1;
    testActions[2].day=21;
    testActions[2].hour=9;
    testActions[2].minute=44;
    testActions[2].month=7;
    testActions[2].second=54;
    testActions[2].year=2023;


    return 0;
}