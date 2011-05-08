SRC_SOURCES := cerror.c cerror_codes.c libc.c
SRC_SOURCES := $(SRC_SOURCES:%=$(CURDIR)/%)

SRC_OBJECTS := $(SRC_SOURCES:.c=.o)
SRC_DEPS := $(SRC_SOURCES:.c=.d)
