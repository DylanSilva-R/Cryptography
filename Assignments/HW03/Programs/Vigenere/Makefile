


all: VigenereExe.o
	./VigenereExe.o ./plain1.txt Key ./cypher2.txt d

VigenereExe.o: Vigenere.cpp
	g++ ./Vigenere.cpp -o VigenereExe.o

clean:
	rm VigenereExe.o

