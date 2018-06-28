Game:
	g++ ./data/source/cpp/Game.cpp -lSDL2 -lGL -lglut -lGLU -Wl,-rpath,/usr/local/lib -g -o Game
Vector:
	g++ ./data/source/cpp/Vector.cpp -o Vector
