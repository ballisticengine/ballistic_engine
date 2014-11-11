#import ManipulatorClass
import ctypes
import world
class testManipulator(ManipulatorClass):
    def onSelfLoad(self):
        wi=world.world.getInstance().getModels()
        print dir(wi)
        for w in wi:
            ##w.getCoords()
            pass


        print "test manipulator self load signal"