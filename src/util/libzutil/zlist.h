/**
 * copyright 2002-2005 Bryce "Zooko" Wilcox-O'Hearn
 * mailto:zooko@zooko.com
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this work to deal in this work without
 * restriction (including the rights to use, modify, distribute,
 * sublicense, and/or sell copies).
 */

#ifndef __INCL_zlist_h
#define __INCL_zlist_h

#include "zutil.h"

#include "zlistimp.h" /* implementation stuff that you needn't look at in order to use this */

/**
 * This is a very simple dynamically-resizing list.  It isn't efficient in some
 * cases -- for example the typical use of appending a bunch of items one at a 
 * time invokes realloc() every time.  The only virtues of this data structure
 * lie in simplicity, portability, and more simplicity.  You might want to read
 * through the implementation before using it -- it only takes a couple of
 * minutes.
 *
 * zlistimp.h defines a macro named DECLARE_ZLIST which you need to use in order
 * to declare a zlist type that holds items of the type that you need to hold.
 * The macro has two operands: the first is the type of the things contained in
 * the list, and the second is the name of this kind of list.
 *
 * For example:
 *
 * DECLARE_ZLIST(int, zlisti)
 *
 * expands to the following declarations:
 *
 * typedef struct {
 * 	size_t len;
 * 	int* arr;
 * } zlisti;
 * 
 * void zlisti_resize(zlisti* l, int item);
 * void zlisti_append(zlisti* l, int item);
 * void zlisti_free(zlisti* l);
 *
 * The optional macro DECLARE_ZLIST_CONTAINS_ITEM expands to:
 *
 * bool zlisti_contains_item(zlisti l, int item);
 *
 * (Why is the contains_item function optional?  Because not every C type can be
 * compared with "==", and you would get a compile error if you tried to define
 * contains_item for such an incomparable type.)
 *
 * The corresponding macro DEFINE_ZLIST and DEFINE_ZLIST_CONTAINS_ITEM expands
 * to the definitions of the functions (i.e, the functions along with their
 * bodies).  You should put DECLARE_ZLIST(neededtype, name) in your .h files and
 * DEFINE_ZLIST(neededtype, name) in exactly one of your .c files.
 *
 * Here is the documentation for each of these functions:
 *
 * void zlisti_resize(zlisti* l, size_t len):
 *     Resize the array (with realloc()) so that it has capacity for len items.
 *
 * void zlistname_append(zlistname* l, containedtype item):
 *     Enlarge the array by one and store item in the newly allocated
 *     (highest-indexed) slot.
 *
 * void zlistname_free(zlistname* l):
 *     free the memory, set l.arr = NULL and l.len = 0;  Okay to call this on an 
 *     already-freed list.
 *
 * bool zlistname_contains_item(zlistname l, containedtype item):
 *      Iterates the list and returns true if any element == item.
 */

#endif /* #ifndef __INCL_zlist_h */
