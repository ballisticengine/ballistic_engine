CFLAGS=-Ihpp/ -lSDL -lGL -lboost_thread
OUTPUT=ballistic -lstdc++ 


$(OUTPUT): main.o sdl.o singleton.o renderer.o rendererGL.o entity.o texture.o world.o skybox.o texturegl.o engine.o sprite.o abstractEntity.o
	gcc $(CFLAGS) main.o sdl.o singleton.o renderer.o rendererGL.o types.o texture.o world.o skybox.o entity.o  engine.o sprite.o texturegl.o  abstractEntity.o -o $(OUTPUT)
	

main.o: main.cpp sdl.o
	g++ $(CFLAGS) -c main.cpp -o main.o


engine.o: cpp/engine.cpp
	g++ $(CFLAGS) -c cpp/engine.cpp  -o engine.o
	
abstractEntity.o: cpp/abstractEntity.cpp
	g++ $(CFLAGS) -c cpp/abstractEntity.cpp  -o abstractEntity.o

sprite.o: cpp/sprite.cpp
	g++ $(CFLAGS) -c cpp/sprite.cpp  -o sprite.o

skybox.o: cpp/skybox.cpp 
	g++ $(CFLAGS) -c cpp/skybox.cpp  -o skybox.o

world.o: cpp/world.cpp 
	g++ $(CFLAGS) -c cpp/world.cpp  -o world.o
	
entity.o: cpp/entity.cpp types.o
	g++ $(CFLAGS) -c cpp/entity.cpp types.o -o entity.o


types.o: cpp/types.cpp 
	g++ $(CFLAGS) -c cpp/types.cpp -o types.o

sdl.o: cpp/sdlio.cpp
	g++ $(CFLAGS) -c cpp/sdlio.cpp -o sdl.o

texturegl.o: cpp/textureGL.cpp
	g++ $(CFLAGS) -c cpp/textureGL.cpp -o texturegl.o

texture.o: cpp/texture.cpp
	g++ $(CFLAGS) -c cpp/texture.cpp -o texture.o

renderer.o: cpp/rendererAbstract.cpp
	g++ $(CFLAGS) -c cpp/rendererAbstract.cpp -o renderer.o

rendererGL.o: cpp/rendererGL.cpp
	g++ $(CFLAGS) -c cpp/rendererGL.cpp -o rendererGL.o

	
singleton.o: cpp/singleton.cpp
	g++ $(CFLAGS) -c cpp/singleton.cpp -o singleton.o
	

clean:
	rm ./*.o
	