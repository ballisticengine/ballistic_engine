CFLAGS=-Ihpp/ -lSDL -lGL
OUTPUT=ballistic -lstdc++


$(OUTPUT): main.o sdl.o singleton.o renderer.o rendererGL.o
	gcc $(CFLAGS) main.o sdl.o singleton.o renderer.o rendererGL.o -o $(OUTPUT)
	

main.o: main.cpp sdl.o
	g++ $(CFLAGS) -c main.cpp -o main.o


sdl.o: cpp/sdlio.cpp
	g++ $(CFLAGS) -c cpp/sdlio.cpp -o sdl.o


renderer.o: cpp/rendererAbstract.cpp
	g++ $(CFLAGS) -c cpp/rendererAbstract.cpp -o renderer.o

rendererGL.o: cpp/rendererGL.cpp
	g++ $(CFLAGS) -c cpp/rendererGL.cpp -o rendererGL.o

	
singleton.o: cpp/singleton.cpp
	g++ $(CFLAGS) -c cpp/singleton.cpp -o singleton.o
	

clean:
	rm ./*.o
	