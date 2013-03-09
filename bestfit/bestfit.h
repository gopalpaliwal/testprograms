/*************************************************************************
 *
 *   Filename:     bestfit.h
 *
 *   Author:       Gopal Paliwal
 *   Created:      07 March 2013
 *
 *   Description:  Header file
 *
 *
 **************************************************************************/

#ifndef __BESTFIT_H__
#define __BESTFIT_H__


#define	TRUE		1
#define	FALSE		0

typedef enum {
	LessThan			= 0,
	LessThanEquals		= 1,
	Equals				= 2,
	GreaterThanEquals	= 3,
	GreaterThan			= 4
} SearchType;

typedef enum {
	NotFound,
	FoundExact,
	FoundGreater,
	FoundLess
} SearchResult;


SearchResult
Search (const int *const	items,
		const int			n_items,
		const int			ascending,
		const int			key,
		const SearchType	type,
		int *const			index);

#endif /* __BESTFIT_H__ */
