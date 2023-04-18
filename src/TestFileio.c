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

    return 0;
}