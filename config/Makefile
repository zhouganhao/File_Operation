
CC=$gcc
LD=$ld
USER_INCLUDE=-I ./
USER_LIB=

OPTIMIZATION=-O2
WARNINGS=-Wall #-Werror

CFLAGS=$(USER_INCLUDE) $(OPTIMIZATION) $(WARNINGS)
LDFLAGS=$(USER_LIB) -lpthread -lm -lrt

## build lib 
HEADERS=libconfig.h
SOURCES=config.c

LIBNAME=libconfig
#LIBMAJOR?=1
#LIBMINOR?=0

LIBOBJS=$(SOURCES:.c=.o)
DYLIBNAME=$(LIBNAME).so
STLIBNAME=$(LIBNAME).a
LIBLINKER=$(CC)

lib:dynamic static test
dynamic: $(DYLIBNAME)
static: $(STLIBNAME)

# dependencs
DEPENDENCS=$(SOURCES:.c=.d)
include $(DEPENDENCS)
%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

include ../buildlib.mk

## test
CONFIG_TEST_BIN=config-test
$(CONFIG_TEST_BIN): main.c 
	$(CC) $^ -L ./ -I ./ -lconfig -o $@ $(CFLAGS) $(LDFLAGS)

test:$(CONFIG_TEST_BIN)


## install
PREFIX=../install-customer
INSTALL_BIN=$(CONFIG_TEST_BIN)
INSTALL_TOOLS=
INSTALL_DOC=
INSTALL_HEADERS=$(HEADERS)
INSTALL_DYLIBNAME=$(DYLIBNAME)
INSTALL_STLIBNAME=$(STLIBNAME)

## functions
tags:
	find . -name '*.[ch]' | xargs etags

gprof:
	$(MAKE) OPTION="-pg"

gcov:
	$(MAKE) OPTION="-fprofile-arcs -ftest-coverage"


## clean
clean:
	-rm -f $(LIBOBJS) $(STLIBNAME) $(DYLIBNAME)* $(CONFIG_TEST_BIN) 

all-clean:clean
	-rm -f $(DEPENDENCS) $(addsuffix .*, $(DEPENDENCS)) *~ TAGS 

.PHONY: all dynamic static \
		test daemon \
		tags gprof gcov	upload\
		clean all-clean

