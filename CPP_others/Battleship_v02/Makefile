output: main.o
	g++ -static -std=c++2a -static-libgcc -static-libstdc++ -lpthread -o "battlefield.exe" battlefield.o print.o ccolor.o

main.o: main.cpp
	g++ -Wall -c main.cpp print.cpp ccolor.cpp main.o print.o ccolor.o
