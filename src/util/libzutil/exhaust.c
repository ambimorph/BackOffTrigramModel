/**
 * copyright 2002-2005 Bryce "Zooko" Wilcox-O'Hearn
 * mailto:zooko@zooko.com
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this work to deal in this work without
 * restriction (including the rights to use, modify, distribute,
 * sublicense, and/or sell copies).
 */

#include "exhaust.h"

#include <stdio.h>
#include <stdlib.h>

void
_z_printerr_and_exit(const char*const msg, const char*const filename, unsigned long lineno) {
	fprintf(stderr, "%s:%d %s\n", __FILE__, __LINE__, msg);
	fflush(stderr);
	exit(EXIT_FAILURE);
}

