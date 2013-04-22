NAME=BackOffTrigramModelPipe

MAKESHAREDLIB=False
# MAKESHAREDLIB=True

INCDIRS=-Isrc/util/libzutil/ -Isrc/util/libzstr/ $(EXTRA_INC_DIRS)
LIBDIRS=-Lsrc/util/libzutil/ -Lsrc/util/libzstr/ $(EXTRA_LIB_DIRS)
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
SRCS=src/C/BackOffTrigramModel.c
TMPIPESRCS=src/C/BackOffTrigramModelPipe.c
OBJS=$(SRCS:%.c=%.o)
TMPIPEOBJS=$(TMPIPESRCS:%.c=%.o)

TMPIPE=bin/BackOffTrigramModelPipe
STATICLIB=src/C/$(LIBPREFIX)$(NAME)$(STATICLIBSUFFIX)
SHAREDLIB=src/C/$(LIBPREFIX)$(NAME)$(SHAREDLIBSUFFIX)


all: $(TMPIPE) 

src/util/libzutil/libzutil.a: 
	cd src/util/libzutil && make libzutil.a

src/util/libzstr/libzstr.a: src/util/libzutil/libzutil.a
	cd src/util/libzstr && make libzstr.a

staticlib: $(STATICLIB)

sharedlib: $(SHAREDLIB)

# .d auto-dependency files
ifneq ($(findstring clean,$(MAKECMDGOALS)),clean)
ifneq (,$(SRCS:%.c=%.d))
-include $(SRCS:%.c=%.d)
endif
endif

ifeq ($(PYTHON),)
PYTHON=python
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

$(TMPIPE): $(TMPIPEOBJS) $(STATICLIB) src/util/libzstr/libzstr.a
	mkdir -p bin
	$(CC) $+ -o $@ $(LDFLAGS)

test:
	PATH=$(PATH):$(PWD)/bin ; export PATH ; cd src/Python/BackOffTrigramModel && $(PYTHON) -m unittest discover

clean:
	-rm $(STATICLIB) $(SHAREDLIB) $(OBJS) $(TMPIPE) $(TMPIPEOBJS) *.d *.class 2>/dev/null

install: $(TMPIPE)
	-install $(TMPIPE) $(prefix)/bin
	-$(PYTHON) setup.py install

.PHONY: clean all staticlib sharedlib install
