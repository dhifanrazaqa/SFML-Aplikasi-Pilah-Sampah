all: compile link
32: compile link32

compile:
	C:/MinGW/bin/g++.exe -c src/main.cpp -Isrc/include
	C:/MinGW/bin/g++.exe -c src/Game/*.cpp -Isrc/include
	mv ./*.o ./bin/out || move ./*.o ./bin/out

link:
	g++ bin/out/*.o -o bin/64/main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

link32:
	g++ bin/out/*.o -o bin/32/main -Lsrc/lib/32-bit -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio