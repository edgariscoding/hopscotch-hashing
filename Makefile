SOURCES = main.cpp
INC_DIR = include

start:	main.cpp
	@mkdir -p build
	g++ -Wall -std=c++11 -o main $(SOURCES) -I$(INC_DIR)

run: main
	./main

clean:
	rm -rf main