CC = g++
CFLAGS = -std=c++11 -Wall
LDFLAGS = -L/path/to/libraries -llibraryname

SRCDIR = src
INCDIR = include
LIBDIR = lib

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
HEADERS = $(wildcard $(INCDIR)/*.h)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(SRCDIR)/%.o)
EXECUTABLE = rubicsCube

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -I$(INCDIR) -o $@ $^ $(LDFLAGS)

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	$(CC) $(CFLAGS) -I$(INCDIR) -c -o $@ $<

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
