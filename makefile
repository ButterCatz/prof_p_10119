# make all
run: all
	./10119

all: main.cpp
	g++ -o 10119 main.cpp

clean:
	rm 10119