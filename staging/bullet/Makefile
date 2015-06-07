CFLAGS=-I/usr/include/bullet -lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath

bullettest: bullet.o
	g++  $^ -o bulltettest $(CFLAGS)
	
bullet.o: bullet.cpp
	g++   $(CFLAGS) -c $^ -o $@
	
clean:
	rm ./*o
	rm ./bulltettest