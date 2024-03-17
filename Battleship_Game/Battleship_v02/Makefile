#in Windows use MingW32-make command if make doesn't work

output: main.o
	g++ -static -std=c++2a -static-libgcc -static-libstdc++ -lpthread -o "battlefield.exe" main.o print.o ccolor.o

main.o: main.cpp
	g++ -Wall -c main.cpp print.cpp ccolor.cpp main.o print.o ccolor.o
