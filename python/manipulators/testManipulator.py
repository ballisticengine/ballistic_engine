#import ManipulatorClass
import ctypes
import world
class testManipulator(ManipulatorClass):
    def onSelfLoad(self):
        print "World"
        models=self.world.getModels()
        for m in models:
            print "x: ",m.getCoords().x
            #m.locate(100,0,0)
            #print m.getCoords()
        #    pass


        print "test manipulator self load signal"