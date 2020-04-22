CC=g++
CFLAGS=-c  -O2 -std=c++11
LDFLAGS=
SOURCES= main.cpp database.cpp menu.cpp post.cpp member.cpp list.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE= assn2

detected_OS := $(patsubst MSYS%,MSYS,$(detected_OS))
detected_OS := $(patsubst MINGW%,MSYS,$(detected_OS))

ifeq ($(detected_OS), MSYS)
	EXECUTABLE= assn2.exe
endif

all: $(SOURCES) $(EXECUTABLE) clean

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -f $(OBJECTS)