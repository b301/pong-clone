all: main game player ball compile

main:
	g++ -std=c++17 -I Source/src/include -c Source/main.cpp -o main.o

game:
	g++ -std=c++17 -I Source/src/include -c Source/Game.cpp -o Game.o

player:
	g++ -std=c++17 -I Source/src/include -c Source/Player.cpp -o Player.o

ball:
	g++ -std=c++17 -I Source/src/include -c Source/Ball.cpp -o Ball.o

compile:
	g++ -std=c++17 main.o Game.o Player.o Ball.o -L Source/src/lib -l sfml-window -l sfml-system -l sfml-graphics -l sfml-audio -o Pong.exe -mwindows

# Refrain from using the -mwindows in the compile line if you want to debug!