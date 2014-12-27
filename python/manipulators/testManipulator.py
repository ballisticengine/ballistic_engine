#import ManipulatorClass
import ctypes
import world
class testManipulator(ManipulatorClass):
    def onSelfLoad(self):
        print "World"
        models=self.world.active_room.models
        print "Current room: ",self.world.active_room.name
        print "Room models: "
        for m in models:
            print m.name,m.type



        print "test manipulator self load signal"

