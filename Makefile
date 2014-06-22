CFLAGS=-Ihpp/ -lSDL
OUTPUT=ballistic -lstdc++


$(OUTPUT): main.o sdl.o singleton.o renderer.o
	gcc $(CFLAGS) main.o sdl.o singleton.o renderer.o -o $(OUTPUT)
	

main.o: main.cpp sdl.o
	g++ $(CFLAGS) -c main.cpp -o main.o


sdl.o: cpp/sdlio.cpp
	g++ $(CFLAGS) -c cpp/sdlio.cpp -o sdl.o


renderer.o: cpp/rendererAbstract.cpp
	g++ $(CFLAGS) -c cpp/rendererAbstract.cpp -o renderer.o


	
singleton.o: cpp/singleton.cpp
	g++ $(CFLAGS) -c cpp/singleton.cpp -o singleton.o
	

clean:
	rm ./*.o
	