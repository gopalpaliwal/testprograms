/*************************************************************************
 *
 *   Filename:     test.c
 *
 *   Author:       Gopal Paliwal
 *   Created:      07 March 2013
 *
 *   Description:  Implements the testing framework to test the Search
 *                 method. 
 *
 **************************************************************************/

#include "bestfit.h"
#include <stdio.h>



/*
 * TEST METHODS BELOW
 */


/*
 * doUnitTest
 * Call Search with given input.
 * Compare results with expected result
 */
void doUnitTest (const int *const   items,
                 const int          n_items,
                 const int          ascending,
                 const int          key,
                 const SearchType   type,
                 SearchResult       expectedResult,
                 int                expectedItem)
{
    SearchResult    result;
    int             index = -1;
    
    
    result = Search(items, n_items, ascending, key, type, &index);
    if (result == expectedResult)
    {
        printf("\n Test:Good (expected:result-- %d : %d returned-index:%d)\n",
               expectedResult, result, index);
        if (expectedItem != -1) {
            printf("ExpectedItem: %d returnedItem: %d\n",
                   expectedItem, items[index]);
        }
    }
    else
    {
        printf("\nTest: Bad (expected:result --  %d %d)\n",
               expectedResult, result);
    }
    
}

/*
 * testMethod
 * Testing Framework
 * Tests the SearchMethod with different inputs
 */
