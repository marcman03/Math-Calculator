OPCIONS = -g -O0 -Wall -std=c++11 -Wno-deprecated -lesin
program.exe: driver_esinmath.o racional.o expressio.o variables.o math_sessio.o math_io.o token.o
	g++ -o program.exe driver_esinmath.o racional.o token.o expressio.o variables.o math_sessio.o math_io.o -lesin

driver_esinmath.o: driver_esinmath.cpp
	g++ -c driver_esinmath.cpp $(OPCIONS);

math_io.o: math_io.cpp math_io.hpp
	g++ -c math_io.cpp $(OPCIONS);

math_sessio.o: math_sessio.cpp math_sessio.hpp math_sessio.rep
	g++ -c math_sessio.cpp $(OPCIONS);

variables.o: variables.cpp variables.hpp variables.rep
	g++ -c variables.cpp $(OPCIONS);

expressio.o: expressio.cpp expressio.hpp expressio.rep
	g++ -c expressio.cpp $(OPCIONS);

token.o: token.cpp token.hpp token.rep
	g++ -c token.cpp $(OPCIONS);

racional.o: racional.cpp racional.hpp racional.rep
	g++ -c racional.cpp $(OPCIONS);

clean:
	rm *.o
	rm *.exe
	rm *.gch
