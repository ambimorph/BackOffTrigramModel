NAME=BackOffTrigramModelPipe

MAKESHAREDLIB=False
# MAKESHAREDLIB=True


INCDIRS=-I../util/libzutil/ -I../util/libzstr/ $(EXTRA_INC_DIRS)
LIBDIRS=-L../util/libzutil/ -L../util/libzstr/ $(EXTRA_LIB_DIRS)
LIBS=-lzstr -lzutil -lJudy -lm

LIBPREFIX=lib
STATICLIBSUFFIX=.a
SHAREDLIBSUFFIX=.so

RANLIB=ranlib
AR=ar

DEBUGMODE=True
# DEBUGMODE=False

ifeq ($(DEBUGMODE),True)
CFLAGS=-Wall -O0 -Werror
CFLAGS += -g
LDFLAGS += -g
else
CFLAGS=-Wall -O2
endif

CFLAGS += -fPIC -std=c99

CFLAGS += $(INCDIRS)
LDFLAGS += $(LIBDIRS) $(LIBS)

# SRCS=$(wildcard *.c)
SRCS=BackOffTrigramModel.c
TMPIPESRCS=BackOffTrigramModelPipe.c
OBJS=$(SRCS:%.c=%.o)
TMPIPEOBJS=$(TMPIPESRCS:%.c=%.o)

TMPIPE=BackOffTrigramModelPipe
STATICLIB=$(LIBPREFIX)$(NAME)$(STATICLIBSUFFIX)
SHAREDLIB=$(LIBPREFIX)$(NAME)$(SHAREDLIBSUFFIX)


all: $(TMPIPE) 

../util/libzutil/libzutil.a: 
	cd ../util/libzutil && make libzutil.a

../util/libzstr/libzstr.a: ../util/libzutil/libzutil.a
	cd ../util/libzstr && make libzstr.a

staticlib: $(STATICLIB)

sharedlib: $(SHAREDLIB)

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

$(STATICLIB): $(OBJS)
	$(AR) -r $@ $+
	$(RANLIB) $@

$(SHAREDLIB): $(OBJS)
	$(CC) -o $@ $+ -shared -fPIC

$(TMPIPE): $(TMPIPEOBJS) $(STATICLIB) ../util/libzstr/libzstr.a
	$(CC) $+ -o $@ $(LDFLAGS)

test:
	cd ../Python && python -m unittest discover

clean:
	-rm $(STATICLIB) $(SHAREDLIB) $(OBJS) $(TMPIPE) $(TMPIPEOBJS) *.d *.class 2>/dev/null

.PHONY: clean all staticlib sharedlib 
