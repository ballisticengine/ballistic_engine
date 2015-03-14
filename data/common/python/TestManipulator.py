class TestManipulator(manipulatorClass):
    def onMouseMove(self,deltax, deltay):
        print "mouse move", deltax, deltay
        self.world.observer.rotate(deltay/2, deltax/2, 0)




