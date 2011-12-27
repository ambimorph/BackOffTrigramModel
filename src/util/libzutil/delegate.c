/**
 * copyright 2002-2005 Bryce "Zooko" Wilcox-O'Hearn
 * mailto:zooko@zooko.com
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this work to deal in this work without
 * restriction (including the rights to use, modify, distribute,
 * sublicense, and/or sell copies).
 */

#include "delegate.h"
#include "moreassert.h"
#include <stdlib.h>

void* invoke(delegate f, void*data) {
	return f.meth(f.self, data);
}
