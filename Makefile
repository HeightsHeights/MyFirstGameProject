Game:
	g++ ./data/source/cpp/Game.cpp -g -c
	g++ ./data/source/cpp/Vector.cpp -c -g
	g++ ./data/source/cpp/RawModel.cpp  -g -c
	g++ -o Game Game.o RawModel.o Vector.o -lSDL2 -lGL -lglut -lGLU -Wl,-rpath,/usr/local/lib
	rm -f ./*.o

Vector:
	g++ ./data/source/cpp/Vector.cpp -o Vector
RawModel:
	g++ ./data/source/cpp/Vector.cpp -c -g
	g++ ./data/source/cpp/RawModel.cpp -c -g
	g++  Vector.o RawModel.o -o RawModel
	rm -f ./*.o
