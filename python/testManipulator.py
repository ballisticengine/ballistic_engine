import ManipulatorClass
import ctypes
import world
class testManipulator(ManipulatorClass):
    def __init__(self):
        self.ccount=0

    def onSelfLoad(self):
        print "World"
        models=self.world.active_room.models
        print "Current room: ",self.world.active_room.name
        print "Room models: "
        for m in models:
            print m.name,m.type



        print "test manipulator self load signal"

    def onEntityCollision(self,entitya,entityb,cvec):
        #print "Ecollision",self.ccount
        #self.ccount+=1
        #return
        print entitya.name,"to",entityb.name
        entityb.velocity.t.x=-entitya.velocity.t.x
        entityb.velocity.t.y=-entitya.velocity.t.y
        entityb.velocity.t.z=-entitya.velocity.t.z

    def onLevelCollision(self,entity,room):
        print "level collision"