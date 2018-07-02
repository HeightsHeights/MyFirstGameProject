Game:
	#g++ ./data/source/cpp/Game.cpp -lSDL2 -lGL -lglut -lGLU -Wl,-rpath,/usr/local/lib -g -o Game
	g++ ./data/source/cpp/Game.cpp -lSDL2 -lGL -lglut -lGLU -Wl,-rpath,/usr/local/lib -g -c
	g++ ./data/source/cpp/RawModel.cpp -lSDL2 -lGL -lglut -lGLU -Wl,-rpath,/usr/local/lib -g -c
	g++ -o  RawModel.o Game.o -lSDL2 -lGL -lglut -lGLU -Wl,-rpath,/usr/local/lib
	rm -f ./*.o
Vector:
	g++ ./data/source/cpp/Vector.cpp -o Vector
