Game:
	g++ ./data/source/cpp/Game.cpp -g -c
	g++ ./data/source/cpp/Vector.cpp -c -g
	g++ ./data/source/cpp/RawModel.cpp  -g -c
	g++ ./data/source/cpp/Object.cpp -c -g
	g++ ./data/source/cpp/Chara.cpp  -g -c
	g++ ./data/source/cpp/Controller.cpp  -g -c
	g++ ./data/source/cpp/Shader.cpp -g -c
	g++ ./data/source/cpp/glsl.cpp -g -c
	g++ ./data/source/cpp/Title.cpp -g -c
	g++ ./data/source/cpp/MainGame.cpp -g -c
	g++ ./data/source/cpp/Pause.cpp -g -c
	g++ ./data/source/cpp/GameSystem.cpp -g -c
	g++ ./data/source/cpp/UI_Image.cpp -g -c
	g++ ./data/source/cpp/ToolKit.cpp -g -c
	g++ ./data/source/cpp/Collider.cpp -g -c
	g++ -o Game Game.o Title.o MainGame.o Pause.o ToolKit.o GameSystem.o UI_Image.o glsl.o Shader.o Controller.o Chara.o Object.o Collider.o RawModel.o Vector.o -lSDL2 -lSDL2_image -lSDL2_mixer -lGL -lglut -lGLU -Wl,-rpath,/usr/local/lib
	rm -f ./*.o
	
	#g++ ./data/source/cpp/Audio.cpp  -g -c
	#g++ ./data/source/cpp/UI_Image.cpp  -g -c
	#g++ -o Game Game.o UI_Image.o Audio.o Controller.o Chara.o Object.o RawModel.o Vector.o -lSDL2 -lSDL2_image -lSDL2_mixer -lGL -lglut -lGLU -Wl,-rpath,/usr/local/lib

Vector:
	g++ ./data/source/cpp/Vector.cpp -o Vector
RawModel:
	g++ ./data/source/cpp/Vector.cpp -c -g
	g++ ./data/source/cpp/RawModel.cpp -c -g
	g++  Vector.o RawModel.o -o RawModel -lGL -lglut -lGLU -Wl,-rpath,/usr/local/lib
	rm -f ./*.o
