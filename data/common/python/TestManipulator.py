import math
from World import Coords

class TestManipulator(manipulatorClass):
    def onMouseMove(self, deltax, deltay):
        self.world.observer.rotate(deltay, deltax, 0)


    def onKeyUp(self, states):
        self.world.observer.velocity.reset()

    def onKeyDown(self, states):
        ocoords = self.world.observer.getCoords()
        step=5
        xdelta = deg2rad(ocoords.rotation.y)
        ydelta = deg2rad(ocoords.rotation.x)

        velocity=Coords()

        if states[26]:
            velocity.t.x += -math.sin(xdelta)*step
            velocity.t.z += math.cos(xdelta)*step
            velocity.t.y += math.sin(ydelta)*step
        if states[22]:
            velocity.t.x +=math.sin(xdelta)*step
            velocity.t.z +=-math.cos(xdelta)*step
        if states[4]:
            velocity.t.x+=math.cos(xdelta)*step
            velocity.t.z+=math.sin(xdelta)*step
        if states[7]:
            velocity.t.x+=-math.cos(xdelta)*step
            velocity.t.z+=-math.sin(xdelta)*step

        self.world.observer.velocity=velocity
