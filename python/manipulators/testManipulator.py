#import ManipulatorClass
import ctypes
import world
class testManipulator(ManipulatorClass):
    def onSelfLoad(self):
        wi=world.world.getInstance().getLights()
        print dir(wi)
        for w in wi:
            w.getCoords()


        print "test manipulator self load signal"