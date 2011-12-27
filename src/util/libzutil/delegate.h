/**
 * copyright 2002-2005 Bryce "Zooko" Wilcox-O'Hearn
 * mailto:zooko@zooko.com
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this work to deal in this work without
 * restriction (including the rights to use, modify, distribute,
 * sublicense, and/or sell copies).
 */

#ifndef __INCL_delegate_h
#define __INCL_delegate_h

/* This is a simple struct with two "void* obj" pointers and a function pointer. 
   You can pass structs like this to a function, and then that function can 
   "call you back" later by invoking the function pointer, passing the objs.  
   This idiom is very useful for event-driven programming, callback design 
   patterns, et cetera.

   Usually "self" is some data that you passed in earlier and when I call you 
   back I pass that data back.  I treat it as opaque and solely for your use.  
   This is the moral equivalent of the "this" pointer in C++, the "this" keyword 
   in Java, or the "self" reference in Python. 

   By contrast "data" is some data that I am giving to you when I call.  "data" 
   is basically the moral equivalent of arguments to the function, but we can't 
   use actual arguments without defining a different type of function pointer 
   for each combination of types of arguments. */
typedef void* (*delegatefunc)(void* self, void* data);

typedef struct {
	void* self;
	delegatefunc meth;
} delegate;

void* invoke(delegate f, void* data);

#endif /* #ifndef __INCL_delegate_h */

