all: compile link

compile:
	C:/MinGW/bin/g++.exe -c src/main.cpp -Isrc/include
	C:/MinGW/bin/g++.exe -c src/Game/*.cpp -Isrc/include
	move ./*.o ./bin/out

link:
	g++ bin/out/*.o -o bin/main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
