/**
 * copyright 2002-2005 Bryce "Zooko" Wilcox-O'Hearn
 * mailto:zooko@zooko.com
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this work to deal in this work without
 * restriction (including the rights to use, modify, distribute,
 * sublicense, and/or sell copies).
 */

#ifndef __INCL_exhaust_h
#define __INCL_exhaust_h

void _z_printerr_and_exit(const char*const msg, const char*const filename, unsigned long lineno);

#define ERRNEXIT(msg) _z_printerr_and_exit((msg), __FILE__, __LINE__)

#define EXHAUSTERR(msg) ERRNEXIT("memory exhaustion: " msg " -- exiting")

#ifdef Z_EXHAUST_EXIT
#define CHECKMALLOC(x) if ((x) == NULL) EXHAUSTERR(#x)
#else
#define CHECKMALLOC(x)
#endif

#endif /* #ifndef __INCL_exhaust_h */
