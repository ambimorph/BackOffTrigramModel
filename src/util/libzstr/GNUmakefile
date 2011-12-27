NAME=zstr

INCDIRS=-I../libzutil
LIBDIRS=-L../libzutil
LIBS=-lzutil

LIBPREFIX=lib
LIBSUFFIX=.a

RANLIB=ranlib
AR=ar

DEBUGMODE=False
# DEBUGMODE=True

CFLAGS += -Wall
CPPFLAGS += $(INCDIRS)
LDFLAGS=$(LIBDIRS) $(LIBS)

ifeq ($(DEBUGMODE),True)
CPPFLAGS += -UNDEBUG
CFLAGS += -O0
CFLAGS += -g
LDFLAGS += -g
else
CPPFLAGS += -DNDEBUG
CFLAGS += -O2
endif

CFLAGS += -fPIC

# SRCS=$(wildcard *.c)
SRCS=zstr.c
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

clean:
	-rm $(LIB) $(OBJS) $(TEST) $(TESTOBJS) *.d 2>/dev/null

.PHONY: clean all
