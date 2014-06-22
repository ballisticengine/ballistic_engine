CFLAGS=-Ihpp/ -lsdl
OUTPUT=ballistic


$(OUTPUT): main.o renderer.o sdlio.o
	gcc $(CFLAGS) main.o -o $(OUTPUT)
	

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp -o main.o


renderer.o: cpp/rendererAbstract.cpp
	g++ $(CFLAGS) -c cpp/rendererAbstract.cpp -o renderer.o

renderer.o: cpp/sdlio.cpp
	g++ $(CFLAGS) -c cpp/sdlio.cpp -o sdlio.o
	
clean:
	rm ./*.o
	rm ./ballistic || rm ./ballistic.exe