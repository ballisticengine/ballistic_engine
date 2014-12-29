CFLAGS=-Ihpp/ -I/usr/include/python2.7 -lSDL2 -lGL -lGLU -lGLEW -lboost_timer -lboost_filesystem -lboost_system -lboost_thread -lpython2.7 -lboost_python
OUTPUT=ballistic -lstdc++ 


$(OUTPUT): main.o sdl.o sdlControls.o singleton.o mathTypes.o \
	   renderer.o rendererGL.o texture.o world.o skybox.o \
	   engine.o sprite.o loaderMD2.o \
	   config.o engineState.o loaderXML.o \
	   factory.o textureFactory.o shapeFactory.o animator.o modelAnimator.o facetexShape.o \
	   python.o utlis.o \
	   entity.o objectEntity.o physicalEntity.o observerEntity.o roomEntity.o camera.o \
	   material.o materiable.o texturable.o light.o pointlight.o \
	   types.o shape2d.o boundingCube.o \
	   timer.o
	g++ $(CFLAGS) $^ -o $(OUTPUT)
	

modelview: tools/modelviewer/modelview.cpp
	g++ $(CFLAGS) $^ -o modelviewer

main.o: main.cpp sdl.o
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

facetexShape.o: cpp/types/facetexShape.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
shape2d.o: cpp/types/shape2d.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
sprite.o: cpp/entities/sprite.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
engine.o: cpp/engine.cpp
	g++ $(CFLAGS) -c $^  -o $@
	


skybox.o: cpp/types/skybox.cpp 
	g++ $(CFLAGS) -c $^  -o $@

world.o: cpp/entities/world.cpp 
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

sdlControls.o: cpp/io/sdlControls.cpp
	g++ $(CFLAGS) -c $^ -o $@


texture.o: cpp/types/texture.cpp
	g++ $(CFLAGS) -c $^ -o $@

renderer.o: cpp/renderer/rendererAbstract.cpp
	g++ $(CFLAGS) -c $^ -o $@

rendererGL.o: cpp/renderer/GL/rendererGL.cpp
	g++ $(CFLAGS) -c $^ -o $@

	
singleton.o: cpp/misc/singleton.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
engineState.o: cpp/config/engineState.cpp
	g++ $(CFLAGS) -c $^ -o $@

mathTypes.o: cpp/types/mathTypes.cpp
	g++ $(CFLAGS) -c $^ -o $@


python.o: cpp/python/python.cpp
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

clean:
	rm ./*.o
	