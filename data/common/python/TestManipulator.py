import math

class TestManipulator(manipulatorClass):
    def onMouseMove(self,deltax, deltay):
        print "mouse move", deltax, deltay
        self.world.observer.rotate(deltay/2, deltax/2, 0)


    def onKeyDown(self,states):
        self.world.observer.velocity.reset()
        ocoords=self.world.observer.getCoords()
        step=5
        xdelta=deg2rad(ocoords.rotation.y)
        ydelta=deg2rad(ocoords.rotation.x)

        if states[26]:
            print 'forward'
            self.world.observer.velocity.t.x+=-math.sin(xdelta)*step
            self.world.observer.velocity.t.z+=math.cos(xdelta)*step

        if states[22]:
            print "backward"

        if states[4]:
            print 'left'

        if states[7]:
            print 'right'

         #print "States: ",states[26]