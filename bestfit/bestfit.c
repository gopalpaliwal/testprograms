/*************************************************************************
 *
 *   Filename:     bestfit.c
 *
 *   Author:       Gopal Paliwal
 *   Created:      07 March 2013
 *
 *   Description:  Implements the array element retrival methods
 *                 defined below:
 *                 LessThan, LessThanEquals, Equals,
 *                 GreaterThan, GreaterThanEquals.
 *
 *
 **************************************************************************/

#include "bestfit.h"
#include <stdio.h>


/*
 * Initialize start/end index
 * For ascending start=0 and end=items-1
 * For descending start=items-1 and end=0
 */
#define START(start, end, n_items, ascending)           \
{                                                       \
    start   = (ascending == 0) ? (n_items - 1) : (0);   \
    end     = (ascending == 0) ? (0): (n_items - 1);    \
}


/*
 * Fetch the next element
 * For ascending, start increment by 1
 * For descending, start decrements by 1
 */
#define NEXT(start, n_items, ascending)                 \
{                                                       \
    start = (ascending == 0) ? (start - 1) : (start+1); \
}



/*
 * testEqual
 * Input: Array, curIndex, key, index/result to return
 * Return: True if equal, False otherwise
 */
static inline int
testEqual (const int *const items,
           int              curIdx,
           const int        key,
           int *const       index,
           SearchResult     *result)
{
    int done = FALSE;
    
    if (items[curIdx] == key) {
        *index      = curIdx;
        *result     = FoundExact;
        done        = TRUE;
    }

    return done;
}

/*
 * testLessThan
 * Input: Array, curIndex, key, index/result to return
 * Return: True if LessThan, False otherwise
 */
static inline int
testLessThan (const int *const  items,
              int               curIdx,
              int               endIdx,
              const int         key,
              int *const        index,
              SearchResult      *result,
              int               firstPass)
{
    int done = FALSE;
    
    /*
     * if firstPass is set, we will do initial boundry check
     * Else, keep on storing index till element is less than key.
     * As soon as element becomes greater than key, return
     * last stored element with FoundLess.
     */
    if (firstPass && items[curIdx] >= key) {
        done = TRUE;
        *index = -1;
    }
    else if (firstPass && items[endIdx] < key) {
        *index = endIdx;
        *result = FoundLess;
        done = TRUE;
    }
    else if (items[curIdx] < key) {
        *index = curIdx;
    }
    else {
        *result = FoundLess;
        done = TRUE;
    }
    
    return done;
}

/*
 * testGreaterThan
 * Input: Array, curIndex, key, index/result to return
 * Return: True if GreaterThan, False otherwise
 */
static inline int
testGreaterThan (const int *const   items,
                 int                curIdx,
                 const int          key,
                 int *const         index,
                 SearchResult       *result)
{
    int done = FALSE;
    
    /*
     * check if current item > key
     */
    if (items[curIdx] > key) {
        *index  = curIdx;
        *result = FoundGreater;
        done    = TRUE;
    }
    
    return done;
}

/* Search an array of sorted numbers.
 *
 * items    : An array of sorted ints, with no duplicates
 * n_items  : Number of elements in the items array
 * ascending: non-zero if the array is sorted in ascending order
 * key      : the key to search for
 * type     : the type of match to find
 *
 * This function finds the element in the array
 * that best fits the search criteria. It returns
 * the match type and the index of the matching item.
 *
 * Assumptions
 * -----------
 *  The items are sorted
 *  Items will be non-NULL
 *  There are no duplicate items
 *  n_items will be > 0
 */
SearchResult
Search (const int *const    items,
        const int           n_items,
        const int           ascending,
        const int           key,
        const SearchType    type,
        int *const          index)
{
    
    int             curIdx, endIdx;
    int             numItems = n_items;
    int             firstPass=TRUE;
    int             done = FALSE;
    SearchResult    sResult = NotFound;
    
    /*
     * Check n_items > 0
     */
    if (!n_items) {
        printf("\nError: No elements in array\n");
        return sResult;
    }
    
    /*
     * Initialize start/end index
     * For ascending scan from start.
     * For descending scan from end.
     */
    START(curIdx, endIdx, n_items,  ascending);
    
    /*
     * Scan till array max elements or till match found
     */
    while (numItems) {
        
        switch (type) {
                
            case LessThan:
                done = testLessThan(items, curIdx, endIdx, key,
                                    index, &sResult, firstPass);
                
                break;
                
            case LessThanEquals:
                if (testEqual(items, curIdx, key, index, &sResult) == TRUE) {
                    done = TRUE;
                }
                else {
                    done = testLessThan(items, curIdx, endIdx, key, 
                                        index, &sResult, firstPass);
                }
                break;
                
            case Equals:
                done = testEqual(items, curIdx, key, 
                                 index, &sResult);
                break;
                
            case GreaterThanEquals:
                if (testEqual(items, curIdx, key, index, &sResult) == TRUE) {
                    done = TRUE;
                }
                else {
                    done = testGreaterThan(items, curIdx, key, 
                                           index, &sResult);
                }
                break;
                
            case GreaterThan:
                done = testGreaterThan(items, curIdx, key, 
                                       index, &sResult);
                break;
                
            default:
                printf("\nError: Undefined type: %d\n", type);
                return sResult;
        }
        
        /*
         * Check if we are done
         */
        if (done == TRUE) {
            return sResult;
        }
        
        /*
         * set firstPass to false after first iteration
         */
        firstPass=FALSE;
        
        /*
         * get next index in array
         */
        numItems--;
        NEXT(curIdx, n_items, ascending);
    }
    
    return sResult;
}
