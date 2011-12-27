/**
 * copyright 2002-2005 Bryce "Zooko" Wilcox-O'Hearn
 * mailto:zooko@zooko.com
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this work to deal in this work without
 * restriction (including the rights to use, modify, distribute,
 * sublicense, and/or sell copies).
 */

#include "stdio.h"

#include "bool.h"

bool _verbose_abort(char const* filename, int lineno, char const* funcname, char const* msg);
bool _verbose_abort2(char const* filename, int lineno, char const* funcname, char const* msg1, const char* msg2);
bool _verbose_abort3(char const* filename, int lineno, char const* funcname, char const* msg1, const char* msg2, const char* msg3);
bool _verbose_abort4(char const* filename, int lineno, char const* funcname, char const* msg1, const char* msg2, const char* msg3, const char* msg4);
bool _verbose_abort5(char const* filename, int lineno, char const* funcname, char const* msg1, const char* msg2, const char* msg3, const char* msg4, const char* msg5);
bool _verbose_abort6(char const* filename, int lineno, char const* funcname, char const* msg1, const char* msg2, const char* msg3, const char* msg4, const char* msg5, const char* msg6);
bool _verbose_abort7(char const* filename, int lineno, char const* funcname, char const* msg1, const char* msg2, const char* msg3, const char* msg4, const char* msg5, const char* msg6, const char* msg7);
bool _verbose_abort8(char const* filename, int lineno, char const* funcname, char const* msg1, const char* msg2, const char* msg3, const char* msg4, const char* msg5, const char* msg6, const char* msg7, const char* msg8);
bool _verbose_abort9(char const* filename, int lineno, char const* funcname, char const* msg1, const char* msg2, const char* msg3, const char* msg4, const char* msg5, const char* msg6, const char* msg7, const char* msg8, const char* msg9);
bool _verbose_abort10(char const* filename, int lineno, char const* funcname, char const* msg1, const char* msg2, const char* msg3, const char* msg4, const char* msg5, const char* msg6, const char* msg7, const char* msg8, const char* msg9, const char* msg10);

#define verbose_abort(msg) ((bool)(_verbose_abort(__FILE__, __LINE__,  __func__, (msg))))
#define verbose_abort2(msg1, msg2) ((bool)(_verbose_abort2(__FILE__, __LINE__,  __func__, (msg1), (msg2))))
#define verbose_abort3(msg1, msg2, msg3) ((bool)(_verbose_abort3(__FILE__, __LINE__,  __func__, (msg1), (msg2), (msg3))))
#define verbose_abort4(msg1, msg2, msg3, msg4) ((bool)(_verbose_abort4(__FILE__, __LINE__,  __func__, (msg1), (msg2), (msg3), (msg4))))
#define verbose_abort5(msg1, msg2, msg3, msg4, msg5) ((bool)(_verbose_abort5(__FILE__, __LINE__,  __func__, (msg1), (msg2), (msg3), (msg4), (msg5))))
#define verbose_abort6(msg1, msg2, msg3, msg4, msg5, msg6) ((bool)(_verbose_abort6(__FILE__, __LINE__,  __func__, (msg1), (msg2), (msg3), (msg4), (msg5), (msg6))))
#define verbose_abort7(msg1, msg2, msg3, msg4, msg5, msg6, msg7) ((bool)(_verbose_abort7(__FILE__, __LINE__,  __func__, (msg1), (msg2), (msg3), (msg4), (msg5), (msg6), (msg7))))
#define verbose_abort8(msg1, msg2, msg3, msg4, msg5, msg6, msg7, msg8) ((bool)(_verbose_abort8(__FILE__, __LINE__,  __func__, (msg1), (msg2), (msg3), (msg4), (msg5), (msg6), (msg7), (msg8))))
#define verbose_abort9(msg1, msg2, msg3, msg4, msg5, msg6, msg7, msg8, msg9) ((bool)(_verbose_abort9(__FILE__, __LINE__,  __func__, (msg1), (msg2), (msg3), (msg4), (msg5), (msg6), (msg7), (msg8), (msg9))))
#define verbose_abort10(msg1, msg2, msg3, msg4, msg5, msg6, msg7, msg8, msg9, msg10) ((bool)(_verbose_abort10(__FILE__, __LINE__,  __func__, (msg1), (msg2), (msg3), (msg4), (msg5), (msg6), (msg7), (msg8), (msg9), (msg10))))

#define runtime_assert(expr, msg) ((expr) ? true : (verbose_abort4("Assertion `", #expr, "' failed.; ", msg)))
#define runtime_assert2(expr, msg1, msg2) ((expr) ? true : (verbose_abort6("Assertion `", #expr, "' failed.; ", (msg1), "; ", (msg2))))
#define runtime_assert3(expr, msg1, msg2, msg3) ((expr) ? true : (verbose_abort8("Assertion `", #expr, "' failed.; ", (msg1), "; ", (msg2), "; ", (msg3))))
#define runtime_assert4(expr, msg1, msg2, msg3, msg4) ((expr) ? true : (verbose_abort10("Assertion `", #expr, "' failed.; ", (msg1), "; ", (msg2), "; ", (msg3), "; ", (msg4))))
