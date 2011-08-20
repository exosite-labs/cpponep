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
CURLLIB = -lcurlpp -lutilspp
EXAMPLESRC = examples/example.cpp
EXAMPLEBIN = example
ONEPLIB = $(LIBDIR)/$(ONEPLIBFILE)

all: $(EXAMPLEBIN) cleanobj	

$(EXAMPLEBIN): $(ONEPLIB)
	$(CC) $(EXAMPLESRC) $(INC) $< $(JSONLIB) $(CURLLIB)  -O2 -Wall -o $@;

$(ONEPLIB) : $(OBJECTS)
	ar crsv $(ONEPLIB) $(OBJECTS)

%.o: src/%.cpp $(HEADERS)
	$(CC) $< $(INC) $(CURLLIB) -c -o $@

.PHONY: clean

clean :
	rm $(EXAMPLEBIN) $(ONEPLIB)

cleanobj:
	rm $(OBJECTS)