void testMethod (void)
{
    int a[10] = {1,3,5,7,9,11,15,17,19,100};            // ascending
    int b[10] = {100, 19, 17, 15, 11, 9, 7, 5, 3, 1};   // descending
    int c[1] = {150};                                   // single element
    
    /*
     * Below tests are testing all the combinations of
     * array (Ascending/descending) with all the searchTypes
     * Array values are checked at the different places in 
     * array to see that all the conditions are tested
     * properly.
     */
    
    
    printf("\n\n*********Test LessThan ascending Array*****\n");
    doUnitTest(a, 10, 1, 0, LessThan, NotFound, -1);
    doUnitTest(a, 10, 1, 1, LessThan, NotFound, -1);
    doUnitTest(a, 10, 1, 3, LessThan, FoundLess, 1);
    doUnitTest(a, 10, 1, 13, LessThan, FoundLess, 11);
    doUnitTest(a, 10, 1, 19, LessThan, FoundLess, 17);
    doUnitTest(a, 10, 1, 100, LessThan, FoundLess, 19);
    doUnitTest(a, 10, 1, 150, LessThan, FoundLess, 100);
    
    printf("\n\n*********Test LessThanEquals ascending Array*****\n");
    doUnitTest(a, 10, 1, 0, LessThanEquals, NotFound, -1);
    doUnitTest(a, 10, 1, 1, LessThanEquals, FoundExact, 1);
    doUnitTest(a, 10, 1, 3, LessThanEquals, FoundExact, 3);
    doUnitTest(a, 10, 1, 13, LessThanEquals, FoundLess, 11);
    doUnitTest(a, 10, 1, 19, LessThanEquals, FoundExact, 19);
    doUnitTest(a, 10, 1, 100, LessThanEquals, FoundExact, 100);
    doUnitTest(a, 10, 1, 150, LessThanEquals, FoundLess, 100);
    
    printf("\n\n*********Test Equals ascending Array*****\n");
    doUnitTest(a, 10, 1, 0, Equals, NotFound, -1);
    doUnitTest(a, 10, 1, 1, Equals, FoundExact, 1);
    doUnitTest(a, 10, 1, 13, Equals, NotFound, -1);
    doUnitTest(a, 10, 1, 15, Equals, FoundExact, 15);
    doUnitTest(a, 10, 1, 100, Equals, FoundExact, 100);
    doUnitTest(a, 10, 1, 150, Equals, NotFound, -1);
    
    printf("\n\n*********Test GreaterThan ascending Array*****\n");
    doUnitTest(a, 10, 1, 0, GreaterThan, FoundGreater, 1);
    doUnitTest(a, 10, 1, 1, GreaterThan, FoundGreater, 3);
    doUnitTest(a, 10, 1, 13, GreaterThan, FoundGreater, 15);
    doUnitTest(a, 10, 1, 15, GreaterThan, FoundGreater, 17);
    doUnitTest(a, 10, 1, 100, GreaterThan, NotFound, -1);
    doUnitTest(a, 10, 1, 150, GreaterThan, NotFound, -1);
    
    printf("\n\n*********Test GreaterThan ascending Array*****\n");
    doUnitTest(a, 10, 1, 0, GreaterThanEquals, FoundGreater, 1);
    doUnitTest(a, 10, 1, 1, GreaterThanEquals, FoundExact, 1);
    doUnitTest(a, 10, 1, 13, GreaterThanEquals, FoundGreater, 15);
    doUnitTest(a, 10, 1, 15, GreaterThanEquals, FoundExact, 15);
    doUnitTest(a, 10, 1, 100, GreaterThanEquals, FoundExact, 100);
    doUnitTest(a, 10, 1, 150, GreaterThanEquals, NotFound, -1);
    
    printf("\n\n*********Test LessThan descending Array*****\n");
    doUnitTest(b, 10, 0, 0, LessThan, NotFound, -1);
    doUnitTest(b, 10, 0, 1, LessThan, NotFound, -1);
    doUnitTest(b, 10, 0, 3, LessThan, FoundLess, 1);
    doUnitTest(b, 10, 0, 13, LessThan, FoundLess, 11);
    doUnitTest(b, 10, 0, 15, LessThan, FoundLess, 11);
    doUnitTest(b, 10, 0, 100, LessThan, FoundLess, 19);
    doUnitTest(b, 10, 0, 150, LessThan, FoundLess, 100);
    
    
    printf("\n\n*********Test LessThanEquals descending Array*****\n");
    doUnitTest(b, 10, 0, 0, LessThanEquals, NotFound, -1);
    doUnitTest(b, 10, 0, 1, LessThanEquals, FoundExact, 1);
    doUnitTest(b, 10, 0, 3, LessThanEquals, FoundExact, 3);
    doUnitTest(b, 10, 0, 13, LessThanEquals, FoundLess, 11);
    doUnitTest(b, 10, 0, 15, LessThanEquals, FoundExact, 15);
    doUnitTest(b, 10, 0, 100, LessThanEquals, FoundExact, 100);
    doUnitTest(b, 10, 0, 150, LessThanEquals, FoundLess, 100);
    
    
    printf("\n\n*********Test Equals descending Array*****\n");
    doUnitTest(b, 10, 0, 0, Equals, NotFound, -1);
    doUnitTest(b, 10, 0, 1, Equals, FoundExact, 1);
    doUnitTest(b, 10, 0, 13, Equals, NotFound, -1);
    doUnitTest(b, 10, 0, 15, Equals, FoundExact, 15);
    doUnitTest(b, 10, 0, 100, Equals, FoundExact, 100);
    doUnitTest(b, 10, 0, 150, Equals, NotFound, -1);
    doUnitTest(b, 10, 0, 1, GreaterThan, FoundGreater, -1);
    
    printf("\n\n*********Test GreaterThan descending Array*****\n");
    doUnitTest(b, 10, 0, 0, GreaterThan, FoundGreater, 1);
    doUnitTest(b, 10, 0, 1, GreaterThan, FoundGreater, 3);
    doUnitTest(b, 10, 0, 13, GreaterThan, FoundGreater, 15);
    doUnitTest(b, 10, 0, 15, GreaterThan, FoundGreater, 17);
    doUnitTest(b, 10, 0, 100, GreaterThan, NotFound, -1);
    doUnitTest(b, 10, 0, 150, GreaterThan, NotFound, -1);
    
    printf("\n\n*********Test GreaterThan descending Array*****\n");
    doUnitTest(b, 10, 0, 0, GreaterThanEquals, FoundGreater, 1);
    doUnitTest(b, 10, 0, 1, GreaterThanEquals, FoundExact, 1);
    doUnitTest(b, 10, 0, 13, GreaterThanEquals, FoundGreater, 15);
    doUnitTest(b, 10, 0, 15, GreaterThanEquals, FoundExact, 15);
    doUnitTest(b, 10, 0, 100, GreaterThanEquals, FoundExact, 100);
    doUnitTest(b, 10, 0, 150, GreaterThanEquals, NotFound, -1);
    
    
    printf("\n\n*********Test LessThan ascending Array*****\n");
    doUnitTest(c, 1, 1, 1, LessThan, NotFound, -1);
    doUnitTest(c, 1, 1, 150, LessThan, NotFound, -1);
    doUnitTest(c, 1, 1, 200, LessThan, FoundLess, 150);
    
    printf("\n\n*********Test LessThanEquals ascending Array*****\n");
    doUnitTest(c, 1, 1, 1, LessThanEquals, NotFound, -1);
    doUnitTest(c, 1, 1, 150, LessThanEquals, FoundExact, 150);
    doUnitTest(c, 1, 1, 200, LessThanEquals, FoundLess, 150);
    
    printf("\n\n*********Test Equals ascending Array*****\n");
    doUnitTest(c, 1, 1, 0, Equals, NotFound, -1);
    doUnitTest(c, 1, 1, 150, Equals, FoundExact, 150);
    doUnitTest(c, 1, 1, 200, Equals, NotFound, -1);
    
    printf("\n\n*********Test GreaterThan ascending Array*****\n");
    doUnitTest(c, 1, 1, 1, GreaterThan, FoundGreater, 150);
    doUnitTest(c, 1, 1, 150, GreaterThan, NotFound, -1);
    doUnitTest(c, 1, 1, 200, GreaterThan, NotFound, -1);
    
    printf("\n\n*********Test GreaterThan ascending Array*****\n");
    doUnitTest(c, 1, 1, 1, GreaterThanEquals, FoundGreater, 150);
    doUnitTest(c, 1, 1, 150, GreaterThanEquals, FoundExact, 150);
    doUnitTest(c, 1, 1, 200, GreaterThanEquals, NotFound, -1);
    
    printf("\n\n*********Test LessThan descending Array*****\n");
    doUnitTest(c, 1, 0, 1, LessThan, NotFound, -1);
    doUnitTest(c, 1, 0, 150, LessThan, NotFound, -1);
    doUnitTest(c, 1, 0, 200, LessThan, FoundLess, 150);
    
    printf("\n\n*********Test LessThanEquals descending Array*****\n");
    doUnitTest(c, 1, 0, 1, LessThanEquals, NotFound, -1);
    doUnitTest(c, 1, 0, 150, LessThanEquals, FoundExact, 150);
    doUnitTest(c, 1, 0, 200, LessThanEquals, FoundLess, 150);
    
    printf("\n\n*********Test Equals descending Array*****\n");
    doUnitTest(c, 1, 0, 0, Equals, NotFound, -1);
    doUnitTest(c, 1, 0, 150, Equals, FoundExact, 150);
    doUnitTest(c, 1, 0, 200, Equals, NotFound, -1);
    
    printf("\n\n*********Test GreaterThan descending Array*****\n");
    doUnitTest(c, 1, 0, 1, GreaterThan, FoundGreater, 150);
    doUnitTest(c, 1, 0, 150, GreaterThan, NotFound, -1);
    doUnitTest(c, 1, 0, 200, GreaterThan, NotFound, -1);
    
    printf("\n\n*********Test GreaterThan descending Array*****\n");
    doUnitTest(c, 1, 0, 1, GreaterThanEquals, FoundGreater, 150);
    doUnitTest(c, 1, 0, 150, GreaterThanEquals, FoundExact, 150);
    doUnitTest(c, 1, 0, 200, GreaterThanEquals, NotFound, -1);
    
}


int main (void)
{
    /*
     * Call test infrastructure
     */
    testMethod();
    
    return 0;
}
