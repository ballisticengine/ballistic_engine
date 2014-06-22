CFLAGS=-Ihpp/
OUTPUT=ballistic


$(OUTPUT): main.o
	gcc $(CFLAGS) main.o -o $(OUTPUT)
	

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp -o main.o
	
clean:
	rm ./*.o
	rm ./ballistic || rm ./ballistic.exe