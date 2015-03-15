import math

class TestManipulator(manipulatorClass):
    def onMouseMove(self,deltax, deltay):
        self.world.observer.rotate(deltay/2, deltax/2, 0)


    def onKeyUp(self,key):
        self.world.observer.velocity.reset()

    def onKeyDown(self,key):
        self.world.observer.velocity.reset()
        ocoords=self.world.observer.getCoords()
        step=10
        xdelta=deg2rad(ocoords.rotation.y)
        ydelta=deg2rad(ocoords.rotation.x)

        if key==26:
            self.world.observer.velocity.t.x+=-math.sin(xdelta)*step
            self.world.observer.velocity.t.z+=math.cos(xdelta)*step

        if key==22:
            print "backward"

        if key==4:
            pass

        if key==7:
            print 'right'


        #print "States: ",states[26]