# function    : build dynamic and static lib
# dependences : LIBOBJS DYLIBNAME STLIBNAME LIBMAJOR LIBMINOR 
#		        LIBLINKER CFLAGS


ifdef DYLIBNAME

$(LIBOBJS):CFLAGS+=-fPIC -fvisibility=hidden
LIBLINKER?=$(CC)

DYLIBNAME_VERSIONED:=$(DYLIBNAME)
ifdef LIBMAJOR
DYLIBNAME_VERSIONED:=$(DYLIBNAME).$(LIBMAJOR)
ifdef LIBMINOR
DYLIBNAME_VERSIONED:=$(DYLIBNAME).$(LIBMAJOR).$(LIBMINOR)
endif
endif

$(DYLIBNAME):$(LIBOBJS)
	$(LIBLINKER) $^ -o $(DYLIBNAME) $(LDFLAGS) -shared -Wl,-soname,$(DYLIBNAME)
	[ "$(DYLIBNAME)" = "$(DYLIBNAME_VERSIONED)" ] || cp -sf $(DYLIBNAME) $(DYLIBNAME_VERSIONED)

endif


ifdef STLIBNAME

$(STLIBNAME):$(LIBOBJS)
	ar rcs $@ $^

endif

