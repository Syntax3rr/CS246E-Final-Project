CXX = g++
CXXFLAGS = -std=c++14 -Werror -MMD -lncurses -g
EXEC = game
OBJECTS = main.o # add other object files here
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} ${GIVEN} -o ${EXEC} ${CXXFLAGS}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
