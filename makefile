OBJ=elementArbre.o arbre.o encodage.o modele.o arg.o translation.o showVector.o EM.o
HEADER=elementArbre.h arbre.h encodage.h modele.h arg.h translation.h EM.h showVector.h

all: main.exe tokeniseur.exe perplex.exe translator.exe codetomot.exe
	rm -f *.o

################################ Executable #####################################

main.exe: $(OBJ) main.o
	g++ -Wall $(OBJ) main.o -o main.exe

tokeniseur.exe: tokeniseur.o $(OBJ)
	g++ -Wall tokeniseur.o $(OBJ) -o tokeniseur.exe

perplex.exe: perplex.o $(OBJ)
	g++ -Wall perplex.o $(OBJ) -o perplex.exe

translator.exe: translator.o $(OBJ)
	g++ -Wall translator.o $(OBJ) -o translator.exe

##################################################################################

tokeniseur.o: tokeniseur.cpp $(HEADER)
	g++ -Wall -c tokeniseur.cpp -o tokeniseur.o

perplex.o: perplex.cpp $(HEADER)
	g++ -Wall -c perplex.cpp -o perplex.o
	
translator.o: translator.cpp $(HEADER)
	g++ -Wall -c translator.cpp -o translator.o

main.o: main.cpp $(HEADER)
	g++ -std=c++11 -Wall -c main.cpp -o main.o

##################################################################################

Arbre: arbre.cpp arbre.h elementArbre.h encodage.h
	g++ -Wall -c arbre.cpp -o arbre.o

elementArbre.o: elementArbre.cpp elementArbre.h
	g++ -Wall -c elementArbre.cpp -o elementArbre.o

encodage.o: encodage.cpp encodage.h
	g++ -Wall -c encodage.cpp -o encodage.o

modele.o: modele.h modele.cpp showVector.h
	g++ -std=c++11 -Wall -c modele.cpp -o modele.o
	
arg.o: arg.h arg.cpp
	g++ -std=c++11 -Wall -c arg.cpp -o arg.o

translation.o: translation.cpp translation.h arbre.h modele.h showVector.h
	g++ -std=c++11 -Wall -c translation.cpp -o translation.o

showVector.o: showVector.cpp showVector.h
	g++ -std=c++11 -Wall -c showVector.cpp -o showVector.o

EM.o: EM.cpp EM.h
	g++ -Wall -c EM.cpp -o EM.o

codetomot.exe: codetomot.c
	g++ -Wall -o codetomot.exe codetomot.c

clean:
	rm -f *.o *~ *.exe
