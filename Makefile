CFLAGS=-Ihpp/ -I/usr/include/python2.7 -I/usr/include/bullet -I/usr/include/SDL2 -lstdc++  -lSDL2 -lSDL2_ttf -lSDL2_image -lGL -lGLU -lGLEW -lBulletCollision \
-lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath \
-lboost_timer -lboost_filesystem -lboost_system -lpthread -lboost_thread -lpython2.7 -lboost_python -ldl
OUTPUT=ballistic 


deps=sdl.o singleton.o mathTypes.o lightormaterial.o \
	sdl2d.o texture.o world.o worldLoad.o skybox.o \
	   engine.o sprite.o loaderMD2.o texLoader.o \
	   config.o engineState.o loaderXML.o PreloadStore.o \
	   factory.o textureFactory.o shapeFactory.o animator.o modelAnimator.o \
	   world_defs.o hud_defs.o pylocker.o manipulator.o pyscripting.o \
	   utlis.o entity.o objectEntity.o physicalEntity.o observerEntity.o roomEntity.o camera.o \
	   material.o materiable.o texturable.o light.o pointlight.o \
	   types.o shape2d.o shape.o boundingCube.o \
	   timerdefs.o LibLoad.o collision.o \
	   timer.o image.o hud.o uimesh.o weapon.o rendererGL.so plane.o


$(OUTPUT): $(deps) main.o 
	g++ -rdynamic  $^ -o $(OUTPUT) $(CFLAGS)


test.o: cpp/test/test.cpp
	g++ $(CFLAGS) -c $^ -o $@

test: $(deps) test.o
	g++ -rdynamic  $^ -o test $(CFLAGS) -lgtest -lgtest_main 
	./test

clean_test:
	rm ./test.o
	rm ./test

rendererGL.o: cpp/renderer/GL/rendererGL.cpp 
	g++  -Ihpp/ -I/usr/include/bullet -I/usr/include/python2.7 -I/usr/include/SDL2 -c  -fPIC  $^ -o $@ 

renderer.o: cpp/renderer/rendererAbstract.cpp
	g++  -Ihpp/ -I/usr/include/bullet -I/usr/include/python2.7 -I/usr/include/SDL2 -c -fPIC  $^ -o $@ 

rendererGL.so: rendererGL.o renderer.o
	g++ $^ -shared -Wl,-soname,rendererGL.so -o rendererGL.so -lGL -lGLU -lGLEW   

LibLoad.o: cpp/libload/LibLoad.cpp
	g++ $(CFLAGS) -c $^ -o $@

timerdefs.o: cpp/python/timer_defs.cpp
	g++ $(CFLAGS) -c $^ -o $@

collision.o: cpp/world/collisionDetector.cpp
	g++ $(CFLAGS)  -c $^ -o $@

weapon.o: cpp/entities/weapon.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
PreloadStore.o: cpp/world/PreloadStore.cpp
	g++ $(CFLAGS) -c $^ -o $@

texLoader.o: cpp/loaders/texLoader.cpp
	g++ $(CFLAGS) -c $^ -o $@

lightormaterial.o: cpp/types/lightOrMaterial.cpp
	g++ $(CFLAGS) -c $^ -o $@

shape.o: cpp/types/shape.cpp
	g++ $(CFLAGS) -c $^ -o $@

sdl2d.o: cpp/io/ttf.cpp
	g++ $(CFLAGS) -c $^ -o $@

uimesh.o: cpp/ui/uiMesh.cpp
	g++ $(CFLAGS) -c $^ -o $@

pylocker.o: cpp/python/locker.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
manipulator.o: cpp/python/manipulator.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
pyscripting.o: cpp/python/scripting.cpp
	g++ $(CFLAGS) -c $^ -o $@

hud_defs.o: cpp/python/hud_defs.cpp
	g++ $(CFLAGS) -c $^ -o $@

world_defs.o: cpp/python/world_defs.cpp
	g++ $(CFLAGS) -c $^ -o $@



main.o: main.cpp 
	g++ $(CFLAGS) -c $^ -o $@

image.o: cpp/ui/image.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
hud.o: cpp/ui/hud.cpp
	g++ $(CFLAGS) -c $^ -o $@

config.o: cpp/config/config.cpp
	g++ $(CFLAGS) -c $^ -o $@


loaderMD2.o: cpp/loaders/loaderMD2.cpp
	g++ $(CFLAGS) -c $^ -o $@

loaderXML.o: cpp/loaders/loaderXML.cpp
	g++ $(CFLAGS) -c $^ -o $@

factory.o: cpp/factories/factory.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
textureFactory.o: cpp/factories/textureFactory.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
shapeFactory.o: cpp/factories/shapeFactory.cpp
	g++ $(CFLAGS) -c $^ -o $@


animator.o: cpp/anim/animator.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
modelAnimator.o: cpp/anim/modelAnimator.cpp
	g++ $(CFLAGS) -c $^ -o $@

pointlight.o: cpp/entities/pointlight.cpp
	g++ $(CFLAGS) -c $^ -o $@


	
shape2d.o: cpp/types/shape2d.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
sprite.o: cpp/entities/sprite.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
engine.o: cpp/engine.cpp
	g++ $(CFLAGS) -c $^  -o $@
	


skybox.o: cpp/types/skybox.cpp 
	g++ $(CFLAGS) -c $^  -o $@

world.o: cpp/world/world.cpp 
	g++ $(CFLAGS) -c $^  -o $@
	
worldLoad.o: cpp/world/worldLoad.cpp
	g++ $(CFLAGS) -c $^  -o $@
	
entity.o: cpp/entities/entity.cpp types.o
	g++ $(CFLAGS) -c $^ -o $@


objectEntity.o: cpp/entities/objectEntity.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
physicalEntity.o: cpp/entities/physicalEntity.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
observerEntity.o: cpp/entities/observerEntity.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
roomEntity.o: cpp/entities/roomEntity.cpp
	g++ $(CFLAGS) -c $^ -o $@

camera.o: cpp/entities/camera.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
types.o: cpp/types/types.cpp 
	g++ $(CFLAGS) -c $^ -o $@

sdl.o: cpp/io/sdlio.cpp
	g++ $(CFLAGS) -c $^ -o $@

texture.o: cpp/types/texture.cpp
	g++ $(CFLAGS) -c $^ -o $@

singleton.o: cpp/misc/singleton.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
engineState.o: cpp/config/engineState.cpp
	g++ $(CFLAGS) -c $^ -o $@

mathTypes.o: cpp/types/mathTypes.cpp
	g++ $(CFLAGS) -c $^ -o $@



material.o: cpp/types/material.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
materiable.o: cpp/entities/materiable.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
texturable.o: cpp/entities/texturable.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
light.o: cpp/entities/light.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
	
boundingCube.o: cpp/types/boundingCube.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
utlis.o: cpp/misc/utils.cpp
	g++ $(CFLAGS) -c $^ -o $@

timer.o: cpp/time/timerPosix.cpp
	g++ $(CFLAGS) -c $^ -o $@
	

	
octree.o: cpp/world/Octree.cpp

plane.o: cpp/types/plane.cpp

	g++ $(CFLAGS) -c $^ -o $@

clean:
	rm ./*.so
	rm ./*.o 
	rm ./$(OUTPUT)
	
	
clean_libs:
	rm ./renderer.o
	rm ./rendererGL.so
	rm ./*.so