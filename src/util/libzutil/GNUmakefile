NAME=zutil

LIBPREFIX=lib
LIBSUFFIX=.a

RANLIB=ranlib
AR=ar

# If you don't use GNU stow, you should!  It is 100% compatible with all of
# your existing packaging and administration tools, it is an extremely simple
# tool, and it completely solves certain common system administration heaches.
# But if for some funny reason you really prefer to keep having these headaches
# instead of spending 5 minutes learning how to use GNU stow, then by all means
# change "INSTALLDIR" to something like "/usr/local".

INSTALLDIR=/usr/local/stow/lib$(NAME)

DEBUGMODE=True
# DEBUGMODE=False

ifeq ($(DEBUGMODE),True)
 CPPFLAGS += -UNDEBUG
 CFLAGS += -Wall -O0
 CFLAGS += -g
 LDFLAGS += -g
else
 CPPFLAGS += -DNDEBUG
 CFLAGS += -Wall -O2
endif

CFLAGS += -std=c99

# SRCS=$(wildcard *.c)
SRCS=zutil.c exhaust.c moreassert.c delegate.c
TESTSRCS=test.c
OBJS=$(SRCS:%.c=%.o)
TESTOBJS=$(TESTSRCS:%.c=%.o)
TEST=test
LIB=$(LIBPREFIX)$(NAME)$(LIBSUFFIX)

all: $(LIB) $(TEST)

# .d auto-dependency files
ifneq ($(findstring clean,$(MAKECMDGOALS)),clean)
ifneq (,$(SRCS:%.c=%.d))
-include $(SRCS:%.c=%.d)
endif
ifneq (,$(TESTSRCS:%.c=%.d))
-include $(TESTSRCS:%.c=%.d)
endif
endif

%.d: %.c
	@echo remaking $@
	@set -e; $(CC) $(CPPFLAGS) $(CFLAGS) -MM $< \
	| sed 's/\($*\)\.o[ :]*/\1.o $@ : GNUmakefile /g' > $@; \
	[ -s $@ ] || rm -f $@

$(LIB): $(OBJS)
	$(AR) -r $@ $+
	$(RANLIB) $@

$(TEST): $(TESTOBJS) $(LIB)
	$(CC) $+ -o $@ $(LDFLAGS)

install:
	mkdir -p $(INSTALLDIR)/include
	cp *.h $(INSTALLDIR)/include/
	mkdir -p $(INSTALLDIR)/lib
	cp *.a $(INSTALLDIR)/lib/

clean:
	-rm $(LIB) $(OBJS) $(TEST) $(TESTOBJS) *.d 2>/dev/null

.PHONY: clean all install

