#Makefile template from http://mrbook.org/tutorials/make
#Uses sources and executable variables to build a binary
#first by building objects when they need updating
#then by linking them togethr

CC=g++
CFLAGS=-c
LDFLAGS=
SOURCES=main.cpp f.cpp g.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=FUNEX

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@


