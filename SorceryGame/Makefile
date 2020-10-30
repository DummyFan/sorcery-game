CXX=g++
CXXFLAGS=-std=c++14 -Wall -MMD
EXEC=sorcery
OBJECTS=main.o board.o player.o card.o minion.o spell.o trigger.o ritual.o enchantment.o ability.o
DEPENDS=${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

