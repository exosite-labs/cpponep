CC = g++
SRCDIR = src
INCDIR = include
LIBDIR = lib
JSONLIBFILE = libjson.a
ONEPLIBFILE = libcpponep.a
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
HEADERS = $(wildcard $(INCDIR)/*.h)
SRCFILES = $(notdir $(SOURCES))
OBJECTS = $(patsubst %.cpp,%.o,$(SRCFILES) )

INC = -I$(INCDIR)
JSONLIB = $(LIBDIR)/$(JSONLIBFILE)
CURLLIB = -lcurlpp -lutilspp -lcurl
EXAMPLESRC = examples/example.cpp
EXAMPLEBIN = example
PEXAMPLESRC = examples/ProvisionExample.cpp
PEXAMPLEBIN = ProvisionExample
ONEPLIB = $(LIBDIR)/$(ONEPLIBFILE)

all: $(EXAMPLEBIN) $(PEXAMPLEBIN) cleanobj	

$(EXAMPLEBIN): $(ONEPLIB)
	$(CC) -std=c++11 $(EXAMPLESRC) $(INC) $< $(CURLLIB) -O2 -Wall -o $@;

$(PEXAMPLEBIN): $(ONEPLIB)
	$(CC) -std=c++11 $(PEXAMPLESRC) $(INC) $< $(CURLLIB) -O2 -Wall -o $@;

$(ONEPLIB) : $(OBJECTS)
	ar crsv $(ONEPLIB) $(OBJECTS)

%.o: src/%.cpp $(HEADERS)
	$(CC) -std=c++11 $< $(INC) $(CURLLIB) -c -o $@

.PHONY: clean

clean :
	rm $(EXAMPLEBIN) $(PEXAMPLEBIN) $(ONEPLIB)

cleanobj:
	rm $(OBJECTS)
