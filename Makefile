CFLAGS=-Ihpp/ -I/usr/include/python2.7 -lSDL2 -lGL -lGLU -lGLEW -lboost_timer -lboost_filesystem -lboost_system -lboost_thread -lpython2.7 -lboost_python
OUTPUT=ballistic -lstdc++ 


$(OUTPUT): main.o sdl.o sdlControls.o singleton.o mathTypes.o \
	   renderer.o rendererGL.o texture.o world.o skybox.o \
	   texturegl.o engine.o sprite.o abstractEntity.o loaderMD2.o \
	   config.o engineState.o loaderXML.o \
	   factory.o textureFactory.o shapeFactory.o animator.o modelAnimator.o facetexShape.o \
	   python.o utlis.o \
	   entity.o objectEntity.o physicalEntity.o observerEntity.o roomEntity.o camera.o \
	   material.o materiable.o texturable.o light.o pointlight.o \
	   types.o shape2d.o boundingCube.o \
	   timer.o
	g++ $(CFLAGS) $^ -o $(OUTPUT)
	

main.o: main.cpp sdl.o
	g++ $(CFLAGS) -c $^ -o $@

config.o: cpp/config.cpp
	g++ $(CFLAGS) -c $^ -o $@


loaderMD2.o: cpp/loaderMD2.cpp
	g++ $(CFLAGS) -c $^ -o $@

loaderXML.o: cpp/loaderXML.cpp
	g++ $(CFLAGS) -c $^ -o $@

factory.o: cpp/factory.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
textureFactory.o: cpp/textureFactory.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
shapeFactory.o: cpp/shapeFactory.cpp
	g++ $(CFLAGS) -c $^ -o $@


animator.o: cpp/animator.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
modelAnimator.o: cpp/modelAnimator.cpp
	g++ $(CFLAGS) -c $^ -o $@

pointlight.o: cpp/pointlight.cpp
	g++ $(CFLAGS) -c $^ -o $@

facetexShape.o: cpp/facetexShape.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
shape2d.o: cpp/shape2d.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
sprite.o: cpp/sprite.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
engine.o: cpp/engine.cpp
	g++ $(CFLAGS) -c $^  -o $@
	
abstractEntity.o: cpp/abstractEntity.cpp
	g++ $(CFLAGS) -c $^  -o $@

skybox.o: cpp/skybox.cpp 
	g++ $(CFLAGS) -c $^  -o $@

world.o: cpp/world.cpp 
	g++ $(CFLAGS) -c $^  -o $@
	
entity.o: cpp/entity.cpp types.o
	g++ $(CFLAGS) -c $^ -o $@


objectEntity.o: cpp/objectEntity.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
physicalEntity.o: cpp/physicalEntity.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
observerEntity.o: cpp/observerEntity.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
roomEntity.o: cpp/roomEntity.cpp
	g++ $(CFLAGS) -c $^ -o $@

camera.o: cpp/camera.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
types.o: cpp/types.cpp 
	g++ $(CFLAGS) -c $^ -o $@

sdl.o: cpp/sdlio.cpp
	g++ $(CFLAGS) -c $^ -o $@

sdlControls.o: cpp/sdlControls.cpp
	g++ $(CFLAGS) -c $^ -o $@

texturegl.o: cpp/textureGL.cpp
	g++ $(CFLAGS) -c $^ -o $@

texture.o: cpp/texture.cpp
	g++ $(CFLAGS) -c $^ -o $@

renderer.o: cpp/rendererAbstract.cpp
	g++ $(CFLAGS) -c $^ -o $@

rendererGL.o: cpp/rendererGL.cpp
	g++ $(CFLAGS) -c $^ -o $@

	
singleton.o: cpp/singleton.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
engineState.o: cpp/engineState.cpp
	g++ $(CFLAGS) -c $^ -o $@

mathTypes.o: cpp/mathTypes.cpp
	g++ $(CFLAGS) -c $^ -o $@


python.o: cpp/python.cpp
	g++ $(CFLAGS) -c $^ -o $@

material.o: cpp/material.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
materiable.o: cpp/materiable.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
texturable.o: cpp/texturable.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
light.o: cpp/light.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
	
boundingCube.o: cpp/boundingCube.cpp
	g++ $(CFLAGS) -c $^ -o $@
	
utlis.o: cpp/utils.cpp
	g++ $(CFLAGS) -c $^ -o $@

timer.o: cpp/timerPosix.cpp
	g++ $(CFLAGS) -c $^ -o $@

clean:
	rm ./*.o
	