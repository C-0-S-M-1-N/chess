all: compile

compile: main.cpp
	g++ main.cpp -o main -O2 -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -std=c++20
