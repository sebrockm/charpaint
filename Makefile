CC = g++-5
FLAGS = -Wall -std=c++14 -O3
LIB = -ljpeg -lpng
HH = ImageData.hpp CharacterMap.hpp

default: test.cpp $(HH)
	$(CC) test.cpp $(FLAGS) $(LIB) -o test

test: default
	./test characters.png characters.txt

clean:
	rm -f test *.jpg
