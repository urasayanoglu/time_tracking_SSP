/*
 * File:        Testaction.c
 * Authors:     Uras Ayanoglu, Jan-Krister Helenius, Sebastian Sopola
 * Description: Unit testing for action.c
 */

#include <stdio.h>
#include "action.h"
#include "action.c"

int main()
{
    // Creating struct arrays for testing
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

    int lengthOfArray = sizeof(testActions) / sizeof(testActions[0]);

    // Test 1:
    if (isEarlier(&testActions[1], &testActions[0]) && isEarlier(&testActions[0], &testActions[2]) && isEarlier(&testActions[1], &testActions[2]))
    {
        printf("isEarlier passed all 3 tests\n");
    }
    else
    {
        printf("isEarlier failed.\n");
    }
/*
    // Test 2:
    struct Action *newArray = NULL;
    newArray = sortActions(&testActions[0]);
    if (newArray[0].month == 5 && newArray[1].month == 8 && newArray[2].month)
    {
        printf("sortActions passed the test\n")
    }
    else
    {
        printf("sortArray failed the test\n")
    }

 */

    // Test 3:
    struct Action *newerArray = NULL;
    newerArray = addAction(0, 2, &testActions[0], lengthOfArray);
    printf("You added an action in year %d, month %d, day %d, hour %d, minute %d\n", newerArray[3].year,
           newerArray[3].month, newerArray[3].day, newerArray[3].hour, newerArray[3].minute);

//    free(newArray);
    free(newerArray);

    return 0;
}
