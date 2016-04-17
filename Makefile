PROJECT:=libcommand.a
SOURCES:=$(shell find . -name "*.c")
OBJECTS:=$(SOURCES:.c=.o)

CFLAGS:= -I./include
LDFLAGS:=
PREFIX:=/usr/local

.PHONY: install all clean

all: $(PROJECT)

clean:
	rm -f $(OBJECTS) $(PROJECT)

install:
	install -d $(PREFIX)/include/command
	install ./include/*.h $(PREFIX)/include/command/
	install $(PROJECT) $(PREFIX)/lib/

$(PROJECT): $(OBJECTS)
	ar rcs $(PROJECT) $(OBJECTS)