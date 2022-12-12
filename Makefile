#Makefile to build the program from src, storing object and dependency files in /build
CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g
LDFLAGS = -lncurses
EXEC = a.out 

SRCDIR = src
BUILDDIR = build

SOURCES := $(shell find $(SRCDIR) -name '*.cc')
OBJECTS := $(patsubst $(SRCDIR)/%.cc, $(BUILDDIR)/%.o, $(SOURCES))
DEPENDS = ${OBJECTS:%.o=%.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} ${GIVEN} -o ${EXEC} ${LDFLAGS}

-include $(OBJECTS:%.o=%.d)

${BUILDDIR}/%.o: ${SRCDIR}/%.cc
	@mkdir -p $(dir $@)
	${CXX} ${CXXFLAGS} -c $< -o $@
	
.PHONY: clean

clean:
	rm -rf ${BUILDDIR} ${EXEC}
