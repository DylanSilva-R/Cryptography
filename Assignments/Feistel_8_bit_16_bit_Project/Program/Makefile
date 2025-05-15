
all: fiestel.o
	python3 Convert_To_Binary.py data/cypherTest.txt data/binary_input.txt
	./fiestel.o binary_input.txt decypherTest.txt Key d 16

fiestel.o:Main.cpp
	g++ Main.cpp -o fiestel.o